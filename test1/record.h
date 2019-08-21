#ifndef  _record_H
#define _record_H

#include<stdio.h>
#include "jiegouti.h"
void recordlist(record *head) ;
void newrecord(record *head, char *p1,int p2,int p3,int p4,int p5);
void searchname1(record *head, char *p1,record *p2);  
int searchall(record *head, char *p1,record *p2);
void sort1(record *p,int n);
void searchtrack(record *head, int p1,record *p2);
void searchcar(record *head, int p1,record *p2);
void searchrank(record *head, int p1,record *p2);

#endif