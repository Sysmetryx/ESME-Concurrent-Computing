/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2 - serie 6													EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE																	Exercice 4							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																											EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 26
int main(int argc, char *argv[])
{
	int rang, process_nbr, i;
	char *alphabet;
	MPI_Init(&argc, &argv);
	MPI_Request req;
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	alphabet = (char*)malloc(N * sizeof(char));
	if(rang == 0)
	{
		for(i = 0; i < N; i++)
		{
			alphabet[i] = i + 97;
		}
		MPI_Isend(alphabet, N, MPI_CHAR, rang + 1, 1, MPI_COMM_WORLD, &req);
	}
	if(rang == 1)
	{
		MPI_Irecv(alphabet, N, MPI_CHAR, rang - 1, 1, MPI_COMM_WORLD, &req);
		MPI_Wait(&req, MPI_STATUS_IGNORE);
		for(i = 0; i < N; i++)
		{
			printf("Le processus %d a recu %c du processus %d \n", rang, alphabet[i], rang - 1 );
		}
	}
	MPI_Finalize();
	return 0;
}