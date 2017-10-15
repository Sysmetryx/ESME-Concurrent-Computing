/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/				Exercice 3							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																		Methode rectangles					EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/
#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 40000

int main (int argc, char *argv[])
{
	int rang, process_nbr;
	double longueur_tranche;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	longueur_tranche =floor( N / (double)process_nbr);
	double aire = 0.0, aire_tot = 0.0, fx, x, x2, fx2, dx;
	double step = 1.0 / (double)N;
	for(int i = (rang * longueur_tranche); i <= ((rang * longueur_tranche) + longueur_tranche); i++)
	{
		x = ((double)i /(double)N);
		x2 = x + step;
		fx = (1.0 / ( 1.0 + pow(x, 2)));
		fx2 = (1.0 / ( 1.0 + pow(x2, 2)));
		dx = (fx + fx2) / 2;
		aire =  aire + dx * step;
	}
	aire = aire * 4;
	printf("l'aire du processus %d est : %.17f \n", rang, aire);
	MPI_Reduce(&aire, &aire_tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rang == 0)
	{
		printf("La valeur recue est %.17f", aire_tot);
	}
	MPI_Finalize();
	return 0;
}
