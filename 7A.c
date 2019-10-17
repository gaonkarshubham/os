#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define size 1000
void main()
{
    FILE *fptr;
    char buffer[size],fname[size];
    pid_t pid;
    char c;
    char str[size],str1[size];	
    int fd1[2],fd2[2],result,n;
    result=pipe(fd1);
	//check whether pipe is unable to open
	if(result==-1)
	{
		printf("SORRY, PIPE P1 NOT CREATED.\n");
		exit(1);
	}
	result=pipe(fd2);
	if(result==-1)
	{
		printf("SORRY, PIPE P2 NOT CREATED.\n");
		exit(1);
	}
    pid=fork();
    if(pid<0)
    {
        perror("fork()");
    }else if(pid>0)
    {
        printf("\nWelcome To Parent Process\n");
        printf("\nParent:Transferring File To Child Process\n");
        close(fd1[0]);
        //printf("\nENTER FILE NAME: ");
        //scanf("%s",fname);
	//write(fd1[1],fname,sizeof(fname));
       //write(fd1[1],"in.txt",size);
        close(fd1[1]);
        //file transferred
        close(fd2[1]);
        read(fd2[0],buffer,size);
        close(fd2[0]);
        printf("\nParent:File Recieved\n");
        //write(fd2[1],fname,sizeof(fname));
        //close(fd1[1]);
        printf("\nParent:Contents Of the File  Are As Follows\n");
        fptr=fopen(buffer,"r");     //open file in read mode
        //while(fgets(buffer,size,fptr))		//read till end of file
			//{
			    //write(fd2[1],buffer,sizeof(buffer));
			  // }
        fgets(str1,size,fptr);
	printf("%s \n",str1);
	exit(0);
    }
    else
    {
        printf("\nENTER FILE NAME: ");
        scanf("%s",fname);
	write(fd1[1],fname,sizeof(fname));
        printf("\nWelcome To Child Process\n");
        close(fd1[1]);
        read(fd1[0],buffer,size);
        close(fd1[0]);
        printf("\nChild:File Recieved\n");
        fptr=fopen(buffer,"r");			//opening file in read mode
			while(fgets(buffer,size,fptr))		//read till end of file
			{
				write(fd2[1],buffer,sizeof(buffer));
										
			}
			close(fd1[0]);
        //fptr=fopen(buffer,"a+");
	//printf("\nEnter a Contents : \t");
	//gets(str);
        //fputs(str,fptr);
        //fprintf(fptr,"Hello World\n");
        //transferring file to parent process
        //printf("\nChild:Contents Successfully Written To File %s\n",buffer);
        printf("\nChild:Contents Successully Read From File\n");
        printf("\nChild:Transferring File To Parent Process\n");
        close(fd2[0]);
        write(fd2[1],buffer,size);
        close(fd2[1]);
        //file transferred
    }
}






/***************************OUTPUT*******************************
ad@ad-OptiPlex-3010:~/Desktop/ProgramOutput$ gcc -p Pipes.c -o Pipes
Pipes.c: In function ‘main’:
Pipes.c:47:2: warning: ‘gets’ is deprecated (declared at /usr/include/stdio.h:638) [-Wdeprecated-declarations]
  gets(str);
  ^
/tmp/cckeHekP.o: In function `main':
Pipes.c:(.text+0x1da): warning: the `gets' function is dangerous and should not be used.
ad@ad-OptiPlex-3010:~/Desktop/ProgramOutput$ ./Pipes

Welcome To Parent Process

Parent:Transferring File To Child Process

Welcome To Child Process

Child:File Recieved

Enter a Message!!	Henlo

Child:Contents Successfully Written To File input.txt

Child:Transferring File To Parent Process

Parent:File Recieved

Parent:Contents Of the File input.txt Are As Follows
 Henlo
 
ad@ad-OptiPlex-3010:~/Desktop/ProgramOutput$ */

