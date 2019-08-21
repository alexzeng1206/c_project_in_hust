#include <stdio.h>
int strlen( char string[100])
{
 int i=0;
 while(string[i]!='\0')
 {i++;}
 return(i);
}
void main()
{
 char string[20]={"hello"};
 printf("%d\n",strlen(string));
}