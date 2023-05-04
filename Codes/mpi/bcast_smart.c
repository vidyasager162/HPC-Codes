#include<stdio.h>
#include<unistd.h>
#include<mpi.h>

int main(int argc, char ** argv)
{
	int rank= 0, size= 0, a= 0, i= 1;
	MPI_Status status;
	MPI_Request r = MPI_REQUEST_NULL;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for(i = 1; i < size; i*= 2){
			if(rank > 0){
				if(rank == size-1){
					MPI_Recv(&a,1,MPI_INT,rank-i,0,MPI_COMM_WORLD, &status);
				}
				MPI_Recv(&a,1,MPI_INT,rank-i,0,MPI_COMM_WORLD, &status);
				MPI_Send(&a,1,MPI_INT,rank+i,0,MPI_COMM_WORLD);
			}
			if(rank == 0){
				a = 100;
				MPI_Send(&a,1,MPI_INT,rank+i,0,MPI_COMM_WORLD);
			}
	}
	printf("%d receieved %d", rank, a);
	MPI_Finalize();
}