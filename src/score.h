int lecture_du_score (int quel_niveau);
void ecriture_du_score(int quel_niveau, int quel_score, char* nom_du_joueur);
void afficher_meilleur_score(char* commande);
char* nom_du_joueur(void);
char* score_trie(FILE* file, int score, char* nom_joueur);
void tab_score_et_nom(FILE* file, int* tab_score, char** tab_nom);
void supprimer_les_doublons(int* tab_score, char** tab_nom);