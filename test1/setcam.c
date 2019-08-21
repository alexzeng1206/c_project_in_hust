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

//让相机在车后3m处
void setcamera(MYPOINT p1,double ang)
{
	angsight=ang;
	pntsight.x=p1.x+(yminsight+carL+3)*cos(angsight-pi/2);
	pntsight.y=p1.y+(yminsight+carL+3)*sin(angsight-pi/2);
}
