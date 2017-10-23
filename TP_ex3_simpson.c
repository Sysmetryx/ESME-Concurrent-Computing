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

/* Programme effectuant une évaluation de la valeur de Pi avec un méthode dite "Simpson d'ordre 3" 
On se propose de décomposer l'interval d'intégration [a;b] en fonction du nombre de processus. Ainsi, sur un nombre de processu faible, le temps de calcul pour une précision similaire
doit être plus faible que pour la méthode des points-milieu. Le principe est d'interpoler (remplacer) la courbe à intégrer (ici 1/(1+x²)) par un polynome de degré n (ici n = 3)
Les formules de l'aire sous un tel polynome sont données par les formules de Newton-Cotes (trouvable en français sur wikipedia). Attention, utiliser un degré de polynome trop élevé 
peut entrainer une augmentation de l'erreur (phénomène de Runge). L'implémentation dans le code est très simple. De plus, il n'y a communication entre les processus qu'une seule fois
car chaque processus peut traiter son morceau d'interval de manière indépendante. Contrairement à la méthode des points milieu ou celle des trapèzes, il n'y a ici aucun problème pour
décomposer l'interval [a;b], le nombre de processus peut donc être choisi purement en foction de la précision voulue.

Information sur la précision (avec troncature)
| N =| prec = |
|  1 |	1	 |
|  2 |	4    |
|  3 |	5    |
|  4 |	6    |
|  5 |	7    |
|  6 |	7    |
|  7 |	7    |
|  8 |	8    |
|  9 |	8    |
| 10 |	8    |
| 11 |	9    |
| 12 |	9    |
| 13 |  9    |
| 14 |  10   |
| 15 |  10   |
| 16 |  10   |
| 20 |  11   |
| 31 |  12   |
| 44 |  13   |
| 93 |  14   |

au dela de n = 100, il devient compliqué d'augmenter la précision 
Le temps de calcul pour n = 93 est inferieur à 1s La methode des points milieu donne une précision à 6 chiffres en 5 secondes sur 93 processus.
*/

#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int rang, process_nbr; //rang est le rang du processeur actif, process_nbr est le nombre de processus total
	double longueur_tranche, Stime, Ftime; //définit la taille de l'interval traité par chaque processus soit N, le nombre de processus, chaque processus doit traiter un interval tel que [rang/N; (rang/N) + N]
	MPI_Init(&argc, &argv); //initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr); //récupère le nombre total de processus
	MPI_Comm_rank(MPI_COMM_WORLD, &rang); //chaque processus récupère son rang
	if(rang == 0)
		Stime = MPI_Wtime();
	longueur_tranche = 1.0 / (double)process_nbr; // calcul de la taille de l'interval
	double aire, aire_tot, fx, x, x2, x3, fx2, fx3; // aire est l'aire sous le polynome d'un processus, l'aire_tot est la somme des aires. les autres variables sont intuitives avec : fx = f(x)
	x = ((double)rang * longueur_tranche);
	x2 = x + longueur_tranche / 2.0;
	x3 = x + longueur_tranche;
	fx = (1.0 / ( 1.0 + pow(x, 2)));
	fx2 = (1.0 / ( 1.0 + pow(x2, 2)));
	fx3 = (1.0 / ( 1.0 + pow(x3, 2)));
	aire = (((x3 - x) / 6.0) * (fx + (4 * fx2) + fx3)); //formule de Newton-Cotes degré 2
	//printf("l'aire du processus %d est : %.17f \n", rang, aire); //Affiche l'aire calculée par un processus 
	MPI_Reduce(&aire, &aire_tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); //effectue la somme de toutes les aires
	
	if(rang == 0)
	{
		aire_tot *= 4; //l'intégrale a pour valeur Pi/4
		Ftime = MPI_Wtime();
		printf("La valeur recue est %.17f \n Le calcul a pris %f s", aire_tot, Ftime - Stime); //affiche l'aire totale.
	}
	MPI_Finalize();
	return 0;
}
