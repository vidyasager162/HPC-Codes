#include <stdio.h>

int fun()
{
  printf("In fun\n");
}

int main()
{
  printf("Before fun\n");
  fun();
  printf("After fun\n");
}
