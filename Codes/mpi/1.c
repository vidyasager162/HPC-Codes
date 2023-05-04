#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank= 0, size= 0, i= 0, j= 0;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank == 1)
    i= 23;
    
  if(rank == 1)
  {
    for(j= 0; j < size; j++)
        if(j != 1)
          MPI_Send(&i,1,MPI_INT,j,1,MPI_COMM_WORLD);
  }
  else
    MPI_Recv(&i,1,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&status);

  printf("My rank = %d i = %d got from %d\n",rank,i,status.MPI_SOURCE);
  //while(i >= 0)
    //i++;
  MPI_Finalize();
}
