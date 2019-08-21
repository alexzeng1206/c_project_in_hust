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

int getkey()
{
	R=0;
	throttledrive=0;
	cmd = GetCommand();
	if (cmd & CMD_QUIT)
	{
		return 1;
	}
	if (cmd & CMD_LEFT)
	{
		R= -rdrive;
	}
	if (cmd & CMD_RIGHT)
	{
		R= rdrive;
	}
	//油门
	if (cmd & CMD_UP)
	{
		throttledrive=1;
	}
	if (cmd&CMD_DOWN)
	{
		throttledrive=-1;
	}
	//按下、松开空格键，trig为1，则换档
	if ((trig & OLD_SPACE)==1)
	{
		trig &=(~OLD_SPACE);//因为松开的时间比动画间时间长，需要trig清零
		myshift++;
		if(myshift>2)
			myshift=2;
	}
	//按z降档
	if ((trig&OLD_Z) == OLD_Z)
	{
		trig &=(~OLD_Z);
		myshift--;
		if(myshift<0)
			myshift=0;
	}
	return 0;
}
//返回键盘按下状态
int GetCommand()
{
  return keystate;
}

//键盘中断处理程序
void interrupt newint9()
{
	unsigned char scan_code,PB;
	//开屏蔽中断
	asm sti
	//取扫描码
	scan_code=inportb(0x60);
	if(scan_code & 0x80)//是松开按键（最高位为1）
		switch(scan_code & 0x7F)//低7位
		{
			case SCAN_LEFT:
				keystate &=(~CMD_LEFT);
				break;
			case SCAN_RIGHT:
				keystate &=(~CMD_RIGHT);
				break;
			case SCAN_UP:
				keystate &=(~CMD_UP);
				break;
			case SCAN_DOWN:
				keystate &=(~CMD_DOWN);
				break;
			case SCAN_SPACE:
				oldstate &=(~OLD_SPACE);//空格前一状态清零
				break;
			case SCAN_Z:
				oldstate &=(~OLD_Z);//Z前一状态清零
				break;
			case SCAN_ESCAPE:
				keystate &=(~CMD_QUIT);
				break;
		}
	else//是按下按键
		switch(scan_code)
		{
			case SCAN_LEFT:
				keystate |=CMD_LEFT;
				break;
			case SCAN_RIGHT:
				keystate |=CMD_RIGHT;
				break;
			case SCAN_UP:
				keystate |=CMD_UP;
				break;
			case SCAN_DOWN:
				keystate |=CMD_DOWN;
				break;
			case SCAN_SPACE:
				if((oldstate & OLD_SPACE) == 0)//前一状态是松开，则触发
				{
					trig |= OLD_SPACE;//空格触发位置1
					oldstate |= OLD_SPACE;//空格前一状态置1
				}
				else
					trig &= (~OLD_SPACE);//空格触发位清零
				break;
			case SCAN_Z:
				if((oldstate & OLD_Z) == 0)//前一状态是松开，则触发
				{
					trig |= OLD_Z;//Z触发位置2
					oldstate |= OLD_Z;//Z前一状态置2
				}
				else
					trig &= (~OLD_Z);//Z触发位清零
				break;
			case SCAN_ESCAPE:
				keystate |=CMD_QUIT;
				break;
		}
	//发EOI
	outportb(0x20,0x20);
}
//设新键盘中断
void setint9()
{
	oldint9=getvect(9);
	setvect(9,newint9);
}
//回复原键盘中断
void recoverint9()
{
	setvect(9,oldint9);
}
