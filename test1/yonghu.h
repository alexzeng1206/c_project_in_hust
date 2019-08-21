#ifndef _yonghu_H
#define _yonghu_H
#include<stdio.h>
#include "jiegouti.h"

void userlist(user *);
int searchname( user *,char * );
int judge(user *head,char *,char *);
void newuser(user *head, char *, char *);
void tozifu( int , char *);
int toshuzi(char *p);
void changecoin(user *head,char *p1,int num);
void changecar(user *head,char *p1,char *type);
void tiqu(user *head,char *p0,char *p1,char *p2);

#endif