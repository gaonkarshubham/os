#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
 
#define MAX_BUF 1024
 
int main()
{
    int fd,c=0;
    char *fifo1="fifo1";
    char *fifo2="fifo2";
    int fd1;
    FILE *fp;
    int wc=0,lc=0,cc=0;
    char buf1[MAX_BUF];
    mkfifo(fifo1,0666);
    fd=open(fifo1,O_RDWR);
    char str;
    printf("\nEnter the String :\n");
    while ((str=getchar())!='#')
    buf1[c++]=str;
    buf1[c]='\0';
    write(fd,buf1,sizeof(buf1));
    close(fd);
    unlink(fifo1);
    fd1=open(fifo2,O_RDWR);
    read(fd1,buf1,sizeof(buf1));
    printf("\nThe contents of file are : \n%s\n",buf1);
    printf("\n\nCalculating the character, word and line counts...........");
	int i=0;	
	while(buf1[i]!='\0')			
	 {
	   if(buf1[i]==' ' ||  buf1[i]=='\n')
	   	wc++;
	   else
	   	cc++;
	   
	   if(buf1[i]=='\n')
	   	lc++;
	   	
	   i++;
	 }  
	 wc++;					
	 lc++;					
	printf("\nWriting the calculated counts into the file \"COUNT.txt\"........");
	fp=fopen("COUNT.txt","w+");		
	fprintf(fp,"No. of LINES are: %d\n",lc);        
	fprintf(fp,"No. of WORDS are: %d\n",wc);        
	fprintf(fp,"No. of CHARACTERS are: %d\n",cc);  	   
	fclose(fp);                             
	close(fd);                              
	unlink(fifo1);			
	
	fd1=open(fifo2,O_WRONLY);		
	system("cat COUNT.txt > myfifo2");	
	close(fd1);				
	printf("\nFile Contains....\n");
	printf("\n No of Words: %d",wc);
        printf("\n No of Characters: %d",cc);
     	printf("\n No of Lines: %d\n",lc);
}
