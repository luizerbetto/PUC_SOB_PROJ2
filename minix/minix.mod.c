#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


<<<<<<< HEAD
MODULE_INFO(srcversion, "0B658F09033E06537C28EC5");
=======
MODULE_INFO(srcversion, "5BC4F742F7D6159064FE56D");
>>>>>>> e4a67de7c22cc64727043aa397d482d0172a33b2
