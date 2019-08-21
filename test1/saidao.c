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
#include "saidao.h"
int sai(user *head,char *p0,int *p1)
{
  int buttons, mx, my;
  int a1[]={380,300,500,300,440,196,380,300};
  int a2[]={390,292,490,292,440,203,390,292};
  int a3[]={400,286,480,286,440,220,400,286};
	cleardevice();
 setcolor(BLUE);
 setbkcolor(CYAN);
 //setlinestyle(2,0,3);
 setfillstyle(1,LIGHTGRAY);
 settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
 setlinestyle(1,0,1);
 rectangle(160,210,240,290);
  setlinestyle(0,0,3);
  rectangle(150,200,250,300);
  rectangle(170,220,230,280);
    setlinestyle(0,0,3);
  drawpoly(4,a1);
    drawpoly(4,a3);
  
  
 bar(150,330,250,350);
 bar(390,330,490,350);
 outtextxy(162,322,"choose");
 outtextxy(402,322,"choose");
 outtextxy(162,295,"square");
 outtextxy(402,295,"triangle");
  outtextxy(500,5,"Back");
  mouseInit(&mx, &my,&buttons);
  
 
 	while (1)
	{
		/*if(kbhit()!=0)
		{
			temp=getkey();
		}*/
		newxy(&mx, &my, &buttons);
		if(mx>=150&&mx<=250&&my>=330&&my<=350&&buttons)
		{
			*p1=1;
			delay(100);
			return 7;
		}
		
			
		if(mx>=390&&mx<=490&&my>=330&&my<=350&&buttons)
	    {
		    *p1=2;
			delay(100);
		    return 7;
	    }

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
		      return 4;
	    }
		
    

}
}