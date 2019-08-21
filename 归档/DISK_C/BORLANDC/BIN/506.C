#include <stdio.h>
#include <string.h>

#define	N 3

void main()
{
	char str[N][50];
	double mark[N];
	double tempmark;
	char tempstr[50];			 //辅助交换变量

	int i, j, k;				 //定义变量

	printf("input marks and names\n");

	for(i=0; i<N; i++)
	{			//输入信息
		//gets(str[i]);
		scanf("%s %lf", str[i], &mark[i]);
	}

	//冒泡排序
	for(i=0; i<N-1; i++)
	{
		for(j=0; j<N-1-i; j++)
		{
			if(mark[j]<mark[j+1])
			{
				tempmark=mark[j];
				mark[j]=mark[j+1];
				mark[j+1]=tempmark;

				strcpy(tempstr,str[j]);
				strcpy(str[j],str[j+1]);
				strcpy(str[j+1],tempstr);
			}
		}
	}

	// 输出
	for(i=0; i<N; i++)
	{
		printf("%s\t%.2lf\n",str[i], mark[i] );
	}
}