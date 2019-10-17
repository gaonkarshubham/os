
//(ORPHAN)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void main()
{
	int i,a[30],n;
	pid_t pid;
	printf("Enter the number of elements to be entered:\n");
	scanf("%d",&n);
	printf("Enter the %d elements:\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	pid=fork();
	switch(pid)
	{
		case -1:
			printf("Error in fork\n");
			break;
		case 0:	//child
			sleep(12);
			printf("CHILD(CURRENT PROCESS)'S PID: %ld \n",(long)getpid());
			printf("PARENT'S PID: %ld \n",(long)getppid());
			asc(a,n);
			break;
		default:	//parent
			printf("CHILD'S PID: %ld \n",(long)pid);
			printf("PARENT(CURRENT PROCESS)'S PID: %ld \n",(long)getpid());
			desc(a,n);
	}
}
void asc(int a[30],int n)
{
	int pass,j,i;
	int temp;
	for(pass=1;pass<=n-1;pass++)
	{

		for(j=0;j<n-pass;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}

	}
	printf("ASCENDING ORDER:\n");
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
}
void desc(int a[30],int n)
{
	int pass,j,i;
	int temp;
	for(pass=1;pass<=n-1;pass++)
	{

		for(j=0;j<n-pass;j++)
		{
			if(a[j]<a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}

	}
	printf("DESCENDING ORDER:\n");
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
}
/*
computer:~/Documents/SL II$ gcc 2A1.c -o 2a
computer:~/Documents/SL II$ ./2a
Enter the number of elements to be entered:
7
Enter the 7 elements:
5
4
9
3
7
2
0
CHILD'S PID: 3552
PARENT(CURRENT PROCESS)'S PID: 3551
DESCENDING ORDER:
9	7	5	4	3	2	0
computer:~/Documents/SL II/os/T7228/2A$ CHILD(CURRENT PROCESS)'S PID: 3552
PARENT'S PID: 1509
ASCENDING ORDER:
0	2	3	4	5	7	9
*/
