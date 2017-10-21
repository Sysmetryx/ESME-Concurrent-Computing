/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/				Exercice 3							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																		Methode Simpson ordre 3				EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/
#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int rang, process_nbr;
	double longueur_tranche;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	longueur_tranche = 1.0 / (double)process_nbr;
	double aire = 0.0, aire_tot = 0.0, fx, x, x2, x3, fx2, fx3;
	x = ((double)rang * longueur_tranche);
	x2 = (x + longueur_tranche) / 2.0;
	x3 = x + longueur_tranche;
	fx = (1.0 / ( 1.0 + pow(x, 2)));
	fx2 = (1.0 / ( 1.0 + pow(x2, 2)));
	fx3 = (1.0 / ( 1.0 + pow(x3, 2)));
	aire += 4*((longueur_tranche / 6.0) * (fx + (4 * fx2) + fx3));
	//printf("l'aire du processus %d est : %.17f \n", rang, aire);
	MPI_Reduce(&aire, &aire_tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rang == 0)
	{
		printf("La valeur recue est %.17f", aire_tot);
	}
	MPI_Finalize();
	return 0;
}
