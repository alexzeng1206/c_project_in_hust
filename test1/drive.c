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

void drivecar()
{
	MYPOINT mypos1;
	double newang,yidong;
	LINE line2;
	ARC arc2;
	double len;
	if(geartype==AUTO)
		get_automatic_vlen(&v,vdrivemax,throttledrive,&len);
	else
		get_stick_vlen(&v,throttledrive,&len);
	if (len != 0)
	{
		//savedriveold();
		if(R==0)
			twowheelstraight(len,&mypos1,&newang,&yidong,&line2);
		else
			twowheelturn(len,&mypos1,&newang,&yidong,&arc2);

		offsetdrive=jicheng(mypos,mypos1,&sumdrive);

		mypos=mypos1;
		myangpos=newang;
	}
}

void get_stick_vlen(double *vcur,double throttle,double *len)
{
	double vold=*vcur,vmax,vnew;
	double a;
	double timesec=tick/1000,t1;
	double rollResist;
	double drag;
	double fraction;
	double F;
	double gearRatio;


	//�õ���λ��Ӧ�ı��ٱȺ�����ٶ�
	gearRatio=gear[myshift];
	vmax=vmaxshift[myshift];
	if(vold>vmax && throttle==1)//�������������ţ����ٶ���Ϊ-1
	{
		a=-1;
	}
	else
	{
		//����Ħ������
		rollResist=Crr*weight*g;
		//�������
		drag=0.5*rou*areaying*Cd*vold*vold;
		//����ǣ����
		fraction=throttle*torque*gearRatio*masterRatio*eta/rwheel;
		//�������
		F=fraction-rollResist-drag;
		//������ٶ�
		a=F/weight;
	}
	vnew=vold+a*timesec;//��������ʱ���ٶ�
	if(throttle>0)//������
	{
		if(a<0)//���٣����ܵ�������ٶ�
		{
			if(vnew<vmax)
				vnew=vmax;
		}
		else//���������ܸ�������ٶ�
		{
			if(vnew>vmax)
				vnew=vmax;
		}
	}
	else//�����ţ�����ͣ����
	{
		if(vnew<0)
			vnew=0;
	}
	*len=0.5*(vold+vnew)*timesec;//��ʻһ��·��
	//�������ٶȲ���Σ���������ٶȲ����
	t1=(vnew-vold)/a;
	if(t1<timesec)
		*len=0.5*(vold+vnew)*t1+vnew*(timesec-t1);
	*vcur=vnew;
}
//˫�������⻷����ת�䵽��һ��λ�ã�mypos1,myangpos1,yidong����Ӧ���е㣬arc2Ϊ�������ӵĹ켣
void twowheelturn(double len, MYPOINT *mypos1, double *myangpos1, double *yidong, ARC *arc2)
{
	MYPOINT mypos1L,mypos1R;
	double myangpos1L, myangpos1R;
	double yidongL,yidongR;
	ARC arc2L,arc2R;
	onewheelturn(-carHW, len, &mypos1L, &myangpos1L, &yidongL,&arc2L);
	onewheelturn(carHW, len, &mypos1R, &myangpos1R, &yidongR,&arc2R);
	if (yidongL <= yidongR)
	{
		*mypos1=mypos1L;
		*myangpos1=myangpos1L;
		*yidong=yidongL;
		*arc2=arc2L;
	}
	else
	{
		*mypos1=mypos1R;
		*myangpos1=myangpos1R;
		*yidong=yidongR;
		*arc2=arc2R;
	}
}
//˫�������⻷����ֱ�е���һ��λ�ã�mypos1,myangpos1,yidong����Ӧ���е㣬line2Ϊ�������ӵĹ켣
void twowheelstraight(double len, MYPOINT *mypos1, double *myangpos1, double *yidong, LINE *line2)
{
	MYPOINT mypos1L,mypos1R;
	double myangpos1L, myangpos1R;
	double yidongL,yidongR;
	LINE line2L,line2R;
	onewheelstraight(-carHW, len, &mypos1L, &myangpos1L, &yidongL,&line2L);
	onewheelstraight(carHW, len, &mypos1R, &myangpos1R, &yidongR,&line2R);
	if (yidongL <= yidongR)
	{
		*mypos1=mypos1L;
		*myangpos1=myangpos1L;
		*yidong=yidongL;
		*line2=line2L;
	}
	else
	{
		*mypos1=mypos1R;
		*myangpos1=myangpos1R;
		*yidong=yidongR;
		*line2=line2R;
	}
}
//���������⻷����ת�䵽��һ��λ�ã�drΪ������������ĵľ��룬��Ϊ����mypos1,myangpos1,yidong����Ӧ���е㣬arc2Ϊ���ӵĹ켣
void onewheelturn(double dr, double len, MYPOINT *mypos1, double *myangpos1, double *yidong, ARC *arc2)
{
	MYPOINT mypos1N,mypos1W;
	double myangpos1N, myangpos1W;
	double yidongN,yidongW;
	ARC arc2N,arc2W;
	oneloopturn(roadareain,dr, len, &mypos1N, &myangpos1N, &yidongN,&arc2N);
	oneloopturn(roadareaout,dr, len, &mypos1W, &myangpos1W, &yidongW,&arc2W);
	if (yidongN <= yidongW)
	{
		*mypos1=mypos1N;
		*myangpos1=myangpos1N;
		*yidong=yidongN;
		*arc2=arc2N;
	}
	else
	{
		*mypos1=mypos1W;
		*myangpos1=myangpos1W;
		*yidong=yidongW;
		*arc2=arc2W;
	}
}
//���������⻷����ֱ�е���һ��λ�ã�drΪ������������ĵľ��룬��Ϊ����mypos1,myangpos1,yidong����Ӧ���е㣬line2Ϊ���ӵĹ켣
void onewheelstraight(double dr, double len, MYPOINT *mypos1, double *myangpos1, double *yidong, LINE *line2)
{
	MYPOINT mypos1N,mypos1W;
	double myangpos1N, myangpos1W;
	double yidongN,yidongW;
	LINE line2N,line2W;
	oneloopstraight(roadareain,dr, len, &mypos1N, &myangpos1N, &yidongN,&line2N);
	oneloopstraight(roadareaout,dr, len, &mypos1W, &myangpos1W, &yidongW,&line2W);
	if (yidongN <= yidongW)
	{
		*mypos1=mypos1N;
		*myangpos1=myangpos1N;
		*yidong=yidongN;
		*line2=line2N;
	}
	else
	{
		*mypos1=mypos1W;
		*myangpos1=myangpos1W;
		*yidong=yidongW;
		*line2=line2W;
	}
}
//�����ڻ�����ת�䵽��һ��λ�ã�drΪ������������ĵľ��룬��Ϊ����mypos1,myangpos1,yidong����Ӧ���е㣬arc2Ϊ���ӵĹ켣
int oneloopturn(ROADAREA ra[],double dr, double len, MYPOINT *mypos1, double *myangpos1, double *yidong,ARC *arc2)
{
	int err=0;
	MYPOINT pcol;
	double R1,angin,newang;
	int collide,no;
	LINE liner;
	ARC arcr,arc0,arc1;

	arc0=getrotarc(len);
	R1=R-dr;
	arc1=arc0;
	arc1.r=fabs(R1);
	collide=checkarccollide(ra,arc1,R1, &pcol);
	if (collide == 1)
	{
		no=whereroadarea(ra,pcol,roadW);
		if (no < 0)
		{
			err=1;
			return err;
		}
		if(R>0)
			angin=pp_angle(pcol,arc_o(arc1));
		else
			angin=pp_angle(arc_o(arc1),pcol);
		if (strcmp(ra[no].type, "line") == 0)
		{
			liner=*(PLINE)(ra[no].pcurve);
			newang=linereflect(liner,angin);
		}
		else
		{
			arcr=*(PARC)(ra[no].pcurve);
			newang=arcreflect(arcr,pcol,angin);
		}
		if (R > 0)
			*yidong=arc0.r*stdangle0(arc1.angstart+arc1.dang-pp_angle(arc_o(arc1),pcol));
		else
			*yidong=arc0.r*stdangle0(pp_angle(arc_o(arc1),pcol)-arc1.angstart);
		*arc2=getrotarc(*yidong);
		arc2->r=arc1.r;
		*mypos1=getpangpnt(pcol,newang,-dr);
		*myangpos1=newang;
	}
	else//δ��
	{
		*yidong=len;
		*arc2=arc1;
		if (R > 0)
		{
			*mypos1=getarcpnt(arc0,arc1.angstart);
			*myangpos1=pp_angle(*mypos1,arc_o(arc1));
		}
		else
		{
			*mypos1=getarcpnt(arc0,arc1.angstart+arc1.dang);
			*myangpos1=pp_angle(arc_o(arc1),*mypos1);
		}
	}
	return err;
}
//�����ڻ�����ֱ�е���һ��λ�ã�drΪ������������ĵľ��룬��Ϊ����mypos1,myangpos1,yidong����Ӧ���е㣬line2Ϊ���ӵĹ켣
int oneloopstraight(ROADAREA ra[], double dr, double len, MYPOINT *mypos1, double *myangpos1, double *yidong, LINE *line2)
{
	int err=0;
	MYPOINT pcol;
	double newang;
	int collide,no;
	LINE line1,liner;
	ARC arcr;

	line1=getline(dr,len);
	collide=checklinecollide(ra,line1, &pcol);
	if (collide == 1)
	{
		no=whereroadarea(ra,pcol,roadW);
		if (no < 0)
		{
			err=1;
			return err;
		}
		if (strcmp(ra[no].type, "line") == 0)
		{
			liner=*(PLINE)(ra[no].pcurve);
			newang=linereflect(liner,myangpos);
		}
		else
		{
			arcr=*(PARC)(ra[no].pcurve);
			newang=arcreflect(arcr,pcol,myangpos);
		}
		
		*mypos1=getpangpnt(pcol,newang,-dr);
		*myangpos1=newang;
		*line2=line1;
		line2->p2=pcol;
		*yidong=pp_dist(line1.p1,pcol);
	}
	else//δ��
	{
		*mypos1=getpangpnt(mypos,myangpos+pi/2,len);
		*myangpos1=myangpos;
		*yidong=len;
		*line2=line1;
	}
	return err;
}
//������ʻ�߶���·���Ľ���
int checklinecollide(ROADAREA ra[], LINE line1, MYPOINT *pout)
{
	int collide=0;
	LINE line2;
	ARC arc1;
	int i,m,sum=0;
	MYPOINT ptmp[4];
	double ang,x[4];
	for (i = 0;i < 2*segs;i++)
	{
		if (strcmp(ra[i].type, "line") == 0)
		{
			line2=*(PLINE)(ra[i].pcurve);
			line_intersection(line1.p1, line1.p2, line2.p1, line2.p2,&m, &ptmp[sum]);
			if(m>0)
				sum+=m;
		}
		else
		{
			arc1=*(PARC)(ra[i].pcurve);
			arcline_intersection(line1.p1, line1.p2, arc1, &ptmp[sum],&m);
			if(m>0)
				sum+=m;
		}
	}
	if (sum > 0)
	{
		ang=pp_angle(line1.p1,line1.p2);
		for (i = 0;i < sum;i++)
		{
			x2xp(line1.p1,ang,ptmp[i],&ptmp[i]);
			x[i]=ptmp[i].x;
		}
		sort(sum,x);
		for (i = 0;i < sum;i++)
		{
			if (fabs(x[i]) >= 1e-6)
			{
				pout->x=x[i];
				collide=1;
				break;
			}
		}
		if(collide==1)
		{
			pout->y=0;
			xp2x(line1.p1,ang,*pout,pout);
		}
	}
	return collide;
}
//����ת��Բ����·���Ľ��㣬rotΪ����ʾ��ת��Ϊ����ʾ��ת
int checkarccollide(ROADAREA ra[], ARC arc1, double rot, MYPOINT *pout)
{
	int collide=0;
	LINE line1;
	ARC arc2;
	int i,m,sum=0;
	MYPOINT ptmp[16],o;
	double ang[16];
	for (i = 0;i < 2*segs;i++)
	{
		if (strcmp(ra[i].type, "line") == 0)
		{
			line1=*(PLINE)(ra[i].pcurve);
			arcline_intersection(line1.p1,line1.p2,arc1,&ptmp[sum],&m);
			if(m>0)
				sum+=m;
		}
		else
		{
			arc2=*(PARC)(ra[i].pcurve);
			arc_intersection(arc1,arc2,&m,&ptmp[sum]);
			if(m>0)
				sum+=m;
		}
	}
	if (sum > 0)
	{
		o=arc_o(arc1);
		for (i = 0;i < sum;i++)
		{
			if(rot<0)//��ת
				ang[i]=stdangle0(pp_angle(o,ptmp[i])-arc1.angstart);
			else//��ת
				ang[i]=stdangle0((arc1.angstart+arc1.dang)-pp_angle(o,ptmp[i]));
		}
		sort(sum,ang);
		for (i = 0;i < sum;i++)
		{
			if (fabs(ang[i]) >= 1e-8)
			{
				if(rot<0)//��ת
					*pout=getarcpnt(arc1,ang[i]+arc1.angstart);
				else
					*pout=getarcpnt(arc1,(arc1.angstart+arc1.dang)-ang[i]);
				collide=1;
				break;
			}
		}
	}
	return collide;
}
ARC getrotarc(double len)
{
	ARC arc1;
	double dang;
	MYPOINT pnt;
	arc1.r=fabs(R);
	dang=-len/R;//R��Ϊ������Ϊ��
	if (R > 0)
	{
		pnt=getpangpnt(mypos,myangpos,R);
		arc1.angstart=myangpos+pi+dang;
		arc1.dang=-dang;
	}
	else
	{
		pnt=getpangpnt(mypos,myangpos,R);
		arc1.angstart=myangpos;
		arc1.dang=dang;
	}
	arc1.x=pnt.x;
	arc1.y=pnt.y;
	return arc1;
}
//lenΪǰ�����е㵥����ʻ·��,drΪ������������ĵľ��룬��Ϊ����
LINE getline(double dr, double len)
{
	MYPOINT p0,p1,p2;
	LINE line1;
	p0=mypos;
	p1=getpangpnt(p0,myangpos,dr);
	p2=getpangpnt(p1,myangpos+pi/2,len);
	line1.p1=p1;
	line1.p2=p2;
	return line1;
}