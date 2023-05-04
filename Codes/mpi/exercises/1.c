//1. Implement MPI_Bcast using MPI_Send from one rank to all others.

#include<stdio.h>
#include<mpi.h>

void Bcast(int source, int message, int rank, int size) {
	MPI_Status status;
	int src = 0;
	int msg = 0;
	src = source;
	if(rank == src) {
		msg = message;
		for (int i = 0; i < size; i++) {
			MPI_Send(&msg,1,MPI_INT,i,1,MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&msg,1,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&status);	
	}
	printf("I am %d, received message %d from %d\n", rank,msg,status.MPI_SOURCE);
}
	
int main(int argc, char **argv)
{
	int rank = 0, size = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	Bcast(0, 1, rank, size);
	MPI_Finalize();
}
	
	

