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

//������ڳ���3m��
void setcamera(MYPOINT p1,double ang)
{
	angsight=ang;
	pntsight.x=p1.x+(yminsight+carL+3)*cos(angsight-pi/2);
	pntsight.y=p1.y+(yminsight+carL+3)*sin(angsight-pi/2);
}
