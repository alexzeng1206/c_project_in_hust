#include <stdio.h>
#include <string.h>
#define n 10
void main()
{
	char str[n];

	int i, a[123];

	gets(str);

	for(i=0; i<123; i++)
		a[i]=0;

	for(i=0; str[i]!='\0'; i++)
	   {a[int(str[i])]++;}

	for(i=65; i<=90; i++)
	   if(a[i])	printf("%c=%d\n", i, a[i]);

	for(i=97; i<=122; i++)
	  if(a[i])	printf("%c=%d\n", i, a[i]);

	printf("sp=%d", a[32]);

}