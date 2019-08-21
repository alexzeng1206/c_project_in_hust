#include <stdio.h>
#include <string.h>

#define N 10
void main()
{
	char str[3][N];

	int i, j, k, L=0, l=0, sp=0, n=0, ot=0;

	printf("input the string:");

	for(i=0; i<3; i++)
		gets(str[i]);

	for(i=0; i<3; i++)
	{
		for(j=0; j<N; j++)
		{
			if (str[i][j]>='a'&&str[i][j]<='z')
				l++;

			else if (str[i][j]>='A'&&str[i][j]<='Z')
				L++;

			else if (str[i][j]>='0'&&str[i][j]<='9')
				n++;

			else if (str[i][j]==' ')
				sp++;

			else
				ot++;
		}
	}

	printf("L=%d\tl=%d\tn=%d\tsp=%d\tot=%d", L, l, n, sp, ot);
}