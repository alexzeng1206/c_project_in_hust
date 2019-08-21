#include "mytype.h"
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <bios.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#define MYMACRO extern
#include "common.h"
void carRace(int*x)
{
	setint9();
	Game_Init();
	displayinf0();
	do
	{
		*x=Game_Main();
		mydelay(dly);
	} while (!(cmd & CMD_QUIT));
	//恢复原键盘中断处理程序
	recoverint9();
}
void Game_Init()
{
	GlobalInit();
	roadinit();
	start=clock();
	finish=start;
	sumpathauto=getlooplen(autoroad[pathno]);//计算自动行驶小车路线周长
	displayinf();
	setcamera(mypos,myangpos);//根据汽车位置设相机参数
	toushitu();
}
int Game_Main()
{
	int x;
	x=getkey();
	autoruncar(autoroad[pathno]);
	drivecar();
	proccarcollide();
	
	setcamera(mypos,myangpos);//根据汽车位置设相机参数
	clearclient();
	//pingmiantu();
	toushitu();
	if(itext==0) displayinf();
	judgetoendline();
	itext++;
	itext%=4;//每4帧变零
	return x;
}
//清屏
void clearclient()
{
	setfillstyle(SOLID_FILL,LIGHTCYAN);
	setcolor(LIGHTCYAN);
	bar(scrW-scrH,0,scrW,scrH/2-1);//动画区天空清屏

	setfillstyle(SOLID_FILL,GREEN);
	setcolor(GREEN);
	bar(0,scrH/2,scrW,scrH);//动画区地面清屏

	if(itext==0)
	{
		setfillstyle(SOLID_FILL,LIGHTCYAN);
		setcolor(LIGHTCYAN);
		bar(startclr,0,scrW-scrH-1,scrH/2-1);//动态数字区清屏
	}
	else
	{
		//动态数字区靠尾20像素区清屏
		setfillstyle(SOLID_FILL,LIGHTCYAN);
		setcolor(LIGHTCYAN);
		bar(140,0,159,239);
	}

	setfillstyle(SOLID_FILL,WHITE);//恢复为白色
	setcolor(WHITE);
}//延迟，clock函数的时间单位，对8086是1000/18.2=55ms
void mydelay(clock_t td)
{
	clock_t start1;
	start1=clock();
	while(clock()<start1+td);
}
double getlooplen(ROADAREA ra[])
{
	int i;
	double sum=0;
	LINE line1;
	ARC arc1;
	for (i = 0;i < 2*segs;i++)
	{
		if (strcmp(ra[i].type, "line") == 0)
		{
			line1=*(PLINE)(ra[i].pcurve);
			sum+=pp_dist(line1.p1,line1.p2);
		}
		else
		{
			arc1=*(PARC)(ra[i].pcurve);
			sum+=arc1.r*arc1.dang;
		}
	}
	return sum;
}
