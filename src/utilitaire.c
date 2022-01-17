#include "main.h"

//Transforme une chaine de caractère de taille donné en entier
int stringToInt(char* string, int taille)
{
	int resultat = 0;
	int chiffre;

	// pour chaque lettre du mot, on compose un entier
	for(int i = 0; i < taille; i++){
		chiffre  = (int) (*(string + i) - '0');
		resultat = resultat * 10 + chiffre;
	}

	return resultat;
}



// convertit un caractère Majuscule en minuscule
char to_lower(char car)
{
	if (car >= 'A' && car <= 'Z')
		return car + 'a' - 'A';
	else
		return car;
}



//Lit un fichier jusqu'à un caractère défini et renvoi la sous-chaîne et sa taille
int lire_un_fichier_jusqu_a_un_car(FILE* fichier, char* string, char fin)
{
	char car = getc(fichier);
	int cpt = 0;

	while(car != fin && car != EOF)
	{
		*(string + cpt) = car;
		car = getc(fichier);
		cpt++;
	}

	*(string + cpt) = '\0';

	return cpt;
}



// Vérifie que deux chaînes de caractères se valent auquel cas renvoie 1
int equals(char* string1, char* string2)
{
	int egalite = 1;
	int cpt = 0;

	// tant qu'il n'y a pas de différence et que l'on n'est pas à la fin d'une des chaînes
	while (egalite && (*(string1 + cpt) != '\0' ||  *(string2 + cpt) != '\0'))
		if (*(string1 + cpt) != *(string2 + cpt)) // détection de différence
			egalite = 0;
		else
			cpt++;

	return egalite;
}



// change la couleur du texte
char* color(char* couleur)
{
	/* extrait de 'man terminal-colors.d'
	 0   to restore default color
	 1   for brighter colors
	 4   for underlined text
	 5   for flashing text
	30   for black foreground
	31   for red foreground
	32   for green foreground
	33   for yellow (or brown) foreground
	34   for blue foreground
	35   for purple foreground
	36   for cyan foreground
	37   for white (or gray) foreground
	*/

	char* code_couleur;



	if (equals("black", couleur))
		code_couleur = "\033[30m";

	else if (equals("red", couleur))
		code_couleur = "\033[31m";

	else if (equals("green", couleur))
		code_couleur = "\033[32m";

	else if (equals("yellow", couleur))
		code_couleur = "\033[33m";

	else if (equals("blue", couleur))
		code_couleur = "\033[34m";

	else if (equals("purple", couleur))
		code_couleur = "\033[35m";

	else if (equals("cyan", couleur))
		code_couleur = "\033[36m";

	else if (equals("white", couleur))
		code_couleur = "\033[37m";

	else
		code_couleur = "\033[0m";



	return code_couleur;
}



// change la couleur de fond du texte
char* bg_color(char* couleur)
{
	/* extrait de 'man terminal-colors.d'
	 0   to restore default color
	 1   for brighter colors
	 4   for underlined text
	 5   for flashing text
	40   for black background
	41   for red background
	42   for green background
	43   for yellow (or brown) background
	44   for blue background
	45   for purple background
	46   for cyan background
	47   for white (or gray) background
	*/

	char* code_couleur;



	if (equals("black", couleur))
		code_couleur = "\033[40m";

	else if (equals("red", couleur))
		code_couleur = "\033[41m";

	else if (equals("green", couleur))
		code_couleur = "\033[42m";

	else if (equals("yellow", couleur))
		code_couleur = "\033[43m";

	else if (equals("blue", couleur))
		code_couleur = "\033[44m";

	else if (equals("purple", couleur))
		code_couleur = "\033[45m";

	else if (equals("cyan", couleur))
		code_couleur = "\033[46m";

	else if (equals("white", couleur))
		code_couleur = "\033[47m";

	else
		code_couleur = "\033[0m";



	return code_couleur;
}