#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void All2AllBcast(int my_id, int p, int msg, int *result) {
	MPI_Status status;
	int l = (my_id - 1 + p) % p;
	int r = (my_id + 1) % p;
	int tracker = my_id;
	result[tracker--] = msg;
	tracker = (tracker + p)%p;
	for(int i = 1; i <= p-1; i++) {
		MPI_Send(&msg,1,MPI_INT,r,1,MPI_COMM_WORLD);
		MPI_Recv(&msg,1,MPI_INT,l,1,MPI_COMM_WORLD,&status);
		result[tracker--] = msg;
		tracker = (tracker + p)%p;
	}
	for (int i = 0; i < sizeof(result); i++){
		printf("I am %d and my result[%d] is %d\n",my_id,i,result[i]);
	}
}

int main(int argc, char **argv)
{
	int rank = 0, size = 0, my_msg = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int *result = (int *)malloc(size * sizeof(int));
	my_msg = rank; 
	All2AllBcast(rank,size,my_msg,result);
	MPI_Finalize();
}