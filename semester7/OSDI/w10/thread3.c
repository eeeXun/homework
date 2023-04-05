/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 * Usage on Solaris/Linux/Mac OS X:
 *
 * gcc thrd.c -lpthread
 * a.out <number>
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);    /* threads call this function */

void main(int argc, char *argv[])
{
	pthread_t tid[5]; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
    int sum = 0;

	/* create the thread */
	pthread_attr_init(&attr);
    for (int i = 0; i < 5; i++) {
	    pthread_create(&tid[i], &attr, runner, &i);
	    pthread_join(tid[i],NULL);
    }

	/* now wait for the thread to exit */
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
    int p_index = *(int*)param;
    printf("%d-th thread start running!\n", p_index);

	for (int i = 1; i <= 1000000; i++)
		sum ++;
	
    printf("%d-th thread end running! The sum=%d\n", p_index, sum);
	pthread_exit(0);
}

