#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<bios.h>
#include "yonghu.h"
#include "mouse1.h"
#include "jiegouti.h"
 
int compare(int x1,int x2)
{
	if(x1<x2)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
//////////////////////////////////////////

///////////////////////////
//result函数参数说明：1.显示最后结果（赢或输）
//                    2.若赢则使该玩家金币+5
//rank为比赛名次
///////////////////////////
void result(user *head, char *p0,int rank)
{
	//int driver = VGA;
	//int mode = VGAHI;
	void *buffer0;
		int size;
		int i=0;
		int buttons, mx, my;
		char *type[3];
		int n;//用来接收金币的整型形式
	char *num[3];
	//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
	//loadresult(1);  
  	mouseInit(&mx, &my,&buttons);
 	if (rank==1)
  	{
		settextstyle(1,0,3);
		setcolor(DARKGRAY);
		bar(200,100,400,300);
		 size=imagesize(210,110,350,250);
 buffer0=malloc(size);
 getimage(210,110,350,250,buffer0);
 setcolor(BLUE);
		rectangle(280,270,320,300);
		outtextxy(285,270,"ok");
	tiqu(head,p0,num,type);
	n=toshuzi(num);
	changecoin(head,p0,n+5);
		outtextxy(250,150,"You Win!");
		outtextxy(260,225,"coin+5");
	   while(1)
	   {
		   newxy(&mx, &my, &buttons);
		 // putimage(210,110,buffer0,COPY_PUT);
		//delay(200);
		//outtextxy(250,150,"You Win!");
		//outtextxy(260,225,"coin+5");
		//delay(200);		
		//i++;		
		if(mx>=280&&mx<=320&&my>=270&&my<=300&&buttons)
		{
			break;
		}
	}
	//getch();
	//return 1;
}
  else if(rank==2)
  {
	  settextstyle(1,0,7);
		//setcolor(DARKGRAY);
	  cleardevice();
	  setcolor(RED);
	  i=0;
	  while(i<10)
	  {
		   cleardevice();
		   delay(200);
		   outtextxy(140,150,"GAME OVER!");
		   delay(200);
		   i++;
		
	  }
	  
  }
	  
}