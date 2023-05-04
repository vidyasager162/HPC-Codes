#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

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

void Bitonic_Sort(int my_id, int p, int *num) {
	MPI_Status status;
	int d = log2(p);
	int partner = 0, bit1 = 0, bit2 = 0;
	for (int i = 0; i < d; i++) {
		for (int j = i; j >= 0; j--) {
			partner = my_id ^ (int)pow(2, j);
			bit1 = my_id & (int)pow(2, j);
			bit2 = my_id & (int)pow(2, i+1);
			if ((bit1 > 0 && bit2 > 0) || (bit1 == 0 && bit2 == 0)) {
				compare_exchange_min(partner, num);
			} else {
				compare_exchange_max(partner, num);
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
	printf("Before: %d:%d\n",rank, num);
	Bitonic_Sort(rank,size,&num);
	printf("After: %d:%d\n",rank, num);
	MPI_Finalize();
	return 0;
}
