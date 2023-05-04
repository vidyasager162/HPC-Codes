//Implement One-to-all Broadcast in ring of p processes, for any p > 2 and from any source.
//implementation that works for p = power of 2, from any source, 10 Marks
//implementation that works for any p, from any source, 10 Marks

#include <stdio.h>
#include <mpi.h>
#include <math.h>

void One_to_all_bcast(void *buf, int count, MPI_Datatype dp, int src, MPI_Comm comm)
{
  //Your implementation here
  MPI_Status status;
  int size = 0;
  int my_id = 0;
  int i = 0;
  MPI_Comm_rank(comm,&my_id);
  MPI_Comm_size(comm,&size);
  int dst = 0;
  int source = 0;
  int d = log2(size);
  int virt_id = my_id ^ src;
  int mask = (pow(2, d)-1);
  // printf("I am %d and my vid is: %d\n",my_id,virt_id);
  for (i = d-1; i >= 0; i--)
  {
    mask = mask^(int)pow(2, i);
    // printf("mask: %d\n",mask);
    if (virt_id & mask == 0)
    { 
      if (virt_id & (int)pow(2, i) == 0)
      {
        dst = (virt_id ^ (int)pow(2, i));
        MPI_Send(&buf,count,dp,(dst ^ src),1,MPI_COMM_WORLD);
      } 
      else 
      {
        source = (virt_id ^ (int)pow(2, i));
        MPI_Recv(&buf,count,dp,(source ^ src),1,MPI_COMM_WORLD,&status);
      }
    }
  }
}

int main(int argc, char **argv)
{
  int rank= 0, size= 0, i= 0;
  int arr[10]= {};
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank == 3)
    for(i= 0; i < 10; i++) 
      arr[i]= 3*i;

  One_to_all_bcast(arr,10,MPI_INT,3,MPI_COMM_WORLD);
  
  printf("%d got %d\n",rank,arr[5]);
  MPI_Finalize();
}

//Logic:
//One to All Broadcast works with one source sending its message to every other process.
//The Algorithm we try to implement here for the ring is that in the first iteration process 0 will send to 4
//and in the second iteration process 0 sends to 2 and 4 to 6
//and in the third iteration process 0 sends to 1, 2 to 3, 4 to 5 and 6 to 7.
//This is accomodated by having a mask and this mask keeps changing for every iteration.
//The mask will restrict the processes participating in each iteration.
//The logic is so that only the source processor mentioned will send in the first iteration.
//To generalixe this algorithm for any source, we take the rank of each processor and xor it with the source id
//so that everything works like 0 is still the source but in fact 3 acts as 0 because of the above mentioned xor operation.

