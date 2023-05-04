#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000
#define I 1

int main()
{
  int *arr= malloc(N * I * sizeof(int));
  int i, sum= 0, iterations = 0;
  clock_t begin, end;

  for (i= 0; i < N * I; i++) {
    if (i % I == 0)
      arr[i] = 5;
    else
      arr[i] = 0;
  }

  begin= clock();
  for (i= 0; i < N * I; i += I) {
    sum += arr[i];
    iterations++;
  }
  end= clock();

  printf("Sum: %d; Iterations: %d, Time taken= %f\n", sum, iterations, (double)(end-begin)/CLOCKS_PER_SEC);

  free(arr);
  return 0;
}
