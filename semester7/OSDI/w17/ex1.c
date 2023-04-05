#include <linux/module.h>  // needed for module
#include <linux/sched.h>   // for task_struct definition
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mei-Ling Chiang");
MODULE_DESCRIPTION("Kernel module for displaying process information");

struct task_struct *kth;
char data;

static int kernel_thread_ex1(void *arg){
  char data = *(char *)arg;
    printk(KERN_INFO "The created kernel thread[%d] is running now!\n", current->pid);
    printk(KERN_INFO "The parameter is: %c\n",data);
    printk(KERN_INFO "current process id : %d\n",current->pid);
    printk(KERN_INFO "current process's parent id : %d\n",current->parent->pid);

  do_exit(0);
  return 0;
}

static int __init display_process_info_init(void){
    printk(KERN_INFO "Insert kernel module for displaying process information sucessfully! \n");
    printk(KERN_INFO "current priority : %d\n",current->prio);
    printk(KERN_INFO "current process id : %d\n",current->pid);
    printk(KERN_INFO "current process's parent id : %d\n",current->parent->pid);

   data = 'A';
    kth = kthread_run(kernel_thread_ex1, &data, "kthread ex1");

    return 0;
}

static void __exit display_process_info_exit(void){
    printk(KERN_INFO "Remove kernel module for displaying process informatioe sucessfully! \n");
}

module_init(display_process_info_init);
module_exit(display_process_info_exit);
