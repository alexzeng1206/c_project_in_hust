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

//���μ��㺯��
//����ֱ���߶����߶εĽ���
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
	if (fabs(p21.y) < 1e-6) p21.y = 0;//y����ܽӽ�0ʱ������Ϊ0
	x2xp(p1, a, p3, &p31);
	if (fabs(p31.y) < 1e-6) p31.y = 0;//y����ܽӽ�0ʱ������Ϊ0
	x2xp(p1, a, p4, &p41);
	if (fabs(p41.y) < 1e-6) p41.y = 0;//y����ܽӽ�0ʱ������Ϊ0

	if (fabs(p31.y) < 1e-6 && fabs(p41.y) < 1e-6)//p3��p4����ֱ��p1p2��
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
	else if (fabs(p31.y) < 1e-6)//��p3��ֱ��p1p2��
	{
		if (p31.x >= p11.x && p31.x <= p21.x)
		{
			pout1[0] = p31;
			n = 1;
		}
	}
	else if (fabs(p41.y) < 1e-6)//��p4��ֱ��p1p2��
	{
		if (p41.x >= p11.x && p41.x <= p21.x)
		{
			pout1[0] = p41;
			n = 1;
		}
	}
	else if (p31.y*p41.y < 0)///p3��p4�ֱ���ֱ��p1p2����
	{
		double angtem;
		dx = p41.x - p31.x;
		dy = p41.y - p31.y;
		angtem = atan2(dy, dx);
		pout1[0].y = 0;
		pout1[0].x = p31.x + (0.0 - p31.y) / sin(angtem)*cos(angtem);
		if (pout1[0].x >= p11.x && pout1[0].x <= p21.x) n = 1;
	}
	if (n>0)//������ת��ȫ������
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
	//OΪԲ�ģ�EΪԲ�ĵ�p1p2�Ĵ��㣬DΪ����
	int count = 0,i;
	double dx, dy, angp1p2, angOP1, angOP2, angOP1E, angOP2E, angOD, OP1, OP2, OE, PE, DE, ox, oy;

	arc1.angstart = stdangle0(arc1.angstart);//ת�������ڵ���0��С��2pi


	//ת����Բ��Բ��Ϊԭ��ľֲ�����ϵ
	ox = arc1.x;//����Բ��Բ��ȫ��x����
	oy = arc1.y;//����Բ��Բ��ȫ��y����
							//p1��p2��Բ��Բ��ת�����ֲ�����ϵ
	p1.x -= ox;
	p1.y -= oy;
	p2.x -= ox;
	p2.y -= oy;
	arc1.x = 0;
	arc1.y = 0;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;

	angp1p2 = atan2(dy, dx);//p1p2�ĽǶ�

	angOP1 = atan2(p1.y, p1.x);//OP1�ĽǶ�
	angOP1E = angp1p2 - angOP1;//����ʸ���нǣ����OP1E��Ȼ򻥲�
	angOP1E = stdangle(angOP1E);//ת���� - pi��pi֮��

	angOP2 = atan2(p2.y, p2.x);//OP2�ĽǶ�
	angOP2E = angp1p2 - angOP2;//����ʸ���нǣ����OP2E��Ȼ򻥲�
	angOP2E = stdangle(angOP2E);//ת���� - pi��pi֮��

	OP1 = sqrt(p1.x*p1.x + p1.y*p1.y);
	OP2 = sqrt(p2.x*p2.x + p2.y*p2.y);
	OE = fabs(OP1*sin(angOP1E));
	PE = fabs(OP1*cos(angOP1E));
	if(fabs(arc1.r - OE)<1e-6 || arc1.r < OE)//Բ���뾶����OE����С��OE
		DE = 0;
	else//Բ���뾶����OE
		DE = sqrt(arc1.r*arc1.r - OE * OE);
	if (fabs(OE - arc1.r)<1e-6)//����
	{
		if ((fabs(angOP1E - pi / 2)<1e-6 || fabs(angOP1E) > pi / 2) && ((fabs(angOP2E - pi / 2)<1e-6 || fabs(angOP1E) < pi / 2)))//p1������E,��p2���ٴ�E��ʼ
		{
			intersection[0].x = p1.x + PE * cos(angp1p2);
			intersection[0].y = p1.y + PE * sin(angp1p2);
			count = 1;
		}
	}
	else if (OE < arc1.r)//��Բ��������������
	{
		if ((fabs(OP1 - arc1.r)<1e-6 || OP1 > arc1.r) && fabs(angOP1E) > pi / 2) //(GREATER_EQUVAL(OP1, arc1.r))//p1��Բ�ϻ�Բ��,��p1����E�˶�
		{
			intersection[0].x = p1.x + (PE - DE)*cos(angp1p2);
			intersection[0].y = p1.y + (PE - DE)*sin(angp1p2);
			if ((fabs(OP2 - arc1.r)<1e-6 && fabs(angOP2E) > pi / 2) || OP2 < arc1.r)//p2��Բ�ϣ�������E�˶�����p2��Բ��
				count = 1;
			else if ((fabs(OP2 - arc1.r) < 1e-6 || OP2 > arc1.r) && fabs(angOP2E) < pi / 2) //p2��Բ�ϻ�Բ��,��p2�뿪E�˶�
			{
				count = 2;
				intersection[1].x = p1.x + (PE + DE)*cos(angp1p2);
				intersection[1].y = p1.y + (PE + DE)*sin(angp1p2);
			}
		}
		else if ((OP1 < arc1.r || (fabs(OP1 - arc1.r) < 1e-6 && fabs(angOP1E) < pi / 2)) && ((fabs(OP2 - arc1.r)<1e-6  && fabs(angOP2E) < pi / 2) || OP2 > arc1.r))//p1��Բ�ڣ���Բ���뿪E�ķ�����p2��Բ���뿪E�ķ��򣬻�Բ��
		{
			count = 1;
			if (fabs(angOP1E) >= pi / 2)//p1����E�˶�
			{
				intersection[0].x = p1.x + (PE + DE)*cos(angp1p2);
				intersection[0].y = p1.y + (PE + DE)*sin(angp1p2);
			}
			else//p1�뿪E�˶�
			{
				intersection[0].x = p1.x + (DE - PE)*cos(angp1p2);
				intersection[0].y = p1.y + (DE - PE)*sin(angp1p2);
			}
		}
	}
	if (count == 1)
	{
		angOD = atan2(intersection[0].y, intersection[0].x);
		angOD -= arc1.angstart;//��Բ����ʼ��Ϊ0��OD�ĽǶ�
		angOD = stdangle0(angOD);//ת�������ڵ���0��С��2pi

		if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))
			count = 1;
		else
			count = 0;
	}
	else if (count == 2)
	{
		angOD = atan2(intersection[0].y, intersection[0].x);
		angOD -= arc1.angstart;//��Բ����ʼ��Ϊ0��OD�ĽǶ�
		angOD = stdangle0(angOD);//ת�������ڵ���0��С��2pi
		if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))//��1���ǽ���
		{
			count = 1;
			angOD = atan2(intersection[1].y, intersection[1].x);
			angOD -= arc1.angstart;//��Բ����ʼ��Ϊ0��OD�ĽǶ�
			angOD = stdangle0(angOD);//ת�������ڵ���0��С��2pi
			if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))//��2���ǽ���
				count = 2;
		}
		else//��1�����ǽ���
		{
			angOD = atan2(intersection[1].y, intersection[1].x);
			angOD -= arc1.angstart;//��Բ����ʼ��Ϊ0��OD�ĽǶ�
			angOD = stdangle0(angOD);//ת�������ڵ���0��С��2pi
			if (angOD >= 0 && ((fabs(angOD - arc1.dang)<1e-6 || angOD < arc1.dang)))//��2���ǽ���
			{
				count = 1;
				intersection[0] = intersection[1];
			}
			else
				count = 0;
		}
	}
	//����ת��ȫ������
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
	n=0;//û�н��㣬n=0
	//�뾶�����ͬ��
	if (fabs(r1 - r2) < 1e-6 && oo < 1e-6)
	{
		point[0]=getarcpnt(arc1,arc1.angstart);
		point[1]=getarcpnt(arc1,arc1.angstart+arc1.dang);
		point[3]=getarcpnt(arc2,arc2.angstart);
		point[4]=getarcpnt(arc2,arc2.angstart+arc2.dang);
		n=4;
	}
	//����
	else if (fabs(r1 + r2 - oo) < 1e-6)
	{
		point[0]=getarcpnt(arc1,angoo);
		n=1;
	}
	//����
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
		if(1<x*x)//һ��Բ����һ��Բ�ڣ��޽���
			n=0;
		else//����������
		{
			y=sqrt(1-x*x);//sin(DOO)
			DOO=atan2(y,x);
			point[0]=getarcpnt(arc1,angoo+DOO);
			point[1]=getarcpnt(arc1,angoo-DOO);
			n=2;
		}
	}
	//�Ƿ�������Բ����
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
	//����
	sort(m,ang);
//�ų��غϵ�
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
	//ת��Ϊ��
	for (i = 0;i < m;i++)
		pout[i]=getarcpnt(arc1,ang[i]+arc1.angstart);
	*count=m;
}
//�ҵ���·�ߵ���һ��
//ȷ�����Ƿ����߶�����һ�����뷶Χ��
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

//ȷ�����Ƿ���Բ������һ�����뷶Χ��
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
//���ݽǶ�ȷ�����Ƿ���Բ����
int isAtArc(ARC arc1, MYPOINT p)
{
	double ang,ang1;
	int i;
	ang1=pp_angle(arc_o(arc1),p),
	ang=stdangle0(ang1-arc1.angstart);
	i=(GEANDLE(0.0,ang,arc1.dang,1e-8))?1:0;
	return i;
}

//������ߵķ���ǣ�ainΪ���ҷ���x��н�
double linereflect(LINE line1, double ain)
{
	double a0;
	a0=pp_angle(line1.p1,line1.p2)-pi/2;//���߽Ƕ�
	return stdangle(2*a0-ain);
}
//�����Բ���ķ����
double arcreflect(ARC arc1, MYPOINT p,double ain)
{
	double a0;
	MYPOINT o;
	o=arc_o(arc1);
	a0=pp_angle(o,p);//���߽Ƕ�
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
//�����p1����ʸ���ƶ���ʸ���ķ����ang�ͳ���len�����õ��µĵ�
MYPOINT getpangpnt(MYPOINT p0, double ang, double len)
{
	MYPOINT p1;
	p1.x=p0.x+len*cos(ang);
	p1.y=p0.y+len*sin(ang);
	return p1;
}

//ת���� - pi��pi֮�䣬������ǡ��۽��ж�
double stdangle(double angle)
{
	//ת����-2pi��2pi֮��
	if (angle > 2 * pi) angle -= (int)(angle / (2 * pi)) * 2 * pi;
	else if (angle < -2 * pi) angle += (int)(angle / (2 * pi)) * 2 * pi;
	//ת���� - pi��pi֮��
	if (angle > pi) angle -= 2 * pi;
	else if (angle < -pi) angle += 2 * pi;
	return angle;
}
//�����Ƚ�ת�������ڵ���0��С��2pi�����ڽǶȴ�С�Ƚ�
double stdangle0(double angle)
{
	//ת����-2pi��2pi֮��
	if (angle > 2 * pi) angle -= (int)(angle / (2 * pi)) * 2 * pi;
	else if (angle < -2 * pi) angle += (int)(angle / (2 * pi)) * 2 * pi;
	//ת���� - pi��pi֮��
	if (angle > pi) angle -= 2 * pi;
	else if (angle < -pi) angle += 2 * pi;
	if (fabs(angle) < 1e-6) angle = 0;//��0�нǺ�С����Ϊ0��
	else if (angle < 0) angle += 2 * pi;//ת�������ڵ���0��С��2pi��
	return angle;
}
//xy��άƽ��ȫ�ֵ��ֲ�����ϵת��
void x2xp(MYPOINT pntsight, double alpha0, MYPOINT pnt, MYPOINT *pnt_p)
{
	double alpha, x, y;
	//alpha = alpha0 / 180.0*pi;
	alpha = alpha0;
	x = pnt.x - pntsight.x;
	y = pnt.y - pntsight.y;//ƽ��
	pnt_p->x = x * cos(alpha) + y * sin(alpha);
	pnt_p->y = -x * sin(alpha) + y * cos(alpha);//��ת
}
//xy��άƽ��ֲ���ȫ������ϵת��
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
//Բ���ƶ���yzƽ��ת������ά��ȫ�ֵ��ֲ�����ϵת��
void y2yp(MY3DPOINT pntsight, double alpha0, MY3DPOINT pnt, MY3DPOINT *pnt_p)
{
	double alpha, x, y, z;
	alpha = alpha0;
	x = pnt.p.x - pntsight.p.x;
	y = pnt.p.y - pntsight.p.y;
	z = pnt.z - pntsight.z;//ƽ��
	pnt_p->p.y = y * cos(alpha) + z * sin(alpha);
	pnt_p->z = -y * sin(alpha) + z * cos(alpha);//��ת
}
//Բ���ƶ���yzƽ��ת������ά��ֲ���ȫ������ϵת��
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


//ȫ��˫���ȵ���ת��Ϊ�������꣬���Ƶ���������
POINT x2scr(MYPOINT p1)
{
	POINT p2;
	p2.x=(long)(p1.x+xcen);
	p2.y=(long)(-p1.y+ycen);
	return p2;
}
//������������ת��Ϊ�������꣬���Ƶ���������
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
		jh=0;//��û�н�������jh����Ϊ0
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
