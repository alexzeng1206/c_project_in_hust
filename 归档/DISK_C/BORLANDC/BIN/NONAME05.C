#include <stdio.h>
void main()
{
 char str1[256],str2[256];
 int i,j;
 gets(str1);
 gets(str2);
 if(str1[1]!='\0')
 {
  i++;


  for(j=0;str2[j]!='\0';j++)  {
  str1[i+j]=str2[j];
 }

  puts(str1);
}