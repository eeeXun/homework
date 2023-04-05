#include <linux/module.h>  // needed for module
#include <linux/sched.h>   // for task_struct definition
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mei-Ling Chiang");
MODULE_DESCRIPTION("Kernel module for displaying process information");

struct task_struct *kth;
int count = 0;

static int kernel_thread_ex2(void *arg){
    printk(KERN_INFO "The created kernel thread[%d] is running now!\n", current->pid);
    printk(KERN_INFO "current process id : %d\n",current->pid);
    printk(KERN_INFO "current process's parent id : %d\n",current->parent->pid);

    while(!kthread_should_stop()){
      count++;
      ssleep(1);
    }
    printk(KERN_INFO "Kernel thread[%d] is exiting now! count = %d\n",current->pid, count);

  do_exit(0);
  return count;
}

static int __init display_process_info_init(void){
    printk(KERN_INFO "Insert kernel module for displaying process information sucessfully! \n");
    printk(KERN_INFO "current priority : %d\n",current->prio);
    printk(KERN_INFO "current process id : %d\n",current->pid);
    printk(KERN_INFO "current process's parent id : %d\n",current->parent->pid);

    kth = kthread_run(kernel_thread_ex2, NULL, "kthread ex2");

    return 0;
}

static void __exit display_process_info_exit(void){
  int ret;
  ret = kthread_stop(kth);
    printk(KERN_INFO "Remove kernel module! count=%d\n", count);
}

module_init(display_process_info_init);
module_exit(display_process_info_exit);
