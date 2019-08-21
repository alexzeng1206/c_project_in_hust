#include <stdio.h>
#define N 5

void main()
{
	int a[N];

	int i, j, t;

	printf("input a group if numbers:");

	for(i=0; i<N-1; i++)
	{
		scanf("%d", &a[i]);
	}

	for(i=0; i<N-2; i++)
	{
		for(j=i+1; j<N-1; j++)
		{
			if(a[i]>a[j])
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}

	for(i=0; i<N-1; i++)
		printf("%d", a[i]);

	printf("\n now input a new number:");

	scanf("%d", &a[N-1]);

	for(i=0; i<N; i++)
	{
		if(a[i]>a[N-1])
		{
			int j=i;

			t=a[N-1];

			for(i=N-1; i>j; i--)
				a[i]=a[i-1];
			a[j]=t;

			break;
		}
	}

	printf("\n");

	for(i=0; i<N; i++)
	{
		printf("%d\t", a[i]);
	}
}