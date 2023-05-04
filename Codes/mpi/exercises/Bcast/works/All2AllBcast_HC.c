#include<stdio.h>
#include<mpi.h>
#include<math.h>
#include<stdlib.h>

void All2AllBcast(int my_id, int p, int msg, int* result){
	MPI_Status status;
	int d = log2(p);
	int *recv_buffer = (int *)malloc((int)pow(2,(d-1))* sizeof(int));
	int tracker = 0;
	result[tracker++] = msg;
	for (int i = d-1; i >= 0; i--) {
		MPI_Send(result,(int)pow(2,d-i-1),MPI_INT,(my_id ^ (int)pow(2,i)),1,MPI_COMM_WORLD);
		MPI_Recv(recv_buffer,(int)pow(2,d-i-1),MPI_INT,(my_id ^ (int)pow(2,i)),1,MPI_COMM_WORLD,&status);
		
		for (int j = 0; j < (int)pow(2,d-i-1); j++) {
			result[tracker++] = recv_buffer[j];
		}
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
	// printf("I am %d and my_msg is : %d\n",rank,my_msg);
	All2AllBcast(rank,size,rank,result);
	for (int i = 0; i < size; i++) {
		printf("I am %d and my result[%d] is %d\n", rank,i,result[i]);
	}
	MPI_Finalize();
}
