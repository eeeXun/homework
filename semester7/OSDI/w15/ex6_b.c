#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Branko Hong");
MODULE_DESCRIPTION("Two kernel modules - module B");

extern int data;
extern int exp0(int base, int num);

static int __init module_B_init(void){
  printk(KERN_INFO "Insert module B successfully!\n");
  printk(KERN_INFO "Kernel module B is using kernel module A! data = %d\n", data);
  printk(KERN_INFO "Kernel module B is using kernel module A! func() = %d\n", exp0(3, 5));
  printk(KERN_INFO "Kernel module B is using kernel module A! data = %d\n", data);

  return 0;
}

static void __exit module_B_exit(void){
  printk(KERN_INFO "Remove module B successfully!\n");
}

module_init(module_B_init);
module_exit(module_B_exit);
