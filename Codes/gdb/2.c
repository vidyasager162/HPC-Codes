//2.c
#include <stdio.h>

int fun(int k)
{
  return(k-10);
}

int main()
{
  int i= 0;
  for(i= 0; i < 20; i++)
    printf("%d\n",i/fun(i));
}
