#include<stdio.h>
#include<alloc.h>
#include<stdlib.h>
#include<string.h>
void main()
{
   char *str;
   if((str=(char*)malloc(10*sizeof(char)))==NULL)
   {
	   printf("not enough memory to allocte bufer.\n");
	   exit(1);
   }
   strcpy(str,"hello");
   printf("string is %s\n",str);
   free(str);
}




















