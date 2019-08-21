#include<stdio.h>
void strcat(char string1[99],char string2[99]);
void main()
{
 char string1[40]={"good morning,"};
 char string2[20]={"everyone!"};
 strcat(string1,string2);
 printf("%s",string1);
}
void strcat(char string1[99],char string2[99])
{
 int i,j,k,a,b,c;
 for(i=0;i<100;i++)
 {
  if(string1[i]=='\0')  {j=i;break;}
 }
 for(a=0;a<100;a++)
 {
  if(string2[a]=='\0')  {b=a;break;}
 }
 for(k=0;k<b;k++,j++)
 {string1[j]=string2[k];}
}