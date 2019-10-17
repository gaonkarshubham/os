#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 31
typedef struct entry
{
	char name[20];
	char num[13];
}entry;

char buffer[31];
void insert(char fname[10])
{
	int fd,i;					//file descriptor
	entry data;					//data to file
	fd=open(fname,O_WRONLY|O_APPEND|O_CREAT);
	if(fd==-1)
	{
		printf("\nError opening the file!!!!");
	}
	else
	{
		printf("\nEnter the Name(**SHORT NAME): ");
		scanf("%s",data.name);
		printf("\nEnter the Phone number: ");
		scanf("%s",data.num);
		for(i=0;i<31;i++)
		{
			if(i<strlen(data.name))
			{
				buffer[i]=data.name[i];
			}
			else
			if(i<20)
			{
				buffer[i]='.';
			}
			else
			{
				buffer[i]=data.num[i-20];
			}
		}
		printf("\nEntering data into file %s: %s",fname,buffer);
		write(fd,buffer,sizeof(buffer));
		close(fd);
	}
}
void display(char fname[10])
{
	int fd;
	fd=open(fname,O_RDONLY);
	if(fd==-1)
	{
		printf("\nError opening the file!!!!");
	}
	else
	{
		printf("\nTHE ADDRESS BOOK:\n--------------------------------");
		if(read(fd,buffer,MAX)==0)
		{
			printf("\nNo entries in the file!!!");
		}
		else
		{
			printf("\nName\t\t\tPhone Number\n------------------------------------------\n");
			do
			{
				printf("%s\n",buffer);									
			}while(read(fd,buffer,MAX));
		}
		close(fd);
	}
};

int search(char fname[10],char name[20])
{
		int fd,flag=0,count=-1,i;
		fd=open(fname,O_RDONLY);
		if(read(fd,buffer,MAX)==0)
			printf("\nNo entries in the file!!!");
		else
		{
			do
			{
				count++;
				for(i=0;(buffer[i]!='.') && (name[i]!='\0');i++)
				{
					if(buffer[i]==name[i])
					{
						flag=1;
						if(name[i+1]=='\0')
						{
							if(buffer[i+1]=='.')
					 		{
					 			flag=1;
							}
					 		else
					 		{
					 			flag=0;
					 			break;
							 }
						}	
					}
					else
					{
						flag=0;
						break;
					}
					
				}
				if(flag==1)
				{
					break;
				}
			}while(read(fd,buffer,MAX));
			if(flag==1)
			{
				printf("\nRecord found!!!!");
				return count;
			}
			else
			{
				printf("\nRecord not found.");
				return -1;
			}
		}
		close(fd);	
}
void search1(char fname[10])
{
	char name[20];
	int flag;
	int fd;
	fd=open(fname,O_RDONLY);
	if(fd==-1)
		printf("\nError opening the file!!!");
	else
	{
		if(read(fd,buffer,MAX)==0)
		{
			printf("\nNo entries in the file!!!!!");
			close(fd);
		}
		else
		{
			close(fd);	
			printf("\nEnter the name to be searched: ");
			scanf("%s",name);
			flag=search(fname,name);
		}
	}
}
void modify(char fname[10])
{
	int fd,flag,ch,i;
	entry data;
	char name[20];
	fd=open(fname,O_RDWR);
	if(fd==-1)
		printf("\nError opening the file!!!");
	else
	{
		if(read(fd,buffer,MAX)==0)
			printf("\nNo entries in the file!!!");
		else
		{
			printf("Enter the name whose record is to be modified: ");
			scanf("%s",name);
			close(fd);
			flag=search(fname,name);
			fd=open(fname,O_RDWR);		
			if(flag==-1)
			{
				printf("\nModification unsuccessful!!!!");
			}
			else
			{
				printf("Enter your choice to change field\n");
				printf("1: Name\n");
				printf("2: Number\n");
				printf("0: Exit\n");
				scanf("%d", &ch);
				switch(ch)
				{
					case 0:
						printf("\nNo modifications made.");
						break;
					case 1:
						printf("\nEnter the new name:");
						scanf("%s",data.name);
						lseek(fd,flag*MAX,SEEK_SET);
						read(fd,buffer,MAX);
						lseek(fd,-sizeof(buffer),SEEK_CUR);
						for(i=0;i<20;i++)
						{
							if(i<strlen(data.name))
							buffer[i] = data.name[i];
							else
								buffer[i] = '.';
						}
						write(fd,buffer,sizeof(buffer));
						printf("\nModification successful!!!!!");
						break;
					case 2:
					printf("\nEnter the new Phone number:");
						scanf("%s", data.num);
						lseek(fd,flag*MAX,SEEK_SET);
						read(fd,buffer,MAX);
						lseek(fd,-sizeof(buffer),SEEK_CUR);
						for(i=20;i<30;i++)
							buffer[i] = data.num[i-20];
						write(fd,buffer,sizeof(buffer));
						printf("\nModifications successful!!!!!");
						break;
				default:
						printf("\nWrong choice!!!!");
				}			
			}
			close(fd);
		}
	}	
}	
void delete1(char fname[10])
{	
	int fd1,fd2,i,flag,count=-1;
	char name[20];
	fd1=open(fname, O_RDONLY);
	if(fd1==-1)
	{
		printf("\nError opening the file!!!");		
	}
	else
	{
		fd2 = open("temp.txt", O_WRONLY|O_CREAT);
		if(read(fd1,buffer,MAX)==0)
			printf("\nNo entries in the file!!!!!");
		else
		{
			printf("\nEnter the name whose record is to be deleted: ");
			scanf("%s",name);
			close(fd1);
			fd1 = open(fname, O_RDONLY);
			flag=search(fname,name);
			if(flag==-1)
				printf("\nDeletion unsuccessful!!!");
			else
			{
				read(fd1,buffer,MAX);
				do
				{
					count++;
					if(count!=flag)
					{
						write(fd2,buffer,sizeof(buffer));
					}
				}while(read(fd1,buffer,MAX));
				remove(fname);
				rename("temp.txt", fname);
				printf("\nDeletion successful!!!");
			}
			close(fd1);
			close(fd2);
		}
	}
}
void main()
{
	int ch,val;
	char fname[10];
	printf("\nEnter the file name(.txt): ");
	scanf("%s",fname);
	printf("\n");
	do
	{
		printf("\nWelcome to your Phone Book\n");
		printf("Choose your option\n");
		printf("1: Insert a new entry\n");
		printf("2: Display all entries\n");
		printf("3: Search an entry\n");
		printf("4: Update an entry\n");
		printf("5: Delete an entry\n");
		printf("0: Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: 
							insert(fname);
							break;
			case 2:
							display(fname);
							break;
			case 3:
							search1(fname);		
							break;
			case 4:
							modify(fname);
							break;
			case 5: 
							delete1(fname);
							break;
			case 6:
							printf("Byeee\n");
							break;
			default:
							printf("Wrong INPUT\n");
		}
	}while(ch!=6);
}

