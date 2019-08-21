#include <stdio.h>
#include <string.h>

void main()
{
	int i, j, l1, l2;

	char str1[50], str2[25];

	gets(str1);
	gets(str2);

	l1=strlen(str1);

	for(i=l1, j=0; i<50, j<25; i++, j++)
	{
		str1[i]=str2[j];
	}
	for (i=0; i<2; i++)
		puts(string[i]);
}