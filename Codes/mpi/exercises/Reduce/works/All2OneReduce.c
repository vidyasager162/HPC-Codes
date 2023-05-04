#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

void All2OneReduce(int my_id, int p, int *arr, int len, int dst)
{
	MPI_Status status;
	int d = (int)log2(p);
	int virt_id = my_id ^ dst;
	int *result = (int *)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++) {
		result[i] = arr[i];
	}
	int mask = 0;
	for (int i = 0; i < d; i++) {
		if (virt_id & mask == 0){
			if (virt_id & (int)pow(2,i) != 0){
				dst = virt_id ^ (int)pow(2,i);
				MPI_Send(result,len,MPI_INT,dst,1,MPI_COMM_WORLD);  
			}
			else {
				int src =  virt_id ^ (int)pow(2,i);
				MPI_Recv(arr,len,MPI_INT,src,1,MPI_COMM_WORLD,&status);
				for (int j = 0; j < len; j++){
					result[j] += arr[j];
					printf("%d\n",result[j]);
				}
			}
		}
		mask = mask ^ (int)pow(2,i);
	}
	for (int i = 0; i < len; i++)
	{
		printf("I am %d and I have %d at %d\n",my_id,result[i],i);
	}
	
}

int main(int argc, char **argv)
{
	int rank = 0, size = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int *arr = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++){
		arr[i] = i;
	}
	All2OneReduce(rank,size,arr,size,0);
	MPI_Finalize();
}
