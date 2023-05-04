#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

void compare_exchange_min(int partner, int *data) {
	int buffer;
	MPI_Status status;
	MPI_Send(data, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
	if (buffer < *data) {
		*data = buffer;
	}
}

void compare_exchange_max(int partner, int *data) {
	int buffer;
	MPI_Status status;
	MPI_Send(data, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
	if (buffer > *data) {
		*data = buffer;
	}
}

void Odd_Even_Transposition_Sort(int my_id, int p, int *num) {
	MPI_Status status;
	int i, partner;
	for (i = 0; i < p; i++)
	{
		if (i % 2 == 0)
		{
			if (my_id % 2 == 0 && my_id < p - 1) 
			{
				partner = my_id + 1;
				compare_exchange_min(partner, num);
			} 
			else if (my_id % 2 != 0) 
			{
				partner = my_id - 1;
				compare_exchange_max(partner, num);
			}
		} 
		else 
		{
			if (my_id > 0) 
			{
				if (my_id % 2 != 0 && my_id < p -1)
				{
					partner = my_id + 1;
					compare_exchange_min(partner, num);
				} 
				else if (my_id % 2 == 0) 
				{
					partner = my_id - 1;
					compare_exchange_max(partner, num);
				}
			}
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
	srand(time(0) + rank);
	int num = rand();
    printf("Before: %d:%d\n", rank, num);
	Odd_Even_Transposition_Sort(rank,size,&num);
	MPI_Barrier(MPI_COMM_WORLD);
    printf("After: %d:%d\n", rank, num);
	MPI_Finalize();
	return 0;
}
