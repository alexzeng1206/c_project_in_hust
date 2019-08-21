#include <stdio.h>
void  main()
{
  char c;

  printf("enter a number:");

  scanf("%d",&c);

  if((c/2)*2==c)
  {
	 printf("c is a oushu\n");
  }
  else
  {
   printf("c is a jishu\n");
  }
}
