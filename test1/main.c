#include<stdio.h>
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>
#include<dos.h>
#include<math.h>
#include<time.h>
#include "mouse1.h"
#include "zhuce2.h"
#include "denglu1.h"
#include "jiemian2.h"
#include "yonghu.h"
#include "jiegouti.h"
#include "shop.h"
#include "xuanche.h"
#include "saidao.h"
#define MYMACRO
#include "mytype.h"
#include "common.h"
#include "record.h"
#include "chaxun.h"
#include "result.h"
#include "asset.h"

int main()
{
   int driver = VGA;
	int mode = VGAHI;
	user *head=NULL;
	record *head1=NULL;
	char p0[15];
    int saidao;
	int mark=1;
    int *p1,*p2,*p3;
	int *p5;
	int a=1,b=1,c=1;
	int d=1;
	int rank;
	int x1,x2,x3;  //x1判断比赛是否完成，x2记录比赛结束后玩家所用时间，x3记录电脑车用时
	x1=1;   //0代表完成比赛， 1代表未完成
	x2=1;
	x3=2;
    p1=&a;    //对应赛道
    p2=&b;    //对应车型
    p3=&c;    //对应挡型
	p5=&d;    //对应燃油购买情况
	initgraph(&driver, &mode, "..\\BORLANDC\\bgi");
	if ((head = (user *)malloc(sizeof(user))) == NULL)
	{
		printf("\nOverflow");
		return 0;
	}
	userlist(head);
	if ((head1 = (record *)malloc(sizeof(record))) == NULL)
	{
		printf("\nOverflow");
		return 0;
	}
	recordlist(head1);
   // jiemian1(head);
  // newrecord(head1,"123",1,1,99,1);
    while(1)
    {
    	if(mark==1)
			mark=jiemian1();
    	if(mark==2)
    		mark=loadzhuce(head,p0);
    	if(mark==3)
    		mark=loaddenglu(head,p0);
    	if(mark==4)
    		mark=zhucaidan(head,p0);
    	if(mark==5)
    		mark=shop(head,p0,p5);
    	if(mark==6)
    		{
				mark=sai(head,p0,p1);		    
    		}   
        if(mark==7)
        {
            mark=cartype(head,p0,p2,p3);

        }
		if(mark==9)
		{
			mark=loadchaxun(head1,p0);
		}
		if(mark==10)
		{
			mark=loadasset(head,p0);
		}
        if (mark==8)
		{
			jiazai();
			setbkcolor(BLACK);
			cleardevice();
			settextstyle(3,0,1);
			setlinestyle(0,0,1);
			if(*p1==1)
				segs=4;
			else if(*p1==2)
				segs=3;
			if(*p2==1)
			{
				if(*p5==0)
				{
					vdrivemax=30;
				}
				else if(*p5==1)
				{		
			        vdrivemax=20;
				}
				mecolor=RED;
			}
		else if(*p2==2)
		{
			if(*p5==0)
			{
				vdrivemax=50;
			}
			else if (*p5==1)
			{
			    vdrivemax=40;
			}
			mecolor=YELLOW;
		}
		else if(*p2==3)
		{
			if(*p5==0)
			{
				vdrivemax =70;
			}
			else if (*p5==1)
			{
			vdrivemax =60;
			}
			mecolor=BLUE;
		}
		if(*p3==1)
			geartype=AUTO;
		else if(*p3==2)
			geartype=STICK;
		carRace(&x1);
	x2=timeme;
	x3=timeauto;
   if(!x1)
   {
	   rank=compare(x2,x3);
   result(head,p0,rank);
   newrecord(head1,p0,*p1,*p2,x2,rank);
   }
   *p5=1;
   mark=4;
		}
		if(mark==0)
		{
			
			delay(100);  //防止下次进入时出bug
			exit(0);
		}
	}
	return 1;
}



