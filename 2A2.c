
//(ZOMBIE)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void main()
{
	int i,a[30],n;
	pid_t pid,k;
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
			printf("CHILD(CURRENT PROCESS)'S PID: %ld \n",(long)getpid());
			printf("PARENT'S PID: %ld \n",(long)getppid());
			asc(a,n);
			break;
		default:	//parent
			system("ps -el|grep Z");
			k=wait(0);
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
computer:~/Documents/SL II$ gcc 2A2.c -o 2b
computer:~/Documents/SL II$ ./2b
Enter the number of elements to be entered:
8
Enter the 8 elements:
5
6
2
0
3
9
1
4
CHILD(CURRENT PROCESS)'S PID: 3619
PARENT'S PID: 3618
ASCENDING ORDER:
0	1	2	3	4	5	6	9
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
1 Z  1000  3619  3618  0  80   0 -     0 -      pts/3    00:00:00 2b <defunct>
CHILD'S PID: 3619
PARENT(CURRENT PROCESS)'S PID: 3618
DESCENDING ORDER:
9	6	5	4	3	2	1	0
computer:~/Documents/SL II/os/T7228/2A$
*/
