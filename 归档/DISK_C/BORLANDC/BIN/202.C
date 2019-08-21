#include <stdio.h>
void main()
 {
   int a,b,c;

   printf("enter three numbers:");

   scanf("%d %d %d",&a,&b,&c);

   if(a>b&&a>c)
   {
	 printf("%d\n",a);
	}
		else if(a<c&&b<c)
		{
		  printf("%d\n",c);
		}

		   else if(a<b&&b>c)
		   {
			  printf("%d\n",b);
		   }
}