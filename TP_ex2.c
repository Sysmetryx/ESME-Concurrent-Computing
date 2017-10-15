/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|		EEEEEE		 sSSSS	MM		 MM		EEEEEE						LAPORTE Nathan 2Z2																EEEEEE		 sSSSS	MM		 MM		EEEEEE
|		EE		   sS		MMMM   MMMM		EE							laporte_n@esme.fr							OCTOBRE 2017						EE		   sS		MMMM   MMMM		EE
|		EEEEE	    sSS		MM	MM	 MM		EEEEEE						https://github.com/Sysmetryx/				Exercice 2							EEEEE	    sSS		MM	MM	 MM		EEEEEE
|		EE			  Ss	MM		 MM		EE																											EE			  Ss	MM		 MM		EE
|		EEEEE	 SSSSs		MM		 MM		EEEEEE																	PROGRAMMATION CONCURRENTE			EEEEE	 SSSSs		MM		 MM		EEEEEE																																																								
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"

#define N 32 // taille totale du tableau qui sera exporté

int main(int argc, char *argv[])
{
	int rang, process_nbr, i, j, longueur_tranche, data = 1; //variables contenant respectivement : le rang du processus actif, le nombre de processus, deux variables utilisées pour les itérations, le nombre de cases du tableau envoyées à chaque processus, le produit à calculer.
	int *valeurs = NULL, *donnees, *rcv_buffer; //Le premier tableau comporte toutes les valeurs à envoyer, le second est une subdivision du premier tableau qui comporte les donnees specifiques à chaque processus, le troisième agit comme memoire tampon à la reception des données.
	srand(time(NULL));
	MPI_Init(&argc, &argv); //initialise le communicateur
	MPI_Comm_size(MPI_COMM_WORLD, &process_nbr); //récupère le nombre de processus
	MPI_Comm_rank(MPI_COMM_WORLD, &rang); //récupère le rang du processus actif (donc chaque processus a accès à son rang)
	longueur_tranche = N/process_nbr; //détermine la taille de la subdivision à faire (avec un tableau de 32 valeurs, et 4 processus, chaque processus doit travailler sur 8 valeurs differentes.)
	donnees = (int*)malloc(longueur_tranche * sizeof(int)); //chaque processus effectue l'allocation d'un tableau qui reçoit ses données à traiter.
	if(rang == 0)//Code seulement executé par le processus 0
	{	
		valeurs = (int*)malloc(N * sizeof(int)); //effectue l'allocation du tableau contenant l'ensemble des valeurs.
		rcv_buffer = (int*)malloc(process_nbr * sizeof(int)); //effectue l'allocation du tableau qui recevra les données traitées (le resultat du produit des éléments de chaque petit tableau)
		for(i = 0; i < N; i++)
		{
			valeurs[i] = 1 + (rand()%5); //remplit le grand tableau, ici, des nombres entiers aléatoires compris entre 1 et 6. Attention l'opération effectuée est un produit, stocké dans un INT, si le resultat dépasse une certaine taille le resultat sera faux.
		}
	}
	MPI_Scatter(valeurs, longueur_tranche, MPI_INT, donnees, longueur_tranche, MPI_INT, 0, MPI_COMM_WORLD); //éprapille les données entre chaque processus. 
	for(i = 0; i < longueur_tranche; i++)
	{
		data = data * donnees[i]; //effectue le produit de toutes la valeurs du tableau reçu.
	}
	printf("data = %d \n", data);//Affiche pour chaque processus, le resultat du produit
	MPI_Gather(&data, 1, MPI_INT, rcv_buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);//Chaque processus envoie son resultat (data) au processus 0, qui le stocke dans le tableau rcv_buffer.
	if(rang == 0)//code executé uniquement par le processus 0
	{
		data = 0; //l'ancienne valeur de Data étant désormais stockée dans rcv_buffer, grace à MPI_Gather, on la remet à 0 et un l'utilisera pour stocker la somme de tous les élements récupérés.
		for(i = 0; i < process_nbr; i++)
		{
			data += rcv_buffer[i]; //fait la somme
		}
		printf("Res = %d \n", data); //l'affriche
	}
	if(valeurs)//vérifie si le tableau existe 
		free(valeurs); //libère la mémoire
	free (donnees);//libère la mémoire
	MPI_Finalize();//met fin au communicateur
	return 0;
}
