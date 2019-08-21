#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<bios.h>
#include "mouse1.h"
#include "jiemian2.h"
#include "caidan1.h"
#include "zhuce2.h"
#include "jiegouti.h"
int getkey1()
{
 int key;
 key=bioskey(0);
 if(key<<8)
 {
	 key=key&0x00ff;
 }
 return key;
}
///////////////////////////////////////////
int loadzhuce(user *head,char *p0)
{
	void *buffer0;
	int size;
	int buttons, mx, my;
	int j=0;
	char temp;
	char pkey[10];
 cleardevice();
 setviewport(0,0,640,480,1);
 setcolor(BLUE);
 setbkcolor(CYAN);
 //setlinestyle(2,0,3);
 setfillstyle(1,LIGHTGRAY);
 outtextxy(265,195,"register");
 bar(150,330,250,350);
 bar(390,330,490,350);
 outtextxy(172,295,"Name");
 outtextxy(420,295,"Key");
  outtextxy(500,5,"Back");
 mouseInit(&mx, &my,&buttons);
 size=imagesize(150,300,255,365);
 buffer0=malloc(size);
 getimage(150,300,255,365,buffer0);

	while (1)
	{
		if(kbhit()!=0)
		{
			temp=getkey1();
		}
		newxy(&mx, &my, &buttons);
		if(mx>=150&&mx<=250&&my>=330&&my<=350&&buttons)
		{
			
			inputname(p0,buffer0);
			
			if(searchname(head,p0))
			{
				printf("success");
				inputkey(pkey);
				newuser(head,p0,pkey);	
				outtextxy(10,10,"register success");
				getch();
                  return 4;
			}
			else
			
				outtextxy(10,10,"the name has been used");
				outtextxy(10,30,"press any key to continue");
				getch();
                 return 2;			
		}

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	{
		return 1;
	}
		}
		
	
 }
///////////////////////////

//////////////////////////////////////////////////////////////////
void inputname(char *name,void *buffer0)
{
	
	int k=0;
	FILE *fp;
	//int buttons, mx, my; 
	void *buffer1;
	int size,size1;
	//void *buffer2;
	//char name[11];
	//char *p=NULL;
	unsigned int key;
char c[2]={'\0','\0'};
	int j=0;
	int i=0;
	//int flag=0;
//	setcolor(BLACK);
putimage(150,300,buffer0,COPY_PUT); //这句话一定要放在后面的getimage之前，否则可能出现bug
size=imagesize(151,330,162,350);
//size1=imagesize(151,330,249,350);
 buffer1=malloc(size);
  //buffer2=malloc(size1);
 getimage(151,330,162,350,buffer1);
//getimage(151,350,162,370,buffer2);
	//putimage(150,300,buffer0,COPY_PUT);
	setlinestyle(0,0,3);
			setcolor(YELLOW);
			rectangle(148,328,252,352);
 setcolor(YELLOW);

 while(1)
 {
	 
	 
	/*if(kbhit()==0)
		{
			 newxy(&mx, &my, &buttons);
			if(flag==1)
			{
				putimage(150,350,buffer0,COPY_PUT);
				flag=0;
			}
			 outtextxy(152,355,name);
			 continue;
		} */
	
 key=getkey1();
 if(key==0x0008)
 {
 	if (j>0&&j<=8)
 	{
 		name[j-1]='\0';
 		j--;
 		//outtextxy(152+12*j,325," ");//空格并不能将原来的东西覆盖
		putimage(152+12*j,330,buffer1,COPY_PUT);
		//flag=1;
 	}
	if(j>7)
	{
		j--;
	}
 }
 else if(key==0x000d)
	break;
else 
	{
		if(j>7)
		{
			j++;
		}
	else 
	{	
c[0]=key;
if(c[0]=='i'||c[0]=='j'||c[0]=='r'||c[0]=='t'||c[0]=='l')//因为rltj这些字母所占空间偏左，按相同方式显示会不好看
{
	outtextxy(152+5+12*j,323,c);
}
else 
{
 outtextxy(152+12*j,323,c);
}
 name[j]=c[0];
 name[j+1]='\0';
 j++;
	}

}
 }
 name[j]='\0';
 //此时已经完成name的输入
 free(buffer1);//很重要，因为对于malloc分配的空间，在函数结束后不会自动消失，所以需要free掉
 free(buffer0);              //防止多次调用后爆了
}
//////////////////////////////////////////////////////
void inputkey(char *key)
{
	void *buffer1;
	int size;
	int k=0;
	FILE *fp;
	int key1;
	//char key[10];
	//char *p=NULL;
	//struct user b[100];
char c[2]={'\0','\0'};
	int j=0;
	//bar(391,300,392,350);
	size=imagesize(393,330,404,350);
 buffer1=malloc(size);
 getimage(393,330,404,350,buffer1);
	//putimage(150,300,buffer0,COPY_PUT);
	setcolor(CYAN);
			rectangle(148,328,252,352);
			setcolor(YELLOW);
			rectangle(388,328,492,352);
	while(1)
 {
 key1=getkey1();
 if(key1==0x0008)
 {
 	if (j>0&&j<=8)
 	{
 		key[j-1]='\0';
 		j--;
 		//outtextxy(152+12*j,325," ");  //空格并不能将原来的东西覆盖
		putimage(392+12*j,330,buffer1,COPY_PUT);
 	}
	else if (j>7)
	{
		j--;
	}
 }
 else if(key1==0x000d)
	break;
else 
	{
		if(j>7)
		{
			j++;
		}
		else
		{
		c[0]=key1;
		if(c[0]=='i'||c[0]=='j'||c[0]=='r'||c[0]=='t'||c[0]=='l')//因为rltj这些字母所占空间偏左，按相同方式显示会不好看
{
	outtextxy(392+5+12*j,323,c);
}
else 
{
 outtextxy(392+12*j,323,c);
}
 key[j]=c[0];
 j++;
		}
}
 }
 key[j]='\0';
 free(buffer1);
}



