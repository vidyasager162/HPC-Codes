#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>

void All2AllReduce(int my_id, int d, int *my_msg, int *result) {
	mask = 0;
	int *temp = (int *)malloc((int)pow(2,d)*sizeof(int));
	for (int i = d-1; i >=0; i--) {
		mask = mask ^ (int)pow(2,i);
		int partner = my_id ^ (int)pow(2,i);
		int send_offset = partner & mask;
		int recv_offset = partner & mask;
		MPI_Send(&my_msg[],1,MPI_INT,partner,1,MPI_COMM_WORLD);
		MPI_Recv(&temp[],1,MPI_INT,partner,1,MPI_COMM_WORLD,&status);
		for (int j = 0; j < (int)pow(2,i); j++) {
			my_msg[recv_offset+j] + = temp[j];
		}
	}
	result = my_msg[my_id];
}