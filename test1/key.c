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
	//����
	if (cmd & CMD_UP)
	{
		throttledrive=1;
	}
	if (cmd&CMD_DOWN)
	{
		throttledrive=-1;
	}
	//���¡��ɿ��ո����trigΪ1���򻻵�
	if ((trig & OLD_SPACE)==1)
	{
		trig &=(~OLD_SPACE);//��Ϊ�ɿ���ʱ��ȶ�����ʱ�䳤����Ҫtrig����
		myshift++;
		if(myshift>2)
			myshift=2;
	}
	//��z����
	if ((trig&OLD_Z) == OLD_Z)
	{
		trig &=(~OLD_Z);
		myshift--;
		if(myshift<0)
			myshift=0;
	}
	return 0;
}
//���ؼ��̰���״̬
int GetCommand()
{
  return keystate;
}

//�����жϴ������
void interrupt newint9()
{
	unsigned char scan_code,PB;
	//�������ж�
	asm sti
	//ȡɨ����
	scan_code=inportb(0x60);
	if(scan_code & 0x80)//���ɿ����������λΪ1��
		switch(scan_code & 0x7F)//��7λ
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
				oldstate &=(~OLD_SPACE);//�ո�ǰһ״̬����
				break;
			case SCAN_Z:
				oldstate &=(~OLD_Z);//Zǰһ״̬����
				break;
			case SCAN_ESCAPE:
				keystate &=(~CMD_QUIT);
				break;
		}
	else//�ǰ��°���
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
				if((oldstate & OLD_SPACE) == 0)//ǰһ״̬���ɿ����򴥷�
				{
					trig |= OLD_SPACE;//�ո񴥷�λ��1
					oldstate |= OLD_SPACE;//�ո�ǰһ״̬��1
				}
				else
					trig &= (~OLD_SPACE);//�ո񴥷�λ����
				break;
			case SCAN_Z:
				if((oldstate & OLD_Z) == 0)//ǰһ״̬���ɿ����򴥷�
				{
					trig |= OLD_Z;//Z����λ��2
					oldstate |= OLD_Z;//Zǰһ״̬��2
				}
				else
					trig &= (~OLD_Z);//Z����λ����
				break;
			case SCAN_ESCAPE:
				keystate |=CMD_QUIT;
				break;
		}
	//��EOI
	outportb(0x20,0x20);
}
//���¼����ж�
void setint9()
{
	oldint9=getvect(9);
	setvect(9,newint9);
}
//�ظ�ԭ�����ж�
void recoverint9()
{
	setvect(9,oldint9);
}
