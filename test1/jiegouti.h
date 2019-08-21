#ifndef _jiegouti_H
#define _jiegouti_H
typedef struct account
{
	char name[11]; 
	char key[11];  
    char coin[4];
	char car[10];
	//char number[4];
	struct account *next;  
}user;
typedef struct jilu
{
	char jiluname[11];
	char jilutrack[10];
	char jilucar[10];
	char jilutime[5];
	char jilurank[3];
	struct jilu *next;
}record;
#endif