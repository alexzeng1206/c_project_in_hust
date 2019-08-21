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
#include "xuanche.h"
int cartype(user *head,char *p0,int *p2,int *p3)
{
	char *type[3];
	char *num[3];
//	void *buffer;
	int buttons, mx, my;
	int flag1=1,flag2=0,flag3=0;
	//int size;	 
setcolor(CYAN);
 outtextxy(402,295,"triangle");
 cleardevice();
 setcolor(BLUE);
 setbkcolor(CYAN);
 setfillstyle(1,LIGHTGRAY);
	mouseInit(&mx, &my,&buttons);
 //size=imagesize(0,120,220,420);
 //buffer=malloc(size);
 //getimage(120,120,220,420,buffer);
	tiqu(head,p0,num,type);
	settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
	draw(flag1,flag2,flag3);
	
	while(1)
	{
		newxy(&mx, &my, &buttons);
		if(mx>=140&&mx<=215&&my>=140&&my<=160&&buttons)
		{
			    //putimage(120,120,buffer,COPY_PUT);
			    draw(1,flag2,flag3);
                rectangle(10,80,125,180);
                *p2=1;
                flag3=1;

			}
		
			
		 if(mx>=140&&mx<=215&&my>=260&&my<=280&&buttons)
	    {
		     if(strcmp(type,"B")==0||strcmp(type,"D")==0)
		     {
		     	//putimage(120,120,buffer,COPY_PUT);
		     	draw(1,flag2,flag3);
                rectangle(10,200,125,300);
                *p2=2;
                flag3=2;
		     }
		    else
		    {
		    	flag3=0;
		    	draw(1,flag2,flag3);
		    	outtextxy(180,200,"you don't have this car");
		    }
	    }

		 if(mx>=140&&mx<=215&&my>=380&&my<=400&&buttons)
	    {
		      if(strcmp(type,"C")==0||strcmp(type,"D")==0)
		      {
		      	//putimage(120,120,buffer,COPY_PUT);
		      	draw(1,flag2,flag3);
                rectangle(10,320,125,410);
                *p2=3;
                flag3=3;
		      }
		      else
		      {
		      	flag3=0;
		      	draw(1,flag2,flag3);
		      	outtextxy(180,200,"you don't have this car");
		      }
	    }
	    if(mx>=480&&mx<=640&&my>=140&&my<=180&&buttons)
	    {
	    		draw(2,flag2,flag3);
	    		rectangle(470,120,640,200);
	    		*p3=1;
	    	flag2=1;

	    }
	     if(mx>=480&&mx<=640&&my>=280&&my<=320&&buttons)
	    {
	    		draw(2,flag2,flag3);
	    		    rectangle(470,260,640,340);

	    	*p3=2;
	    	flag2=2;
	    }
	    if(mx>=480&&mx<=640&&my>=400&&my<=480&&buttons)
	    {
			if(flag2==0||flag3==0)
			{
				outtextxy(180,200,"you need to choose the type");
			}
	    	else return 8;
	    }
		
    }


		

}
/////////////////////////////////////////////////////////////////////
//draw函数说明：                                                   //
//       取值     0           1                 2            3     //    
//参数：flag1     无    选车时flag1=1     选档时flag1=2      无    //
//      flag2   未选挡   已选自动挡       已选手动挡         无    //
//      flag3   未选车   已选1车          已选2车          已选3车 //  
//                                                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void draw(int flag1, int flag2,int flag3)
{
	

    if(flag1==1)
    {
    	if(flag2==0)
    	{
    drawback();
    	}
    	else if(flag2==1)
    	{
    drawback();
    rectangle(470,120,640,200);
    	}
    		else 
    		{
    		drawback();
    rectangle(470,260,640,340);
    		}
    	}

    else if(flag1=2)
    {
    	if(flag3==0)
    	{
    drawback();
    	}
    		else if(flag3==1)
    		{
    drawback();
    rectangle(10,80,125,180);
    		}
    			else if(flag3==2)
    			{
    		drawback();
    rectangle(10,200,125,300);

    			}
    				else
    				{
    					drawback();
    rectangle(10,320,125,410);
    				}
    			
    		
    	
    }
}
////////////////////////////////////////
//函数drawback：画出基础界面（包括车）
////////////////////////////////////
void drawback()
{
	int a1[]={15,140,15,130,25,120,50,120,70,100,100,100,120,120,120,140,15,140};
	int a2[]={15,260,15,250,25,240,50,240,70,220,100,220,120,240,120,260,15,260};
	int a3[]={15,380,15,370,25,360,50,360,70,340,100,340,120,360,120,380,15,380};
	cleardevice();
//////////////////////
//画背景框和文字信息
 setcolor(BLUE);
 setbkcolor(CYAN);
 setfillstyle(1,LIGHTGRAY);
	settextstyle(SANS_SERIF_FONT  ,HORIZ_DIR,3);
	bar(140,140,215,160);
	bar(140,260,215,280);
	bar(140,380,215,400);
	bar(480,140,640,180);
	bar(480,280,640,320);
	bar(480,400,640,480);
	outtextxy(142,135,"choose");
	outtextxy(142,255,"choose");
	outtextxy(142,375,"choose");
	outtextxy(482,135,"automatic");
	outtextxy(482,275,"manual");
	outtextxy(482,395,"start game");
//////////////////////////////////////////
//画红车	
		setcolor(DARKGRAY);
	drawpoly(9,a1);
	arc(45,140,180,360,10);
	arc(100,140,180,360,10);
	setfillstyle(1,RED);
	floodfill(40,130,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(45,146,DARKGRAY);
    floodfill(100,146,DARKGRAY);
/////////////////////////////////////////
//画黄车	
		setcolor(DARKGRAY);
	drawpoly(9,a2);
	arc(45,260,180,360,10);
	arc(100,260,180,360,10);
	setfillstyle(1,YELLOW);
	floodfill(40,250,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(45,266,DARKGRAY);
    floodfill(100,266,DARKGRAY);
////////////////////////////////////
//画蓝车		
		setcolor(DARKGRAY);
	drawpoly(9,a3);
	arc(45,380,180,360,10);
	arc(100,380,180,360,10);
	setfillstyle(1,BLUE);
	floodfill(40,370,DARKGRAY);
	setfillstyle(1,DARKGRAY);
   floodfill(45,386,DARKGRAY);
    floodfill(100,386,DARKGRAY);
		setcolor(BLUE);
}
