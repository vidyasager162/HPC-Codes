#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

void All2AllBcast(int my_id, int p, int msg, int *result) {
	MPI_Status status;
	int sqrtp = (int)sqrt(p);
	int row = my_id / sqrtp;
	int col = my_id % sqrtp;
	int l = row * sqrtp + ((col - 1 + sqrtp) % sqrtp);
 	int r = row * sqrtp + ((col + 1) % sqrtp);
 	int tracker = 0;
 	result[tracker++] = msg;
 	for (int i = 1; i <= sqrtp-1; i++) {
 		MPI_Send(&msg,1,MPI_INT,r,1,MPI_COMM_WORLD);
 		MPI_Recv(&msg,1,MPI_INT,l,1,MPI_COMM_WORLD,&status);
 		result[tracker++] = msg;
 	}
 	int u = ((row + 1) % sqrtp)*sqrtp + col;
 	int d = ((row - 1 + sqrtp)%sqrtp) * sqrtp + col;
 	int *recv_buffer = (int *)malloc(sqrtp * sizeof(int));
 	for (int i = 0; i < sqrtp; i++) {
 		recv_buffer[i] = result[i];	
 	}
 	for (int i = 1; i <= sqrtp-1; i++){
 		MPI_Send(&recv_buffer[i],1,MPI_INT,u,1,MPI_COMM_WORLD);
 		MPI_Recv(&recv_buffer[i],1,MPI_INT,d,1,MPI_COMM_WORLD,&status);
 		result[tracker++] = msg;
 	}
}

int main(int argc, char **argv)
{
	int rank = 0, size = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int *result = (int *)malloc(size * sizeof(int));
	int my_msg = rank;
	printf("I am %d and my_msg is : %d\n",rank,my_msg);
	All2AllBcast(rank,size,my_msg,result);
	MPI_Finalize();
}
