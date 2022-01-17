#include"main.h"

//Renvoi ule score contenu dans le fichier du niveau séléctioné
int lecture_du_score (int quel_niveau)
{
	char* chemin_fichier = malloc(sizeof(char) * 40);
	char* score = malloc(sizeof(char) * 40);
	sprintf(chemin_fichier, "./scores/score_%d", quel_niveau);
	FILE* file = fopen(chemin_fichier, "r");
	int taille = lire_un_fichier_jusqu_a_un_car(file, score, EOF);
	free(chemin_fichier);
	return stringToInt(score, taille);
}



//inscrit le score dans le fichier spécifié
void ecriture_du_score(int quel_niveau, int quel_score, char* nom_joueur)
{
	char* chemin_fichier = malloc(sizeof(char) * 40);
	sprintf(chemin_fichier, "./score_multi/score_multi_%d", quel_niveau);
	char* commande = malloc(sizeof(char) * 60);
	sprintf(commande, "touch %s", chemin_fichier);
	system(commande);
	FILE* fileLecture = fopen(chemin_fichier, "r");
	char* scores = score_trie(fileLecture, quel_score, nom_joueur);
	//char* scores=malloc(sizeof(char)*75);
	//printf("Meilleurs scores:\n%s", scores);
	fclose(fileLecture);
	FILE* fileEcriture = fopen(chemin_fichier, "w");
	fprintf(fileEcriture, "%s", scores);
	//sprintf(scores,"%s", score_trie(file, quel_score, nom_joueur));
	//fprintf(file, "%s", scores);
	//printf("%s",scores);
	
	fclose(fileEcriture);
	free(scores);
	free(chemin_fichier);
	free(commande);
}



//si le score du joueur est le meilleur score alors il est inscrit dans le fichier puis affiche le score contenu dans le fichier du niveau
void afficher_meilleur_score(char* commande)
{
	char* chemin_fichier = malloc(sizeof(char) * 40);
	sprintf(chemin_fichier, "./score_multi/score_multi_%d", stringToInt(commande, 1));
	char* commandeSys = malloc(sizeof(char) * 60);
	sprintf(commandeSys, "cat %s", chemin_fichier);

	//Affichage
	printf("\tClassement\n\n");
	int cmd = system(commandeSys);
	printf("%d\n", cmd);
	printf("\nAppuyer sur une touche quelconque puis sur [Entrée] pour continuer.\n");
	entree_du_joueur();

	// libération des variables
	free(chemin_fichier);
	free(commandeSys);
}



//demande le nom du joueur et renvoie une chaîne de huit caractères
char* nom_du_joueur(void)
{
	char* nom = malloc(sizeof(char) * 8);
	printf("Entrez votrer nom\n");
	scanf("%s", nom);
	return nom;
}



//renvoie une chaine de caractère des scores triés
char* score_trie(FILE* file, int score, char* nom_joueur)
{
	int* tab_score = malloc(sizeof(int) * 6);
	char** tab_nom = malloc(sizeof(char*) * 6);
	tab_score_et_nom(file, tab_score, tab_nom);
	*(tab_score + 5) = score;
	*(tab_nom + 5) = nom_joueur;
	supprimer_les_doublons(tab_score, tab_nom);
	int intStock;
	char* stringStock = malloc(sizeof(char) * 8);

	for (int i = 0; i < 6; i++)
		for (int j = i + 1; j < 6; j++)
			if (((*(tab_score + j) < *(tab_score + i)) && *(tab_score + j) != 0) || *(tab_score + i) == 0)
			{
				intStock = *(tab_score + j);
				*(tab_score + j) = *(tab_score + i);
				*(tab_score + i) = intStock;
				stringStock = *(tab_nom + j);
				*(tab_nom + j) = *(tab_nom + i);
				*(tab_nom + i) = stringStock;			
			}

	char* res = malloc(sizeof(char) * 100);
	char* resClone = malloc(sizeof(char) * 100);

	for (int i = 0; i < 5; i++)
	{
			sprintf(res, "%s%d %s\n", resClone, *(tab_score + i), *(tab_nom + i));
			sprintf(resClone, "%s", res);
		
	}

	free(resClone);
	free(tab_nom);
	free(tab_score);

	return res;
}



//modifie les deux tableaux en paramètres et leur affecte les valeaur du fichier de score
void tab_score_et_nom(FILE* file, int* tab_score, char** tab_nom)
{
	int cpt = -1;
	int longueur;
	char* transition_int = malloc(sizeof(char) * 5);

	for (int i = 0; i < 6; i++)
		*(tab_nom + i) = malloc(sizeof(char) * 8);

	do
	{
		cpt++;
		longueur = lire_un_fichier_jusqu_a_un_car(file, transition_int, ' ');
		*(tab_score + cpt) = stringToInt(transition_int, longueur);
		lire_un_fichier_jusqu_a_un_car(file, *(tab_nom + cpt), '\n');
	} while (longueur > 0 && cpt < 5);
	
	free(transition_int);
}



//supprime le score le moins bon pour deux scores du même joueur
void supprimer_les_doublons(int* tab_score, char** tab_nom)
{
	for (int i = 0; i < 6; i++)
		for (int j = i + 1; j < 6; j++)
			if (equals(*(tab_nom + i), *(tab_nom + j)))
			{
				if(*(tab_score + i) > *(tab_score + j))
				{
					*(tab_score + i) = 0;
					*(tab_nom + i) = "";
				}
				else
				{
					*(tab_score + j) = 0;
					*(tab_nom + j) = "";
				}
			}
}

