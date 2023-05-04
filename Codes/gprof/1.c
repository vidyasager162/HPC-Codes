#include <stdio.h>
#include <unistd.h>

int fun3()
{
  int i= 1;
  while(i > 0)
    i+= 2;
}

int fun1()
{
  int i= 1;
  while(i > 0)
    i++;
  fun3();
}

int fun2()
{
  int i= -1;
  while(i < 0)
    i--;
  fun3();
}


int main()
{
  int i= 1;
  while(i > 0)
    i+= 10;
  for(i= 0; i < 2; i++)
    fun1();
  for(i= 0; i < 1; i++)
    fun2();
  fun3();
}
