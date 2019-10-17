
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
void asc(int a[30],int n)
{
	int i,j,temp;
	for(i=0;i<(n-1);i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[i]>a[j])
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	printf("Sorted elements are:\n");
	for(i=0;i<n;i++)
	{
		printf("%d\n",a[i]);
	}
}

void main(int argc,char *argv[])
{
	int i,a[30],n;
	pid_t pid,k;
	char *args[40];
	for(i=0;i<(argc-2);i++)
	{
		args[i]=argv[i+2];
	}
	n=argc-2;
   args[i]=(char *)0;
	pid=fork();
	for(i=0;i<n;i++)
	{
		a[i]=atoi(args[i]);
	}
	switch(pid)
	{
		case -1:
			printf("Error in fork.\n");
			break;
		case 0:
			printf("CHILD(CURRENT PROCESS) PID: %ld\n",(long)getpid());
			printf("PARENT PROCESS PID: %ld\n",(long)getppid());
			printf("Applying selection sort\n");
			asc(a,n);
			for(i=0;i<n;i++)
			{
				sprintf(args[i],"%d",a[i]);
			}
			execve(argv[1],args,NULL);
			break;
		default:
			k=wait(0);
			printf("\nCHILD PID: %ld",(long)pid);
			printf("\nPARENT(CURRENT PROCESS) PID: %ld",(long)getpid());

	}
}
/* OUTPUT
student@student-OptiPlex-390:~$ ./a b 10 90 50 40 20
CHILD(CURRENT PROCESS) PID: 3705
PARENT PROCESS PID: 3704
Applying selection sort
Sorted elements are:
10
20
40
50
90

Enter the element to be searched:40
Element found.

CHILD PID: 3705
PARENT(CURRENT PROCESS) PID: 3704 */
