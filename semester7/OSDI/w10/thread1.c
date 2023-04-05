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
#include <string.h>

int sum1, sum2, sum3; /* this data is shared by the thread(s) */
void *runner1(void *param);    /* threads call this function */
void *runner2(void *param);    /* threads call this function */
void *runner3(void *param);    /* threads call this function */

void main(int argc, char *argv[])
{
	pthread_t tid1, tid2, tid3; /* the thread identifier */
	pthread_attr_t attr1, attr2, attr3; /* set of attributes for the thread */
    sum2 = 0;

	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		exit(-1);
	}
	if (atoi(argv[1]) < 0) {
	  fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	  exit(-1);
	}
	/* get the default attributes */
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr3);

    char s[10];
    strcpy(s, argv[1]);
	/* create the thread */
	pthread_create(&tid1, &attr1, runner1, argv[1]);
	pthread_create(&tid2, &attr2, runner2, s);
	pthread_create(&tid3, &attr3, runner3, argv[1]);
	pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
}

void *runner1(void *param) 
{
	int upper = atoi(param);
	int i;
	sum1 = 0;	

	for (i = 1; i <= upper; i++)
		sum1 += i;
	
    printf("sum1 = %d\n", sum1);
	pthread_exit(0);
}

void *runner2(void *param) 
{
    int tmp = atoi(param);
    sum2 += tmp;
    tmp--;
    sprintf(param, "%d", tmp);
    
    if (tmp > 0){
        runner2(param);
    } else{
        printf("sum2 = %d\n", sum2);
	    pthread_exit(0);
    }
}

void *runner3(void *param) 
{
	int upper = atoi(param);
	int i;
	sum3 = 1;

	for (i = 2; i <= upper; i++)
		sum3 *= i;
	
    printf("sum3 = %d\n", sum3);
	pthread_exit(0);
}
