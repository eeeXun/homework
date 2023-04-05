#include <pthread.h>
#include <stdio.h>

void *producer(void *param); /* the thread */
void *consumer(void *param); /* the thread */

int counter = 0;
int in=0, out=0;
#define BUFFER_SIZE 10
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
	pthread_attr_t attr; 	/* set of attributes for the thread */
	pthread_t tid[2]; 	/* the thread identifier */

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	pthread_create(&tid[0], &attr, producer, NULL);
	pthread_create(&tid[1], &attr, consumer, NULL);

	/* now wait for the thread to exit */
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	return 0;
}

/**
 * The producer thread will begin control in this function
 */
void *producer(void *param) 
{
	char item;

	printf("\n Producer thread starts running! \n");

	do {

		while (counter==BUFFER_SIZE)
			;
		item = '0' + in;
		buffer[in]=item;
		in = (in +1) % BUFFER_SIZE;
		counter++;
		printf("==> Put item= %c \n", item);

	} while (1);
	
	printf("\n Producer thread is terminated! \n");
	pthread_exit(0);
}

/**
 * The consumer thread will begin control in this function
 */
void *consumer(void *param) 
{
	char item;

	printf("\n Consumer thread starts running! \n");

	do {
		while (counter==0)
			;
		item=buffer[out];
		out = (out +1) % BUFFER_SIZE;
		counter--;
		printf(" Get item= %c \n", item);
	} while (1);
	
	printf("\n Consumer thread is terminated!\n");
	pthread_exit(0);
}

