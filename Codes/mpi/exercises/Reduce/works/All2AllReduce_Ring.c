#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void All2AllReduceRing(int *my_msg, int p, int my_id, int result)
{
	MPI_Status status;
	int l = (my_id - 1 + p) % p;
	int r = (my_id + 1) % p;
	int recv = 0;
	int j = 0;
	for (int i = 1; i < p; i++) {
		j = (my_id + i)%p;
		my_msg[j] += recv;
		MPI_Send(&my_msg[j],1,MPI_INT,l,1,MPI_COMM_WORLD);
		MPI_Recv(&recv,1,MPI_INT,r,1,MPI_COMM_WORLD,&status);
	}
	result = my_msg[my_id] + recv;
	printf("I am %d and my result is %d\n",my_id,result);
}

int main(int argc, char **argv)
{
	int rank = 0, size = 0, result = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int *my_msg = (int *)malloc(size * sizeof(int));
	for (int i = 0;i < size; i++) {
		my_msg[i] = i;
	} 
	All2AllReduceRing(my_msg,size,rank,result);
	MPI_Finalize();
}
