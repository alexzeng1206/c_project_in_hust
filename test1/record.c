#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bios.h>
#include<graphics.h>
#include "jiegouti.h"
#include "yonghu.h"
#include "record.h"
////////////////////////////////////
//函数说明：建立存储比赛所以记录信息的链表，从文件中读取数据装入链表
////////////////////////////////////
void recordlist(record *head)
{
	record *current;
	FILE *fp;
	char c;
	char *p=NULL;
	current=head;
	p=current->jiluname; //开始即录入名字
	 if ((fp = fopen("..\\TEST1\\record.txt","r+")) == NULL)
  {
	  closegraph();
	  printf("Can't open record.txt");
	  getchar();
	  exit(1);
  }
  while(!feof(fp))
  {
	  c=fgetc(fp);
	  if(c=='!')
	  {
		  *p='\0';
		  p=current->jilutrack;
	  }
	  else if(c=='@')
	  {
		  *p='\0';
		  p=current->jilucar;
	  }
	  else if(c=='#')
	  {
		  *p='\0';
		  p=current->jilutime;
	  }
	  else if(c=='~')
	  {
		*p='\0';
		p=current->jilurank;
	  }
	  else if(c=='$')
	  {
		  if((current->next=(record *)malloc(sizeof(record)))==NULL)
		{
		   closegraph();
		   printf("\nOverflow");
		//   getchar();
		   exit(1);
		}
		//printf("%s",current->number);////
		current=current->next;
		*p='\0';
	   p=current->jiluname;
	  }
	  else if(c!=' ')
	  {
		  *p=c;
		  p++;
	  }
  }
  current->next=NULL;   //重要！！！
  //current指针置为0没有意义，必须让current->next这个在结构体中的指针指向NULL才能使链表结束
 // getch();
  fclose(fp);
}
////////////////////////////////////////////////
//voidnewrecord函数说明：用于比赛完成后，将本场比赛的信息加入链表，并同时将信息写入文件
//参数说明：p1为当前用户名字 p2为赛道，p3为车,p4为时间,p5为排名
//其中只有用户名为字符串，后面几个都是以整形传入的，所以要进行转化为字符串这一工作
///////////////////////////////////////////////
void newrecord(record *head, char *p1,int p2,int p3,int p4,int p5)
{
	record *current=head;
 FILE *fp;
 char *p;
 char track1[10];
 char car1[10];
 char time1[5];
 char rank1[3];
 //tozifu(p2,track1);
 //tozifu(p3,car1);
 tozifu(p4,time1);
 tozifu(p5,rank1);
 //char pnum[3];
 //int l;
 //int length2=strlen(p2);
 //int i = 1;
 if(p2==1)
	 stpcpy(track1,"Square");
 if(p2==2)
	 stpcpy(track1,"Triangle");
 if(p3==1)
	 stpcpy(car1,"Red");
 if(p3==2)
	 stpcpy(car1,"Yellow");
 if(p3==3)
	 stpcpy(car1,"Blue");
 
 
 
 while(current->next->next!=NULL)  //重要！！！在创建链表时由于文件读写特点，最后一个节点为空
 {
  current=current->next;
  //i++;
 }
 current->next=NULL;       //重要！！！须将之前创建链表时出现的空节点填补上，做到无缝衔接
if((current->next=(record *)malloc(sizeof(user)))==NULL)
 {
	 closegraph();
	 printf("\nOverflow");
	 getchar();
     exit(1);
 }
 //给链表节点赋值
 current=current->next;
 strcpy(current->jiluname,p1);
  strcpy(current->jilutrack,track1);
  strcpy(current->jilucar,car1);
  strcpy(current->jilutime,time1);
  strcpy(current->jilurank,rank1);
  ////////
 current->next=NULL;
 
  if ((fp = fopen("..\\TEST1\\record.txt", "r+")) == NULL)
 {
	 closegraph();
	 printf("Can't open record.txt");
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
   p=current->jilutrack;
  while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
   putc('@',fp);
   p=current->jilucar;
   while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
  putc('#',fp);
  p=current->jilutime;
   while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
  putc('~',fp);
   p=current->jilurank;
   while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
   putc('$',fp);
   fclose(fp);
//////////////////////
//看似已经完成加入记录操作，但此时还需要在链表尾部加一个空节点，
//为了保证和创建链表时同样有一个空节点，这样才能使提取元素时判断条件统一
//否则可能导致多提取或少提取一个元素，下面操作为了在链表尾部加入一个空节点
///////////////////////
 if((current->next=(record *)malloc(sizeof(user)))==NULL)
 {
	 closegraph();
	 printf("\nOverflow");
	 getchar();
     exit(1);
 }
 current=current->next; //重要！！
  current->next=NULL;
}
//////////////////////////////////////////////
//void searchname1函数说明：
//在链表中搜索符合用户名的比赛记录，提取出来，存入一个结构数组
//////////////////////////////////////////////
void searchname1(record *head, char *p1,record *p2)
{
	record *current=head;
	int i=0;
	while(current!=NULL)
 {
	 if(strcmp(current->jiluname,p1)==0)//因为链表最后一个结点为空，所以提前一个节点结束提取
	 {
 stpcpy(p2[i].jiluname,current->jiluname);
 stpcpy(p2[i].jilutrack,current->jilutrack);
 stpcpy(p2[i].jilucar,current->jilucar);
 stpcpy(p2[i].jilutime,current->jilutime);
 stpcpy(p2[i].jilurank,current->jilurank);
 i++;
	 }
		p2[i].jiluname[0]='\0'; //不需要的下一个数组的name设为'\0'，在查询中可以用来判断要输出的个数


   current=current->next;
 }
}
////////////////////////////////////////////
//int searchall函数说明
//该函数用于提取每一个比赛记录信息存入传入的结构数组，并将比赛信息数量作为返回值
////////////////////////////////////////////
int searchall(record *head, char *p1,record *p2)
{
	record *current=head;
	int i=0;
	while(current->next!=NULL) //重要！！！
 {
	 
 stpcpy(p2[i].jiluname,current->jiluname);
 stpcpy(p2[i].jilutrack,current->jilutrack);
 stpcpy(p2[i].jilucar,current->jilucar);
 stpcpy(p2[i].jilutime,current->jilutime);
 stpcpy(p2[i].jilurank,current->jilurank);
 
   i++;
   p2[i].jiluname[0]='\0';
    current=current->next;
 }
 return i;
}
//////////////////////////////////////////////
//void sort1函数说明：
//该函数将传入的结构数组按时间从小到大排序，其中n为此数组有意义的元素的个数
////////////////////////////////////////////
void sort1(record *p,int n)
{
	int i,j,k1,k2,k;
	record c;
	
	for(i=0;i<n-1;i++)
	{	for(j=0;j<n-i-1;j++)
		{
			k1=toshuzi(p[j].jilutime);
			k2=toshuzi(p[j+1].jilutime);
			if(k1>k2)
			{
				/*strcpy(c.jilutime,p[j].jilutime);
				strcpy(p[j].jilutime,p[j+1].jilutime);
				strcpy(p[j+1].jilutime,c.jilutime);*/
				c=p[j];
				p[j]=p[j+1];
				p[j+1]=c;
			}
		}
	}
	// return n;
}
////////////////////////////////////////////
//void searchtrack函数说明：
//参数p1=1代表提取Square型赛道的记录，
//    p1=2代表提取triangle型赛道的记录
/////////////////////////////////////////////
void searchtrack(record *head, int p1,record *p2)
{
	record *current=head;
	int i=0;
	char track[10];
	if(p1==1)
	 stpcpy(track,"Square");
 if(p1==2)
	 stpcpy(track,"Triangle");
	while(current!=NULL)
 {
	 if(strcmp(current->jilutrack,track)==0)
	 {
 stpcpy(p2[i].jiluname,current->jiluname);
 stpcpy(p2[i].jilutrack,current->jilutrack);
 stpcpy(p2[i].jilucar,current->jilucar);
 stpcpy(p2[i].jilutime,current->jilutime);
 stpcpy(p2[i].jilurank,current->jilurank);
 i++;
	 }

 p2[i].jiluname[0]='\0';
   current=current->next;
 }
}
////////////////////////////////////////////////////////
void searchcar(record *head, int p1,record *p2)
{
	record *current=head;
	int i=0;
	char car[10];
	if(p1==1)
	 stpcpy(car,"Red");
 if(p1==2)
	 stpcpy(car,"Yellow");
 if(p1==3)
	 stpcpy(car,"Blue");
	while(current!=NULL)
 {
	 if(strcmp(current->jilucar,car)==0)
	 {
 stpcpy(p2[i].jiluname,current->jiluname);
 stpcpy(p2[i].jilutrack,current->jilutrack);
 stpcpy(p2[i].jilucar,current->jilucar);
 stpcpy(p2[i].jilutime,current->jilutime);
 stpcpy(p2[i].jilurank,current->jilurank);
 i++;
	 }
		

p2[i].jiluname[0]='\0';
   current=current->next;
 }
}
/////////////////////////////////////////////////////////
void searchrank(record *head, int p1,record *p2)
{
	record *current=head;
	int i=0;
	char rank[3];
	tozifu(p1,rank);
	while(current!=NULL)
 {
	 if(strcmp(current->jiluname,rank)==0)
	 {
 stpcpy(p2[i].jiluname,current->jiluname);
 stpcpy(p2[i].jilutrack,current->jilutrack);
 stpcpy(p2[i].jilucar,current->jilucar);
 stpcpy(p2[i].jilutime,current->jilutime);
 stpcpy(p2[i].jilurank,current->jilurank);
 i++;
	 }
		//return 0;


   current=current->next;
 }
}