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

void proccarcollide()
{
	double vtemp;
	if (carcollide() == 1)//������ײ�������ٶȽ���������ǰ���ٶȼ�10�����ٶȼ�10
	{
		
		if(sumauto>sumdrive)//�Զ���ʻС����ǰ���ٶȽ���
		{
			vtemp=vauto;
			vauto=v+10;
			v=vtemp-10;
			if(v<0)
				v=0;
		}
		else//������ʻС����ǰ���ٶȽ���
		{
			vtemp=v;
			v=vauto+5;
			vauto=vtemp-5;
			if(vauto<0)
				vauto=0;
		}
	}
}
int carcollide()
{
	MYPOINT pp[4];
	int i,collide=0;
	//ת��ȫ�����꣬��ת��������ʻ��������
	for (i = 0;i < 4;i++)
	{
		xp2x(pos,angpos,pcar[i],&pp[i]);
		x2xp(mypos,myangpos,pp[i],&pp[i]);
		if(GEANDLE(-carHW,pp[i].x,carHW,1e-6))
			if (GEANDLE(-carL, pp[i].y, 0,1e-6))
			{
				collide=1;
				break;
			}
	}
	return collide;
}