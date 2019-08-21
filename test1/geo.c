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

//几何计算函数
//计算直线线段与线段的交点
void line_intersection(MYPOINT p1, MYPOINT p2, MYPOINT p3, MYPOINT  p4, int *count, MYPOINT pout[])
{
	MYPOINT p11 = { 0,0 }, p21, p31, p41, pout1[4], ptemp;
	double dx, dy, a;
	int n = 0;
	int	i, j;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	a = atan2(dy, dx);
	//a = a / pi * 180;
	x2xp(p1, a, p2, &p21);
	if (fabs(p21.y) < 1e-6) p21.y = 0;//y坐标很接近0时，调整为0
	x2xp(p1, a, p3, &p31);
	if (fabs(p31.y) < 1e-6) p31.y = 0;//y坐标很接近0时，调整为0
	x2xp(p1, a, p4, &p41);
	if (fabs(p41.y) < 1e-6) p41.y = 0;//y坐标很接近0时，调整为0

	if (fabs(p31.y) < 1e-6 && fabs(p41.y) < 1e-6)//p3、p4都在直线p1p2上
	{
		MYPOINT temp;
		if (p31.x > p41.x)
		{
			temp = p31;
			p31 = p41;
			p41 = temp;
		}
		if (p31.x >= p11.x && p31.x <= p21.x)
		{
			pout1[n] = p31;
			n++;
		}
		if (p41.x >= p11.x && p41.x <= p21.x)
		{
			pout1[n] = p41;
			n++;
		}
		if (p21.x > p31.x && p21.x <p41.x)
		{
			pout1[n] = p21;
			n++;
		}
		if (p11.x > p31.x && p11.x <p41.x)
		{
			pout1[n] = p11;
			n++;
		}
		if (n == 2)
		{
			if (fabs(pout1[0].x - pout1[1].x)<1e-6) n = 1;
		}
		else if (n >= 3)
		{
			for (i = 1;i < n;i++)
			{
				for (j = 0;j < n - i;j++)
				{
					if (pout1[j].x > pout1[j + 1].x)
					{
						ptemp = pout1[j];
						pout1[j] = pout1[j + 1];
						pout1[j + 1] = ptemp;
					}
				}
			}
			pout1[1] = pout1[n - 1];
			n = 2;
		}
	}
	else if (fabs(p31.y) < 1e-6)//仅p3在直线p1p2上
	{
		if (p31.x >= p11.x && p31.x <= p21.x)
		{
			pout1[0] = p31;
			n = 1;
		}
	}
	else if (fabs(p41.y) < 1e-6)//仅p4在直线p1p2上
	{
		if (p41.x >= p11.x && p41.x <= p21.x)
		{
			pout1[0] = p41;
			n = 1;
		}
	}
	else if (p31.y*p41.y < 0)///p3、p4分别在直线p1p2两侧
	{
		double angtem;
		dx = p41.x - p31.x;
		dy = p41.y - p31.y;
		angtem = atan2(dy, dx);
		pout1[0].y = 0;
		pout1[0].x = p31.x + (0.0 - p31.y) / sin(angtem)*cos(angtem);
		if (pout1[0].x >= p11.x && pout1[0].x <= p21.x) n = 1;
	}
	if (n>0)//将交点转回全局坐标
	{
		for (i = 0;i < n;i++)
		{
			xp2x(p1, a, pout1[i], &pout[i]);
		}
	}
	*count = n;
}

void arcline_intersection(MYPOINT p1, MYPOINT p2, ARC arc1, MYPOINT intersection[], int *n)
{
	//O为圆心，E为圆心到p1p2的垂足，D为交点
	int count = 0,i;
	double dx, dy, angp1p2, angOP1, angOP2, angOP1E, angOP2E, angOD, OP1, OP2, OE, PE, DE, ox, oy;

	arc1.angstart = stdangle0(arc1.angstart);//转换到大于等于0，小于2pi


	//转换到圆弧圆心为原点的局部坐标系
	ox = arc1.x;//保存圆弧圆心全局x坐标
	oy = arc1.y;//保存圆弧圆心全局y坐标
							//p1、p2、圆弧圆心转换到局部坐标系
	p1.x -= ox;
	p1.y -= oy;
	p2.x -= ox;
	p2.y -= oy;
	arc1.x = 0;
	arc1.y = 0;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;

	angp1p2 = atan2(dy, dx);//p1p2的角度

	angOP1 = atan2(p1.y, p1.x);//OP1的角度
	angOP1E = angp1p2 - angOP1;//两个矢量夹角，与角OP1E相等或互补
	angOP1E = stdangle(angOP1E);//转换到 - pi到pi之间

	angOP2 = atan2(p2.y, p2.x);//OP2的角度
	angOP2E = angp1p2 - angOP2;//两个矢量夹角，与角OP2E相等或互补
	angOP2E = stdangle(angOP2E);//转换到 - pi到pi之间

	OP1 = sqrt(p1.x*p1.x + p1.y*p1.y);
	OP2 = sqrt(p2.x*p2.x + p2.y*p2.y);
	OE = fabs(OP1*sin(angOP1E));
	PE = fabs(OP1*cos(angOP1E));
	if(fabs(arc1.r - OE)<1e-6 || arc1.r < OE)//圆弧半径等于OE，或小于OE
		DE = 0;
	else//圆弧半径大于OE
		DE = sqrt(arc1.r*arc1.r - OE * OE);
	if (fabs(OE - arc1.r)<1e-6)//相切
	{
		if ((fabs(angOP1E - pi / 2)<1e-6 || fabs(angOP1E) > pi / 2) && ((fabs(angOP2E - pi / 2)<1e-6 || fabs(angOP1E) < pi / 2)))//p1不超过E,且p2至少从E开始
		{
			intersection[0].x = p1.x + PE * cos(angp1p2);
			intersection[0].y = p1.y + PE * sin(angp1p2);
			count = 1;
		}
	}
	else if (OE < arc1.r)//与圆可能有两个交点
	{
		if ((fabs(OP1 - arc1.r)<1e-6 || OP1 > arc1.r) && fabs(angOP1E) > pi / 2) //(GREATER_EQUVAL(OP1, arc1.r))//p1在圆上或圆外,且p1向着E运动
		{
			intersection[0].x = p1.x + (PE - DE)*cos(angp1p2);
			intersection[0].y = p1.y + (PE - DE)*sin(angp1p2);
			if ((fabs(OP2 - arc1.r)<1e-6 && fabs(angOP2E) > pi / 2) || OP2 < arc1.r)//p2在圆上，且向着E运动，或p2在圆内
				count = 1;
			else if ((fabs(OP2 - arc1.r) < 1e-6 || OP2 > arc1.r) && fabs(angOP2E) < pi / 2) //p2在圆上或圆外,且p2离开E运动
			{
				count = 2;
				intersection[1].x = p1.x + (PE + DE)*cos(angp1p2);
				intersection[1].y = p1.y + (PE + DE)*sin(angp1p2);
			}
		}
		else if ((OP1 < arc1.r || (fabs(OP1 - arc1.r) < 1e-6 && fabs(angOP1E) < pi / 2)) && ((fabs(OP2 - arc1.r)<1e-6  && fabs(angOP2E) < pi / 2) || OP2 > arc1.r))//p1在圆内，或圆上离开E的方向；且p2在圆上离开E的方向，或圆外
		{
			count = 1;
			if (fabs(angOP1E) >= pi / 2)//p1向着E运动
			{
				intersection[0].x = p1.x + (PE + DE)*cos(angp1p2);
				intersection[0].y = p1.y + (PE + DE)*sin(angp1p2);
			}
			else//p1离开E运动
			{
				intersection[0].x = p1.x + (DE - PE)*cos(angp1p2);
				intersection[0].y = p1.y + (DE - PE)*sin(angp1p2);
			}
		}
	}
	if (count == 1)
	{
		angOD = atan2(intersection[0].y, intersection[0].x);
		angOD -= arc1.angstart;//以圆弧起始角为0，OD的角度
		angOD = stdangle0(angOD);//转换到大于等于0，小于2pi

		if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))
			count = 1;
		else
			count = 0;
	}
	else if (count == 2)
	{
		angOD = atan2(intersection[0].y, intersection[0].x);
		angOD -= arc1.angstart;//以圆弧起始角为0，OD的角度
		angOD = stdangle0(angOD);//转换到大于等于0，小于2pi
		if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))//第1个是交点
		{
			count = 1;
			angOD = atan2(intersection[1].y, intersection[1].x);
			angOD -= arc1.angstart;//以圆弧起始角为0，OD的角度
			angOD = stdangle0(angOD);//转换到大于等于0，小于2pi
			if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))//第2个是交点
				count = 2;
		}
		else//第1个不是交点
		{
			angOD = atan2(intersection[1].y, intersection[1].x);
			angOD -= arc1.angstart;//以圆弧起始角为0，OD的角度
			angOD = stdangle0(angOD);//转换到大于等于0，小于2pi
			if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))//第2个是交点
			{
				count = 1;
				intersection[0] = intersection[1];
			}
			else
				count = 0;
		}
	}
	//交点转回全局坐标
	for (i = 0;i < count;i++)
	{
		intersection[i].x += ox;
		intersection[i].y += oy;
	}
	*n = count;
}

void arc_intersection(ARC arc1, ARC arc2, int *count, MYPOINT pout[])
{
	double oo,angoo,r1,r2,x,y,DOO,ang[4];
	int n,m,i;
	MYPOINT point[4],ptmp[4],po;
	oo=oo_dist(arc1,arc2);
	angoo=oo_angle(arc1,arc2);
	po=arc_o(arc1);
	r1=arc1.r;
	r2=arc2.r;
	n=0;//没有交点，n=0
	//半径相等且同心
	if (fabs(r1 - r2) < 1e-6 && oo < 1e-6)
	{
		point[0]=getarcpnt(arc1,arc1.angstart);
		point[1]=getarcpnt(arc1,arc1.angstart+arc1.dang);
		point[3]=getarcpnt(arc2,arc2.angstart);
		point[4]=getarcpnt(arc2,arc2.angstart+arc2.dang);
		n=4;
	}
	//外切
	else if (fabs(r1 + r2 - oo) < 1e-6)
	{
		point[0]=getarcpnt(arc1,angoo);
		n=1;
	}
	//内切
	else if (fabs(fabs(r1 - r2) - oo) < 1e-6)
	{
		n=1;
		if (r1 > r2)
			point[0]=getarcpnt(arc1,angoo);
		else
			point[0]=getarcpnt(arc1,angoo+pi);
	}
	else if (r1 + r2 > oo)
	{
		x=(r1*r1+oo*oo-r2*r2)/(2*r1*oo); //cos(DOO)
		if(1<x*x)//一个圆在另一个圆内，无交点
			n=0;
		else//有两个交点
		{
			y=sqrt(1-x*x);//sin(DOO)
			DOO=atan2(y,x);
			point[0]=getarcpnt(arc1,angoo+DOO);
			point[1]=getarcpnt(arc1,angoo-DOO);
			n=2;
		}
	}
	//是否在两个圆弧上
	m=0;
	for(i=0;i < n;i++)
	{
		if(isAtArc(arc1,point[i]) && isAtArc(arc2,point[i]))
			ptmp[m++]=point[i];
	}
	if (m > 0)
	{
		for(i=0;i<m;i++)
			ang[i]=stdangle0(pp_angle(po,ptmp[i])-arc1.angstart);
	}
	//排序
	sort(m,ang);
//排除重合点
	if (m == 2)
	{
		if(fabs(ang[0]-ang[1])<1e-8)
			m=1;
	}
	else if (m > 2)
	{
		ang[1]=ang[m-1];
		m=2;
	}
	//转换为点
	for (i = 0;i < m;i++)
		pout[i]=getarcpnt(arc1,ang[i]+arc1.angstart);
	*count=m;
}
//找点在路线的哪一段
//确定点是否在线段两边一定距离范围内
int isAtLineRegion(LINE line1, MYPOINT p,double hw)
{
	int at=0;
	double ang;
	MYPOINT p21,pp;
	ang=pp_angle(line1.p1,line1.p2);
	x2xp(line1.p1,ang,line1.p2,&p21);
	x2xp(line1.p1,ang,p,&pp);
	if(GEANDLE(0.0,pp.x,p21.x,1e-6))
		if(fabs(pp.y)<hw)
			at=1;
	return at;
}

//确定点是否在圆弧两边一定距离范围内
int isAtArcRegion(ARC arc1, MYPOINT p,double hw)
{
	int at=0;
	double angp,ange;
	MYPOINT o;
	o=arc_o(arc1);
	angp=stdangle0(pp_angle(o,p)-arc1.angstart);
	ange=arc1.dang;
	if(GEANDLE(0.0,angp,ange,1e-8))
		if(fabs(pp_dist(o,p)-arc1.r)<hw)
			at=1;
	return at;
}
//根据角度确定点是否在圆弧上
int isAtArc(ARC arc1, MYPOINT p)
{
	double ang,ang1;
	int i;
	ang1=pp_angle(arc_o(arc1),p),
	ang=stdangle0(ang1-arc1.angstart);
	i=(GEANDLE(0.0,ang,arc1.dang,1e-8))?1:0;
	return i;
}

//计算对线的反射角，ain为车右方与x轴夹角
double linereflect(LINE line1, double ain)
{
	double a0;
	a0=pp_angle(line1.p1,line1.p2)-pi/2;//法线角度
	return stdangle(2*a0-ain);
}
//计算对圆弧的反射角
double arcreflect(ARC arc1, MYPOINT p,double ain)
{
	double a0;
	MYPOINT o;
	o=arc_o(arc1);
	a0=pp_angle(o,p);//法线角度
	return stdangle(2.0*a0-ain);
}
double pp_angle(MYPOINT p1,MYPOINT p2)
{
	double dx,dy;
	dx=p2.x-p1.x;
	dy=p2.y-p1.y;
	return atan2(dy,dx);
}
double oo_angle(ARC arc1, ARC arc2)
{
	double dx,dy;
	dx=arc2.x-arc1.x;
	dy=arc2.y-arc1.y;
	return atan2(dy,dx);
}
MYPOINT arc_o(ARC arc1)
{
	MYPOINT p;
	p.x=arc1.x;
	p.y=arc1.y;
	return p;
}

double pp_dist(MYPOINT p1,MYPOINT p2)
{
	double dx,dy;
	dx=p2.x-p1.x;
	dy=p2.y-p1.y;
	return sqrt(dx*dx+dy*dy);
}
double oo_dist(ARC arc1, ARC arc2)
{
	double dx,dy;
	dx=arc2.x-arc1.x;
	dy=arc2.y-arc1.y;
	return sqrt(dx*dx+dy*dy);
}
MYPOINT getarcpnt(ARC arc1,double ang)
{
	MYPOINT p;
	p.x=arc1.x+arc1.r*cos(ang);
	p.y=arc1.y+arc1.r*sin(ang);
	return p;
}
//由起点p1，按矢量移动（矢量的方向角ang和长度len），得到新的点
MYPOINT getpangpnt(MYPOINT p0, double ang, double len)
{
	MYPOINT p1;
	p1.x=p0.x+len*cos(ang);
	p1.y=p0.y+len*sin(ang);
	return p1;
}

//转换到 - pi到pi之间，用于锐角、钝角判断
double stdangle(double angle)
{
	//转换到-2pi到2pi之间
	if (angle > 2 * pi) angle -= (int)(angle / (2 * pi)) * 2 * pi;
	else if (angle < -2 * pi) angle += (int)(angle / (2 * pi)) * 2 * pi;
	//转换到 - pi到pi之间
	if (angle > pi) angle -= 2 * pi;
	else if (angle < -pi) angle += 2 * pi;
	return angle;
}
//将弧度角转换到大于等于0，小于2pi，用于角度大小比较
double stdangle0(double angle)
{
	//转换到-2pi到2pi之间
	if (angle > 2 * pi) angle -= (int)(angle / (2 * pi)) * 2 * pi;
	else if (angle < -2 * pi) angle += (int)(angle / (2 * pi)) * 2 * pi;
	//转换到 - pi到pi之间
	if (angle > pi) angle -= 2 * pi;
	else if (angle < -pi) angle += 2 * pi;
	if (fabs(angle) < 1e-6) angle = 0;//与0夹角很小，则为0。
	else if (angle < 0) angle += 2 * pi;//转换到大于等于0，小于2pi。
	return angle;
}
//xy二维平面全局到局部坐标系转换
void x2xp(MYPOINT pntsight, double alpha0, MYPOINT pnt, MYPOINT *pnt_p)
{
	double alpha, x, y;
	//alpha = alpha0 / 180.0*pi;
	alpha = alpha0;
	x = pnt.x - pntsight.x;
	y = pnt.y - pntsight.y;//平移
	pnt_p->x = x * cos(alpha) + y * sin(alpha);
	pnt_p->y = -x * sin(alpha) + y * cos(alpha);//旋转
}
//xy二维平面局部到全局坐标系转换
void xp2x(MYPOINT pntsight, double alpha0, MYPOINT pnt_p, MYPOINT *pnt)
{
	double alpha, x, y;
	//alpha = -alpha0 / 180.0*pi;
	alpha = -alpha0;
	x = pnt_p.x * cos(alpha) + pnt_p.y * sin(alpha);
	y = -pnt_p.x * sin(alpha) + pnt_p.y * cos(alpha);
	pnt->x = x + pntsight.x;
	pnt->y = y + pntsight.y;
}
//圆心移动，yz平面转动，三维点全局到局部坐标系转换
void y2yp(MY3DPOINT pntsight, double alpha0, MY3DPOINT pnt, MY3DPOINT *pnt_p)
{
	double alpha, x, y, z;
	alpha = alpha0;
	x = pnt.p.x - pntsight.p.x;
	y = pnt.p.y - pntsight.p.y;
	z = pnt.z - pntsight.z;//平移
	pnt_p->p.y = y * cos(alpha) + z * sin(alpha);
	pnt_p->z = -y * sin(alpha) + z * cos(alpha);//旋转
}
//圆心移动，yz平面转动，三维点局部到全局坐标系转换
void yp2y(MY3DPOINT pntsight, double alpha0, MY3DPOINT pnt_p, MY3DPOINT *pnt)
{
	double alpha, x, y, z;
	alpha = -alpha0;
	y = pnt_p.p.y * cos(alpha) + pnt_p.z * sin(alpha);
	z = -pnt_p.p.y * sin(alpha) + pnt_p.z * cos(alpha);
	pnt->p.x +=  pntsight.p.x;
	pnt->p.y = y + pntsight.p.y;
	pnt->z = z + pntsight.z;
}

LINE scaleline(double k, LINE line1)
{
	MYPOINT p1,p2;
	LINE li;
	p1.x=k*line1.p1.x;
	p1.y=k*line1.p1.y;
	p2.x=k*line1.p2.x;
	p2.y=k*line1.p2.y;
	li.p1=p1;
	li.p2=p2;
	return li;
}
ARC scalearc(double k, ARC arc1)
{
	ARC ar;
	ar=arc1;
	ar.r*=k;
	ar.x*=k;
	ar.y*=k;
	return ar;
}


//全局双精度单点转换为窗口坐标，并移到窗口中心
POINT x2scr(MYPOINT p1)
{
	POINT p2;
	p2.x=(long)(p1.x+xcen);
	p2.y=(long)(-p1.y+ycen);
	return p2;
}
//长整数点数组转换为窗口坐标，并移到窗口中心
void toscreen(POINT p1[])
{
	int i;
	for(i=0;i<5;i++)
	{
		p1[i].x+=xcen;
		p1[i].y=-p1[i].y+ycen;
	}
}
void sort(int n, double a[])
{
	int i,j,jh=1;
	double tmp;
	for (i=n-1;i>0 && jh==1;i--)
	{
		jh=0;//若没有交换，则jh保持为0
		for(j=0;j<i;j++)
		{
			if (a[j]>a[j+1])
			{
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				jh=1;
			}
		}
	}
}
