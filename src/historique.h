niveau_t* copie_du_niveau (niveau_t* niveau);
historique_t* nouvel_historique(void);
historique_t* generer_historique(historique_t* hist, int nb_elements);
void liberer_historique(historique_t* hist);
void ajouter_espace(historique_t* hist, int nb_supplementaire);
void sauvegarde_un_coup(historique_t* hist, niveau_t* niveau);
int coup_precedent_possible(historique_t* hist);
niveau_t* coup_precedent(historique_t* hist);