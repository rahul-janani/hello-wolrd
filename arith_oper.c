#include <stdio.h>

int main()
{
int a=10,b=20,c;
c=add(a,b);
printf("addition is %d\n",c);
c=sub(a,b);
return 0;
}
int add(int x,int y)
{
int z;
return x+y;
}
int sub(int x,int y)
{
int z;
return x-y;
}
