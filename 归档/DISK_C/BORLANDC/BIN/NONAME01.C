#include <stdio.h>
void main()
{
 char str[256];
 int i;
 int l,d,s,ot;
 gets(str);
 l=d=s=ot=0;
 for(i=0;str[i]!='\0';i++)
 {
  if((str[i]>='0'&&str[i]<='9'))
  {
   d++;
  }
  else if(((str[i]>='a')&&(str[i]<='z')) || ((str[i]>='A')&&(str[i]<='Z')) )
  {
   l++;
  }
  else if(str[i]==' ')
  {
   s++;
  }
  else
  {
   ot++;
  }
 }
 printf("l=%d  d=%d  s=%d  ot=%d\n",l,d,s,ot);

}