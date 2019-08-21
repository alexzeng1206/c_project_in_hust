#pragma once

//a<=b<=c。e是1e-6或1e-8，用于相等判断
#define GEANDLE(a,b,c,e) (a<b || fabs(a-b)<e) && (b<c || fabs(b-c)<e)
//a<b<c
#define GTANDLT(a,b,c) (a<b && b<c)

#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_QUIT    64

#define OLD_SPACE 1
#define OLD_Z     2

#define	SCAN_UP			0x48
#define	SCAN_DOWN		0x50
#define	SCAN_LEFT		0x4B
#define	SCAN_RIGHT	0x4D
#define SCAN_Z      0x2C

#define	SCAN_SPACE	0x39

#define	SCAN_ESCAPE 0x01


typedef struct _MYPOINT
{
	double x;
	double y;
}MYPOINT, *PMYPOINT;
typedef struct _POINT
{
	int x;
	int y;
}POINT, *PPOINT;

typedef struct _ARC
{
	double x;
	double y;
	double r;
	double angstart;
	double dang;//圆弧扫过的圆心角
}ARC,*PARC;
typedef struct _LINE
{
	MYPOINT p1;
	MYPOINT p2;
}LINE,*PLINE;
typedef struct _ROADAREA
{
	char type[5];
	void *pcurve;
}ROADAREA;
typedef enum _GEARTYPE{AUTO,STICK} GEARTYPE;
//typedef enum _SIGHT{Global,Drive,Auto} SIGHT;
typedef struct _MY3DPOINT
{
	MYPOINT p;
	double z;
}MY3DPOINT, *PMY3DPOINT;
typedef struct _LINE3D
{
	MY3DPOINT p1;
	MY3DPOINT p2;
}LINE3D,*PLINE3D;
typedef void (*BASEFUNCPTR)(MYPOINT pnt,double ang);

