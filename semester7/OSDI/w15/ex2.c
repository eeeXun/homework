#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Branko Hong");
MODULE_DESCRIPTION("Branko's module for displaying all processes PIDS");

static int __init display_all_pids_init(void){
  struct task_struct *p;

  printk(KERN_INFO "Insert PID module successfully!\n");
  for_each_process(p)
    printk(KERN_INFO "process id: %d\n", p->pid);

  return 0;
}

static void __exit display_all_pids_exit(void){
  printk(KERN_INFO "Remove PID module sucessfully! \n");
}

module_init(display_all_pids_init);
module_exit(display_all_pids_exit);
