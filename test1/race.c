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
	//�ָ�ԭ�����жϴ������
	recoverint9();
}
void Game_Init()
{
	GlobalInit();
	roadinit();
	start=clock();
	finish=start;
	sumpathauto=getlooplen(autoroad[pathno]);//�����Զ���ʻС��·���ܳ�
	displayinf();
	setcamera(mypos,myangpos);//��������λ�����������
	toushitu();
}
int Game_Main()
{
	int x;
	x=getkey();
	autoruncar(autoroad[pathno]);
	drivecar();
	proccarcollide();
	
	setcamera(mypos,myangpos);//��������λ�����������
	clearclient();
	//pingmiantu();
	toushitu();
	if(itext==0) displayinf();
	judgetoendline();
	itext++;
	itext%=4;//ÿ4֡����
	return x;
}
//����
void clearclient()
{
	setfillstyle(SOLID_FILL,LIGHTCYAN);
	setcolor(LIGHTCYAN);
	bar(scrW-scrH,0,scrW,scrH/2-1);//�������������

	setfillstyle(SOLID_FILL,GREEN);
	setcolor(GREEN);
	bar(0,scrH/2,scrW,scrH);//��������������

	if(itext==0)
	{
		setfillstyle(SOLID_FILL,LIGHTCYAN);
		setcolor(LIGHTCYAN);
		bar(startclr,0,scrW-scrH-1,scrH/2-1);//��̬����������
	}
	else
	{
		//��̬��������β20����������
		setfillstyle(SOLID_FILL,LIGHTCYAN);
		setcolor(LIGHTCYAN);
		bar(140,0,159,239);
	}

	setfillstyle(SOLID_FILL,WHITE);//�ָ�Ϊ��ɫ
	setcolor(WHITE);
}//�ӳ٣�clock������ʱ�䵥λ����8086��1000/18.2=55ms
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
