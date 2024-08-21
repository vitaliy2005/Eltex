#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("WRG");
MODULE_AUTHOR("WARG@gmail.com");
MODULE_DESCRIPTION("Hello World Kernel Module");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, World!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, World!\n");
}
module_init(hello_init);
module_exit(hello_exit);
