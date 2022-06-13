#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xc94a8ec9, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x919d88a9, "__register_chrdev" },
	{ 0x24d273d1, "add_timer" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0xcf2a6966, "up" },
	{ 0x92997ed8, "_printk" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x6626afca, "down" },
	{ 0xb280591, "wake_up_process" },
	{ 0x64c256b6, "kthread_create_on_node" },
	{ 0xde5610d4, "kthread_stop" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "807A28EC8C6FA51A13A05BB");
