//4.c
#include <stdio.h>
#define N 10

void main(int argc, char *argv[]) {
   int tock[N];
   int i;
   int oddsum,evensum;

   for(i=0;i<N;i++) {
      if(i<=4) {
        tock[i]=(i*i)%3;
      }else{
        tock[i]=(i*i)%5;
      }
   }

   oddsum=0;
   evensum=0;
   for(i=0;i<N;i++) {
     if(i%2==0) {
       evensum=evensum+tock[i];
     }else{
       oddsum=oddsum+tock[i];
     }
   }

   printf("oddsum=%d\n",oddsum);
   printf("evensum=%d\n",evensum);
}
