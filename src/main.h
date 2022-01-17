/* Ajout des librairies standards */
#include <stdio.h>
#include <stdlib.h>



/* Ajout des structures */
typedef struct {
	int ligne;
	int colonne;
} point_t;

typedef struct {
  	int nb_lignes;
 	int nb_colonnes;
 	char* terrain;
 	int nb_pas;
 	point_t* perso;
} niveau_t;

typedef struct {
	int nb_elements;
	int head;
	niveau_t** pile_elements;
} historique_t;



/* Ajout des entêtes personnelles */
#include "terrain.h"
#include "perso.h"
#include "input.h"
#include "score.h"
#include "historique.h"
#include "commande.h"
#include "utilitaire.h"