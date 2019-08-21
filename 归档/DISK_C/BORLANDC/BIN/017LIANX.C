#include <stdio.h>
void main()
{
 char* name[4][5];
 int score[4];
 int i,j,t;
 char l;
 printf("please enter the students' names");
 for(i=0;i<4;i++)
 {
  scanf("%s",name[i]);
 }
 printf("please enter the students' scores");
 for(i=0;i<4;i++)
 {
  scanf("%d",&score[i]);
 }
  for(i=0;i<3;i++)
  {
   for(j=0;j<3-i;j++)
   {
	if(score[j]>score[j+1])
	{
	 t=score[j];
	 score[j]=score[j+1];
	 score[j+1]=t;
	 l=j;
	 j=j+1;
	 j=l-1;
	}
   }
  }
  for(i=0;i<4;i++)
  {
   printf("%s%d\n",name[i],score[i]);
  }
}