
//ƽ��ͼ��ʾѡ��
MYMACRO int toushi;//Ϊ1ʱ��ʾ͸��ͼ

//====���С������ܵ�ѡ�����====
MYMACRO int segs;//ȷ���ܵ�Ϊ�����Σ������ı���
//������ʻ����ѡ�񣬸߶�,��ɫ
MYMACRO enum COLORS mecolor;//������ʻ����ɫ
MYMACRO int myshift;//�ֶ�����λ
MYMACRO GEARTYPE geartype;//�Զ������ֶ���

MYMACRO int oldstate;//��λ�����浥������ǰһ״̬��1Ϊ����
MYMACRO int trig;//��λ��Ϊ1��ʾ������������һ���ɿ������µ�ת��

//MYMACRO MYPOINT posping;
//MYMACRO double angposping;

MYMACRO clock_t dly;

MYMACRO double throttledrive;//������ʻ������
MYMACRO double throttleauto;//�Զ���ʻ������

MYMACRO double rwheel;//��̥�뾶
MYMACRO double areaying;//ӭ�����
MYMACRO double weight;//������
MYMACRO double g;//�������ٶ�
MYMACRO double rou;//�����ܶ�
MYMACRO double Cd;//����ϵ��
MYMACRO double Crr;//����Ħ��ϵ��
MYMACRO double masterRatio;//�����������ٱȣ�3.5-5
MYMACRO double eta;//����Ч��
MYMACRO double torque;//Ť��
//����������1.7~1.8��������������7.640,4.835,2.857,1.895,1.337,1
MYMACRO double gear[3];//������Ӧ�ı�������ٱȣ�1����Ӧ�±�1,2����Ӧ�±�2
MYMACRO double vdrivemax;//20������ʻ����ٶ�
MYMACRO double vmaxshift[3];//������Ӧ������ٶ�

MYMACRO int cmd;//��������
MYMACRO int keystate;//�������ESQ������״̬

//�ӵ�ߡ�ˮƽ��λ�á��ӳ��������ȫ������ת���Ƕ�
MYMACRO double camH;//��λm
MYMACRO double w;//�߰����λm

MYMACRO double carHW;//�������
MYMACRO double carL;//��������

MYMACRO double v, R;//������ʻ�ٶȣ�ת��뾶
MYMACRO double vautomax;//�Զ���ʻ����ٶ�
MYMACRO double vauto;//�Զ���ʻ�ٶ�
MYMACRO double tick;
MYMACRO double rdrive;

MYMACRO MYPOINT pntsight;//��λm
MYMACRO double angsight;//��λrad

//�ܵ������߲���
MYMACRO double roadW;

MYMACRO double kdash;//�������ڷŴ�ϵ��

MYMACRO double road_halfo;//��·�м���Բ��Բ�������������
MYMACRO double road_r;//��·���������Բ���뾶

MYMACRO double autoH;//�Զ���ʻ���߶�
MYMACRO int nopos;//�Զ���ʻ��ǰ�κ�
MYMACRO int pathno;//�Զ���ʻ��ǰ·�ߺ�
MYMACRO double sumauto;//�Զ���ʻ��Ӧ�Զ���ʻ·��·��
MYMACRO double angpos;//�Զ���ʻ���ҷ�����x��ĵ�ǰ�н�

MYMACRO double sumdrive;//������ʻ��Ӧ�Զ���ʻ·��·��
MYMACRO double myangpos;//������ʻ�ҷ�����x��ļн�

//��Ļ����
MYMACRO double scrW,scrH;
MYMACRO double k ;//��Ļ��߱�
//��ͼ����
MYMACRO double xcen;
MYMACRO double ycen;
MYMACRO double startclr;//ˢ�����������Ͻ�x���꣬Ϊ80

MYMACRO double offsetauto;//�Զ���ʻ��ƫ���м��Զ���ʻ·�ߵľ���
MYMACRO double offsetdrive;//������ʻ��ƫ���м��Զ���ʻ·�ߵľ���
MYMACRO MYPOINT mypos;//������ʻ��ǰλ��
MYMACRO MYPOINT pos;//�Զ���ʻ��ǰλ��
MYMACRO LINE endline;
MYMACRO double dashang;
MYMACRO double dashlen;//�������ڳ�

//�ӳ�����
MYMACRO double angvmax ;//�ӳ��Ĵ�����ӽ�
MYMACRO double yminsight, ymaxsight;//�ӳ��Ľ��ࡢԶ��
MYMACRO double anghmax; //�ӳ���ˮƽ���ӽǣ��봹ֱ���ӽ���ȣ���Ļ������û���õ��ĵط�
MYMACRO double a2hsignt;//�ӳ���߽��
MYMACRO double a1hsignt;//�ӳ��ұ߽��
//�����ӳ����Լ��ֲ����꣨�ӵ�Ϊԭ�㣬��ǰ��Ϊy�ᣩ�µ��ĸ���
MYMACRO MYPOINT p[5];
MYMACRO ROADAREA roadareadash[2][12];
//�м��������ñ���
MYMACRO LINE road_linedash[2][6];
MYMACRO ARC road_arcdash[2][6];
MYMACRO ROADAREA roadareaout[12],roadareain[12];
//�ܵ���߽����ñ���
MYMACRO LINE road_lineout[6];
MYMACRO ARC road_arcout[6];
//�ܵ��ڱ߽����ñ���
MYMACRO LINE road_linein[6];
MYMACRO ARC road_arcin[6];

//�Զ���ʻ·�ߣ�����·��
MYMACRO ROADAREA autoroad[3][12];
MYMACRO LINE auto_line[3][6];
MYMACRO ARC  auto_arc[3][6];


//�������������㣬�׵׵�β�ף���������ϵ��
MYMACRO MY3DPOINT pcarleft[7];
MYMACRO MY3DPOINT pcarright[7];
MYMACRO MYPOINT pcar[5];


//����ǰ������������ģ���������ϵ��
MYMACRO MY3DPOINT pcarcenleft[2];
MYMACRO MY3DPOINT pcarcenright[2];

//����ǰ�������ڲ����ģ���������ϵ��
MYMACRO MY3DPOINT pcarcenleftin[2];
MYMACRO MY3DPOINT pcarcenrightin[2];

//��������������ϵ��
MYMACRO MY3DPOINT pcarwinleft[3][4];
MYMACRO MY3DPOINT pcarwinright[3][4];

MYMACRO double sumpathauto;//�Զ���ʻ·�߳���

MYMACRO double oneauto;
MYMACRO double onedrive;

MYMACRO double pi;

MYMACRO clock_t start, finish;
MYMACRO double  duration;
MYMACRO double timeme,timeauto;//��ʻʱ��

MYMACRO void interrupt(*oldint9)();
MYMACRO void interrupt(*nint9)();

MYMACRO int itext;//ÿ��֡��ʾ�ٶȵ���Ϣ�Ŀ��Ʊ���

void draw_solidloop(int nseg,ROADAREA ra[]);
void draw_dashloop(int nseg,ROADAREA ra[]);
void draw_solidarc(ARC arc1);
void draw_dashline(LINE linearea,LINE line);
void draw_dasharc(ARC arcarea,ARC arc);
void draw_line(LINE line1);
void draw_arc(ARC arc2);
int judgein(MYPOINT p1);

void Pnt_Toushi(MYPOINT pnt, MYPOINT *pnt_t);
void Pnt_ToushiZ(MYPOINT pnt,double z, MYPOINT *pnt_t);
void roadinit();
void setrecroadloop(double r,LINE li[],ARC ar[],ROADAREA ra[]);
void settriroadloop(double r,LINE li[],ARC ar[],ROADAREA ra[]);
int Game_Main();

void setcamera(MYPOINT p1,double ang);
void autoruncar(ROADAREA ra[]);//�Զ���ʻ
double runarc(ROADAREA ra[],double xingshi,int frompos);//�Զ���Բ������ʻ
double runline(ROADAREA ra[],double xingshi,int frompos);//�Զ�ֱ������ʻ
int getkey();
void drivecar();
void twowheelturn(double len, MYPOINT *mypos1, double *myangpos1, double *yidong,ARC *arc2);
void twowheelstraight(double len, MYPOINT *mypos1, double *myangpos1, double *yidong,LINE *line2);
void onewheelturn(double dr, double len, MYPOINT *mypos1, double *myangpos1, double *yidong,ARC *arc2);
void onewheelstraight(double dr, double len, MYPOINT *mypos1, double *myangpos1, double *yidong,LINE *line2);
int oneloopturn(ROADAREA ra[],double dr,double len,MYPOINT *mypos1,double *myangpos1,double *yidong,ARC *arc2);
int oneloopstraight(ROADAREA ra[],double dr,double len,MYPOINT *mypos1,double *myangpos1,double *yidong,LINE *line2);
int seeline(MYPOINT p1, MYPOINT p2, LINE *line1);
int seearc(ARC arc2, ARC arc3[]);
int checklinecollide(ROADAREA ra[], LINE line1, MYPOINT *pout);
int checkarccollide(ROADAREA ra[], ARC arc1,double rot, MYPOINT *pout);
int carcollide();
LINE getline(double dr,double len);

int wheredashline(LINE line,MYPOINT pnt,int *n);
int wheredasharc(ARC arc1,double ang, int *n);
int whereroadarea(ROADAREA ra[],MYPOINT p1,double offset);
ARC getrotarc(double len);


void sort(int n,double a[]);
void drawdanline(LINE line1);
void drawdanarc(ARC arc1);
void drawdanloop(ROADAREA ra[]);
void drawpingmianendline();
int GetCommand();
void drawendline();
void toushitu();
void displayinf();
void displayinf();
void proccarcollide();
void judgetoendline();
void get_automatic_vlen(double *vcur,double vmax,double throttle,double *len);
void get_stick_vlen(double *vcur,double throttle,double *len);

double getlooplen(ROADAREA ra[]);
double jicheng(MYPOINT p1,MYPOINT p2,double *sum);
void clearclient();
int autostop(int s);
int drivestop(int s);
void GlobalInit();
void Game_Init();
void Game_Shutdown();
void setsight();

void interrupt newint9();
void setint9();
void recoverint9();
void sepkey(int ikey,int *iscan,int *iascii);

void mydelay(clock_t td);

//���μ��㺯��
void line_intersection(MYPOINT p1, MYPOINT p2, MYPOINT p3, MYPOINT  p4, int *count, MYPOINT pout[]);
void arcline_intersection(MYPOINT p1, MYPOINT p2, ARC arc1, MYPOINT intersection[], int *n);
void arc_intersection(ARC arc1,ARC arc2,int *count,MYPOINT pout[]);
int isAtLineRegion(LINE line1,MYPOINT p,double hw);
int isAtArcRegion(ARC arc1, MYPOINT p,double hw);
int isAtArc(ARC arc1,MYPOINT p);
double linereflect(LINE line1,double ain);
double arcreflect(ARC arc1,MYPOINT p,double ain);
double pp_angle(MYPOINT p1,MYPOINT p2);
double oo_angle(ARC arc1, ARC arc2);
MYPOINT arc_o(ARC arc1);
double pp_dist(MYPOINT p1,MYPOINT p2);
double oo_dist(ARC arc1,ARC arc2);
MYPOINT getarcpnt(ARC arc1,double ang);
MYPOINT getpangpnt(MYPOINT p0,double ang,double len);
double stdangle(double angle);
double stdangle0(double angle);
void x2xp(MYPOINT pntsight, double alpha0, MYPOINT pnt, MYPOINT *pnt_p);
void xp2x(MYPOINT pntsight, double alpha0, MYPOINT pnt_p, MYPOINT *pnt);
LINE scaleline(double k,LINE line1);
ARC scalearc(double k,ARC arc1);
POINT x2scr(MYPOINT p1);
void toscreen(POINT p1[]);
void setroadloop(double r, LINE li[], ARC ar[], ROADAREA ra[]);

int see3Dline(MY3DPOINT p1, MY3DPOINT p2, LINE3D *line3D);
void drawcar3Dline(LINE3D line3D);

void drawwheel(MY3DPOINT pcen);
void drawautocarface();
void drawdrivecarface();
void draw3Dfill(int n,MY3DPOINT p3D[],int poly[]);
void drawwheelface(MYPOINT pos1,double angpos1,MY3DPOINT pcenout,MY3DPOINT pcenin);
void wheelup(MY3DPOINT pcen,int n,MY3DPOINT p3Dup[]);
void draw_lanloop(int nseg,ROADAREA ra[]);
void draw_lanarc(ARC arc1);
void draw_lanline(LINE line1);
void draw_lanvline(LINE linearea,LINE line,BASEFUNCPTR funptr);
void draw_lanvarc(ARC arcarea,ARC arc,BASEFUNCPTR funptr);
void draw_lanvbase(MYPOINT pnt,double ang);
int whereat(LINE line, MYPOINT pnt, int *n);
void y2yp(MY3DPOINT pntsight, double alpha0, MY3DPOINT pnt, MY3DPOINT *pnt_p);
void yp2y(MY3DPOINT pntsight, double alpha0, MY3DPOINT pnt_p, MY3DPOINT *pnt);
void draw_treeloop(int nseg,ROADAREA ra[]);
void draw_treebase(MYPOINT pnt,double ang);
void carRace(int*x);