#include <stdio.h>
#include <stdlib.h>

#define N 100

void main(int argc, char *argv[]) {
   int *tock= malloc(N * sizeof(int));
   int i= 0, oddsum= 0, evensum= 0;

   for(i= 0; i < N; i++) {
     if(i < 5)
       tock[i]=(i*i)%3;
     else
       tock[i]=(i*i)%5;
   }
   
   for(i= 0; i < N; i++) {
     if(i%2 == 0)
       evensum+= tock[i];
     else
       oddsum+= tock[i];
   }

   printf("oddsum=%d\n",oddsum);
   printf("evensum=%d\n",evensum);
}
