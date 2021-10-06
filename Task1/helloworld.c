#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
        printk(KERN_DEBUG "Loading module...\n");
        return 0;
}

static void hello_exit(void)
{
        printk(KERN_DEBUG "Unloading module...\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Francia");
MODULE_DESCRIPTION("A module that logs some text on load and unload");
