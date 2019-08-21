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

void toushitu()
{
	int i;
	if(toushi==1)
	{
		draw_solidloop(2*segs,roadareaout);//�����ܵ���߽�͸��ͼ
		for(i=0;i<2;i++)
		{
			draw_dashloop(2*segs,roadareadash[i]);//�����ܵ�������͸��ͼ
		}
		draw_solidloop(2*segs,roadareain);//�����ܵ��ڱ߽�͸��ͼ
		drawendline();
		draw_lanloop(2*segs,roadareaout);//�����ܵ���߽�����
		draw_lanloop(2*segs,roadareain);//�����ܵ��ڱ߽�����

		//draw_treeloop(2*segs,roadareaout);//�����ܵ���߽���
		//draw_treeloop(2*segs,roadareain);//�����ܵ��ڱ߽���

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

//͸��ʵ�߹�·�߽���
void draw_solidloop(int nseg,ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//ֱ�߶�
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	draw_line(lineout);
		}
		else//Բ��
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
				draw_solidarc(arcout[j]);
		}
	}
}
//͸�ӹ�·����
void draw_dashloop(int nseg, ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//ֱ�߶�
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	draw_dashline(linein,lineout);
		}
		else//Բ��
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
//����·��ֱ�ߣ������ں���
//��1�����߶Σ�
void draw_dashline(LINE linearea,LINE line)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	LINE line1;
	double ang;
	ang=pp_angle(linearea.p1,linearea.p2);
	at1=wheredashline(linearea,line.p1,&n1);
	at2=wheredashline(linearea,line.p2,&n2);
	if (n2 == n1)//��ͬһ��
	{
		if (at1 == 1)//��1��������
		{
			if (at2 == 1)//��2��������
			{
				draw_line(line);
			}
		}
		else//��1�ڼ����
		{
			if (at2 == 1)//��2��������
			{
				line1.p1=getpangpnt(linearea.p1,ang,(n1+0.5)*dashlen);
				line1.p2=line.p2;
				draw_line(line1);
			}
		}
	}
	else//�ڲ�ͬ��
	{
		if (at1 == 1)//�ײ���������
		{
			line1.p1=line.p1;
			line1.p2=getpangpnt(linearea.p1,ang,(n1+1)*dashlen);
			draw_line(line1);
		}
		if(at2==1)//β����������
		{
			line1.p1=getpangpnt(linearea.p1,ang,(n2+0.5)*dashlen);
			line1.p2=line.p2;
			draw_line(line1);
		}
		//��������
		n=n2-n1-1;//�м�����������
		if(at1==1)//��1�����߶Σ��м������δ�n1+1��ʼ
		{
			nstart=n1+1;
		}
		else//��1�������߶Σ��м�����������1
		{
			n++;
			nstart=n1;//�ӿ������ο�ʼ
		}
		for (i = 0;i < n;i++)//�м���������
		{
			m=nstart+i;	
			line1.p1=getpangpnt(linearea.p1,ang,(m+0.5)*dashlen);
			line1.p2=getpangpnt(linearea.p1,ang,(m+1)*dashlen);
			draw_line(line1);
		}
	}
}
//����·�黡�ߣ������ں���
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
	if (n2 == n1)//��ͬһ��
	{
		if (at1 == 1)//��1��������
		{
			if (at2 == 1)//��2��������
			{
				draw_solidarc(arc);
			}
		}
	}
	else//�ڲ�ͬ��
	{
		if (at1 == 1)//�ײ���������
		{
				arc1.angstart=ang1;
				arc1.dang=stdangle0(arcarea.angstart+(n1+1)*dashang-ang1);
				draw_solidarc(arc1);
		}
		if(at2==1)//β����������
		{
			arc1.angstart=arcarea.angstart+(n2+0.5)*dashang;
			arc1.dang=stdangle0(ang2-arc1.angstart);
			draw_solidarc(arc1);
		}
		//��������
		n=n2-n1-1;//�м�����������
		if(at1==1)
		{
			nstart=n1+1;
		}
		else//�������μ����м�������
		{
			n++;
			nstart=n1;//�ӿ������ο�ʼ
		}
		for (i = 0;i < n;i++)//�м������黡��
		{
			m=nstart+i;	
			arc1.angstart=arcarea.angstart+(m+0.5)*dashang;
			arc1.dang=dashang/2;
			draw_solidarc(arc1);
		}
	}
}
//���п�ȵ�ֱ�߶�
void draw_line(LINE line1)
{
	MYPOINT point[4];
	int i;
	int poly[8];
	double a;
	if(pp_dist(line1.p1,line1.p2)<0.01) return;//��ֱ�߳��ȹ��̣����˳�
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
		x2xp(pntsight, angsight, point[i], &point[i]);//ת���������ϵ
		Pnt_Toushi(point[i], &point[i]);//���㵥λ��Ļ��͸�ӵ�
		//͸������ֵ������Ļ�ߣ�����poly����
		poly[2*i] =(int)(scrH*point[i].x+xcen);
		poly[2*i+1] = (int)(scrH*point[i].y+ycen);

	}
	fillpoly(4, poly);//���߶�
}
//���ȷֻ����Ϊ2w��Բ��͸��ͼ
void draw_arc(ARC arc2)
{
	int poly[16],i;
	double x0,y0,r,theta, dang;
	MYPOINT p,pnt_p,pnt_t;
	if(arc2.dang*arc2.r<0.01) return;//��ֱ�߳��ȹ��̣����˳�
	x0=arc2.x;
	y0=arc2.y;
	r=arc2.r;
	theta=arc2.angstart;
	dang=arc2.dang/3.0;//Բ��ndiv-1�ȷ�
	for (i = 0;i < 4;i++)
	{
		p.x = x0+(r + w)*cos(theta);
		p.y = y0+(r + w)*sin(theta);
		x2xp(pntsight, angsight, p, &pnt_p);
		Pnt_Toushi(pnt_p, &pnt_t);
		//͸������ֵ������Ļ�ߣ�����poly����
		poly[2 * i] = (int)(pnt_t.x *scrH+xcen);
		poly[2 * i + 1] =(int)( pnt_t.y * scrH+ycen);

		p.x = x0+(r - w)*cos(theta);
		p.y = y0+(r - w)*sin(theta);
		x2xp(pntsight, angsight, p, &pnt_p);
		Pnt_Toushi(pnt_p, &pnt_t);
		//͸������ֵ������Ļ�ߣ�����poly����
		poly[2 * (7 - i)] = (int)(pnt_t.x * scrH+xcen);
		poly[2 * (7 - i) + 1] =(int)(pnt_t.y * scrH+ycen);
		
		theta += dang;
	}

	fillpoly(8, poly);
}
//������������ϵ�n�����ڣ������Ƿ��������ϣ��ں������ڣ�
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
	//��벿��Ϊ���ߵ�����
	if(d-m>=0.5) atline=1;
	*n=m;
	return atline;
}

//���������Բ�����ϵ�n�����ڣ������Ƿ��������ϣ��ں������ڣ�
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

//����һ�߶Σ�ȫ�����꣩���ӳ��߽罻�㼰���ӳ��ڲ��˵㣬����ֵΪ�����������ﻹ���ص㣨ȫ�����꣩����������㣬һ�Ρ�
//���°汾��ת��p1p2�ֲ����꣬����y����Ϊ0�����ڱȽ��Ƿ��غϣ����׿���
int seeline(MYPOINT p1, MYPOINT p2, LINE *line1)
{
	int n = 0,i,j,j1,m;//���ӳ��ڲ��˵�򽻵�����
	MYPOINT p11={0,0}, p21;//p1��p2��p1p2�ֲ�����ϵ������
	MYPOINT pp1[5];
	MYPOINT pseg[2];//����ڲ��˵�򽻵�
	double dx,dy,a;
	MYPOINT ptmp[2],ptemp;//��ʱ��¼����
	int nn;//��ʱ��¼������
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	a = atan2(dy, dx);
	x2xp(p1, a, p2, &p21);//p2ת��p1p2�ֲ����꣨ԭ����p1��ת���Ƕ���a��
	//�ӳ���ת��p1p2�ֲ�����
	for (j = 0;j < 4;j++)
	{
		xp2x(pntsight, angsight,  p[j], &pp1[j]);//�ӳ���ת��ȫ������
		x2xp(p1, a,  pp1[j], &pp1[j]);//�ӳ���ת��p1p2�ֲ�����
	}
	pp1[4] = pp1[0];

	//�����ӳ��ڵĵ�
	if (judgein(p1) && judgein(p2))//�����ӳ����������
	{
		line1->p1 = p1;
		line1->p2 = p2;
		return 1;
	}
	else if (judgein(p1))//ֻp1���ӳ���
	{
		pseg[0] = p11;
		n = 1;
	}
	else if (judgein(p2))//ֻp2���ӳ���
	{
		pseg[0] = p21;
		n = 1;
	}
	//���㽻��
	for (i = 0;i < 4;i++)//���ӳ�ÿ���߽��м���
	{
		line_intersection(p11, p21, pp1[i], pp1[i + 1], &nn, ptmp);
		for(j=0;j<nn && n<2;j++)//��ÿ����������ж��Ƿ����pseg���飬nС��2��ѭ��
		{
			double x=ptmp[j].x;
			j1=0;
			for (m = 0;m < n;m++)//��pseg������ĵ㶼���غϵĽ���Ŵ���pseg����
			{
				if(fabs(x-pseg[m].x)<1e-6)
				{
					j1=1;//�غϣ�j1��1
					break;
				}
			}
			if(j1==0) pseg[n++]=ptmp[j];//��pseg������ĵ㶼���غϣ�����pseg����
		}
	}
	if (n == 2)//�������㣬˵���ӳ�����һ��ֱ��
	{
		if (pseg[0].x > pseg[1].x)//����
		{
			ptemp=pseg[0];
			pseg[0]=pseg[1];
			pseg[1]=ptemp;
		}
		for (j = 0;j < 2;j++)
		{
			xp2x(p1, a, pseg[j], &pseg[j]); //����ת��ȫ������
		}
		line1->p1 = pseg[0];
		line1->p2 = pseg[1];
		return 1;
	}
	else
		return 0;
}
//����һԲ����ȫ�����꣩���ӳ��ڻ��Σ�����ֵΪ�������������ﻹ���ػ���ARC�ṹֵ��ȫ�����꣩
int seearc(ARC arc2, ARC arc3[])
{
	int n,i,j,m,j1;//���׻��ڲ�������
	int nn,num;//
	MYPOINT intersection[2], p1[5], middle, ps, pe, point[10];
	double a, ang[10], dang[9], temp;
	double x0,y0,ang0,R;

	x0=arc2.x;
	y0=arc2.y;
	ang0=arc2.angstart;
	R=arc2.r;

	//�ӳ���ת��ȫ������
	for (i = 0;i < 4;i++)
	{
		xp2x(pntsight, angsight, p[i], &p1[i]);
	}
	p1[4] = p1[0];

	//����Բ���˵�
	ps.x = x0 + R*cos(ang0);
	ps.y = y0 + R*sin(ang0);
	a = ang0 + arc2.dang;
	pe.x = x0 + R*cos(a);
	pe.y = y0 + R*sin(a);

	//Բ���˵������ӳ��ڣ�����point���飬������Բ����ʼ�ǵļнǴ���ang����
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
	//�ӳ���������Բ���Ľ������point����
	for (i = 0;i < 4;i++)
	{
		arcline_intersection(p1[i], p1[i + 1], arc2, intersection, &nn);
		for(j=0;j<nn;j++)//��ÿ����������ж��Ƿ����pseg����
		{
			a=atan2(intersection[j].y-y0,intersection[j].x-x0)-ang0;
			a=stdangle0(a);
			j1=0;
			for (m = 0;m < n;m++)//��point������ĵ㶼���غϵĽ���Ŵ���point����
			{
				if(fabs(a-ang[m])<1e-8)
				{
					j1=1;//�غϣ�j1��1
					break;
				}
			}
			if(j1==0)
			{
				point[n]=intersection[j];//��point������ĵ㶼���غϣ�����point���飬
				ang[n++]=a;//��Բ����ʼ�ǵļнǴ���ang����
			}
		}
	}
	//�н�����
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
	//�����ӳ��ڵĻ���
	num=0;
	if(n>=2)
	{
		//���������ɨ���ĽǶȣ�����dang����
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
//�����תΪ͸�ӵ㣬͸�ӵ������Ӧ��Ļ�߶�Ϊ1��ֵ������������camH������Ϊz�ᣬ��ǰ��Ϊy�ᣬ����Ϊx�ᣬ
//͸������ϵԭ������Ļ���Ͻǣ�x������Ϊ����y������Ϊ����
//���ڵ���
void Pnt_Toushi(MYPOINT pnt, MYPOINT *pnt_t)
{
	double x, dist, fact;
	x = pnt.x;
	dist = pnt.y;
	fact = 0.5 / (dist*tan(angvmax));
	pnt_t->x = x * fact;
	pnt_t->y = camH *fact;
}
//�����תΪ͸�ӵ㣬͸�ӵ������Ӧ��Ļ�߶�Ϊ1��ֵ������������camH������Ϊz�ᣬ��ǰ��Ϊy�ᣬ����Ϊx�ᣬ
//͸������ϵԭ������Ļ���Ͻǣ�x������Ϊ����y������Ϊ����
//zΪ��������ľ���
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

//�ж�1�����Ƿ����ӳ���
//��Ҫ�ӵ�λ��pntsight���ӳ��������ȫ������ת���Ƕ�angsight���ӳ��Ľ���yminsight��Զ��ymaxsight��
//�ӳ���߽��a2hsight���ӳ��ұ߽��a1hsightΪȫ�ֱ������������Ϊp1
int judgein(MYPOINT p1)
{
	MYPOINT p2;
	double b;
	int flag = 0;
	x2xp(pntsight, angsight, p1, &p2);//ת���ӳ��ֲ�����
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

//����һ��ά�߶Σ�ȫ�����꣩���ӳ��߽罻�㼰���ӳ��ڲ��˵㣬����ֵΪ�����������ﷵ���ӳ�����ά�߶Σ�ȫ�����꣩��
//������Ǧ���ߣ�ˮƽ�ߣ�һ��ռ���
int see3Dline(MY3DPOINT p1, MY3DPOINT p2, LINE3D *line3D)
{
	int n = 0;
	MYPOINT p2D1,p2D2,p2D3,p2D4;
	LINE line;
	double dx,dy,dz,z1,z3,z4;
	MY3DPOINT p3,p4;
	double p1p2,p1p3,p1p4;
	
	//�߶ζ˵�p1��p2ת��Ϊ��ά��
	p2D1=p1.p;
	p2D2=p2.p;

	p1p2=pp_dist(p2D1,p2D2);
	if(p1p2<1e-6)//Ǧ����
	{
		if(judgein(p2D1))//���ӳ���
		{
			n=2;
			line3D->p1=p1;
			line3D->p2=p2;
		}
	}
	else//ˮƽ�ߣ���һ��ռ���
	{
		//���ӳ��ڶ�ά�߶�p3p4
		n=seeline(p2D1,p2D2,&line);
		if(n>0)//���ӳ������߶�
		{
			//����p1p3��p1p4����
			p2D3=line.p1;
			p2D4=line.p2;
			p1p3=pp_dist(p2D1,p2D3);
			p1p4=pp_dist(p2D1,p2D4);
			//����p3��p4��z����
			z1=p1.z;
			dz=p2.z-p1.z;
			z3=z1+p1p3/p1p2*dz;
			z4=z1+p1p4/p1p2*dz;
			//������ά�߶�
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
//����ά�߶ε�͸��ͼ
void drawcar3Dline(LINE3D line3D)
{
	MYPOINT pp1,pp2;
	MYPOINT p1,p2;
	int x1,y1,x2,y2;
	int x11,y11,x22,y22;
	//ת�˵�p1
	//��ά��
	p1=line3D.p1.p;

	x2xp(pntsight, angsight, p1, &pp1);//ת���������ϵ
	Pnt_ToushiZ(pp1,line3D.p1.z, &p1);//���㵥λ��Ļ��͸�ӵ�
	//͸������ֵ������Ļ�ߣ��Ƶ���Ļ����
	x1 =(int)(scrH*p1.x+xcen);
	y1 = (int)(scrH*p1.y+ycen);

	//ת�˵�p2
	//��ά��
	p2=line3D.p2.p;

	x2xp(pntsight, angsight, p2, &pp2);//ת���������ϵ
	Pnt_ToushiZ(pp2,line3D.p2.z, &p2);//���㵥λ��Ļ��͸�ӵ�
	//͸������ֵ������Ļ�ߣ��Ƶ���Ļ����
	x2 =(int)(scrH*p2.x+xcen);
	y2 = (int)(scrH*p2.y+ycen);

	//��͸����
	line(x1,y1,x2,y2);
}
//������͸��ͼ��pcenΪ���������ڳ�����������ϵ�µ���ά����
void drawwheel(MY3DPOINT pcen)
{
	int i,n;
	double y0,z0,r,theta,dang;
	MYPOINT pp;
	MY3DPOINT pnt,p3D[21];
	LINE3D lineout;
	//�ڳ�����������ϵ��
	y0=pcen.p.y;
	z0=pcen.z;
	r=rwheel;
	theta=0;
	dang=2*pi/20;//20�ȷ�
	pnt.p.x = pcen.p.x;
	for (i = 0;i <= 20;i++)
	{
		//����Բ��20�ȷֵ��ڳ�����������ϵ�µ���ά����
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//ת��ȫ������
		xp2x(pos,angpos, pnt.p, &pp);
		p3D[i].p=pp;
		p3D[i].z=pnt.z;

		theta += dang;
	}
	//20�ȷ�����͸��
	for (i = 0;i < 20;i++)
	{
		n=see3Dline(p3D[i],p3D[i+1],&lineout);
		if(n>0)
			drawcar3Dline(lineout);
	}
}
//����ά����棬nΪ������
void draw3Dfill(int n,MY3DPOINT p3D[],int poly[])
{
	int i;
	MYPOINT pp,p1;

	for(i=0;i<n;i++)
	{
		x2xp(pntsight, angsight,p3D[i].p, &pp);//ת���������ϵ
		Pnt_ToushiZ(pp,p3D[i].z, &p1);//���㵥λ��Ļ��͸�ӵ�
		//͸������ֵ������Ļ�ߣ��Ƶ���Ļ����
		poly[2*i] =(int)(scrH*p1.x+xcen);
		poly[2*i+1] = (int)(scrH*p1.y+ycen);
	}
	//��͸���ı���
	fillpoly(n, poly);
}
//�������棬����Ϊ��λ�ã��Ҳ���x��нǣ�������ĺ��ڲ�������С����������ϵ�µ���ά��
void drawwheelface(MYPOINT pos1,double angpos1,MY3DPOINT pcenout,MY3DPOINT pcenin)
{
	int poly[20];
	int i,n;
	double y0,z0,r,theta,dang;
	MYPOINT pp;
	MY3DPOINT pnt,p3Dout[11],p3Din[11],p3D[4];
	LINE3D lineout;
	//�ڳ�����������ϵ��
	y0=pcenout.p.y;
	z0=pcenout.z;
	r=rwheel;
	theta=0;
	dang=2*pi/10;

	//���������ȷֵ�
	pnt.p.x = pcenout.p.x;
	for (i = 0;i <= 10;i++)
	{
		//����Բ�ϵȷֵ��ڳ�����������ϵ�µ���ά����
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//ת��ȫ������
		xp2x(pos1,angpos1, pnt.p, &pp);
		p3Dout[i].p=pp;
		p3Dout[i].z=pnt.z;

		theta += dang;
	}
	p3Dout[10]=p3Dout[0];

	//�����ڲ���ȷֵ�
	//y0=pcenin.p.y;
	//z0=pcenin.z;
	//r=rwheel;
	theta=0;
	pnt.p.x = pcenin.p.x;
	for (i = 0;i <= 10;i++)
	{
		//����Բ�ϵȷֵ��ڳ�����������ϵ�µ���ά����
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//ת��ȫ������
		xp2x(pos1,angpos1, pnt.p, &pp);
		p3Din[i].p=pp;
		p3Din[i].z=pnt.z;

		theta += dang;
	}
	p3Din[10]=p3Din[0];

	//���ڲ���
	setfillstyle(SOLID_FILL,BLACK);
	setcolor(WHITE);
	draw3Dfill(10,p3Din,poly);

	//��������
	setcolor(BLACK);
	for(i=0;i<10;i++)
	{
		p3D[0]=p3Din[i];
		p3D[1]=p3Dout[i];
		p3D[2]=p3Dout[i+1];
		p3D[3]=p3Din[i+1];

		draw3Dfill(4,p3D,poly);
	}

	//�������
	setcolor(WHITE);
	draw3Dfill(10,p3Dout,poly);
}
//��������ϰ�Բ����ά�ȵ㣬�Ӻ�ǰ��nΪ�ȷ���
void wheelup(MY3DPOINT pcen,int n,MY3DPOINT p3Dup[])
{
	int i;
	double y0,z0,r,theta,dang;
	MYPOINT pp;
	MY3DPOINT pnt;
	//�ڳ�����������ϵ��
	y0=pcen.p.y;
	z0=pcen.z;
	r=rwheel;
	theta=pi;
	dang=pi/n;

	//���������ȷֵ�
	pnt.p.x = pcen.p.x;
	for (i = 0;i <= n;i++)
	{
		//����Բ�ϵȷֵ��ڳ�����������ϵ�µ���ά����
		pnt.p.y =y0+r*cos(theta);
		pnt.z = z0+r*sin(theta);
		//ת��ȫ������
		xp2x(pos,angpos, pnt.p, &pp);
		p3Dup[i].p=pp;
		p3Dup[i].z=pnt.z;

		theta -= dang;
	}
}
//���Զ�С���棬�����ǰ1�ײŻ�
void drawautocarface()
{
	enum COLORS autocolor=LIGHTMAGENTA;
	MYPOINT pp;
	MYPOINT p0={0,0},p1,p2,p3,p4,ptmp;
	MY3DPOINT p3Dleft[20],p3Dright[20];//���Ӳ����ȫ����ά��
	MY3DPOINT p3Dwin[4];
	MY3DPOINT p3D[10];
	LINE3D lineout;
	LINE line1;
	int poly[40];
	int n;
	int i,j;
	//��������ת��ȫ������
	for (i = 0;i < 7;i++)
	{
		xp2x(pos,angpos,pcarleft[i].p,&pp);
		p3Dleft[i].p=pp;
		p3Dleft[i].z=pcarleft[i].z;

		xp2x(pos,angpos,pcarright[i].p,&pp);
		p3Dright[i].p=pp;
		p3Dright[i].z=pcarright[i].z;
	}
	//�����ϰ�Բ�ȷֵ�ȫ������
	wheelup(pcarcenleft[1],5,&p3Dleft[7]);
	wheelup(pcarcenleft[0],5,&p3Dleft[13]);
	//�����ϰ�Բ�ȷֵ�ȫ������
	wheelup(pcarcenright[1],5,&p3Dright[7]);
	wheelup(pcarcenright[0],5,&p3Dright[13]);

	//����Ƿ������ǰ1�ף���0��6��
	x2xp(pntsight, angsight,p3Dleft[0].p,&p1);//ת���������ϵ
	x2xp(pntsight, angsight,p3Dleft[6].p,&p2);//ת���������ϵ
	x2xp(pntsight, angsight,p3Dright[0].p,&p3);//ת���������ϵ
	x2xp(pntsight, angsight,p3Dright[6].p,&p4);//ת���������ϵ
	if(p1.y<1 || p2.y<1 || p3.y<1 || p4.y<1)
		return;

	setfillstyle(SOLID_FILL,autocolor);

	//������
	for(i=0;i<6;i++)
	{
		//�ı��ζ���浽����
		p3D[0]=p3Dleft[i];
		p3D[1]=p3Dright[i];
		p3D[2]=p3Dright[i+1];
		p3D[3]=p3Dleft[i+1];

		draw3Dfill(4,p3D,poly);
	}

	//�ж��Ƿ����ɼ�
	x2xp(pntsight, angsight,p3Dleft[0].p,&p1);//ת���������ϵ
	x2xp(pntsight, angsight,p3Dleft[6].p,&p2);//ת���������ϵ
	if (p1.y > p2.y)
	{
		ptmp=p1;
		p1=p2;
		p2=ptmp;
	}

	if (stdangle(pp_angle(p0, p2) - pp_angle(p0, p1)) > 0)//���ɼ�
	{
		//������,�������֣�����ǰ���ں��Һ��֣�����ǰ���ں�
		for(i=0;i<2;i++)
		{
			drawwheelface(pos,angpos,pcarcenleft[i],pcarcenleftin[i]);
		}
		drawwheelface(pos,angpos,pcarcenrightin[1],pcarcenright[1]);
		
		//�����
		setfillstyle(SOLID_FILL,autocolor);
		draw3Dfill(19,p3Dleft,poly);

		//����
		//�󴰵�ת��ȫ������
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
	else//�Ҳ�ɼ�
	{
		//������,�������֣�����ǰ���ں����������ǰ���ں�
		for(i=0;i<2;i++)
		{
			drawwheelface(pos,angpos,pcarcenright[i],pcarcenrightin[i]);
		}
		drawwheelface(pos,angpos,pcarcenleftin[1],pcarcenleft[1]);

		//���Ҳ�
		setfillstyle(SOLID_FILL,autocolor);
		draw3Dfill(19,p3Dright,poly);

		//���Ҵ�
		//�Ҵ���ת��ȫ������
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
	setfillstyle(SOLID_FILL,WHITE);//�ָ�Ϊ��ɫ
}

//������С����
void drawdrivecarface()
{
	MYPOINT pp;
	MYPOINT p0={0,0},p1,p2,p3,p4,ptmp;
	MY3DPOINT p3Dleft[20],p3Dright[20];//���Ӳ����ȫ����ά��
	MY3DPOINT p3D[10];
	int poly[20];
	int i;
	//��������ת��ȫ������
	for (i = 0;i < 7;i++)
	{
		xp2x(mypos,myangpos,pcarleft[i].p,&pp);
		p3Dleft[i].p=pp;
		p3Dleft[i].z=pcarleft[i].z;

		xp2x(mypos,myangpos,pcarright[i].p,&pp);
		p3Dright[i].p=pp;
		p3Dright[i].z=pcarright[i].z;
	}

	//������
	drawwheelface(mypos,myangpos,pcarcenleftin[1],pcarcenleft[1]);
	drawwheelface(mypos,myangpos,pcarcenright[1],pcarcenrightin[1]);

	setcolor(LIGHTMAGENTA);

	//������
	setfillstyle(SOLID_FILL,mecolor);
	for(i=3;i<6;i++)
	{
		//�ı��ζ���浽����
		p3D[0]=p3Dleft[i];
		p3D[1]=p3Dright[i];
		p3D[2]=p3Dright[i+1];
		p3D[3]=p3Dleft[i+1];

		draw3Dfill(4,p3D,poly);
	}

	setfillstyle(SOLID_FILL,WHITE);//�ָ�Ϊ��ɫ
	setcolor(WHITE);
}
//������
void draw_lanloop(int nseg,ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	setfillstyle(SOLID_FILL,DARKGRAY);
	setcolor(DARKGRAY);
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//ֱ�߶�
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	
			{
				//������ˮƽ��
				//draw_lanline(lineout);
				//�����˴�ֱ��
				draw_lanvline(linein,lineout,draw_lanvbase);
			}
		}
		else//Բ��
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
			{
				//������ˮƽ��
				//draw_lanarc(arcout[j]);
				//�����˴�ֱ��
				draw_lanvarc(arcin,arcout[j],draw_lanvbase);
			}
		}
	}
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
}
//��Բ������
void draw_lanarc(ARC arc1)
{
	MY3DPOINT p3D[4];
	int poly[8];
	double ang1,dang1;
	int ndiv,i;
	LINE line;
	//Լ2m�ȷ�
	ndiv=(int)(arc1.dang*arc1.r/2.0)+1;
	ang1=arc1.angstart;
	dang1=arc1.dang/ndiv;
	arc1.dang=dang1;
	for (i = 0;i < ndiv;i++)
	{
		arc1.angstart=ang1;
		//��ÿһ��Բ��
		line.p1=getarcpnt(arc1,ang1);
		line.p2=getarcpnt(arc1,ang1+dang1);
		draw_lanline(line);

		ang1+=dang1;
	}
}
//��ˮƽ�����ˣ�����Ϊ��ά�߶�
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
//��ֱ���ϵĴ�ֱ����
void draw_lanvline(LINE linearea,LINE line,BASEFUNCPTR funptr)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	double ang,angx;
	MYPOINT pnt;
	ang=pp_angle(linearea.p1,linearea.p2);
	angx=ang-pi/2;
	//�ж��ں�����Ϊ1
	at1=wheredashline(linearea,line.p1,&n1);
	at2=wheredashline(linearea,line.p2,&n2);
	//ת��Ϊ��ǰ���Ϊ1
	at1=(at1==0?1:0);
	at2=(at1==0?1:0);
	if (n2 == n1)//��ͬһ��
	{
		if (at1 == 1)//��1�ڱ����е�ǰ
		{
			if (at2 == 0)//��2�ڱ����е��
			{
				pnt=getpangpnt(linearea.p1,ang,(n1+0.5)*dashlen);
				//����ֱ����
				funptr(pnt,angx);
			}
		}
	}
	else//�ڲ�ͬ��
	{
		//��1���е�ǰ������ʼ��Ϊn1������Ϊn1+1
		//��1���е�ǰ�����������м������������ϼ�1
		//��2���е�����������м������������ϼ�1
		n=n2-n1-1;//�м�������
		if(at1==1)//��1�ڱ����е�ǰ
		{
			nstart=n1;
			n++;
			if (at2 == 0)//��2�ڱ����е��
				n++;
		}
		else//��1�ڱ����е��
		{
			nstart=n1+1;
			if (at2 == 0)//��2�ڱ����е��
				n++;
		}
		for (i = 0;i < n;i++)//������
		{
			m=nstart+i;	
			pnt=getpangpnt(linearea.p1,ang,(m+0.5)*dashlen);
			funptr(pnt,angx);
		}
	}
}
//��Բ�����ϵĴ�ֱ���ˣ����Ƕȵȷ�Ϊ��Σ���ɼ�Բ��������Χ�����˵�
void draw_lanvarc(ARC arcarea,ARC arc,BASEFUNCPTR funptr)
{
	int at1,at2,n1,n2,n,m,i,nstart;
	ARC arc1;
	double ang1,ang2,ang;
	MYPOINT pnt;
	arc1=arcarea;
	ang1=arc.angstart;
	ang2=ang1+arc.dang;
	//�ж��ں�����Ϊ1
	at1=wheredasharc(arcarea,ang1,&n1);
	at2=wheredasharc(arcarea,ang2,&n2);
	//ת��Ϊ��ǰ���Ϊ1
	at1=(at1==0?1:0);
	at2=(at1==0?1:0);
	if (n2 == n1)//��ͬһ��
	{
		if (at1 == 1)//��1�����е�ǰ
		{
			if (at2 == 0)//��2�ڱ����е��
			{
				ang=arcarea.angstart+(n1+0.5)*dashang;//���˴��ľ���
				pnt=getarcpnt(arcarea,ang);
				funptr(pnt,ang);
			}
		}
	}
	else//�ڲ�ͬ��
	{
		//��1���е�ǰ������ʼ��Ϊn1������Ϊn1+1
		//��1���е�ǰ�����������м������������ϼ�1
		//��2���е�����������м������������ϼ�1
		n=n2-n1-1;//�м�������
		if(at1==1)//��1�ڱ����е�ǰ
		{
			nstart=n1;
			n++;
			if (at2 == 0)//��2�ڱ����е��
				n++;
		}
		else//��1�ڱ����е��
		{
			nstart=n1+1;
			if (at2 == 0)//��2�ڱ����е��
				n++;
		}
		for (i = 0;i < n;i++)//������
		{
			m=nstart+i;	
			ang=arcarea.angstart+(m+0.5)*dashang;//���˴��ľ���
			pnt=getarcpnt(arcarea,ang);
			funptr(pnt,ang);
		}
	}
}

//�ɶ�ά���·�ߵķ��߷��򣬻�һ����ֱ����
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
//����
void draw_treeloop(int nseg,ROADAREA ra[])
{
	LINE linein,lineout;
	ARC arcin,arcout[9];
	int n,i,j;
	setfillstyle(SOLID_FILL,DARKGRAY);
	setcolor(DARKGRAY);
	for(i=0;i<nseg;i++)
	{
		if(strcmp(ra[i].type,"line")==0)//ֱ�߶�
		{
			linein=*(PLINE)(ra[i].pcurve);
			n=seeline(linein.p1,linein.p2,&lineout);
			if(n>0)	
			{
				draw_lanvline(linein,lineout,draw_treebase);
			}
		}
		else//Բ��
		{
			arcin=*(PARC)(ra[i].pcurve);
			n=seearc(arcin,arcout);
			for(j=0;j<n;j++)
			{
				//������ˮƽ��
				//draw_lanarc(arcout[j]);
				//�����˴�ֱ��
				draw_lanvarc(arcin,arcout[j],draw_treebase);
			}
		}
	}
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
}
//�ɶ�ά���·�ߵķ��߷��򣬻�һ����
void draw_treebase(MYPOINT pnt,double ang)
{
	MY3DPOINT p3D[4];
	int poly[8];
	LINE line1;
	//������
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
	//������
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
