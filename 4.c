 
#include <stdio.h>
#include<unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>

int front=-1,rear=-1,flag=0;
typedef struct{
	int buff[99];
	sem_t full,empty;
}shared;


shared sh;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

void *producer(void *argp)
{
	int i,item;
	while(1)
	{
	    sem_wait(&sh.empty);
	    pthread_mutex_lock(&mut);
		sleep(1);
		printf("\n\nEnter the product to be produced: ");
		scanf("%d",&item);
		if(rear==-1)
		{
			sh.buff[++rear]=item;
			front=rear;
			flag=1;
		}
		else
			sh.buff[++rear]=item;
		printf("\nPRODUCER ID=%lu\tPRODUCED ITEM = %d",syscall(SYS_gettid),item);

	    pthread_mutex_unlock(&mut);
		sem_post(&sh.full);

	}
	return NULL;
	pthread_exit(0);
}


void main()
{
		int i,j,k,l,prod=2,cons=1;
		pthread_t ptid,ctid;

		sem_init(&sh.empty,0,1);
		sem_init(&sh.full,0,0);
		for(i=0;i<prod;i++)
		{
			pthread_create(&ptid,NULL,producer,NULL);
		}

		for(j=0;j<cons;j++)
		{
			pthread_create(&ctid,NULL,consumer,NULL);
		}
		for(k=0;k<prod;k++)
		{
			pthread_join(ptid,NULL);

		}

		for(l=0;l<cons;l++)
		{
			pthread_join(ctid,NULL);

		}
}



void *consumer(void *argc)
{
	int i,item;

	while(1)
	{
		sem_wait(&sh.full);
	    pthread_mutex_lock(&mut);
		sleep(1);
		item=sh.buff[front++];
		printf("\nCONSUMER ID=%lu\tCONSUMED ITEM = %d",syscall(SYS_gettid),item);
	    pthread_mutex_unlock(&mut);
	    sem_post(&sh.empty);
	}

	return NULL;
	pthread_exit(0);
}
/*
computer~/Documents/SL II$ gcc -pthread final.c -o pc
computer~/Documents/SL II$ ./pc


Enter the product to be produced: 4

PRODUCER ID=4808	PRODUCED ITEM = 4
CONSUMER ID=4809	CONSUMED ITEM = 4

Enter the product to be produced: 9

PRODUCER ID=4807	PRODUCED ITEM = 9
CONSUMER ID=4809	CONSUMED ITEM = 9

Enter the product to be produced: 2

PRODUCER ID=4808	PRODUCED ITEM = 2
CONSUMER ID=4809	CONSUMED ITEM = 2

Enter the product to be produced: 2

PRODUCER ID=4807	PRODUCED ITEM = 2
CONSUMER ID=4809	CONSUMED ITEM = 2

Enter the product to be produced: 5

PRODUCER ID=4808	PRODUCED ITEM = 5
CONSUMER ID=4809	CONSUMED ITEM = 5
*/
