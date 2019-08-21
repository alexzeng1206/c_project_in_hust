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

void roadinit()
{
	int i,pathno=1;
	double r0,r1;
	r0=road_r-0.5*roadW;
	r1=road_r-roadW;
	if(segs==4)//�ı����ܵ�
	{
		//�ܵ��м�����
		for(i=0;i<2;i++)
		{
			setrecroadloop(r0+i*roadW, road_linedash[i], road_arcdash[i], roadareadash[i]);
		}
		//�ܵ���߽�
		setrecroadloop(road_r+1.5*roadW, road_lineout, road_arcout, roadareaout);
		//�ܵ��ڱ߽�
		setrecroadloop(road_r-1.5*roadW, road_linein, road_arcin, roadareain);
		//�Զ���ʻ·��
		for(i=0;i<3;i++)
		{
			setrecroadloop(r1+i*roadW, auto_line[i], auto_arc[i],autoroad[i]);
		}
	}
	else if(segs==3)//�������ܵ�
	{
		//�ܵ��м�����
		for(i=0;i<2;i++)
		{
			settriroadloop(r0+i*roadW, road_linedash[i], road_arcdash[i], roadareadash[i]);
		}
		//�ܵ���߽�
		settriroadloop(road_r+1.5*roadW, road_lineout, road_arcout, roadareaout);
		//�ܵ��ڱ߽�
		settriroadloop(road_r-1.5*roadW, road_linein, road_arcin, roadareain);
		//�Զ���ʻ·��
		for(i=0;i<3;i++)
		{
			settriroadloop(r1+i*roadW, auto_line[i], auto_arc[i],autoroad[i]);
		}
	}
	else//���������ܵ�
	{
		//�ܵ��м�����
		for(i=0;i<2;i++)
		{
			setroadloop(r0+i*roadW, road_linedash[i], road_arcdash[i], roadareadash[i]);
		}
		//�ܵ���߽�
		setroadloop(road_r+1.5*roadW, road_lineout, road_arcout, roadareaout);
		//�ܵ��ڱ߽�
		setroadloop(road_r-1.5*roadW, road_linein, road_arcin, roadareain);
		//�Զ���ʻ·��
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
//��ʼ���ı����ܵ�
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
//��ʼ���������ܵ�
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
	double a=0;//aΪֱ�߶�ƽ�Ʒ���
	double b=pi/segs;//bΪԲ�����ߵ�2��ļ�����Ƕ�
	double len=100.0/sin(b);//����������Բ�뾶
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
//ȫ�ֱ�����ʼ��
void GlobalInit()
{
	double theta;
	int n;
	int i,j;
	//ƽ��ͼ�ӵ���ӽ�ѡ��
	//sight=Global;
	//ƽ��ͼ��ʾѡ��
	//pingmian=0;//Ϊ1ʱ��ʾƽ��ͼ
	//͸��ͼ��ʾѡ��
	toushi=1;//Ϊ1ʱ��ʾ͸��ͼ
	//kroad=0.8;//��·ƽ��ͼ�Ŵ�ϵ��

	//====���С������ܵ�ѡ�����====
	//segs=6;//ȷ���ܵ�Ϊ�����Σ������ı���
	//������ʻ����ѡ�񣬸ĸ߶ȣ���ɫ
	//mecolor=YELLOW;
	myshift=0;//�ֶ�����λ
	//geartype=	STICK;//STICK; //AUTO

	oldstate=0;//������ǰһ״̬��1Ϊ����
	trig=0;//Ϊ1��ʾ������������һ���ɿ������µ�ת��

	//posping.x=0;
	//posping.y=0;
	//angposping=0;

	dly=1;

	throttledrive=0;//������ʻ������
	throttleauto=1;//�Զ���ʻ������

	rwheel=0.310;//��̥�뾶
	areaying=2.45;//ӭ�����
	weight=1750;//������
	g=9.8;//�������ٶ�
	rou=1.29;//�����ܶ�
	Cd=1.5;//����ϵ��
	Crr=0.05;//����Ħ��ϵ��
	//����������1.7~1.8��������������7.640,4.835,2.857,1.895,1.337,1
	masterRatio=3.3;//�����������ٱȣ�3.5-5
	eta=0.9;//����Ч��
	torque=170;//Ť��
	//������Ӧ�ı�������ٱȣ�1����Ӧ�±�1,2����Ӧ�±�2
	gear[0]=0;
	gear[1]=4;
	gear[2]=3;
	//vdrivemax=20;//20������ʻ����ٶ�
	//������Ӧ�ı�������ٱ�
	vmaxshift[0]=0;
	vmaxshift[1]=vdrivemax/2;
	vmaxshift[2]=vdrivemax;

	cmd = 0;
	keystate=0;
	itext=0;//ÿ��֡��ʾ�ٶȵ���Ϣ�Ŀ��Ʊ���

	//�ӵ�ߡ�ˮƽ��λ�á��ӳ��������ȫ������ת���Ƕ�
	camH = 3;//��λm
	w = 0.1;//�߰����λm

	carHW=0.9;//�������
	carL=4;//��������
	v = 0;//ת��뾶
	R = 0;//ת��뾶
	vautomax=19;//�Զ���ʻ����ٶ�
	vauto=0;//�Զ���ʻ�ٶ�
	tick = 1000.0/CLOCKS_PER_SEC;
	rdrive=60;

	//�ܵ������߲���
	roadW=5;//3.5;

	kdash=1;//�������ڷŴ�ϵ��

	road_halfo=100;//��·�м���Բ��Բ�������������
	road_r=153;//��·���������Բ���뾶

	//ROADAREA *pathauto;
	autoH=1.4;//�Զ���ʻ���߶�
	nopos=0;//�Զ���ʻ��ǰ�κ�
	pathno=1;//�Զ���ʻ��ǰ·�ߺ�
	sumauto=0;//�Զ���ʻ��Ӧ�Զ���ʻ·��·��
	//sumautoold=0;
	angpos=0;//�Զ���ʻ���ҷ�����x��ĵ�ǰ�н�
	//angposold=0;//�Զ���ʻ���ҷ�����x���ǰһ�н�

	sumdrive=0;//������ʻ��Ӧ�Զ���ʻ·��·��
	//sumdriveold=0;
	myangpos=0;//-pi/6;//������ʻ�ҷ�����x��ļн�
	//myangposold=0;//������ʻ���ҷ�����x���ǰһ�н�

	//��Ļ����
	scrW = 640.0;
	scrH=480.0;	
	startclr=(scrW-scrH)/2;
	pi = 4.0*atan(1.0);
	vmaxshift[2]=vdrivemax;
	//ohstep=1.5*vauto/1000.0*tick;
	oneauto=vauto/1000.0*tick;
	dashlen=4*kdash;//�������ڳ�
	theta=2*pi/segs;
	n=(int)(theta*road_r/dashlen);//��ֱ������������ȷ���
	dashang=theta/n;//pi/2.0/(60.0/kdash);
	endline.p1.x=road_r+road_halfo-1.5*roadW;
	endline.p1.y=0;
	endline.p2.x=road_r+road_halfo+1.5*roadW;
	endline.p2.y=0;
	k = scrW / scrH;//��Ļ��߱�
	xcen= scrW-scrH/2;
	ycen=scrH/2;
	angvmax = pi/6;//�ӳ��Ĵ�����ӽ�
	yminsight =2*camH, ymaxsight = 200+yminsight;//�ӳ��Ľ��ࡢԶ��
	anghmax = angvmax;//�ӳ���ˮƽ���ӽǣ��봹ֱ���ӽ���ȣ���Ļ������û���õ��ĵط�
	a2hsignt = pi / 2 + anghmax;//�ӳ���߽��
	a1hsignt = pi / 2 - anghmax;//�ӳ��ұ߽��
	p[0].x=-yminsight * tan(anghmax);
	p[0].y=yminsight;
	p[1].x=yminsight * tan(anghmax);
	p[1].y=yminsight;
	p[2].x=ymaxsight * tan(anghmax);
	p[2].y=ymaxsight;
	p[3].x=-ymaxsight * tan(anghmax);
	p[3].y=ymaxsight;
	p[4]=p[0];

	//������������ϵ�µ�����������,��Ϊx����ͷ�е�Ϊԭ��
	//����ͷ�׵�β��
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

	//ǰ�����������
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

	//ǰ�����ڲ�����
	for(i=0;i<2;i++)
	{
		pcarcenrightin[i]=pcarcenright[i];
		pcarcenleftin[i]=pcarcenright[i];
		pcarcenrightin[i].p.x=0.9-0.215;
		pcarcenleftin[i].p.x=-(0.9-0.215);
	}

	//����
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