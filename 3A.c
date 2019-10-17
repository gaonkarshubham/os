 
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
struct numeral
{
	int n1;
	int n2;
};

void *multiply(void *argp)
{
	printf("KERNEL LEVEL THREAD ID = %lu\n",syscall(SYS_gettid));
	struct numeral *num=(struct numeral *)argp;
	intptr_t ele;
	ele=(num->n1)*(num->n2);
	return (void *)ele;

}
void main()
{
    pthread_t tid;
	int a[10][10],b[10][10],c[10][10],k,i,j,r1,c1,r2,c2;
	long int sum;
	struct numeral num;
	printf("\nEnter the number of rows and columns of matrix A: ");
	scanf("%d%d",&r1,&c1);
	printf("\nEnter the elements of matrix A:\n");
	for(i=0;i<r1;i++)
	  {
	   for(j=0;j<c1;j++)
	     {
	     	scanf("%d",&a[i][j]);
	     }
	  }
	printf("\nEnter the number of rows and columns of matrix B:");
	scanf("%d%d",&r2,&c2);
	printf("\nEnter the elements of matrix B:\n");
	for(i=0;i<r2;i++)
	  {
	   for(j=0;j<c2;j++)
	     {
	     	scanf("%d",&b[i][j]);
	     }
	  }
	printf("\nMatrix A:\n");
        for(i=0;i<r1;i++)
            {
             for(j=0;j<c1;j++)
                {
 			printf("%d\t",a[i][j]);
                }
                printf("\n");
            }
	printf("\nMatrix B:\n");
        for(i=0;i<r2;i++)
            {
             for(j=0;j<c2;j++)
                {
 			printf("%d\t",b[i][j]);
                }
                printf("\n");
            }
	if(r2==c1)
	{
          for(i=0;i<r1;i++)
            {
             for(j=0;j<c2;j++)
                {
                	c[i][j]=0;
                	for(k=0;k<c1;k++)
                	{
                	    num.n1=a[i][k];
                	    num.n2=b[k][j];
                	    pthread_create(&tid,NULL,multiply,(void *)&num);
                	    pthread_join(tid,(void *)&sum);
                	    c[i][j]=c[i][j]+sum;
                	}
                }
            }
          printf("\nA*B=\n");
          for(i=0;i<r1;i++)
            {
             for(j=0;j<c2;j++)
                {
 			printf("%d\t",c[i][j]);
                }
                printf("\n");
            }
	}
	else
	{
		printf("\nMatrices can't be multiplied.");
	}
}
/*
computer~/Documents/SL II$ gcc -pthread p31.c -o mat0
computer~/Documents/SL II/os/T7228/3$ ./mat0

Enter the number of rows and columns of matrix A: 3 2

Enter the elements of matrix A:
2 4 6
1 3 5

Enter the number of rows and columns of matrix B:2 3

Enter the elements of matrix B:
1 3
2 4
5 7

Matrix A:
2	4
6	1
3	5

Matrix B:
1	3	2
4	5	7
KERNEL LEVEL THREAD ID = 5185
KERNEL LEVEL THREAD ID = 5186
KERNEL LEVEL THREAD ID = 5187
KERNEL LEVEL THREAD ID = 5188
KERNEL LEVEL THREAD ID = 5189
KERNEL LEVEL THREAD ID = 5190
KERNEL LEVEL THREAD ID = 5191
KERNEL LEVEL THREAD ID = 5192
KERNEL LEVEL THREAD ID = 5193
KERNEL LEVEL THREAD ID = 5194
KERNEL LEVEL THREAD ID = 5195
KERNEL LEVEL THREAD ID = 5196
KERNEL LEVEL THREAD ID = 5197
KERNEL LEVEL THREAD ID = 5198
KERNEL LEVEL THREAD ID = 5199
KERNEL LEVEL THREAD ID = 5200
KERNEL LEVEL THREAD ID = 5201
KERNEL LEVEL THREAD ID = 5202

A*B=
18	26	32
10	23	19
23	34	41
*/
