#include "main.h"

// Génère un joueur en trouvant sa position sur le terrain
point_t* generer_joueur(niveau_t* niveau)
{
	// Réservation de l'espace nécessaire à accueillir un point_t
	point_t* joueur = malloc(sizeof(point_t));

	int l = 0;
	int c;
	int trouve = 0;

	while (l < niveau->nb_lignes && !trouve)
	{
		c = 0;
		while (c < niveau->nb_colonnes && !trouve)
		{
			trouve = lecture_du_terrain(niveau, c, l) == '@';
			++c;
		}
		++l;
	}

	joueur->ligne   = l - 1;
	joueur->colonne = c - 1;

	return joueur;
}



// Libère l'espace mémoire occupé par la structure point_t
void liberation_point(point_t* point)
{
	free(point);
}



// initialise un point par un autre point
point_t* init_point_par(point_t* parent)
{
	point_t* enfant = malloc(sizeof(point_t));

	enfant->ligne   = parent->ligne;
	enfant->colonne = parent->colonne;

	return enfant;
}



// modifie les coordonnées d'une case selon une direction donnée
void position_ap_deplacement(point_t* position, char direction)
{
	/* à noter que : - le terminal suit un sens de lecture de gauche à droite et de haut en bas
					 - les déplacements gauche et droite correspondent à la ligne alors que les déplacements haut et bas correspondent à la colonne
	*/
	if (direction == 'z')
		--position->ligne;   // déplacement vers le haut, donc contre le sens de lecture, d'où l'incrémentation négative

	else if (direction == 'q')
		--position->colonne; // gauche, contre sens, incrémentation négative

	else if (direction == 's')
		++position->ligne;   // bas,    bon sens,    incrémentation positive

	else if (direction == 'd')
		++position->colonne; // droite, bon sens,    incrémentation positive
}



// vrai si le joueur est face à une caisse et souhaite la déplacer
int contient_caisse(niveau_t* niveau, point_t* cible)
{
	char car = lecture_du_terrain(niveau, cible->colonne, cible->ligne);
	return car == '$' || car == '*';
}



// vrai si le joueur est face à une caisse et souhaite la déplacer
int contient_joueur(niveau_t* niveau, point_t* cible)
{
	char car = lecture_du_terrain(niveau, cible->colonne, cible->ligne);
	return car == '@' || car == '+';
}



// vrai si le joueur est face à une caisse et souhaite la déplacer
int contient_vide(niveau_t* niveau, point_t* cible)
{
	char car = lecture_du_terrain(niveau, cible->colonne, cible->ligne);
	return car == ' ';
}



// vrai si le joueur est face à une caisse et souhaite la déplacer
int contient_objectif(niveau_t* niveau, point_t* cible)
{
	char car = lecture_du_terrain(niveau, cible->colonne, cible->ligne);
	return car == '.';
}



// valide la faisabilité d'un déplacement
int deplacement_possible(niveau_t* niveau, point_t* case_suivante)
{
	/* MÉMO :
		— ’ ’ représente les cases vides
		— ’.’ représente une zone de rangement sur laquelle vous devez placer une caisse
	*/

	char car = lecture_du_terrain(niveau, case_suivante->colonne, case_suivante->ligne);
	return car == ' ' || car == '.';
}



// deplace un élément d'une case A vers une case B
void move(niveau_t* niveau, point_t* case_A, point_t* case_B)
{
	/* MÉMO :
		— ’ ’ représente les cases vides
		— ’.’ représente une zone de rangement sur laquelle vous devez placer une caisse

		— ’$’ représente une caisse que vous pouvez déplacer
		— ’*’ représente une zone de rangement sur laquelle une caisse est actuellement placée
		
		— ’@’ représente votre personnage
		— ’+’ représente votre personnage lorsqu’il est sur une zone de rangement.
	*/

	char car_initial_A = lecture_du_terrain(niveau, case_A->colonne, case_A->ligne);
	char car_final_A;
	char car_initial_B = lecture_du_terrain(niveau, case_B->colonne, case_B->ligne);
	char car_final_B;

	if (contient_joueur(niveau, case_A)) // cas d'un déplacement de joueur
	{
		if (car_initial_A == '@')
		{
			if (contient_vide(niveau, case_B))
			{
				car_final_A = car_initial_B;
				car_final_B = car_initial_A;
				niveau->perso = case_B;
				niveau->nb_pas++;
			}
			else if (contient_objectif(niveau, case_B))
			{
				car_final_A = ' ';
				car_final_B = '+';
				niveau->perso = case_B;
				niveau->nb_pas++;
			}
		}
		else // est forcément '+'
		{
			if (contient_vide(niveau, case_B))
			{
				car_final_A = '.';
				car_final_B = '@';
				niveau->perso = case_B;
				niveau->nb_pas++;
			}
			else if (contient_objectif(niveau, case_B))
			{
				car_final_A = car_initial_B;
				car_final_B = car_initial_A;
				niveau->perso = case_B;
				niveau->nb_pas++;
			}
		}
	}
	else if (contient_caisse(niveau, case_A)) // cas d'un déplacement de caisse
	{
		if (car_initial_A == '$')
		{
			if (contient_vide(niveau, case_B))
			{
				car_final_A = car_initial_B;
				car_final_B = car_initial_A;
			}
			else if (contient_objectif(niveau, case_B))
			{
				car_final_A = ' ';
				car_final_B = '*';
			}
		}
		else // est forcément '*'
		{
			if (contient_vide(niveau, case_B))
			{
				car_final_A = '.';
				car_final_B = '$';
			}
			else if (contient_objectif(niveau, case_B))
			{
				car_final_A = car_initial_B;
				car_final_B = car_initial_A;
			}
		}
	}

	place_sur_terrain (niveau, case_A->colonne, case_A->ligne, car_final_A);
	place_sur_terrain (niveau, case_B->colonne, case_B->ligne, car_final_B);
}



// Déplace le joueur d'une case à l'autre
void deplacement(historique_t* hist, niveau_t* niveau, char direction)
{
	point_t* case_suivante_joueur = init_point_par(niveau->perso);
	position_ap_deplacement(case_suivante_joueur, direction);

	if (contient_caisse(niveau, case_suivante_joueur)) // veut pousser une caisse
	{
		point_t* case_suivante_caisse = init_point_par(case_suivante_joueur);
		position_ap_deplacement(case_suivante_caisse, direction);

		if (deplacement_possible(niveau, case_suivante_caisse))
		{
			sauvegarde_un_coup(hist, niveau);
			move(niveau, case_suivante_joueur, case_suivante_caisse); // déplacement de la caisse
			move(niveau, niveau->perso, case_suivante_joueur);        // déplacement du joueur
		}
	}
	else if (deplacement_possible(niveau, case_suivante_joueur))
	{
		sauvegarde_un_coup(hist, niveau);
		move(niveau, niveau->perso, case_suivante_joueur);
	}
}