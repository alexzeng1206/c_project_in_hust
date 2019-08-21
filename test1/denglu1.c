#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<bios.h>
#include "zhuce2.h"
#include "mouse1.h"
#include "caidan1.h"
#include "denglu1.h"
#include "jiegouti.h"
#include "jiemian2.h"

int loaddenglu(user *head,char *p0)
{
	void *buffer0;
	int size;
	int buttons, mx, my;
	int j=0;
	//char pname[10];
	char pkey[10];
int k=0;
char temp;
	FILE *fp;
  //	struct user a;
   //	struct user b[100];
char c[2]={'\0','\0'};
 int i=0;
 //int sum=0;
 cleardevice();
 setviewport(0,0,640,480,1);
 setcolor(BLUE);
 setbkcolor(CYAN);
// setlinestyle(2,0,3);
 setfillstyle(1,LIGHTGRAY);
 bar(150,330,250,350);
 bar(390,330,490,350);
 outtextxy(285,195,"Log In");
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
			inputkey(pkey);
			if(judge(head,p0,pkey))
			{
				//printf("666");
				outtextxy(10,10,"log in success");
				outtextxy(10,30,"press any key to continue");
				getch();
				//zhucaidan(head,pname);
				return 4;
			}
			else
				outtextxy(10,10,"wrong number");
			  outtextxy(10,30,"press any key to continue");
			    getch();
			return 3;
		}
		/*if(mx>=150&&mx<=250&&my>=300&&my<=350&&buttons)
		{
			inputkey();

		}*/

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	{
		return 1;
	}
		}

 }

