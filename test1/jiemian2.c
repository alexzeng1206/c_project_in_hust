#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#include<bios.h>
#include "mouse1.h"
#include "zhuce2.h"
#include "denglu1.h"
#include "jiemian2.h"
#include "jiegouti.h"
#define PI 3.1415926
void jiazai()
{
	
	int i;
	settextstyle(1,0,5);
		setbkcolor(BLACK);
	cleardevice();
	setfillstyle(1,WHITE);
	bar(100,300,550,330);
	setfillstyle(1,RED);
	outtextxy(230,200,"Loading");
	for(i=0;i<450;i++)
	{
		bar(100+i,300,101+i,330);
		delay(10);
	}
	
		
	
}
int jiemian1()
{
	char temp;
	int buttons, mx, my; 
	//jiazai();
	setcolor(BLUE);
 setbkcolor(CYAN);
	cleardevice();
//rectangle(0,0,640,480);
 setfillstyle(1,BROWN);
bar(150,300,250,350);
 bar(390,300,490,350);
 settextstyle(3,0,7);
 outtextxy(200,150,"welcome");
 settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
 outtextxy(162,308,"Register");
 outtextxy(410,308,"Log In");
 outtextxy(500,5,"Quit");
 //settextstyle(1,HORIZ_DIR,1);
	mouseInit(&mx, &my,&buttons);

	while (1)
	{
		newxy(&mx, &my, &buttons);
		if(kbhit()!=0)
		{
			temp=getkey();
		}
		if(mx>=390&&mx<=490&&my>=300&&my<=350&&buttons)
		{
			return 3;

		}
		if(mx>=150&&mx<=250&&my>=300&&my<=350&&buttons)
		{
			return 2;

		}

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	{
		cleardevice();
		delay(100);
		exit(0);
	}
		}
}
