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
#include "asset.h"

int loadasset(user *head, char* p0)
{
	char *type[3];
	char *num[3];
	int buttons, mx, my;
	tiqu(head,p0,num,type);
mouseInit(&mx, &my,&buttons);
setbkcolor(CYAN);
	cleardevice();	
 setviewport(0,0,640,480,1);
  setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,num);
if(strcmp(type,"A")==0)
	{
		drawred();
	}
	else if(strcmp(type,"B")==0)
	{
		drawred();
		drawyel();
	}
		else if(strcmp(type,"C")==0)
		{
			drawred();
			drawblue();
		}
			else if(strcmp(type,"D")==0)
			{
				drawred();
				drawyel();
				drawblue();
		
		}
		while(1)
		{
			newxy(&mx, &my, &buttons);
			if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
             //返回主菜单
			 setbkcolor(RED);
		      return 4;
	    }
		}
			

}
//////////////////////////////////////////
void drawred()
{
	int a1[]={15,140,15,130,25,120,50,120,70,100,100,100,120,120,120,140,15,140};
	setcolor(DARKGRAY);
	drawpoly(9,a1);
	arc(45,140,180,360,10);
	arc(100,140,180,360,10);
	setfillstyle(1,RED);
	floodfill(40,130,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(45,146,DARKGRAY);
    floodfill(100,146,DARKGRAY);
	////////////////////////////////
	setfillstyle(1,WHITE);
 settextstyle(3,0,1);
 outtextxy(130,132,"Speed");
 bar(185,140,285,152);
 setfillstyle(1,RED);
 bar(185,140,230,152);
 //////////////////////////////////
 setcolor(BLUE);
}
void drawblue()
{
	int a3[]={15,380,15,370,25,360,50,360,70,340,100,340,120,360,120,380,15,380};
	setcolor(DARKGRAY);
	drawpoly(9,a3);
	arc(45,380,180,360,10);
	arc(100,380,180,360,10);
	setfillstyle(1,BLUE);
	floodfill(40,370,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(45,386,DARKGRAY);
    floodfill(100,386,DARKGRAY);
/////////////////////////////
	setfillstyle(1,WHITE);
 settextstyle(3,0,1);
 outtextxy(130,372,"Speed");
 bar(185,380,285,392);
 setfillstyle(1,RED);
 bar(185,380,279,392);
 ///////////////////////////////
		setcolor(BLUE);
}
void drawyel()
{
	int a2[]={15,260,15,250,25,240,50,240,70,220,100,220,120,240,120,260,15,260};
	setcolor(DARKGRAY);
	drawpoly(9,a2);
	arc(45,260,180,360,10);
	arc(100,260,180,360,10);
	setfillstyle(1,YELLOW);
	floodfill(40,250,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(45,266,DARKGRAY);
    floodfill(100,266,DARKGRAY);
	////////////////////////////////
	setfillstyle(1,WHITE);
 settextstyle(3,0,1);
 outtextxy(130,252,"Speed");
 bar(185,260,285,272);
 setfillstyle(1,RED);
 bar(185,260,260,272);
 //////////////////////////////////
	setcolor(BLUE);
}