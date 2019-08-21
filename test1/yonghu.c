#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bios.h>
#include<graphics.h>
#include "jiegouti.h"
#include "yonghu.h"
//////////////////////////////////////////////////
//void userlist函数说明：
//该函数用于将用户信息从文件读入链表中，注意：注册时不能有空格，因为改金币数需要补空格，但金币数并不包含空格，
//所以读入数据时按跳过空格编的代码
//////////////////////////////////////////////////
void userlist(user *head)
{
	user *current;
	FILE *fp;
	char c;
	char *p=NULL;
	current=head;
	p=current->name;
	 if ((fp = fopen("..\\TEST1\\user.txt","r+")) == NULL)
  {
	  closegraph();
	  printf("Can't open user.txt");
	  getchar();
	  exit(1);
  }
  while(!feof(fp))
  {
	  c=fgetc(fp);
	  if(c=='!')
	  {
		  *p='\0';
		  p=current->key;
	  }
	  else if(c=='@')
	  {
		  *p='\0';
		  p=current->coin;
	  }
	  else if(c=='#')
	  {
		  *p='\0';
		  p=current->car;
	  }
	  else if(c=='$')
	  {
		  if((current->next=(user *)malloc(sizeof(user)))==NULL)
		{
		   closegraph();
		   printf("\nOverflow");
		//   getchar();
		   exit(1);
		}
		current=current->next;
		*p='\0';
	   p=current->name;
	  }
	  else if(c!=' ')
	  {
		  *p=c;
		  p++;
	  }
  }
  current->next=NULL;
  fclose(fp);
}
////////////////////////////////////////////////////
//int searchname函数说明：
//比较注册时用户键入的用户名是否已存在，若存在，则返回0，不存在则返回1
////////////////////////////////////////////////
int searchname( user *head,char *p )
{
	 user *current=head;
	 while(current!=NULL)
 {
	 if(strcmp(current->name,p)==0)
		return 0;
   current=current->next;
 }
  return 1;
}
///////////////////////////////////////////////////////////
//int judge函数说明
//在登录时，判断用户输入的用户名和密码是否匹配，匹配返回1，否则返回0
////////////////////////////////////
int judge(user *head,char *p1,char *p2)
{
	user *current=head;
	 while(current!=NULL)
 {
	 if(strcmp(current->name,p1)==0&&strcmp(current->key,p2)==0)
		 return 1;
   current=current->next;
 }
 return 0;
}

///////////////////////////////////////////////////////////
void newuser(user *head, char *p1, char *p2)
{
	user *current=head;
 FILE *fp;
 char *p;
 while(current->next!=NULL)  
 {
  current=current->next;
 }
if((current->next=(user *)malloc(sizeof(user)))==NULL)
 {
	 closegraph();
	 printf("\nOverflow");
	 getchar();
     exit(1);
 }  
 current=current->next;
 strcpy(current->name,p1);
 strcpy(current->key,p2);
 strcpy(current->coin,"4");
 strcpy(current->car,"A");
 current->next=NULL;
  if ((fp = fopen("..\\TEST1\\user.txt", "r+")) == NULL)
 {
	 closegraph();
	 printf("Can't open user.txt");
	 getchar();
	 exit(1);
 }
 fseek(fp,0,2);
 p=p1;
 while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
  putc('!',fp);
   p=p2;
  while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
   putc('@',fp);
   fprintf(fp,"4  #A$");
   fclose(fp);   //用完必须关闭文件，否则会出错，且打开状态下很占内存
}
///////////////////////////////////
void tozifu(int number, char *p)
{
	int n=number;
	int i=0,j=1;	
	if(n)
	{
		while(n)
        {
        	n/=10;
            i++;
        }
    while(number)
    {
    	p[i-j]=number%10+48;
    	number/=10;
    	j++;
    }
    p[i]='\0';
    }
    else 
    {	p[0]='0';
        p[1]='\0';
    }
}
///////////////////////////////////////////////////////
int toshuzi(char *p)
{
	int i=1;
	int j;
	int sum=0;
	j=strlen(p);
	while(j-1)
	{
		i*=10;
		j--;
	}
	j=0;
	while(i)
	{
		sum+=(p[j]-48)*i;
		j++;
		i/=10;
	}
	return sum;

}
//////////////////////////////////////////
void changecoin(user *head,char *p1,int num)
{
  user *current=head;
  FILE *fp;
  int i=0;
  char pcoin[4];
  int length;
  char tempname[15];
  char ch;
  char *p;
  tozifu(num,pcoin);
   length = strlen(pcoin);
	 while(current!=NULL)
 {
	 if(strcmp(current->name,p1)==0)
         break;
   current=current->next;
 }
   if ((fp = fopen("..\\TEST1\\user.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open usercode.txt");
		getchar();
		exit(1);
	}
	while (!feof(fp))
	{
		ch = fgetc(fp);
		
		if (ch == '$')
		{
			ch = fgetc(fp);
			for (p = tempname;ch != '!';ch = fgetc(fp))
			{
				*p = ch;
				*(p + 1) = '\0';
				p++;
			}
			if (strcmp(tempname, p1) == 0)
			{
				while(ch!='$')
				{	ch=fgetc(fp);}
				fseek(fp, -6, SEEK_CUR);
				fputs(pcoin, fp);
				for (i = 0;i < 3 - length;i++)
					putc(' ', fp);
				break;
			}
		}
	}
	strcpy(current->coin, pcoin);
	fclose(fp);
} 
/////////////////////////////////////////////////
void changecar(user *head,char *p1,char *type)
{
	user *current=head;
  FILE *fp;
  int length;
  char tempname[15];
  char ch;
  char *p;
  while(current!=NULL)
 {
	 if(strcmp(current->name,p1)==0)
         break;
   current=current->next;
 }
 
 if ((fp = fopen("..\\TEST1\\user.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open usercode.txt");
		getch();
		exit(1);
	}

	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '$')
		{
			ch = fgetc(fp);
			for (p = tempname;ch != '!';ch = fgetc(fp))
			{
				*p = ch;
				*(p + 1) = '\0';
				p++;
			}
			if (strcmp(tempname, p1) == 0)
			{
				while(ch!='$')
				{	
			ch=fgetc(fp);
			}
				fseek(fp, -2, 1);
				fputs(type, fp);				
				break;
			}
		}
	}
	strcpy(current->car,type);
	fclose(fp);
}
//////////////////////////////////////////////
void tiqu(user *head,char *p0,char *p1,char *p2)
{
	user *current=head;
	 while(current!=NULL)
 {
	 if(strcmp(current->name,p0)==0)
		break;
   current=current->next;
 }
  strcpy(p1,current->coin);
  strcpy(p2,current->car);

}