
//平面图显示选择
MYMACRO int toushi;//为1时显示透视图

//====车行、挡，跑道选择变量====
MYMACRO int segs;//确定跑道为三角形，还是四边形
//交互行驶车型选择，高度,颜色
MYMACRO enum COLORS mecolor;//交互行驶车颜色
MYMACRO int myshift;//手动挡挡位
MYMACRO GEARTYPE geartype;//自动挡，手动挡

MYMACRO int oldstate;//按位，保存单击键的前一状态，1为按下
MYMACRO int trig;//按位，为1表示单击键经过了一次松开到按下的转变

//MYMACRO MYPOINT posping;
//MYMACRO double angposping;

MYMACRO clock_t dly;

MYMACRO double throttledrive;//交互驾驶车油门
MYMACRO double throttleauto;//自动驾驶车油门

MYMACRO double rwheel;//轮胎半径
MYMACRO double areaying;//迎风面积
MYMACRO double weight;//车质量
MYMACRO double g;//重力加速度
MYMACRO double rou;//空气密度
MYMACRO double Cd;//风阻系数
MYMACRO double Crr;//滚动摩擦系数
MYMACRO double masterRatio;//主减速器变速比，3.5-5
MYMACRO double eta;//传动效率
MYMACRO double torque;//扭矩
//各挡传动比1.7~1.8，如六挡变速器7.640,4.835,2.857,1.895,1.337,1
MYMACRO double gear[3];//各挡对应的变速箱变速比，1挡对应下标1,2挡对应下标2
MYMACRO double vdrivemax;//20交互行驶最大速度
MYMACRO double vmaxshift[3];//各挡对应的最大速度

MYMACRO int cmd;//键盘命令
MYMACRO int keystate;//方向键、ESQ键按下状态

//视点高、水平面位置、视场坐标相对全局坐标转动角度
MYMACRO double camH;//单位m
MYMACRO double w;//线半宽，单位m

MYMACRO double carHW;//汽车半宽
MYMACRO double carL;//汽车长度

MYMACRO double v, R;//交互行驶速度，转弯半径
MYMACRO double vautomax;//自动行驶最大速度
MYMACRO double vauto;//自动行驶速度
MYMACRO double tick;
MYMACRO double rdrive;

MYMACRO MYPOINT pntsight;//单位m
MYMACRO double angsight;//单位rad

//跑道中心线参数
MYMACRO double roadW;

MYMACRO double kdash;//虚线周期放大系数

MYMACRO double road_halfo;//道路中间线圆弧圆心与坐标轴距离
MYMACRO double road_r;//道路中心线弯道圆弧半径

MYMACRO double autoH;//自动行驶车高度
MYMACRO int nopos;//自动行驶当前段号
MYMACRO int pathno;//自动行驶当前路线号
MYMACRO double sumauto;//自动行驶对应自动行驶路线路程
MYMACRO double angpos;//自动行驶车右方向与x轴的当前夹角

MYMACRO double sumdrive;//交互行驶对应自动行驶路线路程
MYMACRO double myangpos;//交互行驶右方向与x轴的夹角

//屏幕参数
MYMACRO double scrW,scrH;
MYMACRO double k ;//屏幕宽高比
//视图中心
MYMACRO double xcen;
MYMACRO double ycen;
MYMACRO double startclr;//刷新文字区左上角x坐标，为80

MYMACRO double offsetauto;//自动行驶车偏离中间自动行驶路线的距离
MYMACRO double offsetdrive;//交互行驶车偏离中间自动行驶路线的距离
MYMACRO MYPOINT mypos;//交互行驶当前位置
MYMACRO MYPOINT pos;//自动行驶当前位置
MYMACRO LINE endline;
MYMACRO double dashang;
MYMACRO double dashlen;//虚线周期长

//视场参数
MYMACRO double angvmax ;//视场的垂向半视角
MYMACRO double yminsight, ymaxsight;//视场的近距、远距
MYMACRO double anghmax; //视场的水平半视角，与垂直半视角相等，屏幕两边有没有用到的地方
MYMACRO double a2hsignt;//视场左边界角
MYMACRO double a1hsignt;//视场右边界角
//梯形视场在自己局部坐标（视点为原点，向前看为y轴）下的四个点
MYMACRO MYPOINT p[5];
MYMACRO ROADAREA roadareadash[2][12];
//中间虚线引用变量
MYMACRO LINE road_linedash[2][6];
MYMACRO ARC road_arcdash[2][6];
MYMACRO ROADAREA roadareaout[12],roadareain[12];
//跑道外边界引用变量
MYMACRO LINE road_lineout[6];
MYMACRO ARC road_arcout[6];
//跑道内边界引用变量
MYMACRO LINE road_linein[6];
MYMACRO ARC road_arcin[6];

//自动行驶路线，三条路线
MYMACRO ROADAREA autoroad[3][12];
MYMACRO LINE auto_line[3][6];
MYMACRO ARC  auto_arc[3][6];


//汽车侧面轮廓点，首底到尾底，自身坐标系下
MYMACRO MY3DPOINT pcarleft[7];
MYMACRO MY3DPOINT pcarright[7];
MYMACRO MYPOINT pcar[5];


//汽车前后轮子外侧中心，自身坐标系下
MYMACRO MY3DPOINT pcarcenleft[2];
MYMACRO MY3DPOINT pcarcenright[2];

//汽车前后轮子内侧中心，自身坐标系下
MYMACRO MY3DPOINT pcarcenleftin[2];
MYMACRO MY3DPOINT pcarcenrightin[2];

//车窗，自身坐标系下
MYMACRO MY3DPOINT pcarwinleft[3][4];
MYMACRO MY3DPOINT pcarwinright[3][4];

MYMACRO double sumpathauto;//自动行驶路线长度

MYMACRO double oneauto;
MYMACRO double onedrive;

MYMACRO double pi;

MYMACRO clock_t start, finish;
MYMACRO double  duration;
MYMACRO double timeme,timeauto;//行驶时间

MYMACRO void interrupt(*oldint9)();
MYMACRO void interrupt(*nint9)();

MYMACRO int itext;//每几帧显示速度等信息的控制变量

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
void autoruncar(ROADAREA ra[]);//自动行驶
double runarc(ROADAREA ra[],double xingshi,int frompos);//自动在圆弧上行驶
double runline(ROADAREA ra[],double xingshi,int frompos);//自动直线上行驶
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

//几何计算函数
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