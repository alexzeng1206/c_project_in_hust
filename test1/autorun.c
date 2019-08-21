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

//自动在路线上跑
void autoruncar(ROADAREA ra[])
{
	MYPOINT p1,p2;
	double len;
	int frompos;
	double xingshi,jixu;
	get_automatic_vlen(&vauto,vautomax,1,&len);
	//saveautoold();
	p1=pos;
	xingshi=len;
	frompos=1;//从当前位置
	nopos=whereroadarea(ra,pos,2*roadW);
	if(strcmp(ra[nopos].type,"line")==0)
		jixu=runline(ra,xingshi,frompos);
	else
		jixu=runarc(ra,xingshi,frompos);
	while(jixu>0)
	{
		nopos++;
		nopos%=2*segs;
		xingshi=jixu;
		frompos=0;//从段的开始点
		if(strcmp(ra[nopos].type,"line")==0)
			jixu=runline(ra,xingshi,frompos);
		else
			jixu=runarc(ra,xingshi,frompos);
	}
	p2=pos;
	offsetauto=jicheng(p1,p2,&sumauto);
}
//计算自动档时，一步路程和下一步小车速度
void get_automatic_vlen(double *vcur,double vmax,double throttle,double *len)
{
	double vloc=*vcur;
	double a;
	double timesec=tick/1000;
	double rollResist;
	double drag;
	double fraction;
	double F;
	double gearRatio;


	//根据速度确定档位
	if(vloc<=10)
		gearRatio=gear[1];
	else
		gearRatio=gear[2];
	if(vloc>vmax && throttle==1)//若超速且有油门，加速度设为-1
	{
		a=-1;
	}
	else
	{
		//计算摩擦阻力
		rollResist=Crr*weight*g;
		//计算风阻
		drag=0.5*rou*areaying*Cd*vloc*vloc;
		//计算牵引力
		fraction=throttle*torque*gearRatio*masterRatio*eta/rwheel;
		//计算合力
		F=fraction-rollResist-drag;
		//计算加速度
		a=F/weight;
	}
	*len=vloc*timesec+0.5*a*timesec*timesec;//行驶一步路程
	*vcur+=a*timesec;//本步结束时的速度
	if(throttle>0)//有油门
	{
		if(a<0)//超速，不能低于最高速度
		{
			if(*vcur<vmax)
				*vcur=vmax;
		}
		else//正常，不能高于最高速度
		{
			if(*vcur>vmax)
				*vcur=vmax;
		}
	}
	else//无油门
	{
		if(*vcur<0)
			*vcur=0;
	}
}
int whereroadarea(ROADAREA ra[], MYPOINT p1,double offset)
{
	int i,no=-1;
	LINE line1;
	ARC arc1;
	for (i = 0;i < 2*segs;i++)
	{
		if (strcmp(ra[i].type, "line") == 0)
		{
			line1=*(PLINE)(ra[i].pcurve);
			if(isAtLineRegion(line1,p1,offset)==1)
			{
				no=i;
				break;
			}
		}
		else
		{
			arc1=*(PARC)(ra[i].pcurve);
			if(isAtArcRegion(arc1,p1,offset)==1)
			{
				no=i;
				break;
			}
		}
	}
	return no;
}
//在直线段跑
double runline(ROADAREA ra[],double xingshi,int frompos)
{
	LINE line1;
	double ang,toEnd,jixu;
	MYPOINT p11,p21,pos0,pos1;
	line1=*(PLINE)(ra[nopos].pcurve);
	if(frompos==1)//从当前位置
		pos0=pos;
	else//从段的起点
		pos0=line1.p1;
	ang=pp_angle(line1.p1,line1.p2);
	x2xp(line1.p1,ang,line1.p1,&p11);
	x2xp(line1.p1,ang,line1.p2,&p21);
	x2xp(line1.p1,ang,pos0,&pos1);
	pos1.y=0;
	toEnd=p21.x-pos1.x;
	jixu=xingshi-toEnd;
	if(jixu<=0)//未出本段
	{
		pos1.x+=xingshi;
		pos1.y=0;
		xp2x(line1.p1,ang,pos1,&pos);
		angpos=ang-pi/2;
	}
	return jixu;
}
//在弧线跑
double runarc(ROADAREA ra[],double xingshi,int frompos)
{
	ARC arc1;
	double toEnd,jixu,angpos0;
	arc1=*(PARC)(ra[nopos].pcurve);
	if(frompos==1)//从当前位置
		angpos0=angpos;
	else//从段的起点
		angpos0=arc1.angstart;
	toEnd=arc1.dang-stdangle0(angpos0-arc1.angstart);
	xingshi/=arc1.r;//转换为角度
	jixu=(xingshi-toEnd)*arc1.r;//继续的距离
	if(jixu<=0)//未出本段
	{
		angpos+=xingshi;
		pos=getarcpnt(arc1,angpos);
	}
	return jixu;
}
//计算对应中间自动行驶路线的路程，返回与该路线的偏离值
double jicheng(MYPOINT p1, MYPOINT p2, double *sum)
{
	LINE line1;
	ARC arc1;
	int no1,no2;
	double lenstart1,lenend1;
	double lenstart2,lenend2;
	double ang;
	MYPOINT p21,pp;
	double angp,ange;
	MYPOINT o;
	double offset;
	no1=whereroadarea(autoroad[1],p1,2*roadW);
	if (strcmp(autoroad[1][no1].type, "line") == 0)
	{
		line1=*(PLINE)(autoroad[1][no1].pcurve);
		ang=pp_angle(line1.p1,line1.p2);
		x2xp(line1.p1,ang,line1.p2,&p21);
		x2xp(line1.p1,ang,p1,&pp);
		lenstart1=pp.x;
		lenend1=p21.x-pp.x;
	}
	else
	{
		arc1=*(PARC)(autoroad[1][no1].pcurve);
		o=arc_o(arc1);
		angp=stdangle0(pp_angle(o,p1)-arc1.angstart);
		ange=arc1.dang;
		lenstart1=arc1.r*angp;
		lenend1=arc1.r*(ange-angp);
	}
	no2=whereroadarea(autoroad[1],p2,2*roadW);
	if (strcmp(autoroad[1][no2].type, "line") == 0)
	{
		line1=*(PLINE)(autoroad[1][no2].pcurve);
		ang=pp_angle(line1.p1,line1.p2);
		x2xp(line1.p1,ang,line1.p2,&p21);
		x2xp(line1.p1,ang,p2,&pp);
		lenstart2=pp.x;
		lenend2=p21.x-pp.x;
		offset=pp.y;
	}
	else
	{
		arc1=*(PARC)(autoroad[1][no2].pcurve);
		o=arc_o(arc1);
		angp=stdangle0(pp_angle(o,p2)-arc1.angstart);
		ange=arc1.dang;
		lenstart2=arc1.r*angp;
		lenend2=arc1.r*(ange-angp);
		offset=pp_dist(o,p2)-arc1.r;
	}
	if(no1!=no2)//不在同一段
	{
		if (no1 == 2*segs-1 && no2 == 0)
		{
			no2=2*segs;
		}
		else if (no1 == 0 && no2 == 2*segs-1)
		{
			no2=-1;
		}
		if (no2 > no1)//前进
		{
			*sum+=lenend1+lenstart2;
		}
		else//后退
		{
			*sum-=(lenstart1+lenend2);
		}
	}
	else//在同一段
	{
		*sum+=lenstart2-lenstart1;
	}
	return offset;
}
