#include <stdio.h>
void main()
{
   int a,b,i;
   scanf("%d",&a);
   b =1 ;
   for(i = 1; ; i++)
   {
   if ( a/b ==0)
   {
	  printf("%d",i-1);
	  break;
   }
   dao(a,i-1);
}

int dao(int c, int d)
{
   int e;
   int f=10;
   for(e=1;e<d+1;e++)
   {
	  int t =c;
	  t %= f;
	  t /= (f/10);
	  f*=10;
	  printf("%d",t);
   }
}