#include <stdio.h>
void main()
{
 char string[3][81];
 int i,j;
 int l,m,n,s,ot;
 for (i=0;i<3;i++)
 {
  gets(string[i]);
 }
 l=m=n=s=ot=0;
 for(i=0;i<3;i++)
 {
  for(j=0;j<80&&string[i][j]!='\0';j++)
  {
   if((string[i][j]>='A')&&(string[i][j]<='Z'))
   {
	l++;
   }
   else if((string[i][j]>='a')&&(string[i][j]<='z'))
   {
	n++;
   }
   else if(string[i][j]==' ')
   {
	s++;
   }
   else
   {
	ot++;
   }
  }
  printf("l=%d  m=%d  n=%d  s=%d  ot=%d\n",l,m,n,s,ot);

 }
}