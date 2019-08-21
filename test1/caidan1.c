#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#include<bios.h>
#include "mouse1.h"
#include "jiegouti.h"
#include "shop.h"
int zhucaidan(user *head, char *p0)
{
	int size;
	int buttons, mx, my;
	setcolor(YELLOW);
	setbkcolor(RED);
	settextstyle(1,0,3);   //必要的初始化
	setlinestyle(0,0,3);
	cleardevice();
	settextstyle(1,HORIZ_DIR,7);
	outtextxy(40,72,"Play");
	outtextxy(40,162,"Asset");
	outtextxy(40,245,"SHOP");
	outtextxy(40,400,"Quit");
	outtextxy(40,320,"Search");
	mouseInit(&mx, &my,&buttons);
	rectangle(37,85,170,155);
	rectangle(37,175,190,245);
	rectangle(35,258,196,320);
	rectangle(35,415,170,470);
	rectangle(35,335,242,395);
	while (1)
	{
		newxy(&mx, &my, &buttons);
		if(mx>=37&&mx<=170&&my>=85&&my<=155&&buttons)
		{
			//进入游戏
			return 6;

		}
		if(mx>=37&&mx<=190&&my>=175&&my<=245&&buttons)
		{
			//查看资产
			return 10;

		}
		if(mx>=35&&mx<=196&&my>=258&&my<=320&&buttons)
		{
		   	//返回main，进入商店
		   	return 5;

		}
		if(mx>=35&&mx<=170&&my>=415&&my<=470&&buttons)
		{
           // 退出游戏
		   delay(100);
		   cleardevice();
		   exit(0);
		}

		if(mx>=35&&mx<=242&&my>=335&&my<=395&&buttons)
	{
		// 返回main，进入查询
		return 9;
	}
		}
	
}