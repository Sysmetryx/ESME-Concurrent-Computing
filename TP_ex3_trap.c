/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/				Exercice 3							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																		Methode trapèzes					EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/
#include "mpi.h"
#include <math.h> //optionnel, puisqu'on peut se passer de "pow(x, 2)" en écrivant x*x. Permet de modifier la fonction plus tard.
#include <stdio.h>
#include <stdlib.h>

#define N 80000000 //définit le nombre de points qui seront pris EN TOUT pour l'évaluation de l'aire. Plus N est grand, meilleure est la précision et plus long est le temps de calcul.

int main (int argc, char *argv[])
{
	int rang, process_nbr; /*on initialise les variables. Respectivement : Le rang du processeur actif (donc pour le processus 1, le rang est égal à 1), 
								Le nombre total de processeur (défini par mpiexec, cf script de lancement)*/
	double longueur_tranche, i, Ftime, Stime; //longueur_tranche correspond au sous interval utilisé par chaque processus (exempe : Avec 8 processus, le P0 se charge de x [0;1/8[, et P1 de [1/8;2/8])
	MPI_Init(&argc, &argv); //On initialise le communicateur MPI
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr);//détecte le nombre total de processus 
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);//chaque processus peut s'identifier par son rang
	if(rang == 0)
		Stime = MPI_Wtime();
	longueur_tranche = 1.0 / (double)process_nbr; //cf déclaration de la variable
	double aire = 0.0, aire_tot = 0.0, fx, x, x2, fx2; // aire est l'aire calculée par un processus. aire_tot est donc la somme des aires. les autres variables sont plus intuitives d'un ppoint de vu mathématique
	double step = 1.0 / (double)N; //définit l'interval entre x et x2. Plus N est grand plus celui-ci est fin.
	for(i = (rang * longueur_tranche); i < ((rang * longueur_tranche) + longueur_tranche); i += step) //chaque processus parcourt son interval, (cf déclaration de longueur tranche) avec un pas == step
	{
		x = i;
		x2 = x + step;
		fx = (1.0 / ( 1.0 + pow(x, 2))); //calcule f(x)
		fx2 = (1.0 / ( 1.0 + pow(x2, 2)));//calcule f(x2)
		aire += ((x2 - x)/2)*(fx +fx2); //1ère formule de Newto-Cotes, qui correspond à interpoler par une foction affine
	}
	// printf("l'aire du processus %d est : %.17f \n", rang, aire); //affiche l'aire calculée par chaque processus (ligne optionnelle)
	MPI_Reduce(&aire, &aire_tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rang == 0)
	{
		aire_tot *= 4;//l'aire calculée est une approximation de pi/4, car une primitive de 1/(1+x²) est arcan(x), et arctan(1) = pi/4
		Ftime = MPI_Wtime();
		printf("La valeur recue est %.17f \n Le calcul a pris %f s", aire_tot, Ftime - Stime);//affiche la valeur approximée de Pi, avec
	}
	MPI_Finalize(); //On finalise la procédure MPI
	return 0;
}
