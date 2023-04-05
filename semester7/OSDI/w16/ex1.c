#include <pthread.h>
#include <stdio.h>

void *add(void *param); /* the thread */
int total = 0;

int main(int argc, char *argv[])
{
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_t tid[4]; /* the thread identifier */
	int i;

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	for (i=0; i < 4; i++)
		pthread_create(&tid[i], &attr, add, (void *)(long)i);

	/* now wait for the thread to exit */
	for (i=0; i < 4; i++)
		pthread_join(tid[i],NULL);

	printf("\n total = %d\n", total);
	return 0;
}

/**
 * The thread will begin control in this function
 */
void *add(void *param) 
{
	long thno = (long) param;

	printf("\n Thread #%ld starts running!", thno);

	for (int i = 0; i < 1000000; i++)
		total += 1;
	
	printf("\n Thread #%ld is terminated! total=%d\n", thno, total);
	pthread_exit(0);
}

