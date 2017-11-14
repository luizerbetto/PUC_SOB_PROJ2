/*
 *  linux/fs/minix/file.c
 *
 *  Copyright (C) 1991, 1992 Linus Torvalds
 *
 *  minix regular file handling primitives
 */

#include "minix.h"
#include <linux/crypto.h>
#include <crypto/aes.h>
#include <linux/string.h>
#include <linux/uio.h>
#include<linux/string.h>

/*
 * We have mostly NULLs here: the current defaults are OK for
 * the minix filesystem.
 */
const struct file_operations minix_file_operations = {
        .llseek		= generic_file_llseek,
        .read		= do_sync_read,
        .aio_read	= minix_file_aio_read,      /*Linha modificada */
        .write		= do_sync_write,
        .aio_write	= minix_file_aio_write, /*Linha modificada */
        .mmap		= generic_file_mmap,
        .fsync		= generic_file_fsync,
        .splice_read	= generic_file_splice_read,
};

void minix_print_iovec(struct iovec *data)
{
    u32 i;
    char *tempData = data->iov_base;
    for(i = 0; i < data->iov_len; i++){
        pr_info("%d) %c", i, tempData[i]);
    }
}

void minix_crypt(const struct iovec *in, struct iovec *out, u32 size, u8 *key1, u8 keySize, u8 type)
{
    // Estrutura usada para cifrar e decifrar.
    struct crypto_cipher *tfm;
    // Variáveis auxiliares.
    void *inData, *outData;
    int i, count, div, modd;

    pr_info("minix_crypt: Size of data in->iov_len: %d", in->iov_len);
    div = size / AES_BLOCK_SIZE;
    modd = size % AES_BLOCK_SIZE;
    pr_info("minix_crypt: Number of AES blocks: %d - Module: %d", div, modd);

    // Verifica se é múltiplo de 16.
    if(modd > 0){
        pr_err("minix_crypt: o tamanho do vetor não é múltiplo de 16");
        return;
    }
    count = div;

    // inicializa estrutura tfm que será usada para cifrar/decifrar.
    tfm = crypto_alloc_cipher("aes", 4, CRYPTO_ALG_ASYNC);
    crypto_cipher_setkey(tfm, key1, keySize);

    inData = in->iov_base;
    outData = out->iov_base;
    for(i = 0; i < count; i++){
        if(type == 0){
            // cifrar
            crypto_cipher_encrypt_one(tfm, outData, inData);
        }else{
            // decifrar
            crypto_cipher_decrypt_one(tfm, outData, inData);
        }
        // atualiza endereços. O processo de cifra/decifra é feito 
        // de 16 em 16 bytes. O valor é representado pela variável
        // AES_BLOCK_SIZE
        inData = inData + AES_BLOCK_SIZE;
        outData = outData + AES_BLOCK_SIZE;
    }
    // desaloca estrutura.
    crypto_free_cipher(tfm);
}

ssize_t minix_file_aio_read(struct kiocb *iocb, const struct iovec *iov,
        unsigned long nr_segs, loff_t pos)
{
// Variável que representa o número de bytes lidos.
    ssize_t ret;
    struct iovec *iovecDecrypt;
    u8 key[2] = {0xc1,0xb2};  /*Linha modificada --> valor da key modificada*/
    int div, modd;
 // Chama o função de leitura original. Os dados lidos estarão
    // cifrados. 
    ret = generic_file_aio_read(iocb, iov, nr_segs, pos);
    pr_info("minix_file_aio_read: BGN\n");
    pr_info("minix_file_aio_read: %d bytes read", ret);

    iovecDecrypt = kmalloc(sizeof(struct iovec), GFP_KERNEL);
    if (!iovecDecrypt){
        pr_err("the allocation failed - handle appropriately\n");
    }

    iovecDecrypt->iov_base = kmalloc(ret, GFP_KERNEL);
    iovecDecrypt->iov_len = iov->iov_len;

    if(ret > 0 ){
        div= ret / AES_BLOCK_SIZE;
        modd= ret % AES_BLOCK_SIZE;

        // O terceiro argumento pode ser entendido de duas maneira.
        // Quando modd == 0, implica que o tamanho dos dados que passarão
        // pelo processo de transformação é multiplo de 16. 
        // C.C, implica que esse tamanho não é múltiplo de 16. Logo
        // O último bloco não passará por transformação.
        minix_crypt(iov, iovecDecrypt, modd == 0 ? ret : div * AES_BLOCK_SIZE, key, 2, 1);
        // O iov_base representa a base do endereço dos dados no espaço do usuário
        // Logo, devemos atualizar o endereço da estrutura original. 
        if (copy_to_user(iov->iov_base, iovecDecrypt->iov_base,  modd == 0 ? iov->iov_len : div * AES_BLOCK_SIZE)){
            pr_err("copy to user error");
        }
        pr_info("minix_file_aio_read: END\n");
    }

    return ret;
}

ssize_t minix_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
        unsigned long nr_segs, loff_t pos)
{
    struct iovec *iovecEncypt;
    int div, modd;
    u8 key[2] = {0xc1,0xb2};  /*Linha modificada --> valor da key modificada*/

    pr_info("minix_file_aio_write: BGN\n");

    iovecEncypt = kmalloc(sizeof(struct iovec), GFP_KERNEL);
    if (!iovecEncypt){
        pr_err("the allocation failed - handle appropriately\n");
    }
    iovecEncypt->iov_base = kmalloc(iov->iov_len, GFP_KERNEL);
    iovecEncypt->iov_len = iov->iov_len;

    memset(iovecEncypt->iov_base, 0, iov->iov_len);

    div = iov->iov_len / AES_BLOCK_SIZE;
    modd = iov->iov_len % AES_BLOCK_SIZE;

    if(div > 0){
        // O terceiro argumento pode ser entendido de duas maneira.
        // Quando modd == 0, implica que o tamanho dos dados  que passarão
        // pelo processo de transformação é multiplo de 16. 
        // C.C, implica que esse tamanho não é múltiplo de 16. Logo
        // O último bloco não passará por transformação.
        minix_crypt(iov, iovecEncypt, modd == 0 ? iov->iov_len : div * AES_BLOCK_SIZE, key, 2, 0);
        // O iov_base representa a base do endereço dos dados no espaço do usuário
        // Logo, devemos atualizar o endereço da estrutura original.        
        if (copy_to_user(iov->iov_base, iovecEncypt->iov_base, modd == 0 ? iov->iov_len : div * AES_BLOCK_SIZE)){
            pr_err("copy to user error");
        }
    }

    pr_info("minix_file_aio_write: END\n");
// Chama a função de escrita original com os dados cifrados.
    return generic_file_aio_write(iocb, iov, nr_segs, pos);
}

static int minix_setattr(struct dentry *dentry, struct iattr *attr)
{
    struct inode *inode = dentry->d_inode;
    int error;

    error = inode_change_ok(inode, attr);
    if (error)
        return error;

    if ((attr->ia_valid & ATTR_SIZE) &&
            attr->ia_size != i_size_read(inode)) {
        error = vmtruncate(inode, attr->ia_size);
        if (error)
            return error;
    }

    setattr_copy(inode, attr);
    mark_inode_dirty(inode);
    return 0;
}

const struct inode_operations minix_file_inode_operations = {
        .truncate	= minix_truncate,
        .setattr	= minix_setattr,
        .getattr	= minix_getattr,
};
