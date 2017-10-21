/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2 - serie 6													EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE																	Exercice 4							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE							"envoyer un tableau contenant l'alphabet 										EE  		  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE						du processus 0 au processus 1"				PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 26 //définit la taille du tableau. Ici on met 26, on pourrait mettre un nombre compris entre 0 et 255, qui correspond à la table ASCII

int main(int argc, char *argv[])
{
	int rang, process_nbr, i; /*on initialise les variables. Respectivement : Le rang du processeur actif (donc pour le processus 1, le rang est égal à 1), 
								Le nombre total de processeur (défini par mpiexec, cf script de lancement), et i une variable d'incrémentation */
	char *alphabet;	//On déclare un tableau de pointeurs de char. On a donc un tableau dynamique qui contiendra des char.
	MPI_Init(&argc, &argv); //On initialise le communicateur MPI
	MPI_Request req; //On définit une requête (cf cours) Utilisé dans MPI_Isend();
	MPI_Status status; //définit le statut d'une communication. Utilisé dans MPI_Isend();
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr); //détecte le nombre total de processus 
	MPI_Comm_rank(MPI_COMM_WORLD, &rang); //chaque processus peut s'identifier par son rang
	alphabet = (char*)malloc(N * sizeof(char)); // Chaque processus "agrandit" le tableau en fonction de N.
	if(rang == 0) //code executé uniquement par le rang 0
	{
		for(i = 0; i < N; i++) // Parcourt les N élements 
		{
			alphabet[i] = i + 97; //Stocke les lettres minuscules dans le tableau. (pour les majuscules on mettra i + 65) cf http://www.table-ascii.com/
		}
		MPI_Isend(alphabet, N, MPI_CHAR, rang + 1, 1, MPI_COMM_WORLD, &req); //effectue une communication point à point non bloquante. Ici, on transmet l'intégralité du tableau en une seule communication. du processus N vers N+1.
	}	
	if(rang == 1)//code effectué par le processus 1
	{
		MPI_Irecv(alphabet, N, MPI_CHAR, rang - 1, 1, MPI_COMM_WORLD, &req); //reçoit les données envoyées par le processus N-1, avec pour flag 1 etc... CF cours
		MPI_Wait(&req, &status); //permet de confirmer qu'on a reçu le message et de terminer la requete. 
		for(i = 0; i < N; i++)
		{
			printf("Le processus %d a recu %c du processus %d \n", rang, alphabet[i], rang - 1 ); //affiche les éléments du tableau du processus 1
		}
	}
	if(alphabet)
	{
		free(alphabet); //On n'oublie pas de libérer l'espace mémoire, puisque l'on a des pointeurs !
	}
	MPI_Finalize(); //On finalise la procédure MPI
	return 0;
}