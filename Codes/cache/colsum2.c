#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10000
#define N 10000

int main()
{
  double A[M][N]= {}, B[N]= {};
  int i= 0, j= 0;
  clock_t b1, e1, b2, e2;

  b1= clock();
  for(i= 0; i < M; i++)
    for(j= 0; j < N; j++)
      A[i][j]= drand48();
  e1= clock();

  b2= clock();
  for(i= 0; i < M; i++)
    for(j= 0; j < N; j++)
      B[j]+= A[i][j];
  e2= clock();

  printf("Elapsed time1= %f sec\n",(double)(e1-b1)/CLOCKS_PER_SEC);
  printf("Elapsed time2= %f sec\n",(double)(e2-b2)/CLOCKS_PER_SEC);

  return(0);
}
