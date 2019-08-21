#include <stdio.h>
#include <string.h>
void main ()
{
 char w[][10]={"ABCD","EFGH","IJKL","MNOP"},k;
 for(k=1;k<3;k++)
   printf("%s\n",&w[k][k]);
}