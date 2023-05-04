#include<stdio.h>
#include<mpi.h>
#include<math.h>

void One2AllBcastHC(int my_id, int d, int msg, int src) {
	MPI_Status status;
	int dst = 0;
	int source = 0;
	int virt_id = my_id ^ src;
	int mask = (int)pow(2, d)-1;
	for (int i = d; i >=0; i--)
	{
		mask = mask ^ (int)pow(2, i);
		if (virt_id & mask == 0)
		{
			if (virt_id & (int)pow(2, i) == 0)
			{
				dst = (virt_id ^ (int)pow(2, i));
				MPI_Send(&msg,1,MPI_INT,(dst ^ src),1,MPI_COMM_WORLD);
			} 
			else {
				source = (virt_id ^ (int)pow(2, i)); 
				MPI_Recv(&msg,1,MPI_INT,(source ^ src),1,MPI_COMM_WORLD,&status);
			}
		}
	}
	printf("I am %d and I have received %d from %d\n",my_id,msg,src);
}

int main(int argc, char **argv)
{
	int rank = 0, size = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	One2AllBcastHC(rank,3,1,0);
	MPI_Finalize();
}
