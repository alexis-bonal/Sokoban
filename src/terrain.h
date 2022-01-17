niveau_t* nouveau_niveau(int nb_colonnes, int nb_lignes);
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);
void initialise_le_terrain(niveau_t* niveau);
void affichage_niveau(niveau_t* niveau);
niveau_t* generer_niveau(char nom_fichier[]);
void liberation_du_niveau(niveau_t* niveau);
int niveau_termine(niveau_t* niveau);