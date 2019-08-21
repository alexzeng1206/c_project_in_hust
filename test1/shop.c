#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bios.h>
#include<graphics.h>
#include "jiegouti.h"
#include "yonghu.h"
#include "caidan1.h"
#include "shop.h"
#include "mouse1.h"
//////////////////////////////////
//int shop函数说明：
//该函数提取用户金币、车型等信息，根据信息加载不同界面
//用户完成购买后会回到此函数，是一个循环，继续根据修改后的数据再次加载商店
/////////////////////////////////
int shop(user *head,char *p0, int *p)
{
	char *type[3];
	char *num[3];
	int mark;
	tiqu(head,p0,num,type);
	settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
	if(strcmp(type,"A")==0&&(*p==0))
	{
		mark=loadshop1(head,p0,num,type);
	}
	else if(strcmp(type,"B")==0&&(*p==0))
	{
		mark=loadshop2(head,p0,num,type);
	}
		else if(strcmp(type,"C")==0&&(*p==0))
		{
			mark=loadshop3(head,p0,num,type);
		}
			else if(strcmp(type,"D")==0&&(*p==0))
			{
				mark=loadshop4(head,p0,num,type);
			}
			else if(strcmp(type,"A")==0&&(*p==1))
	{
		mark=loadshop5(head,p0,num,type,p);
	}
	else if(strcmp(type,"B")==0&&(*p==1))
	{
		mark=loadshop6(head,p0,num,type,p);
	}
	else if(strcmp(type,"C")==0&&(*p==1))
	{
		mark=loadshop7(head,p0,num,type,p);
	}
	else if(strcmp(type,"D")==0&&(*p==1))
	{
		mark=loadshop8(head,p0,num,type,p);
	}
			return mark;

    
}
/////////////////////////////////////////////////
//loadshop1函数说明：当玩家未购买过车且购买了燃油时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//
/////////////////////////////////////////////////
int loadshop1(user *head,char *p0,char *p1,char *p2)
{
	int buttons, mx, my;
	int n;
	int mb=3,mc=4;
	cleardevice();	
 setviewport(0,0,640,480,1);
 drawcar2();
 drawcar3();
  setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
 mouseInit(&mx, &my,&buttons);
 n=toshuzi(p1);
 
 	while (1)
	{
		
		newxy(&mx, &my, &buttons);
		if(mx>=150&&mx<=250&&my>=350&&my<=370&&buttons)
		{
			if(n>=mb)
			{
				changecar(head,p0,"B");
			    changecoin(head,p0,n-mb);
			    //outtextxy(192,125,"now you can use the yellow car");
			    //outtextxy(192,150,"press any key to continue");
				msgbox(1);
			   // getch();
			    return 5;
		    }
		    else 
		    {
			    //outtextxy(192,125,"your coin is not enough");
			    //getch();
				msgbox(0);
			    return 5;
		    }
		}
		
			
		if(mx>=390&&mx<=490&&my>=350&&my<=370&&buttons)
	    {
		     if(n>=mc)
			{
				changecar(head,p0,"C");
			    changecoin(head,p0,n-mc);
			    //outtextxy(192,125,"now you can use the blue car");
			    //outtextxy(192,150,"press any key to continue");
				msgbox(1);
			   // getch();
			    return 5;
		    }
		    else 
		    {
			   // outtextxy(192,125,"your coin is not enough");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(0);
			    return 5;
		    }
	    }

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
             //返回主菜单
		      return 4;
	    }
		
    }

}

/////////////////////////////////////////////////
//loadshop2函数说明：当玩家未购买过黄车且购买了燃油时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//
/////////////////////////////////////////////////
int loadshop2(user *head,char *p0,char *p1,char *p2)
{
	int buttons, mx, my;
	int n;
	int mc=4;
	cleardevice();	
 setviewport(0,0,640,480,1);
drawcar3();
   setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
 mouseInit(&mx, &my,&buttons);
 n=toshuzi(p1);
 while (1)
	{
		
		newxy(&mx, &my, &buttons);
		
		
			
		if(mx>=390&&mx<=490&&my>=350&&my<=370&&buttons)
	    {
		     if(n>=mc)
			{
				changecar(head,p0,"D");
			    changecoin(head,p0,n-mc);
			   // outtextxy(192,125,"now you can use the blue car");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(1);
			    return 4;
		    }
		    else 
		    {
			    //outtextxy(192,125,"your coin is not enough");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(0);
			    return 4;
		    }
	    }

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
		      
		      return 4;
	    }
		
    }
	
}

/////////////////////////////////////////////////
//loadshop3函数说明：当玩家未购买过蓝车且购买了燃油时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//
/////////////////////////////////////////////////
int loadshop3(user *head,char *p0,char *p1,char *p2)
{
	int buttons, mx, my;
	int n;
	int mb=3;
	cleardevice();	
 setviewport(0,0,640,480,1);
drawcar2();
 setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
 mouseInit(&mx, &my,&buttons);
 n=toshuzi(p1);
 
 	while (1)
	{
		
		newxy(&mx, &my, &buttons);
		if(mx>=150&&mx<=250&&my>=350&&my<=370&&buttons)
		{
			if(n>=mb)
			{
				changecar(head,p0,"D");
			    changecoin(head,p0,n-mb);
			   //outtextxy(192,125,"now you can use the yellow car");
			   //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(1);
			    return 4;
		    }
		    else 
		    {
			    //outtextxy(192,125,"your coin is not enough");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(0);
			    return 4;
		    }
		}
		
			
		

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
		     
		      return 4;
	    }
		
    }
}

/////////////////////////////////////////////////
//loadshop4函数说明：当玩家未购买过黄车和蓝车且购买了燃油时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//
/////////////////////////////////////////////////
int loadshop4(user *head,char *p0,char *p1,char *p2)
{
	int buttons, mx, my;
	mouseInit(&mx, &my,&buttons);
	cleardevice();
	setfillstyle(1,LIGHTGRAY);
	bar(170,180,470,250);
	rectangle(290,215,340,250);
	outtextxy(300,215,"OK");
	outtextxy(190,180,"you have bought all things");
	while(1)
	{
		newxy(&mx, &my, &buttons);
	if(mx>=290&&mx<=340&&my>=215&&my<=250&&buttons)
	{
		return 4;
	}
	}
}

/////////////////////////////////////////////////
//loadshop5函数说明：当玩家未购买过车和燃油时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//                      p实际代表从主函数传过来的一个标准，*p=0则玩家此次游戏已经购买了燃油，*p=1则还未购买
/////////////////////////////////////////////////
int loadshop5(user *head,char *p0,char *p1,char *p2,int *p)
{
	int buttons, mx, my;
	int n;
	int mb=3,mc=4;
	int mg=1;
	cleardevice();	
 setviewport(0,0,640,480,1);
 drawcar2();
 drawcar3();
 drawgas();
  setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
 mouseInit(&mx, &my,&buttons);
 n=toshuzi(p1);
 
 	while (1)
	{
		
		newxy(&mx, &my, &buttons);
		if(mx>=150&&mx<=250&&my>=350&&my<=370&&buttons)
		{
			if(n>=mb)
			{
				changecar(head,p0,"B");
			    changecoin(head,p0,n-mb);
			    //outtextxy(192,125,"now you can use the yellow car");
			    //outtextxy(192,150,"press any key to continue");
				msgbox(1);
			   // getch();
			    return 5;
		    }
		    else 
		    {
			    //outtextxy(192,125,"your coin is not enough");
			    //getch();
				msgbox(0);
			    return 5;
		    }
		}
		
			
		if(mx>=390&&mx<=490&&my>=350&&my<=370&&buttons)
	    {
		     if(n>=mc)
			{
				changecar(head,p0,"C");
			    changecoin(head,p0,n-mc);
			    //outtextxy(192,125,"now you can use the blue car");
			    //outtextxy(192,150,"press any key to continue");
				msgbox(1);
			   // getch();
			    return 5;
		    }
		    else 
		    {
			   // outtextxy(192,125,"your coin is not enough");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(0);
			    return 5;
		    }
	    }
		if(mx>=80&&mx<=160&&my>=140&&my<=180&&buttons)
	    {
			if(n>=mg)
			{
				changecoin(head,p0,n-mg);
				*p=0;
		     msgbox(1);
			 return 5;
			}
			else
			{
				msgbox(0);
		      return 5;
			}
	    }

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
             //返回主菜单
		      return 4;
	    }
		
    }

}

/////////////////////////////////////////////////
//loadshop6函数说明：当玩家只购买了黄车时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//                      p实际代表从主函数传过来的一个标准，*p=0则玩家此次游戏已经购买了燃油，*p=1则还未购买
/////////////////////////////////////////////////
int loadshop6(user *head,char *p0,char *p1,char *p2,int *p)
{
	int buttons, mx, my;
	int n;
	int mc=4;
	int mg=1;
	cleardevice();	
 setviewport(0,0,640,480,1);
drawcar3();
drawgas();
   setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
 mouseInit(&mx, &my,&buttons);
 n=toshuzi(p1);
 while (1)
	{
		
		newxy(&mx, &my, &buttons);
		
		
			
		if(mx>=390&&mx<=490&&my>=350&&my<=370&&buttons)
	    {
		     if(n>=mc)
			{
				changecar(head,p0,"D");
			    changecoin(head,p0,n-mc);
			   // outtextxy(192,125,"now you can use the blue car");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(1);
			    return 5;
		    }
		    else 
		    {
			    //outtextxy(192,125,"your coin is not enough");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(0);
			    return 5;
		    }
	    }
		if(mx>=80&&mx<=160&&my>=140&&my<=180&&buttons)
	    {
			if(n>=mg)
			{
				changecoin(head,p0,n-mg);
				*p=0;
		     msgbox(1);
			 return 5;
			}
			else
			{
				msgbox(0);
		      return 5;
			}
	    }

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
		      
		      return 4;
	    }
		
    }
	
}

/////////////////////////////////////////////////
//loadshop7函数说明：当玩家只购买了蓝车时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//                      p实际代表从主函数传过来的一个标准，*p=0则玩家此次游戏已经购买了燃油，*p=1则还未购买
/////////////////////////////////////////////////
int loadshop7(user *head,char *p0,char *p1,char *p2,int *p)
{
	int buttons, mx, my;
	int n;
	int mb=3;
	int mg=1;
	cleardevice();	
 setviewport(0,0,640,480,1);
drawcar2();
drawgas();
 setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
 mouseInit(&mx, &my,&buttons);
 n=toshuzi(p1);
 
 	while (1)
	{
		
		newxy(&mx, &my, &buttons);
		if(mx>=150&&mx<=250&&my>=350&&my<=370&&buttons)
		{
			if(n>=mb)
			{
				changecar(head,p0,"D");
			    changecoin(head,p0,n-mb);
			   //outtextxy(192,125,"now you can use the yellow car");
			   //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(1);
			    return 5;
		    }
		    else 
		    {
			    //outtextxy(192,125,"your coin is not enough");
			    //outtextxy(192,150,"press any key to continue");
			    //getch();
				msgbox(0);
			    return 5;
		    }
		}
		if(mx>=80&&mx<=160&&my>=140&&my<=180&&buttons)
	    {
			if(n>=mg)
			{
				changecoin(head,p0,n-mg);
				*p=0;
		     msgbox(1);
			 return 5;
			}
			else
			{
				msgbox(0);
		      return 5;
			}
	    }
			
		

		if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	    {
		     
		      return 4;
	    }
		
    }
}

/////////////////////////////////////////////////
//loadshop8函数说明：当玩家只有燃油未购买时加载的界面及一些后台操作
//参数：p0该玩家用户名  p1为该玩家持有的金币数，但此时为字符串形式
//                      p2为该玩家持有的车
//                      p实际代表从主函数传过来的一个标准，*p=0则玩家此次游戏已经购买了燃油，*p=1则还未购买
/////////////////////////////////////////////////
int loadshop8(user *head,char *p0,char *p1,char *p2, int *p )
{
	int buttons, mx, my;
	int mg=1;
	int n;
	n=toshuzi(p1);
	mouseInit(&mx, &my,&buttons);
	cleardevice();
	drawgas();
	setfillstyle(1,BROWN);
  bar(0,0,640,40);
  settextstyle(1,0,3);
  outtextxy(500,5,"Back");
  outtextxy(55,5,"coin");
  outtextxy(120,5,p1);
	while(1)
	{
		newxy(&mx, &my, &buttons);
		if(mx>=80&&mx<=160&&my>=140&&my<=180&&buttons)
	    {
			if(n>=mg)
			{
				changecoin(head,p0,n-mg);
				*p=0;
		     msgbox(1);
			 return 4;
			}
			else
			{
				msgbox(0);
		      return 4;
			}
	    }
	if(mx>=495&&mx<=545&&my>=12&&my<=33&&buttons)
	{
		return 4;
	}
	}
}

/////////////////////////////////////////////////
//void drawcar3函数用于画蓝车和它的一些相关信息的背景
/////////////////////////////////////////////////
void drawcar3()
{
	int a1[]={415,290,415,280,425,270,450,270,470,250,500,250,520,270,520,290,415,290};
	setcolor(BLUE);
 setbkcolor(CYAN);
////////////////////////////
//画速度条
 setfillstyle(1,WHITE);
 settextstyle(3,0,1);
 outtextxy(380,322,"Speed");
 bar(430,330,535,342);
 setfillstyle(1,RED);
 bar(430,330,520,342);
////////////////////////////
//画按钮与信息
 setfillstyle(1,LIGHTGRAY);
	bar(390,350,525,370);
	settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
	outtextxy(530,345,"$4");
 outtextxy(392,345,"Click To Buy");
  outtextxy(420,295,"Blue Car");
/////////////////////////////////
//画蓝车
		setcolor(DARKGRAY);
	drawpoly(9,a1);
	arc(445,290,180,360,10);
	arc(500,290,180,360,10);
	setfillstyle(1,BLUE);
	floodfill(440,280,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(445,296,DARKGRAY);
    floodfill(500,296,DARKGRAY);
	setcolor(BLUE);
}
/////////////////////////////////////////////////
//void drawcar2函数用于画黄车和它的一些相关信息的背景
/////////////////////////////////////////////////
void drawcar2()
{
	int a1[]={165,290,165,280,175,270,200,270,220,250,250,250,270,270,270,290,165,290};
	 setcolor(BLUE);
 setbkcolor(CYAN);
 ////////////////////////////
//画速度条
 setfillstyle(1,WHITE);
 settextstyle(3,0,1);
 outtextxy(130,322,"Speed");
 bar(180,330,285,342);
 setfillstyle(1,RED);
 bar(180,330,245,342);
////////////////////////////
//画按钮与信息
settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
 setfillstyle(1,LIGHTGRAY);
	bar(140,350,275,370);
	outtextxy(280,345,"$3");
 outtextxy(142,345,"Click To Buy");
 outtextxy(152,295,"Yellow Car");
/////////////////////////
//画黄车
		setcolor(DARKGRAY);
	drawpoly(9,a1);
	arc(195,290,180,360,10);
	arc(250,290,180,360,10);
	setfillstyle(1,YELLOW);
	floodfill(190,280,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(195,296,DARKGRAY);
    floodfill(250,296,DARKGRAY);
	setcolor(BLUE);
}

///////////////////////////////////////////
//void msgbox函数用来画弹出的提示框
//         n=1代表购买成功提示，n=0代表购买失败提示
///////////////////////////////////////////////
void msgbox(int n)
{
	int buttons, mx, my;
	setfillstyle(1,LIGHTGRAY);
	bar(200,100,400,300);
	setlinestyle(0,0,3);
	rectangle(200,100,400,300);
	rectangle(280,270,320,300);
		outtextxy(285,270,"ok");
		//setlinestyle(1,0,1);
		if(n==1)
		{
		outtextxy(250,150,"Success!");
		}
		else
		{
			settextstyle(3,0,1);
			outtextxy(220,150,"Coin is not enough");
			settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
		}
		 setfillstyle(1,BROWN);
		 mouseInit(&mx, &my,&buttons);
		 while(1)
	   {
		   newxy(&mx, &my, &buttons);
		 	
		if(mx>=280&&mx<=320&&my>=270&&my<=300&&buttons)
		{
			break;
		}
	}
}

//////////////////////////////////////////////////////////////
//void drawgas函数：用来画燃油的和有关信息
/////////////////////////////////////////////////////////////
void drawgas()
{
	int a1[ ]={160,180,260,180,260,50,240,50,220,70,190,70,160,80,160,180};
	setcolor(BROWN);
	setfillstyle(1,RED);
	drawpoly(8,a1);
	floodfill(180,120,BROWN);
	setcolor(BROWN);
	setlinestyle(0,0,3);
	line(196,70,210,48);
	line(210,48,234,48);
	setcolor(BLUE);
	setfillstyle(1,BROWN);
	rectangle(80,160,140,180);
	outtextxy(50,152,"$1");
	outtextxy(95,152,"Buy");
	outtextxy(55,127,"speed+");
}
