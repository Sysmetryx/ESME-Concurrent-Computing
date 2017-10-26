/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/				Exercice 3							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																		Methode Monte-Carlo 				EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rang, process_nbr;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	if(rang%2 == 0)
	{
		printf("Je suis un processus pair dont le rang est : %d \n", rang);
	}
	else
	{
		printf("Je suis un processus impair dont le rang est : %d \n", rang);
	}
	MPI_Finalize();
	return 0;
}