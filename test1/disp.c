//�Զ���ͷ�ļ�
#include "mytype.h"

//C����ʱͷ�ļ�
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <bios.h>
#include <string.h>
#include <dos.h>
#include <math.h>

//�Զ���ͷ�ļ�
#define MYMACRO extern
#include "common.h"

//����Ļ��ʾ��̬����
void displayinf()
{
	char str[30];
	int i;
	static double sumdrive_t,sumauto_t,v_t,vauto_t;
	finish=clock();
	sumdrive_t=sumdrive;
	sumauto_t=sumauto;
	v_t=v;
	vauto_t=vauto;
	duration=(finish-start)/CLOCKS_PER_SEC;

	setcolor(RED);

	i=1;
	sprintf(str,"%6.0f",sumdrive_t);
	outtextxy(startclr,(i++)*16,str);

	sprintf(str,"%6.0f",sumauto_t);
	outtextxy(startclr,(i++)*16,str);

	sprintf(str,"%6.1f",v_t);
	outtextxy(startclr,(i++)*16,str);

	sprintf(str,"%6.1f",vauto_t);
	outtextxy(startclr,(i++)*16,str);

	sprintf(str,"%6.0f",duration);
	outtextxy(startclr,(i++)*16,str);
	if(geartype==STICK)
	{
		sprintf(str,"%6d",myshift);
		outtextxy(startclr,(i++)*16,str);
	}
	setcolor(WHITE);

}
//����Ļ�����ʾ������ı�
void displayinf0()
{
	char str[30];
	int i;
	static double sumdrive_t,sumauto_t,v_t,vauto_t;
	finish=clock();
	sumdrive_t=sumdrive;
	sumauto_t=sumauto;
	v_t=v;
	vauto_t=vauto;
	duration=(finish-start)/CLOCKS_PER_SEC;

	setfillstyle(SOLID_FILL,LIGHTCYAN);
	setcolor(LIGHTCYAN);
	bar(0,0,(scrW-scrH)/2,scrH/2);//��̬����������

	setcolor(RED);
	i=1;
	outtextxy(0,(i++)*16,"me(m):");

	outtextxy(0,(i++)*16,"auto(m):");

	outtextxy(0,(i++)*16,"me(m/s):");

	outtextxy(0,(i++)*16,"auto(m/s):");

	outtextxy(0,(i++)*16,"time(s):");

	if(geartype==STICK) outtextxy(0,(i++)*16,"me stick:");
	setfillstyle(SOLID_FILL,WHITE);//�ָ�Ϊ��ɫ
	setcolor(WHITE);

}