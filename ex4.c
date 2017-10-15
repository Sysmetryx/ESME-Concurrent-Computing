#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[])
{
	int rang;
	int data = 2;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	MPI_Bcast(&data, 1, MPI_INT, 2, MPI_COMM_WORLD);
	printf("Je suis le processus %d, j'ai recu %d du processus 2\n", rang, data);
	MPI_Finalize();
	return 0;
}