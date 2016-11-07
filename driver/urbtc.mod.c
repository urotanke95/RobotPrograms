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

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x331df01a, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x38f8fbac, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x66dae54, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x659a3410, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x1afae5e7, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x4d41feb2, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x5d3af1c7, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xa9076c40, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x35a58ba9, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x7ff75090, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x71d8b5d7, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x17e3f7be, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xe9e34fd5, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0x3b821b8b, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x97cf203b, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x344b7739, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xf473ffaf, __VMLINUX_SYMBOL_STR(down) },
	{ 0xad3706b1, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xc1b18a5, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe9bff861, __VMLINUX_SYMBOL_STR(down_trylock) },
	{ 0xecc20572, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x917107f1, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v08DApFC00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FF8p0001d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "3EB956F3CE48B57C8DC9BEF");
