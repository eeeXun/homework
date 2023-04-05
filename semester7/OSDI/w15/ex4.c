#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Branko Hong");
MODULE_DESCRIPTION("Branko's module for displaying current process information");

static int __init display_all_pids_init(void){
  printk(KERN_INFO "Insert module for displaying current process information successfully\n");
  printk("current priority: %d\n", current->prio);
  printk("current process id: %d\n", current->pid);
  printk("current parent process id: %d\n", current->parent->pid);

  return 0;
}

static void __exit display_all_pids_exit(void){
  printk(KERN_INFO "Remove PID module sucessfully! \n");
}

module_init(display_all_pids_init);
module_exit(display_all_pids_exit);
