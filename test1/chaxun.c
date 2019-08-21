#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<bios.h>
#include "mouse1.h"
#include "jiegouti.h"
#include "yonghu.h"
#include "chaxun.h"
#include "record.h"
/////////////////////////////////////////////
//int loadchaxun函数说明：
//该函数用于加载查询初始界面，并根据用户点击情况进一步加载查询
//mark：用来标识是否需要清屏，若进入了下一级界面，则返回后mark=1，说明下一次循环时需要清屏重画，否则一直清屏会很闪
/////////////////////////////
int loadchaxun(record *head, char *p1)
{
	
	int buttons, mx, my;
	int mark=0;
	huacha();
mouseInit(&mx, &my,&buttons);
	while(1)
	{
		if(mark==1)
		{
		huacha();
		mark=0;
		mouseInit(&mx, &my,&buttons);
		}
		newxy(&mx, &my, &buttons);
		if(mx>=100&&mx<=230&&my>=100&&my<=130&&buttons)
		{
			chaxun(head,p1,1,0);
			mark=1;
			//return 4;
		}
		if(mx>=100&&mx<=180&&my>=200&&my<=230&&buttons)
		{
			chaxun(head,p1,2,0);
			mark=1;
			//return 4;
		}
		if(mx>=210&&mx<=290&&my>=285&&my<=310&&buttons)
		{
			chaxun(head,p1,3,1);
			mark=1;
			//return 4;
		}
		if(mx>=210&&mx<=310&&my>=320&&my<=345&&buttons)
		{
			chaxun(head,p1,3,2);
			mark=1;
			//return 4;
		}
		if(mx>=210&&mx<=310&&my>=370&&my<=395&&buttons)
		{
			chaxun(head,p1,4,1);
			mark=1;
			//return 4;
		}
		if(mx>=210&&mx<=310&&my>=405&&my<=430&&buttons)
		{
			chaxun(head,p1,4,2);
			mark=1;
			//return 4;
		}
		if(mx>=210&&mx<=310&&my>=440&&my<=465&&buttons)
		{
			chaxun(head,p1,4,3);
			mark=1;
			//return 4;
		}
		
		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
		{

			  return 4;
		}
	}

}
//////////////////////////////////////////////////////////////
//chaxun函数说明：参数：n1 1生涯， 2top10, 3赛道，4车
//            n2对应赛道和车的编号          
//////////////////////////////////////////////////////////////
void chaxun(record *head, char *p1,int n1,int n2)
{
	int buttons, mx, my; 
	record b[15];
	int i,j,n;
	cleardevice();
	 outtextxy(500,5,"Back");
	mouseInit(&mx, &my,&buttons);
	outtextxy(50,50,"User");
	outtextxy(200,50,"Track");
	outtextxy(285,50,"Car");
	outtextxy(355,50,"Time");
	outtextxy(450,50,"Rank");
	if(n1==1)
	{
		searchname1(head,p1,b);
	}
	else if(n1==2)
	{
		n=searchall(head,p1,b);
		sort1(b,n);
		
	}
	else if(n1==3)
	{
		searchtrack(head,n2,b);
	}
		else if (n1==4)
		{
			searchcar(head,n2,b);
		}
	
	for(i=0;i<10&&strcmp(b[i].jiluname,"\0")!=0;i++)
	{
	outtextxy(50,100+30*i,b[i].jiluname);
	outtextxy(200,100+30*i,b[i].jilutrack);
	outtextxy(295,100+30*i,b[i].jilucar);
	outtextxy(370,100+30*i,b[i].jilutime);
	outtextxy(470,100+30*i,b[i].jilurank);
	}
	while(1)
	{
		newxy(&mx, &my, &buttons);
		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
		      break;
	    }
	}
}
void huacha()
{
	cleardevice();
	settextstyle(1,0,3);
	rectangle(100,100,230,130);
	outtextxy(105,100,"My Record");
	rectangle(100,200,180,230);
	outtextxy(105,200,"TOP10");
	rectangle(100,300,180,330);
	outtextxy(105,300,"TRACK");
	rectangle(100,400,150,430);
	outtextxy(105,400,"CAR");
	outtextxy(500,5,"Back");
	rectangle(210,285,290,310);
	outtextxy(215,280,"Square");
	rectangle(210,320,310,345);
	outtextxy(215,315,"Triangle");
	rectangle(210,370,290,395);
	outtextxy(215,365,"RED");
	rectangle(210,405,310,430);
	outtextxy(215,400,"YELLOW");
	rectangle(210,440,290,465);
	outtextxy(215,435,"BLUE");
}
