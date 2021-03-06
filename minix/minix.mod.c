#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6ffcc1a3, "module_layout" },
	{ 0xb67f2319, "__kmap_atomic" },
	{ 0x5ea84045, "kmem_cache_destroy" },
	{ 0x228d3f1c, "iget_failed" },
	{ 0xe0d91edc, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x405c1144, "get_seconds" },
	{ 0xbde75f70, "mark_buffer_dirty_inode" },
	{ 0x4fd611a6, "generic_file_llseek" },
	{ 0x3b651320, "__mark_inode_dirty" },
	{ 0x76ebea8, "pv_lock_ops" },
	{ 0xd0d8621b, "strlen" },
	{ 0x9b6df511, "page_address" },
	{ 0x18b00ef9, "block_write_begin" },
	{ 0x25820c64, "fs_overflowuid" },
	{ 0xc01cf848, "_raw_read_lock" },
	{ 0x4078599a, "__lock_page" },
	{ 0xc369d46f, "__lock_buffer" },
	{ 0x8739cbcd, "generic_file_aio_read" },
	{ 0xfbc55c80, "block_read_full_page" },
	{ 0xd3cbaaf0, "end_writeback" },
	{ 0x96714827, "mount_bdev" },
	{ 0xd0da9c89, "generic_read_dir" },
	{ 0x7f0eab76, "__getblk_gfp" },
	{ 0x1b1af154, "unlock_buffer" },
	{ 0x6b425f9, "generic_file_aio_write" },
	{ 0x749b5e56, "__insert_inode_hash" },
	{ 0x2bc95bd4, "memset" },
	{ 0x4489269f, "__bread_gfp" },
	{ 0x50eedeb8, "printk" },
	{ 0x5debbd02, "d_rehash" },
	{ 0x5152e605, "memcmp" },
	{ 0xe7b70ea6, "find_or_create_page" },
	{ 0xf2c1a9a0, "d_alloc_root" },
	{ 0xc4535ba1, "kunmap" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0xb4390f9a, "mcount" },
	{ 0x5253deb5, "kmem_cache_free" },
	{ 0x7f658e80, "_raw_write_lock" },
	{ 0xed93f29e, "__kunmap_atomic" },
	{ 0x7975502, "setattr_copy" },
	{ 0x3543b3a6, "page_symlink" },
	{ 0x23631bc1, "sync_dirty_buffer" },
	{ 0xd4674598, "unlock_page" },
	{ 0x6e187784, "__brelse" },
	{ 0xf11543ff, "find_first_zero_bit" },
	{ 0x15dcd339, "inode_init_once" },
	{ 0xb19906b3, "page_follow_link_light" },
	{ 0x990ae2ad, "invalidate_inode_buffers" },
	{ 0x7acddca7, "kmem_cache_alloc" },
	{ 0x738803e6, "strnlen" },
	{ 0x8807aca1, "generic_file_mmap" },
	{ 0x4db77666, "kmap" },
	{ 0xa413443e, "bdevname" },
	{ 0x55d349aa, "block_write_full_page" },
	{ 0xf64498f4, "block_write_end" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa3a729a, "generic_write_end" },
	{ 0xa54ff7a2, "do_sync_read" },
	{ 0x581da463, "unlock_new_inode" },
	{ 0x3195602e, "kill_block_super" },
	{ 0xa037ffb9, "crypto_destroy_tfm" },
	{ 0xc188bf0f, "inode_change_ok" },
	{ 0x9bc2e0c5, "kmem_cache_alloc_trace" },
	{ 0x67f7403e, "_raw_spin_lock" },
	{ 0x5dcd5129, "kmem_cache_create" },
	{ 0x5a7b465e, "register_filesystem" },
	{ 0x20dc531, "iput" },
	{ 0xfd64a178, "read_cache_page" },
	{ 0x731044fa, "generic_file_fsync" },
	{ 0x37a0cba, "kfree" },
	{ 0xe76b54ea, "do_sync_write" },
	{ 0x9fdc9311, "ihold" },
	{ 0x2e60bace, "memcpy" },
	{ 0x50f5e532, "call_rcu_sched" },
	{ 0x6128b5fc, "__printk_ratelimit" },
	{ 0x408514fa, "vmtruncate" },
	{ 0x9710ac47, "block_truncate_page" },
	{ 0xa4d914db, "sb_set_blocksize" },
	{ 0xa3c36dfb, "generic_readlink" },
	{ 0xf9e450e0, "put_page" },
	{ 0x52d84bd5, "__bforget" },
	{ 0x74c134b9, "__sw_hweight32" },
	{ 0x5b321cf3, "__block_write_begin" },
	{ 0xd27b570d, "mark_buffer_dirty" },
	{ 0x18b2a83a, "unregister_filesystem" },
	{ 0xa9e03abe, "write_one_page" },
	{ 0x54455361, "init_special_inode" },
	{ 0x75bdd521, "new_inode" },
	{ 0x246129d7, "generic_file_splice_read" },
	{ 0xf4e3cbf9, "crypto_alloc_base" },
	{ 0x90e96df8, "page_put_link" },
	{ 0x98dfaf96, "d_instantiate" },
	{ 0x9b26ba74, "generic_block_bmap" },
	{ 0x9db3065e, "iget_locked" },
	{ 0x7c30286d, "generic_fillattr" },
	{ 0x5305714, "inode_init_owner" },
	{ 0xe914e41e, "strcpy" },
	{ 0x23c12a32, "truncate_inode_pages" },
	{ 0xdf929370, "fs_overflowgid" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "640ABA61AE4C404022EB7FA");
