#include "main.h"

// Alloue l'espace mémoire pour un niveau_t et son tableau. Assigne le nombres de colonnes et de lignes
niveau_t* nouveau_niveau(int nb_colonnes, int nb_lignes)
{
	// Réservation de l'espace nécessaire à un niveau
	niveau_t* niveau = malloc(sizeof(niveau_t));

	// Initialisation des caractéristiques du niveau
	niveau->nb_lignes   = nb_lignes;
	niveau->nb_colonnes = nb_colonnes;
	niveau->terrain     = malloc(sizeof(char) * nb_colonnes * nb_lignes);
	niveau->nb_pas      = 0;
	niveau->perso       = malloc(sizeof(point_t));

	return niveau;
}



// Affecte un caractère à une case défini du tableau
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car)
{
	// détermine la positon dans le terrain
	int coordonnee = niveau->nb_colonnes * ligne + colonne;

	// modifie le terrain à la case voulue
	*((niveau->terrain) + coordonnee) = car;
}



// Renvoi le caractère d'une case défini du tableau
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne)
{
	// détermine la positon dans le terrain
	int coordonnee = niveau->nb_colonnes * ligne + colonne;

	// renvoie le caractère en question
	return *(niveau->terrain + coordonnee);
}



// Initialise toutes les cases du tableau avec le caractères '#'
void initialise_le_terrain(niveau_t* niveau)
{
	// pour chaque case du terrain, on place un mur
	for (int l = 0; l < niveau->nb_lignes; l++)
		for (int c = 0; c < niveau->nb_colonnes; c++)
			place_sur_terrain(niveau, c, l, '#');
}



// Affiche tous les caractères contenus dans le tableau
void affichage_niveau(niveau_t* niveau)
{
	printf("\n\t");

	// pour chaque case du terrain, on affiche le caractère qu'elle contient
	for (int l = 0; l < niveau->nb_lignes; l++)
	{
		for (int c = 0;c < niveau->nb_colonnes; c++)
		{
			char car = lecture_du_terrain(niveau, c, l);
			char* couleur;

			if (car == '#')
				couleur = color("purple");
			else if (car == '.')
				couleur = color("yellow");
			else if (car == '$' || car == '*')
				couleur = color("green");
			else
				couleur = color("");

			printf("%s%c%s", couleur, car, color(""));
		}
		printf("\n\t");
	}
	printf("\n");
}



// Génère un niveau_t spécifique à partir d'un fichier texte et renvoi le niveau
niveau_t* generer_niveau(char nom_fichier[])
{
	FILE* fichier = fopen(nom_fichier, "r");

	char string[40];

	int taille = lire_un_fichier_jusqu_a_un_car(fichier, string, ' ');
	int nb_colonnes = stringToInt(string, taille);

	taille = lire_un_fichier_jusqu_a_un_car(fichier, string, '\n');
	int nb_lignes = stringToInt(string, taille);

	niveau_t* niveau = nouveau_niveau(nb_colonnes, nb_lignes);

	for (int l = 0; l < nb_lignes; l++)
	{
		lire_un_fichier_jusqu_a_un_car(fichier, string, '\n');
		for(int c = 0; c < nb_colonnes; c++)
			place_sur_terrain(niveau, c, l, *(string + c));
	}

	niveau->perso = generer_joueur(niveau);

	return niveau;
}



// Libère l'espace mémoire occupé par un type niveau_t
void liberation_du_niveau(niveau_t* niveau)
{
	free(niveau->terrain);
	liberation_point(niveau->perso);
	free(niveau);
}



// Vérifie s'il ne reste plus de '$' sur le terrain, auquel cas le joueur a gagné(renvoi 1)
int niveau_termine(niveau_t* niveau)
{
	int presence_caisse = 1;
	for(int i=0;i<niveau->nb_lignes;i++)
		for(int j=0;j<niveau->nb_colonnes;j++)
		{
			char contenu_case = lecture_du_terrain(niveau,j,i);
			if (contenu_case == '$')
			presence_caisse = 0;
		}

    return presence_caisse;

}