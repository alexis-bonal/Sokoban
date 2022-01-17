#include "main.h"

extern char entree[20];

// valide une instruction
int instruction_valide(char instruction)
{
	return instruction == 'z' 
		|| instruction == 'q'
		|| instruction == 's'
		|| instruction == 'd';
}

// Saisie d'un caractère de l'utilisateur
char* entree_du_joueur(void)
{
	scanf("%s", entree);
	return entree;
}

char saisie_car(void)
{
	char saisie;
	scanf("%c", &saisie);
	return saisie;
}