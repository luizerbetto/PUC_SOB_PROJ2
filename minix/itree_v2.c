#include <linux/buffer_head.h>
#include "minix.h"

enum {DIRECT = 7, DEPTH = 4};	/* Have triple indirect */

typedef u32 block_t;	/* 32 bit, host order */

static inline unsigned long block_to_cpu(block_t n)
{
	printk(KERN_INFO "Acessou block_to_cpu do itree_v2.c\n");
	printk(KERN_INFO "Deixou block_to_cpu do itree_v2.c\n");
	return n;
}

static inline block_t cpu_to_block(unsigned long n)
{
	printk(KERN_INFO "Acessou cpu_to_block do itree_v2.c\n");
	printk(KERN_INFO "Deixou cpu_to_block do itree_v2.c\n");
	return n;
}

static inline block_t *i_data(struct inode *inode)
{
	printk(KERN_INFO "Acessou i_data do itree_v2.c\n");
	printk(KERN_INFO "Deixou i_data do itree_v2.c\n");
	return (block_t *)minix_i(inode)->u.i2_data;
}

#define DIRCOUNT 7
#define INDIRCOUNT(sb) (1 << ((sb)->s_blocksize_bits - 2))

static int block_to_path(struct inode * inode, long block, int offsets[DEPTH])
{
	printk(KERN_INFO "Acessou block_to_path do itree_v2.c\n");

	int n = 0;
	struct super_block *sb = inode->i_sb;

	if (block < 0) {
		printk("MINIX-fs: block_to_path: block %ld < 0 on dev %pg\n",
			block, sb->s_bdev);
	} else if ((u64)block * (u64)sb->s_blocksize >=
			minix_sb(sb)->s_max_size) {
		if (printk_ratelimit())
			printk("MINIX-fs: block_to_path: "
			       "block %ld too big on dev %pg\n",
				block, sb->s_bdev);
	} else if (block < DIRCOUNT) {
		offsets[n++] = block;
	} else if ((block -= DIRCOUNT) < INDIRCOUNT(sb)) {
		offsets[n++] = DIRCOUNT;
		offsets[n++] = block;
	} else if ((block -= INDIRCOUNT(sb)) < INDIRCOUNT(sb) * INDIRCOUNT(sb)) {
		offsets[n++] = DIRCOUNT + 1;
		offsets[n++] = block / INDIRCOUNT(sb);
		offsets[n++] = block % INDIRCOUNT(sb);
	} else {
		block -= INDIRCOUNT(sb) * INDIRCOUNT(sb);
		offsets[n++] = DIRCOUNT + 2;
		offsets[n++] = (block / INDIRCOUNT(sb)) / INDIRCOUNT(sb);
		offsets[n++] = (block / INDIRCOUNT(sb)) % INDIRCOUNT(sb);
		offsets[n++] = block % INDIRCOUNT(sb);
	}

	printk(KERN_INFO "Deixou block_to_path do itree_v2.c\n");

	return n;
}

#include "itree_common.c"

int V2_minix_get_block(struct inode * inode, long block,
			struct buffer_head *bh_result, int create)
{
	printk(KERN_INFO "Acessou V2_minix_get_block do itree_v2.c\n");
	printk(KERN_INFO "Deixou V2_minix_get_block do itree_v2.c\n");
	return get_block(inode, block, bh_result, create);
}

void V2_minix_truncate(struct inode * inode)
{
	printk(KERN_INFO "Acessou V2_minix_truncate do itree_v2.c\n");
	printk(KERN_INFO "Deixou V2_minix_truncate do itree_v2.c\n");
	truncate(inode);
}

unsigned V2_minix_blocks(loff_t size, struct super_block *sb)
{
	printk(KERN_INFO "Acessou V2_minix_blocks do itree_v2.c\n");
	printk(KERN_INFO "Deixou V2_minix_blocks do itree_v2.c\n");
	return nblocks(size, sb);
}
