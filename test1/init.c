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

void roadinit()
{
	int i,pathno=1;
	double r0,r1;
	r0=road_r-0.5*roadW;
	r1=road_r-roadW;
	if(segs==4)//四边形跑道
	{
		//跑道中间虚线
		for(i=0;i<2;i++)
		{
			setrecroadloop(r0+i*roadW, road_linedash[i], road_arcdash[i], roadareadash[i]);
		}
		//跑道外边界
		setrecroadloop(road_r+1.5*roadW, road_lineout, road_arcout, roadareaout);
		//跑道内边界
		setrecroadloop(road_r-1.5*roadW, road_linein, road_arcin, roadareain);
		//自动行驶路线
		for(i=0;i<3;i++)
		{
			setrecroadloop(r1+i*roadW, auto_line[i], auto_arc[i],autoroad[i]);
		}
	}
	else if(segs==3)//三角形跑道
	{
		//跑道中间虚线
		for(i=0;i<2;i++)
		{
			settriroadloop(r0+i*roadW, road_linedash[i], road_arcdash[i], roadareadash[i]);
		}
		//跑道外边界
		settriroadloop(road_r+1.5*roadW, road_lineout, road_arcout, roadareaout);
		//跑道内边界
		settriroadloop(road_r-1.5*roadW, road_linein, road_arcin, roadareain);
		//自动行驶路线
		for(i=0;i<3;i++)
		{
			settriroadloop(r1+i*roadW, auto_line[i], auto_arc[i],autoroad[i]);
		}
	}
	else//其他段数跑道
	{
		//跑道中间虚线
		for(i=0;i<2;i++)
		{
			setroadloop(r0+i*roadW, road_linedash[i], road_arcdash[i], roadareadash[i]);
		}
		//跑道外边界
		setroadloop(road_r+1.5*roadW, road_lineout, road_arcout, roadareaout);
		//跑道内边界
		setroadloop(road_r-1.5*roadW, road_linein, road_arcin, roadareain);
		//自动行驶路线
		for(i=0;i<3;i++)
		{
			setroadloop(r1+i*roadW, auto_line[i], auto_arc[i],autoroad[i]);
		}
	}
	offsetauto=r0+pathno*roadW-road_r;
	pos.x=road_halfo+road_r+offsetauto;
	pos.y=0;
	sumauto=pos.y;
	//sumautoold=sumauto;

	offsetdrive=-roadW;
	mypos.x=road_halfo+road_r+offsetdrive;
	mypos.y=0;
	sumdrive=mypos.y;
	//sumdriveold=sumdrive;
}
//初始化四边形跑道
void setrecroadloop(double r, LINE li[], ARC ar[], ROADAREA ra[])
{
	MYPOINT p1,p2;
	int i;
	double road_halfl= road_halfo+r;
	p1.x=road_halfl;
	p1.y=-road_halfo;
	p2.x=p1.x;
	p2.y=-p1.y;
	li[0].p1=p1;
	li[0].p2=p2;

	p1.x=road_halfo;
	p1.y=road_halfl;
	p2.x=-p1.x;
	p2.y=p1.y;
	li[1].p1=p1;
	li[1].p2=p2;

	p1.x=-road_halfl;
	p1.y=road_halfo;
	p2.x=p1.x;
	p2.y=-p1.y;
	li[2].p1=p1;
	li[2].p2=p2;

	p1.x=-road_halfo;
	p1.y=-road_halfl;
	p2.x=-p1.x;
	p2.y=p1.y;
	li[3].p1=p1;
	li[3].p2=p2;

	ar[0].x=road_halfo;
	ar[0].y=ar[0].x;
	ar[0].r=r;
	ar[0].angstart=0;
	ar[0].dang=pi/2;

	ar[1].x=-road_halfo;
	ar[1].y=-ar[1].x;
	ar[1].r=r;
	ar[1].angstart=pi/2;
	ar[1].dang=pi/2;

	ar[2].x=-road_halfo;
	ar[2].y=ar[2].x;
	ar[2].r=r;
	ar[2].angstart=pi;
	ar[2].dang=pi/2;

	ar[3].x=road_halfo;
	ar[3].y=-ar[3].x;
	ar[3].r=r;
	ar[3].angstart=3*pi/2;
	ar[3].dang=pi/2;

	for (i = 0;i < 4;i++)
	{
		strcpy(ra[2*i].type,"line");
		ra[2*i].pcurve=&li[i];
		strcpy(ra[2*i+1].type,"arc");
		ra[2*i+1].pcurve=&ar[i];
	}
}
//初始化三角形跑道
void settriroadloop(double r, LINE li[], ARC ar[], ROADAREA ra[])
{
	int i;
	MYPOINT p1,p2,pc0,pc1,pc2;
	double theta0=2*pi/3,theta;
	double road_halfl= road_halfo+r;
	p1.x=road_halfl;
	p1.y=-road_halfo;
	p2.x=p1.x;
	p2.y=-p1.y;
	li[0].p1=p1;
	li[0].p2=p2;

	pc0.x=road_halfo;
	pc0.y=road_halfo;
	pc2.x=pc0.x;
	pc2.y=-pc0.y;

	theta=theta0;
	p1.x=pc0.x+r*cos(theta);
	p1.y=pc0.y+r*sin(theta);
	theta+=pi/2;
	p2.x=p1.x+2*road_halfo*cos(theta);
	p2.y=p1.y+2*road_halfo*sin(theta);
	li[1].p1=p1;
	li[1].p2=p2;

	pc1.x=pc0.x+2*road_halfo*cos(theta);
	pc1.y=0;
	p1=li[1].p2;
	p1.y=-p1.y;
	p2=li[1].p1;
	p2.y=-p2.y;
	li[2].p1=p1;
	li[2].p2=p2;

	ar[0].x=pc0.x;
	ar[0].y=pc0.y;
	ar[0].r=r;
	ar[0].angstart=0;
	ar[0].dang=theta0;

	ar[1].x=pc1.x;
	ar[1].y=pc1.y;
	ar[1].r=r;
	ar[1].angstart=theta0;
	ar[1].dang=theta0;

	ar[2].x=pc2.x;
	ar[2].y=pc2.y;
	ar[2].r=r;
	ar[2].angstart=2*theta0;
	ar[2].dang=theta0;

	for (i = 0;i < 3;i++)
	{
		strcpy(ra[2*i].type,"line");
		ra[2*i].pcurve=&li[i];
		strcpy(ra[2*i+1].type,"arc");
		ra[2*i+1].pcurve=&ar[i];
	}
}
void setroadloop(double r, LINE li[], ARC ar[], ROADAREA ra[])
{
	int i;
	MYPOINT p0,p1={100,-100},p2={100,100};
	double a=0;//a为直线段平移方向
	double b=pi/segs;//b为圆心连线第2点的极坐标角度
	double len=100.0/sin(b);//正多边形外接圆半径
	p0.y=0;
	p0.x=100.0-100.0/tan(b);
	for(i=0;i<segs;i++)
	{
		li[i].p1=getpangpnt(p1,a,r);
		li[i].p2=getpangpnt(p2,a,r);

		ar[i].x=p2.x;
		ar[i].y=p2.y;
		ar[i].r=r;
		ar[i].angstart=a;
		ar[i].dang=2*pi/segs;

		a+=2*pi/segs;
		b+=2*pi/segs;
		p1=p2;
		p2=getpangpnt(p0,b,len);
	}

	for (i = 0;i < segs;i++)
	{
		strcpy(ra[2*i].type,"line");
		ra[2*i].pcurve=&li[i];
		strcpy(ra[2*i+1].type,"arc");
		ra[2*i+1].pcurve=&ar[i];
	}

}
//全局变量初始化
void GlobalInit()
{
	double theta;
	int n;
	int i,j;
	//平面图视点和视角选择
	//sight=Global;
	//平面图显示选择
	//pingmian=0;//为1时显示平面图
	//透视图显示选择
	toushi=1;//为1时显示透视图
	//kroad=0.8;//道路平面图放大系数

	//====车行、档，跑道选择变量====
	//segs=6;//确定跑道为三角形，还是四边形
	//交互行驶车型选择，改高度，颜色
	//mecolor=YELLOW;
	myshift=0;//手动档档位
	//geartype=	STICK;//STICK; //AUTO

	oldstate=0;//单击键前一状态，1为按下
	trig=0;//为1表示单击键经过了一次松开到按下的转变

	//posping.x=0;
	//posping.y=0;
	//angposping=0;

	dly=1;

	throttledrive=0;//交互驾驶车油门
	throttleauto=1;//自动驾驶车油门

	rwheel=0.310;//轮胎半径
	areaying=2.45;//迎风面积
	weight=1750;//车质量
	g=9.8;//重力加速度
	rou=1.29;//空气密度
	Cd=1.5;//风阻系数
	Crr=0.05;//滚动摩擦系数
	//各档传动比1.7~1.8，如六档变速器7.640,4.835,2.857,1.895,1.337,1
	masterRatio=3.3;//主减速器变速比，3.5-5
	eta=0.9;//传动效率
	torque=170;//扭矩
	//各档对应的变速箱变速比，1档对应下标1,2档对应下标2
	gear[0]=0;
	gear[1]=4;
	gear[2]=3;
	//vdrivemax=20;//20交互行驶最大速度
	//各档对应的变速箱变速比
	vmaxshift[0]=0;
	vmaxshift[1]=vdrivemax/2;
	vmaxshift[2]=vdrivemax;

	cmd = 0;
	keystate=0;
	itext=0;//每几帧显示速度等信息的控制变量

	//视点高、水平面位置、视场坐标相对全局坐标转动角度
	camH = 3;//单位m
	w = 0.1;//线半宽，单位m

	carHW=0.9;//汽车半宽
	carL=4;//汽车长度
	v = 0;//转弯半径
	R = 0;//转弯半径
	vautomax=19;//自动行驶最大速度
	vauto=0;//自动行驶速度
	tick = 1000.0/CLOCKS_PER_SEC;
	rdrive=60;

	//跑道中心线参数
	roadW=5;//3.5;

	kdash=1;//虚线周期放大系数

	road_halfo=100;//道路中间线圆弧圆心与坐标轴距离
	road_r=153;//道路中心线弯道圆弧半径

	//ROADAREA *pathauto;
	autoH=1.4;//自动行驶车高度
	nopos=0;//自动行驶当前段号
	pathno=1;//自动行驶当前路线号
	sumauto=0;//自动行驶对应自动行驶路线路程
	//sumautoold=0;
	angpos=0;//自动行驶车右方向与x轴的当前夹角
	//angposold=0;//自动行驶车右方向与x轴的前一夹角

	sumdrive=0;//交互行驶对应自动行驶路线路程
	//sumdriveold=0;
	myangpos=0;//-pi/6;//交互行驶右方向与x轴的夹角
	//myangposold=0;//交互行驶车右方向与x轴的前一夹角

	//屏幕参数
	scrW = 640.0;
	scrH=480.0;	
	startclr=(scrW-scrH)/2;
	pi = 4.0*atan(1.0);
	vmaxshift[2]=vdrivemax;
	//ohstep=1.5*vauto/1000.0*tick;
	oneauto=vauto/1000.0*tick;
	dashlen=4*kdash;//虚线周期长
	theta=2*pi/segs;
	n=(int)(theta*road_r/dashlen);//按直虚线周期数求等分数
	dashang=theta/n;//pi/2.0/(60.0/kdash);
	endline.p1.x=road_r+road_halfo-1.5*roadW;
	endline.p1.y=0;
	endline.p2.x=road_r+road_halfo+1.5*roadW;
	endline.p2.y=0;
	k = scrW / scrH;//屏幕宽高比
	xcen= scrW-scrH/2;
	ycen=scrH/2;
	angvmax = pi/6;//视场的垂向半视角
	yminsight =2*camH, ymaxsight = 200+yminsight;//视场的近距、远距
	anghmax = angvmax;//视场的水平半视角，与垂直半视角相等，屏幕两边有没有用到的地方
	a2hsignt = pi / 2 + anghmax;//视场左边界角
	a1hsignt = pi / 2 - anghmax;//视场右边界角
	p[0].x=-yminsight * tan(anghmax);
	p[0].y=yminsight;
	p[1].x=yminsight * tan(anghmax);
	p[1].y=yminsight;
	p[2].x=ymaxsight * tan(anghmax);
	p[2].y=ymaxsight;
	p[3].x=-ymaxsight * tan(anghmax);
	p[3].y=ymaxsight;
	p[4]=p[0];

	//车子自身坐标系下的轮廓点坐标,右为x，车头中点为原点
	//侧面头底到尾底
	pcarright[0].p.y=0;
	pcarright[0].z=0.3100;
	pcarright[1].p.y=-0.0686;
	pcarright[1].z=0.8117;
	pcarright[2].p.y=-0.8571;
	pcarright[2].z=0.9197;
	pcarright[3].p.y=-1.7056;
	pcarright[3].z=1.4;
	pcarright[4].p.y=-3.5426;
	pcarright[4].z=1.4;
	pcarright[5].p.y=-4.0;
	pcarright[5].z=0.8739;
	pcarright[6].p.y=-4.0;
	pcarright[6].z=0.31;

	for(i=0;i<7;i++)
	{
		pcarleft[i]=pcarright[i];
		pcarright[i].p.x=0.9;
		pcarleft[i].p.x=-0.9;
	}

	pcar[0]=pcarleft[0].p;
	pcar[1]=pcarright[0].p;
	pcar[2]=pcarright[6].p;
	pcar[3]=pcarleft[6].p;
	pcar[4]=pcar[0];

	/*pcar[0].x=-carHW;
	pcar[0].y=0;
	pcar[1].x=carHW;
	pcar[1].y=0;
	pcar[2].x=carHW;
	pcar[2].y=-carL;
	pcar[3].x=-carHW;
	pcar[3].y=-carL;
	pcar[4]=pcar[0];*/

	//前后轮外侧中心
	pcarcenright[0].p.y=-0.7;
	pcarcenright[0].z=0.31;
	pcarcenright[1].p.y=-3.3;
	pcarcenright[1].z=0.31;

	for(i=0;i<2;i++)
	{
		pcarcenleft[i]=pcarcenright[i];
		pcarcenright[i].p.x=0.9;
		pcarcenleft[i].p.x=-0.9;
	}

	//前后轮内侧中心
	for(i=0;i<2;i++)
	{
		pcarcenrightin[i]=pcarcenright[i];
		pcarcenleftin[i]=pcarcenright[i];
		pcarcenrightin[i].p.x=0.9-0.215;
		pcarcenleftin[i].p.x=-(0.9-0.215);
	}

	//车窗
	pcarwinright[0][0].p.y=-1.0632;
	pcarwinright[0][0].z=0.9167;
	pcarwinright[0][1].p.y=-1.7684;
	pcarwinright[0][1].z=1.3159;
	pcarwinright[0][2].p.y=-2.3720;
	pcarwinright[0][2].z=1.3159;
	pcarwinright[0][3].p.y=-2.2180;
	pcarwinright[0][3].z=0.8999;

	pcarwinright[1][0].p.y=-2.4497;
	pcarwinright[1][0].z=0.8965;
	pcarwinright[1][1].p.y=-2.5407;
	pcarwinright[1][1].z=1.3159;
	pcarwinright[1][2].p.y=-2.9585;
	pcarwinright[1][2].z=1.3159;
	pcarwinright[1][3].p.y=-3.1788;
	pcarwinright[1][3].z=0.8858;

	pcarwinright[2][0].p.y=-3.3241;
	pcarwinright[2][0].z=0.8837;
	pcarwinright[2][1].p.y=-3.1027;
	pcarwinright[2][1].z=1.3159;
	pcarwinright[2][2].p.y=-3.4861;
	pcarwinright[2][2].z=1.3159;
	pcarwinright[2][3].p.y=-3.8688;
	pcarwinright[2][3].z=0.8758;

	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			pcarwinleft[i][j]=pcarwinright[i][j];
			pcarwinright[i][j].p.x=0.9;
			pcarwinleft[i][j].p.x=-0.9;
		}
	}
}