#include "main.h"

// permet de faire une copie d'un niveau donné en paramètres
niveau_t* copie_du_niveau (niveau_t* niveau)
{
	int   nb_lignes = niveau->nb_lignes;
	int nb_colonnes = niveau->nb_colonnes;
	niveau_t* copie = nouveau_niveau(nb_colonnes, nb_lignes);

	// copie terrain
	for (int i = 0; i < niveau->nb_lignes * niveau->nb_colonnes; ++i)
		copie->terrain[i] = niveau->terrain[i];

	// copie nombre de pas
	copie->nb_pas = niveau->nb_pas;

	// copie perso
	copie->perso->ligne = niveau->perso->ligne;
	copie->perso->colonne = niveau->perso->colonne;

	return copie;
}



// Génère un historique vide
historique_t* nouvel_historique(void)
{
	historique_t* historique = malloc(sizeof(historique_t));

	historique->nb_elements = 0;
	historique->head = 0;

	return historique;
}



// Génère un historique vide
historique_t* generer_historique(historique_t* hist, int nb_elements)
{
	hist->nb_elements = nb_elements;
	hist->pile_elements = malloc(sizeof(niveau_t*) * nb_elements);

	return hist;
}



// Génère un historique vide
void liberer_historique(historique_t* hist)
{
	free(hist->pile_elements);
	free(hist);
}



// Ajoute de la place au tableau
void ajouter_espace(historique_t* hist, int nb_supplementaire)
{
	niveau_t** save = malloc(sizeof(niveau_t*) * (hist->nb_elements + nb_supplementaire));

	// création d'une copie du tableau d'historique
	for (int i = 0; i < hist->nb_elements; ++i)
		save[i] = copie_du_niveau(hist->pile_elements[i]);

	hist->nb_elements += nb_supplementaire;

	free(hist->pile_elements);
	hist->pile_elements = save;
}



// Permet d'ajouter le coup à sauvegarder dans notre historique
void sauvegarde_un_coup(historique_t* hist, niveau_t* niveau)
{
	if (hist->head == hist->nb_elements) // s'il n'y a plus de la place
		ajouter_espace(hist, 25);

	hist->pile_elements[hist->head] = copie_du_niveau(niveau);
	++hist->head;
}



// vérifie s'il est possible de faire un retour en arrière
int coup_precedent_possible(historique_t* hist)
{
	return hist->head > 0;
}



// permet de charger le dernier coup joué
niveau_t* coup_precedent(historique_t* hist)
{
	--hist->head;
	return hist->pile_elements[hist->head];
}