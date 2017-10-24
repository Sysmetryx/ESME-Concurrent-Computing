/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/				Exercice 3							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																		Methode Monte Carlo 				EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define N 1000000

double fx(double x);

int main(int argc, char *argv[])
{
	int rang, process_nbr, in = 0, i;
	long int intot = 0;
	double xi ,yi, prob;
	srand(time(NULL));
	MPI_Init(&argc, &argv); //initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr); //récupère le nombre total de processus
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	for(i = 0; i < N; i++)
	{
		xi = rand()/(double)RAND_MAX;
		yi = rand()/(double)RAND_MAX;
		if(yi <= fx(xi))
		{
			in++;
		}
	}
	MPI_Reduce(&in, &intot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rang == 0)
	{
		prob = (double)intot / ((double)process_nbr*(double)N);
		printf("Pi = %.17f", 4*prob);
	}
	MPI_Finalize();
	return 0;
}


double fx(double x)
{
	return(1/(1+x*x));
}

