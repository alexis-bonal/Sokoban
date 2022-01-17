#include "main.h"

extern char entree[20];

// gestion des commandes de l'utilisateur
void afficher_prompt(char* pseudo)
{
	char prompt[100];
	sprintf(prompt, "%s%s%s@%ssokoban%s:~#%s ", color("yellow"), pseudo, color("cyan"), color("yellow"), color("cyan"), color(""));
	printf("%s", prompt);
}



// vérifie si la commande saisie existe
int est_commande()
{
	return equals(entree, "exit") || est_rename() || est_lvl() || est_score();
}



// vérifie si la commande est rename
int est_rename(void)
{
	int valide = 1;
	char name[6] = "rename";

	int cpt = 0;
	while ((valide && cpt < 6) || entree[cpt] != '\0') 
	{
		if (name[cpt] != entree[cpt])
			valide = 0;
		++cpt;
	}

	return valide;
}



// vérifie si la commande est lvl
int est_lvl(void)
{
	int valide = 1;
	char name[3] = "lvl";

	int cpt = 0;
	while ((valide && cpt < 3) || entree[cpt] != '\0') 
	{
		if (name[cpt] != entree[cpt])
			valide = 0;
		++cpt;
	}

	return valide;
}



// vérifie si la commande est score
int est_score(void)
{
    int valide = 1;
    char name[5] = "score";

    int cpt = 0;
    while ((valide && cpt < 5) || entree[cpt] != '\0') 
    {
        if (name[cpt] != entree[cpt])
            valide = 0;
        ++cpt;
    }

    return valide;
}