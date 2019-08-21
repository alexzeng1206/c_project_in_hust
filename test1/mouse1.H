#ifndef _nmouse1_H
#define _nmouse1_H


void cursor(int x, int y);
void setMouseShape(int mark, int mx, int my);
void mousehide(int x, int y);
void getMousebk(int x, int y);
int init(int xmi, int xma, int ymi, int yma);
void mouseInit(int *mx, int *my, int *mbutt);
int read(int *mx, int *my, int *mbutt);
void newxy(int *mx, int *my, int *mbutt);
void backgroundChange(int mx, int my, int x1, int y1, int x2, int y2);
void AddFrame(int mx, int my, int x1, int y1, int x2, int y2, int color);
#endif