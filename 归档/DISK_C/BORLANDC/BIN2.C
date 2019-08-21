#include <stdio.h>
void main()
{
 int a,b,c,d;
 printf("please input a,b,c:");
 scanf("%d %d %d",&a,&b,&c);
 if(a>=b)
 {
  d8=a;
  if(a>=c)
  {
   printf("max=%d",d);
  }
  else
  {
   d=c;
   printf("max=%d",d);
  }
 }
 else
 {
  d=b;
  if(b>=c)
  {
   printf("max=%d",d);
  }
  else
  {
   d=c;
   printf("max=%d",d);
  }
 }
}