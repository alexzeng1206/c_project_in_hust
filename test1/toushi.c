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

void toushitu()
{
	int i;
	if(toushi==1)
	{
		draw_solidloop(2*segs,roadareaout);//绘制跑道外边界透视图
		for(i=0;i<2;i++)
		{
			draw_dashloop(2*segs,roadareadash[i]);//绘制跑道中心线透视图
		}
		draw_solidloop(2*segs,roadareain);//绘制跑道内边界透视图
		drawendline();
		draw_lanloop(2*segs,roadareaout);//绘制跑道外边界栏杆
		draw_lanloop(2*segs,roadareain);//绘制跑道内边界栏杆

		//draw_treeloop(2*segs,roadareaout);//绘制跑道外边界树
		//draw_treeloop(2*segs,roadareain);//绘制跑道内边界树

		drawautocarface();
		drawdrivecarface();
	}
}
void drawendline()
{
	LINE lineout;
	int n;
	n=seeline(endline.p1,endline.p2,&lineout);
	if(n>0)	draw_line(lineout);
}

//透视实线公路边界线
void draw_solidloop(int nseg,ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//直线段
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	draw_line(lineout);
		}
		else//圆弧
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
				draw_solidarc(arcout[j]);
		}
	}
}
//透视公路虚线
void draw_dashloop(int nseg, ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//直线段
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	draw_dashline(linein,lineout);
		}
		else//圆弧
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
				draw_dasharc(arcin,arcout[j]);
		}
	}
}
void draw_solidarc(ARC arc1)
{
	double ang1,dang1;
	int ndiv,i;
	ndiv=(int)(arc1.dang*arc1.r/2.0)+1;
	ang1=arc1.angstart;
	dang1=arc1.dang/ndiv;
	arc1.dang=dang1;
	for (i = 0;i < ndiv;i++)
	{
		arc1.angstart=ang1;
		draw_arc(arc1);
		ang1+=dang1;
	}
}
//画道路虚直线，虚线在后半段
//点1在虚线段，
void draw_dashline(LINE linearea,LINE line)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	LINE line1;
	double ang;
	ang=pp_angle(linearea.p1,linearea.p2);
	at1=wheredashline(linearea,line.p1,&n1);
	at2=wheredashline(linearea,line.p2,&n2);
	if (n2 == n1)//在同一段
	{
		if (at1 == 1)//点1在虚线上
		{
			if (at2 == 1)//点2在虚线上
			{
				draw_line(line);
			}
		}
		else//点1在间隔上
		{
			if (at2 == 1)//点2在虚线上
			{
				line1.p1=getpangpnt(linearea.p1,ang,(n1+0.5)*dashlen);
				line1.p2=line.p2;
				draw_line(line1);
			}
		}
	}
	else//在不同段
	{
		if (at1 == 1)//首不完整虚线
		{
			line1.p1=line.p1;
			line1.p2=getpangpnt(linearea.p1,ang,(n1+1)*dashlen);
			draw_line(line1);
		}
		if(at2==1)//尾不完整虚线
		{
			line1.p1=getpangpnt(linearea.p1,ang,(n2+0.5)*dashlen);
			line1.p2=line.p2;
			draw_line(line1);
		}
		//完整虚线
		n=n2-n1-1;//中间完整虚线数
		if(at1==1)//点1在虚线段，中间完整段从n1+1开始
		{
			nstart=n1+1;
		}
		else//点1不在虚线段，中间连续段数加1
		{
			n++;
			nstart=n1;//从可视起点段开始
		}
		for (i = 0;i < n;i++)//中间完整虚线
		{
			m=nstart+i;	
			line1.p1=getpangpnt(linearea.p1,ang,(m+0.5)*dashlen);
			line1.p2=getpangpnt(linearea.p1,ang,(m+1)*dashlen);
			draw_line(line1);
		}
	}
}
//画道路虚弧线，虚线在后半段
void draw_dasharc(ARC arcarea,ARC arc)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	ARC arc1;
	double ang1,ang2;
	arc1=arcarea;
	ang1=arc.angstart;
	ang2=ang1+arc.dang;
	at1=wheredasharc(arcarea,ang1,&n1);
	at2=wheredasharc(arcarea,ang2,&n2);
	if (n2 == n1)//在同一段
	{
		if (at1 == 1)//点1在虚线上
		{
			if (at2 == 1)//点2在虚线上
			{
				draw_solidarc(arc);
			}
		}
	}
	else//在不同段
	{
		if (at1 == 1)//首不完整虚线
		{
				arc1.angstart=ang1;
				arc1.dang=stdangle0(arcarea.angstart+(n1+1)*dashang-ang1);
				draw_solidarc(arc1);
		}
		if(at2==1)//尾不完整虚线
		{
			arc1.angstart=arcarea.angstart+(n2+0.5)*dashang;
			arc1.dang=stdangle0(ang2-arc1.angstart);
			draw_solidarc(arc1);
		}
		//完整虚线
		n=n2-n1-1;//中间完整虚线数
		if(at1==1)
		{
			nstart=n1+1;
		}
		else//可视起点段加入中间连续段
		{
			n++;
			nstart=n1;//从可视起点段开始
		}
		for (i = 0;i < n;i++)//中间完整虚弧线
		{
			m=nstart+i;	
			arc1.angstart=arcarea.angstart+(m+0.5)*dashang;
			arc1.dang=dashang/2;
			draw_solidarc(arc1);
		}
	}
}
//画有宽度的直线段
void draw_line(LINE line1)
{
	MYPOINT point[4];
	int i;
	int poly[8];
	double a;
	if(pp_dist(line1.p1,line1.p2)<0.01) return;//若直线长度过短，则退出
	a=atan2(line1.p2.y-line1.p1.y,line1.p2.x-line1.p1.x);
	point[0].x = line1.p1.x + w * cos(a - pi / 2);
	point[0].y = line1.p1.y + w * sin(a - pi / 2);
	point[3].x = line1.p1.x + w * cos(a + pi / 2);
	point[3].y = line1.p1.y + w * sin(a + pi / 2);

	point[1].x = line1.p2.x + w * cos(a - pi / 2);
	point[1].y = line1.p2.y + w * sin(a - pi / 2);
	point[2].x = line1.p2.x + w * cos(a + pi / 2);
	point[2].y = line1.p2.y + w * sin(a + pi / 2);
	for (i = 0;i < 4;i++)
	{
		x2xp(pntsight, angsight, point[i], &point[i]);//转到相机坐标系
		Pnt_Toushi(point[i], &point[i]);//计算单位屏幕高透视点
		//透视坐标值乘以屏幕高，存入poly数组
		poly[2*i] =(int)(scrH*point[i].x+xcen);
		poly[2*i+1] = (int)(scrH*point[i].y+ycen);

	}
	fillpoly(4, poly);//画线段
}
//三等分画宽度为2w的圆弧透视图
void draw_arc(ARC arc2)
{
	int poly[16],i;
	double x0,y0,r,theta, dang;
	MYPOINT p,pnt_p,pnt_t;
	if(arc2.dang*arc2.r<0.01) return;//若直线长度过短，则退出
	x0=arc2.x;
	y0=arc2.y;
	r=arc2.r;
	theta=arc2.angstart;
	dang=arc2.dang/3.0;//圆弧ndiv-1等分
	for (i = 0;i < 4;i++)
	{
		p.x = x0+(r + w)*cos(theta);
		p.y = y0+(r + w)*sin(theta);
		x2xp(pntsight, angsight, p, &pnt_p);
		Pnt_Toushi(pnt_p, &pnt_t);
		//透视坐标值乘以屏幕高，存入poly数组
		poly[2 * i] = (int)(pnt_t.x *scrH+xcen);
		poly[2 * i + 1] =(int)( pnt_t.y * scrH+ycen);

		p.x = x0+(r - w)*cos(theta);
		p.y = y0+(r - w)*sin(theta);
		x2xp(pntsight, angsight, p, &pnt_p);
		Pnt_Toushi(pnt_p, &pnt_t);
		//透视坐标值乘以屏幕高，存入poly数组
		poly[2 * (7 - i)] = (int)(pnt_t.x * scrH+xcen);
		poly[2 * (7 - i) + 1] =(int)(pnt_t.y * scrH+ycen);
		
		theta += dang;
	}

	fillpoly(8, poly);
}
//计算点在虚线上第n个周期，返回是否在虚线上（在后半段则在）
int wheredashline(LINE line, MYPOINT pnt, int *n)
{
	int atline=0,m;
	double d;
	double ang=pp_angle(line.p1,line.p2);
	MYPOINT pp,p21;
	x2xp(line.p1,ang,pnt,&pp);
	x2xp(line.p1,ang,line.p2,&p21);
	d=pp.x/dashlen;
	m=(int)d;
	//后半部分为虚线的线区
	if(d-m>=0.5) atline=1;
	*n=m;
	return atline;
}

//计算点在虚圆弧线上第n个周期，返回是否在虚线上（在后半段则在）
int wheredasharc(ARC arc1,double ang, int *n)
{
	int atarc=0,m;
	double d;
	double ang1;
	ang1=stdangle0(ang-arc1.angstart);
	d=ang1/dashang;
	m=(int)d;
	if(d-m>=0.5) atarc=1;
	*n=m;
	return atarc;
}

//计算一线段（全局坐标）与视场边界交点及在视场内部端点，返回值为点数，参数里还返回点（全局坐标）。最多两个点，一段。
//以下版本是转到p1p2局部坐标，交点y坐标为0，便于比较是否重合，容易看懂
int seeline(MYPOINT p1, MYPOINT p2, LINE *line1)
{
	int n = 0,i,j,j1,m;//在视场内部端点或交点总数
	MYPOINT p11={0,0}, p21;//p1、p2在p1p2局部坐标系的坐标
	MYPOINT pp1[5];
	MYPOINT pseg[2];//存放内部端点或交点
	double dx,dy,a;
	MYPOINT ptmp[2],ptemp;//临时记录交点
	int nn;//临时记录交点数
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	a = atan2(dy, dx);
	x2xp(p1, a, p2, &p21);//p2转到p1p2局部坐标（原点是p1，转动角度是a）
	//视场点转到p1p2局部坐标
	for (j = 0;j < 4;j++)
	{
		xp2x(pntsight, angsight,  p[j], &pp1[j]);//视场点转到全局坐标
		x2xp(p1, a,  pp1[j], &pp1[j]);//视场点转到p1p2局部坐标
	}
	pp1[4] = pp1[0];

	//计算视场内的点
	if (judgein(p1) && judgein(p2))//都在视场里，结束函数
	{
		line1->p1 = p1;
		line1->p2 = p2;
		return 1;
	}
	else if (judgein(p1))//只p1在视场里
	{
		pseg[0] = p11;
		n = 1;
	}
	else if (judgein(p2))//只p2在视场里
	{
		pseg[0] = p21;
		n = 1;
	}
	//计算交点
	for (i = 0;i < 4;i++)//与视场每条边进行计算
	{
		line_intersection(p11, p21, pp1[i], pp1[i + 1], &nn, ptmp);
		for(j=0;j<nn && n<2;j++)//对每个交点进行判断是否存入pseg数组，n小于2才循环
		{
			double x=ptmp[j].x;
			j1=0;
			for (m = 0;m < n;m++)//与pseg数组里的点都不重合的交点才存入pseg数组
			{
				if(fabs(x-pseg[m].x)<1e-6)
				{
					j1=1;//重合，j1置1
					break;
				}
			}
			if(j1==0) pseg[n++]=ptmp[j];//与pseg数组里的点都不重合，存入pseg数组
		}
	}
	if (n == 2)//有两个点，说明视场里有一段直线
	{
		if (pseg[0].x > pseg[1].x)//排序
		{
			ptemp=pseg[0];
			pseg[0]=pseg[1];
			pseg[1]=ptemp;
		}
		for (j = 0;j < 2;j++)
		{
			xp2x(p1, a, pseg[j], &pseg[j]); //交点转回全局坐标
		}
		line1->p1 = pseg[0];
		line1->p2 = pseg[1];
		return 1;
	}
	else
		return 0;
}
//计算一圆弧（全局坐标）在视场内弧段，返回值为弧段数，参数里还返回弧段ARC结构值（全局坐标）
int seearc(ARC arc2, ARC arc3[])
{
	int n,i,j,m,j1;//交底或内部点总数
	int nn,num;//
	MYPOINT intersection[2], p1[5], middle, ps, pe, point[10];
	double a, ang[10], dang[9], temp;
	double x0,y0,ang0,R;

	x0=arc2.x;
	y0=arc2.y;
	ang0=arc2.angstart;
	R=arc2.r;

	//视场点转到全局坐标
	for (i = 0;i < 4;i++)
	{
		xp2x(pntsight, angsight, p[i], &p1[i]);
	}
	p1[4] = p1[0];

	//计算圆弧端点
	ps.x = x0 + R*cos(ang0);
	ps.y = y0 + R*sin(ang0);
	a = ang0 + arc2.dang;
	pe.x = x0 + R*cos(a);
	pe.y = y0 + R*sin(a);

	//圆弧端点若在视场内，存入point数组，并且与圆弧起始角的夹角存入ang数组
	n = 0;
	if (judgein(ps))
	{
		point[n] = ps;
		ang[n++]=0.0;
	}
	if (judgein(pe))
	{
		point[n] = pe;
		ang[n++]=arc2.dang;
	}
	//视场四条边与圆弧的交点存入point数组
	for (i = 0;i < 4;i++)
	{
		arcline_intersection(p1[i], p1[i + 1], arc2, intersection, &nn);
		for(j=0;j<nn;j++)//对每个交点进行判断是否存入pseg数组
		{
			a=atan2(intersection[j].y-y0,intersection[j].x-x0)-ang0;
			a=stdangle0(a);
			j1=0;
			for (m = 0;m < n;m++)//与point数组里的点都不重合的交点才存入point数组
			{
				if(fabs(a-ang[m])<1e-8)
				{
					j1=1;//重合，j1置1
					break;
				}
			}
			if(j1==0)
			{
				point[n]=intersection[j];//与point数组里的点都不重合，存入point数组，
				ang[n++]=a;//与圆弧起始角的夹角存入ang数组
			}
		}
	}
	//夹角排序
	for (i = 0;i<n - 1;i++)
		for (j = i + 1;j < n;j++)
		{
			if (ang[i] > ang[j])
			{
				temp = ang[i];
				ang[i] = ang[j];
				ang[j] = temp;
			}
		}
	//计算视场内的弧段
	num=0;
	if(n>=2)
	{
		//计算各弧段扫过的角度，存入dang数组
		for (i = 0;i < n-1;i++)
		{
			dang[i]=ang[i+1]-ang[i];
		}
		for (i = 0;i < n-1;i++)
		{
			temp = ang[i] + ang0;
			a = temp + dang[i] / 2;
			middle.x = x0 + R*cos(a);
			middle.y = y0 + R*sin(a);
			if (judgein(middle))
			{
				arc3[num] = arc2;
				arc3[num].angstart = temp;
				arc3[num++].dang = dang[i];
			}
		}
	}
	return num;
}
//地面点转为透视点，透视点坐标对应屏幕高度为1的值，相机距离地面camH，垂向为z轴，向前看为y轴，向右为x轴，
//透视坐标系原点在屏幕左上角，x轴向右为正，y轴向下为正。
//点在地面
void Pnt_Toushi(MYPOINT pnt, MYPOINT *pnt_t)
{
	double x, dist, fact;
	x = pnt.x;
	dist = pnt.y;
	fact = 0.5 / (dist*tan(angvmax));
	pnt_t->x = x * fact;
	pnt_t->y = camH *fact;
}
//地面点转为透视点，透视点坐标对应屏幕高度为1的值，相机距离地面camH，垂向为z轴，向前看为y轴，向右为x轴，
//透视坐标系原点在屏幕左上角，x轴向右为正，y轴向下为正。
//z为点距离地面的距离
void Pnt_ToushiZ(MYPOINT pnt,double z, MYPOINT *pnt_t)
{
	double x, dist, fact,H;
	x = pnt.x;
	dist = pnt.y;
	H=dist*tan(angvmax);
	fact = 0.5 / H;
	pnt_t->x = x * fact;
	pnt_t->y = (camH-z) *fact;
}

//判断1个点是否在视场内
//需要视点位置pntsight、视场坐标相对全局坐标转动角度angsight，视场的近距yminsight、远距ymaxsight、
//视场左边界角a2hsight、视场右边界角a1hsight为全局变量，输入参数为p1
int judgein(MYPOINT p1)
{
	MYPOINT p2;
	double b;
	int flag = 0;
	x2xp(pntsight, angsight, p1, &p2);//转到视场局部坐标
	if (p2.y > yminsight && p2.y < ymaxsight)
	{
		b = atan2(p2.y, p2.x);
		if (b > a1hsignt && b < a2hsignt)
		{
			flag = 1;
		}
	}
	return flag;
}

//计算一三维线段（全局坐标）与视场边界交点及在视场内部端点，返回值为点数，参数里返回视场内三维线段（全局坐标）。
//适用于铅垂线，水平线，一般空间线
int see3Dline(MY3DPOINT p1, MY3DPOINT p2, LINE3D *line3D)
{
	int n = 0;
	MYPOINT p2D1,p2D2,p2D3,p2D4;
	LINE line;
	double dx,dy,dz,z1,z3,z4;
	MY3DPOINT p3,p4;
	double p1p2,p1p3,p1p4;
	
	//线段端点p1、p2转换为二维点
	p2D1=p1.p;
	p2D2=p2.p;

	p1p2=pp_dist(p2D1,p2D2);
	if(p1p2<1e-6)//铅垂线
	{
		if(judgein(p2D1))//在视场内
		{
			n=2;
			line3D->p1=p1;
			line3D->p2=p2;
		}
	}
	else//水平线，或一般空间线
	{
		//求视场内二维线段p3p4
		n=seeline(p2D1,p2D2,&line);
		if(n>0)//在视场内有线段
		{
			//计算p1p3、p1p4长度
			p2D3=line.p1;
			p2D4=line.p2;
			p1p3=pp_dist(p2D1,p2D3);
			p1p4=pp_dist(p2D1,p2D4);
			//计算p3、p4的z坐标
			z1=p1.z;
			dz=p2.z-p1.z;
			z3=z1+p1p3/p1p2*dz;
			z4=z1+p1p4/p1p2*dz;
			//返回三维线段
			p3.p=p2D3;
			p3.z=z3;
			p4.p=p2D4;
			p4.z=z4;
			line3D->p1=p3;
			line3D->p2=p4;
		}
	}
	return n;
}
//画三维线段的透视图
void drawcar3Dline(LINE3D line3D)
{
	MYPOINT pp1,pp2;
	MYPOINT p1,p2;
	int x1,y1,x2,y2;
	int x11,y11,x22,y22;
	//转端点p1
	//二维点
	p1=line3D.p1.p;

	x2xp(pntsight, angsight, p1, &pp1);//转到相机坐标系
	Pnt_ToushiZ(pp1,line3D.p1.z, &p1);//计算单位屏幕高透视点
	//透视坐标值乘以屏幕高，移到屏幕中心
	x1 =(int)(scrH*p1.x+xcen);
	y1 = (int)(scrH*p1.y+ycen);

	//转端点p2
	//二维点
	p2=line3D.p2.p;

	x2xp(pntsight, angsight, p2, &pp2);//转到相机坐标系
	Pnt_ToushiZ(pp2,line3D.p2.z, &p2);//计算单位屏幕高透视点
	//透视坐标值乘以屏幕高，移到屏幕中心
	x2 =(int)(scrH*p2.x+xcen);
	y2 = (int)(scrH*p2.y+ycen);

	//画透视线
	line(x1,y1,x2,y2);
}
//画轮子透视图，pcen为轮子中心在车子自身坐标系下的三维坐标
void drawwheel(MY3DPOINT pcen)
{
	int i,n;
	double y0,z0,r,theta,dang;
	MYPOINT pp;
	MY3DPOINT pnt,p3D[21];
	LINE3D lineout;
	//在车子自身坐标系下
	y0=pcen.p.y;
	z0=pcen.z;
	r=rwheel;
	theta=0;
	dang=2*pi/20;//20等分
	pnt.p.x = pcen.p.x;
	for (i = 0;i <= 20;i++)
	{
		//轮子圆上20等分点在车子自身坐标系下的三维坐标
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//转到全局坐标
		xp2x(pos,angpos, pnt.p, &pp);
		p3D[i].p=pp;
		p3D[i].z=pnt.z;

		theta += dang;
	}
	//20等分折线透视
	for (i = 0;i < 20;i++)
	{
		n=see3Dline(p3D[i],p3D[i+1],&lineout);
		if(n>0)
			drawcar3Dline(lineout);
	}
}
//画三维多边面，n为顶点数
void draw3Dfill(int n,MY3DPOINT p3D[],int poly[])
{
	int i;
	MYPOINT pp,p1;

	for(i=0;i<n;i++)
	{
		x2xp(pntsight, angsight,p3D[i].p, &pp);//转到相机坐标系
		Pnt_ToushiZ(pp,p3D[i].z, &p1);//计算单位屏幕高透视点
		//透视坐标值乘以屏幕高，移到屏幕中心
		poly[2*i] =(int)(scrH*p1.x+xcen);
		poly[2*i+1] = (int)(scrH*p1.y+ycen);
	}
	//画透视四边形
	fillpoly(n, poly);
}
//画车轮面，输入为车位置，右侧与x轴夹角，外侧中心和内侧中心在小车自身坐标系下的三维点
void drawwheelface(MYPOINT pos1,double angpos1,MY3DPOINT pcenout,MY3DPOINT pcenin)
{
	int poly[20];
	int i,n;
	double y0,z0,r,theta,dang;
	MYPOINT pp;
	MY3DPOINT pnt,p3Dout[11],p3Din[11],p3D[4];
	LINE3D lineout;
	//在车子自身坐标系下
	y0=pcenout.p.y;
	z0=pcenout.z;
	r=rwheel;
	theta=0;
	dang=2*pi/10;

	//车轮外侧面等分点
	pnt.p.x = pcenout.p.x;
	for (i = 0;i <= 10;i++)
	{
		//轮子圆上等分点在车子自身坐标系下的三维坐标
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//转到全局坐标
		xp2x(pos1,angpos1, pnt.p, &pp);
		p3Dout[i].p=pp;
		p3Dout[i].z=pnt.z;

		theta += dang;
	}
	p3Dout[10]=p3Dout[0];

	//车轮内侧面等分点
	//y0=pcenin.p.y;
	//z0=pcenin.z;
	//r=rwheel;
	theta=0;
	pnt.p.x = pcenin.p.x;
	for (i = 0;i <= 10;i++)
	{
		//轮子圆上等分点在车子自身坐标系下的三维坐标
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//转到全局坐标
		xp2x(pos1,angpos1, pnt.p, &pp);
		p3Din[i].p=pp;
		p3Din[i].z=pnt.z;

		theta += dang;
	}
	p3Din[10]=p3Din[0];

	//画内侧面
	setfillstyle(SOLID_FILL,BLACK);
	setcolor(WHITE);
	draw3Dfill(10,p3Din,poly);

	//画滚动面
	setcolor(BLACK);
	for(i=0;i<10;i++)
	{
		p3D[0]=p3Din[i];
		p3D[1]=p3Dout[i];
		p3D[2]=p3Dout[i+1];
		p3D[3]=p3Din[i+1];

		draw3Dfill(4,p3D,poly);
	}

	//画外侧面
	setcolor(WHITE);
	draw3Dfill(10,p3Dout,poly);
}
//获得轮子上半圆的三维等点，从后到前，n为等分数
void wheelup(MY3DPOINT pcen,int n,MY3DPOINT p3Dup[])
{
	int i;
	double y0,z0,r,theta,dang;
	MYPOINT pp;
	MY3DPOINT pnt;
	//在车子自身坐标系下
	y0=pcen.p.y;
	z0=pcen.z;
	r=rwheel;
	theta=pi;
	dang=pi/n;

	//车轮外侧面等分点
	pnt.p.x = pcen.p.x;
	for (i = 0;i <= n;i++)
	{
		//轮子圆上等分点在车子自身坐标系下的三维坐标
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//转到全局坐标
		xp2x(pos,angpos, pnt.p, &pp);
		p3Dup[i].p=pp;
		p3Dup[i].z=pnt.z;

		theta -= dang;
	}
}
//画自动小车面，在相机前1米才画
void drawautocarface()
{
	enum COLORS autocolor=LIGHTMAGENTA;
	MYPOINT pp;
	MYPOINT p0={0,0},p1,p2,p3,p4,ptmp;
	MY3DPOINT p3Dleft[20],p3Dright[20];//车子侧面的全局三维点
	MY3DPOINT p3Dwin[4];
	MY3DPOINT p3D[10];
	LINE3D lineout;
	LINE line1;
	int poly[40];
	int n;
	int i,j;
	//侧轮廓点转到全局坐标
	for (i = 0;i < 7;i++)
	{
		xp2x(pos,angpos,pcarleft[i].p,&pp);
		p3Dleft[i].p=pp;
		p3Dleft[i].z=pcarleft[i].z;

		xp2x(pos,angpos,pcarright[i].p,&pp);
		p3Dright[i].p=pp;
		p3Dright[i].z=pcarright[i].z;
	}
	//左轮上半圆等分点全局坐标
	wheelup(pcarcenleft[1],5,&p3Dleft[7]);
	wheelup(pcarcenleft[0],5,&p3Dleft[13]);
	//右轮上半圆等分点全局坐标
	wheelup(pcarcenright[1],5,&p3Dright[7]);
	wheelup(pcarcenright[0],5,&p3Dright[13]);

	//检查是否在相机前1米，用0、6点
	x2xp(pntsight, angsight,p3Dleft[0].p,&p1);//转到相机坐标系
	x2xp(pntsight, angsight,p3Dleft[6].p,&p2);//转到相机坐标系
	x2xp(pntsight, angsight,p3Dright[0].p,&p3);//转到相机坐标系
	x2xp(pntsight, angsight,p3Dright[6].p,&p4);//转到相机坐标系
	if(p1.y<1 || p2.y<1 || p3.y<1 || p4.y<1)
		return;

	setfillstyle(SOLID_FILL,autocolor);

	//画顶面
	for(i=0;i<6;i++)
	{
		//四边形顶点存到数组
		p3D[0]=p3Dleft[i];
		p3D[1]=p3Dright[i];
		p3D[2]=p3Dright[i+1];
		p3D[3]=p3Dleft[i+1];

		draw3Dfill(4,p3D,poly);
	}

	//判断是否左侧可见
	x2xp(pntsight, angsight,p3Dleft[0].p,&p1);//转到相机坐标系
	x2xp(pntsight, angsight,p3Dleft[6].p,&p2);//转到相机坐标系
	if (p1.y > p2.y)
	{
		ptmp=p1;
		p1=p2;
		p2=ptmp;
	}

	if (stdangle(pp_angle(p0, p2) - pp_angle(p0, p1)) > 0)//左侧可见
	{
		//画轮子,两个左轮，内在前外在后；右后轮，外在前内在后
		for(i=0;i<2;i++)
		{
			drawwheelface(pos,angpos,pcarcenleft[i],pcarcenleftin[i]);
		}
		drawwheelface(pos,angpos,pcarcenrightin[1],pcarcenright[1]);
		
		//画左侧
		setfillstyle(SOLID_FILL,autocolor);
		draw3Dfill(19,p3Dleft,poly);

		//画左窗
		//左窗点转到全局坐标
		for(i=0;i<3;i++)
		{
			for (j = 0;j < 4;j++)
			{
				xp2x(pos,angpos,pcarwinleft[i][j].p,&pp);
				p3Dwin[j].p=pp;
				p3Dwin[j].z=pcarwinleft[i][j].z;
			}
			draw3Dfill(4,p3Dwin,poly);
		}
	}
	else//右侧可见
	{
		//画轮子,两个右轮，内在前外在后；左后轮外在前内在后
		for(i=0;i<2;i++)
		{
			drawwheelface(pos,angpos,pcarcenright[i],pcarcenrightin[i]);
		}
		drawwheelface(pos,angpos,pcarcenleftin[1],pcarcenleft[1]);

		//画右侧
		setfillstyle(SOLID_FILL,autocolor);
		draw3Dfill(19,p3Dright,poly);

		//画右窗
		//右窗点转到全局坐标
		for(i=0;i<3;i++)
		{
			for (j = 0;j < 4;j++)
			{
				xp2x(pos,angpos,pcarwinright[i][j].p,&pp);
				p3Dwin[j].p=pp;
				p3Dwin[j].z=pcarwinright[i][j].z;
			}
			draw3Dfill(4,p3Dwin,poly);
		}
	}
	setfillstyle(SOLID_FILL,WHITE);//恢复为白色
}

//画交互小车面
void drawdrivecarface()
{
	MYPOINT pp;
	MYPOINT p0={0,0},p1,p2,p3,p4,ptmp;
	MY3DPOINT p3Dleft[20],p3Dright[20];//车子侧面的全局三维点
	MY3DPOINT p3D[10];
	int poly[20];
	int i;
	//侧轮廓点转到全局坐标
	for (i = 0;i < 7;i++)
	{
		xp2x(mypos,myangpos,pcarleft[i].p,&pp);
		p3Dleft[i].p=pp;
		p3Dleft[i].z=pcarleft[i].z;

		xp2x(mypos,myangpos,pcarright[i].p,&pp);
		p3Dright[i].p=pp;
		p3Dright[i].z=pcarright[i].z;
	}

	//画后轮
	drawwheelface(mypos,myangpos,pcarcenleftin[1],pcarcenleft[1]);
	drawwheelface(mypos,myangpos,pcarcenright[1],pcarcenrightin[1]);

	setcolor(LIGHTMAGENTA);

	//画顶面
	setfillstyle(SOLID_FILL,mecolor);
	for(i=3;i<6;i++)
	{
		//四边形顶点存到数组
		p3D[0]=p3Dleft[i];
		p3D[1]=p3Dright[i];
		p3D[2]=p3Dright[i+1];
		p3D[3]=p3Dleft[i+1];

		draw3Dfill(4,p3D,poly);
	}

	setfillstyle(SOLID_FILL,WHITE);//恢复为白色
	setcolor(WHITE);
}
//画栏杆
void draw_lanloop(int nseg,ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	setfillstyle(SOLID_FILL,DARKGRAY);
	setcolor(DARKGRAY);
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//直线段
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	
			{
				//画栏杆水平线
				//draw_lanline(lineout);
				//画栏杆垂直线
				draw_lanvline(linein,lineout,draw_lanvbase);
			}
		}
		else//圆弧
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
			{
				//画栏杆水平线
				//draw_lanarc(arcout[j]);
				//画栏杆垂直线
				draw_lanvarc(arcin,arcout[j],draw_lanvbase);
			}
		}
	}
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
}
//画圆弧栏杆
void draw_lanarc(ARC arc1)
{
	MY3DPOINT p3D[4];
	int poly[8];
	double ang1,dang1;
	int ndiv,i;
	LINE line;
	//约2m等分
	ndiv=(int)(arc1.dang*arc1.r/2.0)+1;
	ang1=arc1.angstart;
	dang1=arc1.dang/ndiv;
	arc1.dang=dang1;
	for (i = 0;i < ndiv;i++)
	{
		arc1.angstart=ang1;
		//画每一段圆弧
		line.p1=getarcpnt(arc1,ang1);
		line.p2=getarcpnt(arc1,ang1+dang1);
		draw_lanline(line);

		ang1+=dang1;
	}
}
//画水平线栏杆，输入为二维线段
void draw_lanline(LINE line1)
{
	MY3DPOINT p3D[4];
	int poly[8];
	p3D[0].p=line1.p1;
	p3D[0].z=0.5;
	p3D[1].p=line1.p2;
	p3D[1].z=0.5;
	p3D[2]=p3D[1];
	p3D[2].z+=0.05;
	p3D[3]=p3D[0];
	p3D[3].z+=0.05;
	draw3Dfill(4,p3D,poly);
}
//画直线上的垂直栏杆
void draw_lanvline(LINE linearea,LINE line,BASEFUNCPTR funptr)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	double ang,angx;
	MYPOINT pnt;
	ang=pp_angle(linearea.p1,linearea.p2);
	angx=ang-pi/2;
	//判断在后半段则为1
	at1=wheredashline(linearea,line.p1,&n1);
	at2=wheredashline(linearea,line.p2,&n2);
	//转换为在前半段为1
	at1=(at1==0?1:0);
	at2=(at1==0?1:0);
	if (n2 == n1)//在同一段
	{
		if (at1 == 1)//点1在本段中点前
		{
			if (at2 == 0)//点2在本段中点后
			{
				pnt=getpangpnt(linearea.p1,ang,(n1+0.5)*dashlen);
				//画垂直栏杆
				funptr(pnt,angx);
			}
		}
	}
	else//在不同段
	{
		//点1在中点前，则起始段为n1，否则为n1+1
		//点1在中点前，栏杆数在中间栏杆数基础上加1
		//点2在中点后，栏杆数在中间栏杆数基础上加1
		n=n2-n1-1;//中间栏杆数
		if(at1==1)//点1在本段中点前
		{
			nstart=n1;
			n++;
			if (at2 == 0)//点2在本段中点后
				n++;
		}
		else//点1在本段中点后
		{
			nstart=n1+1;
			if (at2 == 0)//点2在本段中点后
				n++;
		}
		for (i = 0;i < n;i++)//画栏杆
		{
			m=nstart+i;	
			pnt=getpangpnt(linearea.p1,ang,(m+0.5)*dashlen);
			funptr(pnt,angx);
		}
	}
}
//画圆弧线上的垂直栏杆，按角度等分为多段，求可见圆弧段所包围的栏杆点
void draw_lanvarc(ARC arcarea,ARC arc,BASEFUNCPTR funptr)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	ARC arc1;
	double ang1,ang2,ang;
	MYPOINT pnt;
	arc1=arcarea;
	ang1=arc.angstart;
	ang2=ang1+arc.dang;
	//判断在后半段则为1
	at1=wheredasharc(arcarea,ang1,&n1);
	at2=wheredasharc(arcarea,ang2,&n2);
	//转换为在前半段为1
	at1=(at1==0?1:0);
	at2=(at1==0?1:0);
	if (n2 == n1)//在同一段
	{
		if (at1 == 1)//点1本段中点前
		{
			if (at2 == 0)//点2在本段中点后
			{
				ang=arcarea.angstart+(n1+0.5)*dashang;//栏杆处的径向
				pnt=getarcpnt(arcarea,ang);
				funptr(pnt,ang);
			}
		}
	}
	else//在不同段
	{
		//点1在中点前，则起始段为n1，否则为n1+1
		//点1在中点前，栏杆数在中间栏杆数基础上加1
		//点2在中点后，栏杆数在中间栏杆数基础上加1
		n=n2-n1-1;//中间栏杆数
		if(at1==1)//点1在本段中点前
		{
			nstart=n1;
			n++;
			if (at2 == 0)//点2在本段中点后
				n++;
		}
		else//点1在本段中点后
		{
			nstart=n1+1;
			if (at2 == 0)//点2在本段中点后
				n++;
		}
		for (i = 0;i < n;i++)//画栏杆
		{
			m=nstart+i;	
			ang=arcarea.angstart+(m+0.5)*dashang;//栏杆处的径向
			pnt=getarcpnt(arcarea,ang);
			funptr(pnt,ang);
		}
	}
}

//由二维点和路线的法线方向，画一根垂直栏杆
void draw_lanvbase(MYPOINT pnt,double ang)
{
	MY3DPOINT p3D[4];
	int poly[8];
	LINE line1;
	line1.p1=getpangpnt(pnt,ang+pi/2,0.025);
	line1.p2=getpangpnt(pnt,ang-pi/2,0.025);
	p3D[0].p=line1.p1;
	p3D[0].z=0;
	p3D[1].p=line1.p2;
	p3D[1].z=0;
	p3D[2]=p3D[1];
	p3D[2].z+=0.5;
	p3D[3]=p3D[0];
	p3D[3].z+=0.5;
	draw3Dfill(4,p3D,poly);
}
//画树
void draw_treeloop(int nseg,ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	setfillstyle(SOLID_FILL,DARKGRAY);
	setcolor(DARKGRAY);
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//直线段
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	
			{
				draw_lanvline(linein,lineout,draw_treebase);
			}
		}
		else//圆弧
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
			{
				//画栏杆水平线
				//draw_lanarc(arcout[j]);
				//画栏杆垂直线
				draw_lanvarc(arcin,arcout[j],draw_treebase);
			}
		}
	}
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
}
//由二维点和路线的法线方向，画一颗树
void draw_treebase(MYPOINT pnt,double ang)
{
	MY3DPOINT p3D[4];
	int poly[8];
	LINE line1;
	//画树干
	line1.p1=getpangpnt(pnt,ang+pi/2,0.025);
	line1.p2=getpangpnt(pnt,ang-pi/2,0.025);
	p3D[0].p=line1.p1;
	p3D[0].z=0;
	p3D[1].p=line1.p2;
	p3D[1].z=0;
	p3D[2]=p3D[1];
	p3D[2].z+=1;
	p3D[3]=p3D[0];
	p3D[3].z+=1;
	draw3Dfill(4,p3D,poly);
	//画树冠
	line1.p1=getpangpnt(pnt,ang+pi/2,0.75);
	line1.p2=getpangpnt(pnt,ang-pi/2,0.75);
	p3D[0].p=line1.p1;
	p3D[0].z=1;
	p3D[1].p=line1.p2;
	p3D[1].z=1;
	p3D[2].p=pnt;
	p3D[2].z=3;
	draw3Dfill(3,p3D,poly);
}
