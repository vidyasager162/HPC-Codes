//2. Implement MPI_Bcast using MPI_Send from each rank to its right neighbour.

#include<stdio.h>
#include<mpi.h>

void Bcast(int my_id, int message, int rank, int size) {
	MPI_Status status;
	

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
