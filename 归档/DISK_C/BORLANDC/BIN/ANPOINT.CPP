#include <stdio.h>
#define M 100
#define N 100
void main()
{
	int i,j,m,n;
	int max,jmax,flag,f=1;
	int a[M][N];
	scanf("%d %d",&m,&n);
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<m;i++)
	{
		max=a[i][0];
		jmax=0;
		for(j=1;j<n;j++)
		{
			if(max<a[i][j])
			{
				max=a[i][j];
				jmax=j;
			}
		}
		flag=1;
		for(j=0;j<m&&flag;j++)
		{
			if(a[j][jmax]<max)
			{
				flag=0;
			}
		}
		if(flag==1)
		{
			printf("a[%d][%d]=%d\n",i,jmax,max);
			f=0;
		}
	}
	if(f)
	{
		printf("No point an");
	}
}
