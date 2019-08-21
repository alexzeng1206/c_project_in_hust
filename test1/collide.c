//自定义头文件
#include "mytype.h"

//C运行时头文件
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <bios.h>
#include <string.h>
#include <dos.h>
#include <math.h>

//自定义头文件
#define MYMACRO extern
#include "common.h"

void proccarcollide()
{
	double vtemp;
	if (carcollide() == 1)//两车相撞，两车速度交换，并且前车速度加10，后车速度减10
	{
		
		if(sumauto>sumdrive)//自动行驶小车在前，速度较慢
		{
			vtemp=vauto;
			vauto=v+10;
			v=vtemp-10;
			if(v<0)
				v=0;
		}
		else//交互行驶小车在前，速度较慢
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
	//转到全局坐标，再转到交互驾驶汽车坐标
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