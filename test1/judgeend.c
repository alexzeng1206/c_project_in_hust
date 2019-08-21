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

void judgetoendline()
{
	char str[50];
	double time1=(clock()-start)/CLOCKS_PER_SEC;

	setcolor(RED);
	if(sumdrive/sumpathauto>=1)
	{
		timeme=time1;
		if(sumdrive>=sumauto)
		{
			sprintf(str,"No1,%6.1fs:me",timeme);
			//outtextxy(160,4*16,str);
			outtextxy(0,10*16,str);
			timeauto=timeme+(sumpathauto-sumauto)/vauto;
			sprintf(str,"No2,%6.1fs:auto",timeauto);
			//outtextxy(160+1*240,4*16,str);
			outtextxy(0,11*16,str);
		}
		else
		{
			sprintf(str,"No1,%6.1fs:auto",timeauto);
			//outtextxy(160,4*16,str);
			outtextxy(0,10*16,str);
			sprintf(str,"No2,%6.1fs:me",timeme);
			//outtextxy(160+1*240,4*16,str);
			outtextxy(0,11*16,str);
		}
		cmd |= CMD_QUIT;
	}
	else
	{
		if (sumauto / sumpathauto <= 1)
		{
			timeauto=(finish-start)/CLOCKS_PER_SEC;
		}
	}
		setcolor(WHITE);
}