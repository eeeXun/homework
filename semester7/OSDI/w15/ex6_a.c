#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Branko Hong");
MODULE_DESCRIPTION("Two kernel modules - module A");

int data = 99;

int exp0(int base, int num){
  int result = base;
  int i;
  for (i = 1; i < num; i++)
    result *= base;
  printk(KERN_INFO "This is func() in kernel module A! The exp0(%d, %d)=%d\n", 
      base, num, result);
  data = result;
  return data;
}

EXPORT_SYMBOL(data);
EXPORT_SYMBOL(exp0);

static int __init module_A_init(void){
  printk(KERN_INFO "Insert module A successfully!\n");

  return 0;
}

static void __exit module_A_exit(void){
  printk(KERN_INFO "Remove module A successfully!\n");
}

module_init(module_A_init);
module_exit(module_A_exit);
