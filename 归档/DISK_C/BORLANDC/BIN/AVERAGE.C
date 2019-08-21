#include<stdio.h>
#define N 10
void main()
{
	int a[N][3],b[N];
	int i,j,m,t;
	printf("please input m=");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<m;i++)
	{
		b[i]=(a[i][0]+a[i][1]+a[i][2])/3;
	}
	for(i=0;i<m-1;i++)
	{
		for(j=0;j<m-1-i;j++)
		{
			if(b[j]>b[j+1])
			{
				t=b[j];
				b[j]=b[j+1];
				b[j+1]=t;
			}
		}
	}
	for(i=0;i<m;i++)
	{
		printf("%d\t",b[i]);
	}
}



