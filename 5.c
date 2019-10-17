
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/syscall.h>


int flag=0;
int read_count=0;
int buff;

pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt=PTHREAD_MUTEX_INITIALIZER;

void *reader(void *argp)
{
	while(1)
	{
		pthread_mutex_lock(&mut);
			read_count++;
			if(read_count==1)
			{
				pthread_mutex_lock(&wrt);

			}
		pthread_mutex_unlock(&mut);
		if(flag==1)
		{
			printf("\nREADER ID=%lu, AND VALUE READ FROM BUFFER= %d\n",syscall(SYS_gettid),buff);
			sleep(2);
			flag=0;

		}
		pthread_mutex_lock(&mut);
			read_count--;
			if(read_count==0)
			{
				pthread_mutex_unlock(&wrt);


			}
		pthread_mutex_unlock(&mut);
	}

}
void *writer(void *argp)
{
	while(1)
	{
		pthread_mutex_lock(&wrt);
			if(flag==0)
			{
				printf("\nWRITER ID=%lu,  ENTER THE VALUE TO BE WRITTEN TO BUFFER= ",syscall(SYS_gettid));
				scanf("%d",&buff);
				flag=1;
			};

		pthread_mutex_unlock(&wrt);
	}
}


void main()
{
	int i;
	pthread_t wtid,rtid;

	pthread_create(&wtid,NULL,writer,NULL);

	for(i=0;i<6;i++){
	pthread_create(&rtid,NULL,reader,NULL);
	}


	pthread_join(wtid,NULL);

	for(i=0;i<6;i++){
			pthread_join(rtid,NULL);
	}
}
/*
computer:~/Documents/SL II/os/T7228/5$ gcc -pthread rw.c -o rw
computer:~/Documents/SL II/os/T7228/5$ ./rw

WRITER ID=4910,  ENTER THE VALUE TO BE WRITTEN TO BUFFER= 12

READER ID=4911, AND VALUE READ FROM BUFFER= 12

READER ID=4912, AND VALUE READ FROM BUFFER= 12

READER ID=4913, AND VALUE READ FROM BUFFER= 12

READER ID=4914, AND VALUE READ FROM BUFFER= 12

READER ID=4915, AND VALUE READ FROM BUFFER= 12

READER ID=4916, AND VALUE READ FROM BUFFER= 12

WRITER ID=4910,  ENTER THE VALUE TO BE WRITTEN TO BUFFER= 01

READER ID=4912, AND VALUE READ FROM BUFFER= 1

READER ID=4914, AND VALUE READ FROM BUFFER= 1

READER ID=4911, AND VALUE READ FROM BUFFER= 1

READER ID=4915, AND VALUE READ FROM BUFFER= 1

READER ID=4916, AND VALUE READ FROM BUFFER= 1

READER ID=4913, AND VALUE READ FROM BUFFER= 1

WRITER ID=4910,  ENTER THE VALUE TO BE WRITTEN TO BUFFER= 9

READER ID=4913, AND VALUE READ FROM BUFFER= 9

READER ID=4916, AND VALUE READ FROM BUFFER= 9

READER ID=4912, AND VALUE READ FROM BUFFER= 9

READER ID=4914, AND VALUE READ FROM BUFFER= 9

READER ID=4911, AND VALUE READ FROM BUFFER= 9

READER ID=4915, AND VALUE READ FROM BUFFER= 9

WRITER ID=4910,  ENTER THE VALUE TO BE WRITTEN TO BUFFER= 5

READER ID=4914, AND VALUE READ FROM BUFFER= 5

READER ID=4915, AND VALUE READ FROM BUFFER= 5

READER ID=4911, AND VALUE READ FROM BUFFER= 5

READER ID=4913, AND VALUE READ FROM BUFFER= 5

READER ID=4912, AND VALUE READ FROM BUFFER= 5

READER ID=4916, AND VALUE READ FROM BUFFER= 5
*/
