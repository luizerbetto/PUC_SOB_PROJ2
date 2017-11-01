#include <linux/buffer_head.h>
#include <linux/slab.h>
#include "minix.h"

enum {DEPTH = 3, DIRECT = 7};	/* Only double indirect */

typedef u16 block_t;	/* 16 bit, host order */

static inline unsigned long block_to_cpu(block_t n)
{
	printk(KERN_INFO "Acessou block_to_cpu do itree_v1.c\n");
   	printk(KERN_INFO "Deixou block_to_cpu do itree_v1.c\n");

	return n;
}

static inline block_t cpu_to_block(unsigned long n)
{
	printk(KERN_INFO "Acessou cpu_to_block do itree_v1.c\n");
	printk(KERN_INFO "Deixou cpu_to_block do itree_v1.c\n");
	return n;
}

static inline block_t *i_data(struct inode *inode)
{
	printk(KERN_INFO "Acessou i_data do itree_v1.c\n");
	printk(KERN_INFO "Deixou i_data do itree_v1.c\n");
	return (block_t *)minix_i(inode)->u.i1_data;
}

static int block_to_path(struct inode * inode, long block, int offsets[DEPTH])
{
	int n = 0;
	printk(KERN_INFO "Acessou block_to_path do itree_v1.c\n");

	if (block < 0) {
		printk("MINIX-fs: block_to_path: block %ld < 0 on dev %pg\n",
			block, inode->i_sb->s_bdev);
	} else if (block >= (minix_sb(inode->i_sb)->s_max_size/BLOCK_SIZE)) {
		if (printk_ratelimit())
			printk("MINIX-fs: block_to_path: "
			       "block %ld too big on dev %pg\n",
				block, inode->i_sb->s_bdev);
	} else if (block < 7) {
		offsets[n++] = block;
	} else if ((block -= 7) < 512) {
		offsets[n++] = 7;
		offsets[n++] = block;
	} else {
		block -= 512;
		offsets[n++] = 8;
		offsets[n++] = block>>9;
		offsets[n++] = block & 511;
	}

	printk(KERN_INFO "Deixou block_to_path do itree_v1.c\n");

	return n;
}

#include "itree_common.c"

int V1_minix_get_block(struct inode * inode, long block,
			struct buffer_head *bh_result, int create)
{
	printk(KERN_INFO "Acessou V1_minix_get_block do itree_v1.c\n");
	printk(KERN_INFO "Deixou V1_minix_get_block do itree_v1.c\n");
	return get_block(inode, block, bh_result, create);
}

void V1_minix_truncate(struct inode * inode)
{
	printk(KERN_INFO "Acessou V1_minix_truncate do itree_v1.c\n");
	printk(KERN_INFO "Deixou V1_minix_truncate do itree_v1.c\n");
	truncate(inode);
}

unsigned V1_minix_blocks(loff_t size, struct super_block *sb)
{
	printk(KERN_INFO "Acessou V1_minix_blocks do itree_v1.c\n");
	printk(KERN_INFO "Deixou V1_minix_blocks do itree_v1.c\n");
	return nblocks(size, sb);
}
