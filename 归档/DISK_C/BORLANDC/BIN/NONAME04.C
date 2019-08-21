#include <stdio.h>
void main()
{
 char str[256];
 int i;
 int count[26]={0},sp;
 gets(str);
 
 sp=0;
 for(i=0;str[i]!='\0';i++)
 {
  if((str[i]>='a')&&(str[i]<='z'))
  {
   count[str[i]-'0']++;
  }
  else if(str[i]==' ')
  {
   sp++;
  }
 }
 for(i=0;i<26;i++)
 {
  printf("'a+'i''=%d\n",i,count[i]);

 }
 printf("sp=%d\n",sp);
}
