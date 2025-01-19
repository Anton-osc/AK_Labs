#include <linux/module.h>
#include <linux/printk.h>
#include "hello.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello2 module");
MODULE_AUTHOR("IO-24 Dziura Anton");

static int param = 1;
module_param(param, int, 0444);
MODULE_PARM_DESC(param, "Number of times to print 'Hello, world!' message");

static int __init hello2_init(void)
{
    if (param < 0 || param >= 10) {
        pr_err("Error: param parameter is greater than 10 or less than 0: %d\n", param);
        return -EINVAL;
    }
    
    if (param == 0 || (param >= 5 && param <= 10)) {
	pr_warn("Warning: param parameter is 0 or between 5 and 10. Continuing.\n");
    }
    
    pr_info("Calling print_hello() from hello1 module\n");
    print_hello(param);

    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("Goodbye from hello2 module\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
