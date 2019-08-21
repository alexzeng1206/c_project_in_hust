#include <stdio.h>
#include <string.h>

#define R 3
#define C 3

void main()
{
	int	a[R][C];
	int i, j, k, t, n, max, min, count;

	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
			scanf("%d", &a[i][j]);
	}

	for(i=0; i<R-1; i++)
	{

		for(j=0, k=1; j<C; j++)
		{
			if( a[i][j] > a[i][k] )
			{
				max=a[i][j];
				k=j;
			}
			else
			{
				max=a[i][k];
			}
		}

		for(t=0, n=1; t<R; t++)
		{
			if(a[t][k]<a[n][k])
			{
				min=a[t][k];
				n=t;
			}
			else
			{
				min=a[n][k];
			}
		}

		if(n==i)
		{
			printf("an dian is %d, it's location is  row=%d column=%d\n", a[n][k], n+1, k+1);

			count++;
		}
		if(count==0)
			printf("on andian\n");
	}
}