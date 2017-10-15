/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/													EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																											EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define N 128

int main (int argc, char *argv[])
{
	int rang, i, process_nbr, longueur_tranche;
	float *valeurs = NULL, *donnees;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	longueur_tranche = N / process_nbr;
	donnees = (double*)malloc(longueur_tranche * sizeof(double));
	if( rang == 0)
	{
		valeurs = (double*) malloc(N*sizeof(double));
		for(i = 0; i < N; i++)
			valeurs[i] = (float)(1000+i);
	}
	MPI_Scatter(valeurs, longueur_tranche, MPI_FLOAT, donnees, longueur_tranche, MPI_FLOAT, 0, MPI_COMM_WORLD);
	printf("Je suis le processus %d, j'ai recu %0f du processus 0\n", rang, donnees[0]);
	MPI_Reduce(donnees, valeurs, longueur_tranche, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rang == 0)
	{
		printf("La valeur reçue est %f", valeurs[0]);
	}
	if(valeurs)
		free(valeurs);
	free (donnees);
	MPI_Finalize();
	return 0;
}