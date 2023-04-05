#include <linux/module.h>  // needed for module
#include <linux/sched.h>   // for task_struct definition
#include <linux/kthread.h>
#include <linux/mutex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mei-Ling Chiang");
MODULE_DESCRIPTION("Kernel module for displaying process information");

struct task_struct *kth;
struct mutex etx_mutex, total_mutex;
long count = 0;
char data;
int i, j;

static int kernel_thread_ex3(void *arg){
  char data3;
  mutex_lock(&etx_mutex);
  data3 = *(char *)arg;
  *(char*)arg = (*(char*)(arg))+1;

  printk(KERN_INFO "The created kernel thread[%c] is running now! pid = %d\n", data3, current->pid);
  for(j = 0; j < 1000000; j++){
    count++;
  }
  printk(KERN_INFO "The created kernel thread[%c] is running now! count = %ld\n", data3, count);

  if (data3 == 'D')
    mutex_unlock(&total_mutex);

  mutex_unlock(&etx_mutex);

  do_exit(0);
  return 0;
}

static int __init display_process_info_init(void){
    mutex_init(&etx_mutex);
    mutex_init(&total_mutex);
    data = 'A';
    printk(KERN_INFO "Insert kernel module for creating 4 kernel threads\n");
    printk(KERN_INFO "current process id : %d\n",current->pid);

    mutex_lock(&total_mutex);
    for(i = 0; i < 4; i++){
      kth = kthread_run(kernel_thread_ex3, &data, "kthread ex3");
    }
    while(mutex_is_locked(&total_mutex));
    printk(KERN_INFO "The total = %ld\n", count);

    return 0;
}

static void __exit display_process_info_exit(void){
    printk(KERN_INFO "Remove kernel module for creating 4 kernel threads\n");
}

module_init(display_process_info_init);
module_exit(display_process_info_exit);
