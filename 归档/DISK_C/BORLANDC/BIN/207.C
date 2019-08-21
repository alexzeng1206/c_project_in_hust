#include<stdio.h>
void main()
{
 int x, y;

 printf("please input x:");

 scanf("%d",&x);

 if(x<1)
 {
	y=x;
	printf("y=%d\n",y);
 }
	else if(x<10)
	{
		y=2*x-1;
		printf("y=%d\n",y);
	}
	  else
	  {
		 y=3*x-11;
		 printf("y=%d\n",y);
	  }
}