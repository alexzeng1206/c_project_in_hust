#include <stdio.h>
void main()
{
 char name[19][10];
 int score[19];
 int i,j,a,b,c;
 printf("please enter the student's name and score=");
 for(i=0;i<19;i++)
 {
  scanf("%s",name[i]);
 }
 for(j=0;j<19;j++)
 {
  scanf("%d",&score[j]);
 }
  for(a=0;a<18;i++)
  {
   for(b=0;b<18-i;b++)
   {
	if(score[b]>score[j+1])
	{
	 c=score[b];
	 score[b]=score[b+1];
	 score[b+1]=c;
	}
   }
  }
  for(i=0;i<19;i++)
  {
   printf("%s%d",name[i],score[i]);
  }
}