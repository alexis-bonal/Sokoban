#include "main.h"

// Création des variables externes
char entree[20];

int main(int argc, char *argv[])
{
	// création du pseudo en fonction du premier argument passé
	char* pseudo = malloc(sizeof(char) * 30);
	if (argc > 1)
		sprintf(pseudo, argv[1]);
	else
		sprintf(pseudo, "hiroyuki");

	int exit = 0;

	do
	{
		entree[0] = ' '; // évite de tourner en boucle sur la même commande
		printf("\n"); // évite un bug d'affichage lorsque l'on donne un paramètre après une commande

		// Écran titre
		system("clear && cat ./msg/hello.txt");

		// Affichage de l'aide
		printf("\t%sA I D E%s :\n", color("blue"), color(""));
		printf("\t  - Pour changer de pseudo : %srename %s[name]%s\n" , color("green"), color("blue"), color(""));
		printf("\t  - Lancer un niveau       : %slvl %s[num]%s\n"     , color("green"), color("blue"), color(""));
		printf("\t  - Voir les scores        : %sscore %s[num]%s\n"   , color("green"), color("blue"), color(""));
		printf("\t  - Quitter                : %sexit%s\n\n"          , color("green"), color(""));

		// Saisie de la commande à l'utilisateur
		while(!est_commande())
		{
			afficher_prompt(pseudo);
			entree_du_joueur();
			if (!est_commande())
				printf("\n%sERREUR%s : %s%s%s : Commande introuvable...\n\n\a", color("red"), color(""), bg_color("red"), entree, color(""));
		}

		// Alternatives selon la commande
		if (equals(entree, "exit")) // interruption du programme
			exit = 1;
		else if (est_rename()) // renommage du joueur
		{
			printf("\nQuel est ton pseudo ?\n> ");
			scanf("%s", pseudo);
			printf("\nPseudo correctement modifié !\n> ");
		}
		else if(est_score()) // affichage des scores d'un niveau
		{
            printf("\nVoir les scores de quel niveau ?\n> ");
            char* cmd = entree_du_joueur();
            system("clear");
            printf("Meilleurs scores du niveau %s:\n\n", cmd);
            afficher_meilleur_score(cmd);
        }
		else if (est_lvl()) // lancement d'un niveau
		{
			printf("\nÀ quel niveau jouer ?\n\n");

			// proposer choix niveau
			system("ls niveaux | tr _n \\ N");

			// Vérification de la saisie de l'utilisateur
			// int nb_lvl = system("exit $(ls niveaux/|wc -l)");
			char* cmd;
			// while (cmd[0] > nb_lvl + '0' && cmd[0] < '0')
			// {
				printf("\n> ");
				cmd = entree_du_joueur();
			// }


			//rajouter vérification niveau séléctionner

			// importation du niveau à partir de son fichier
			char* chemin_fichier = malloc(sizeof(char)*40);
			sprintf(chemin_fichier, "./niveaux/niveau_%s", cmd);
			niveau_t* niveau = generer_niveau(chemin_fichier);
			free(chemin_fichier);

			// création de l'historique
			historique_t* hist = generer_historique(nouvel_historique(), 50);

			// boucle principale de la partie
			char instruction;
			do
			{
				// affichage du jeu
				system("clear");
				printf("Nombre de pas :%s %d%s\n\n", color("green"), niveau->nb_pas, color(""));
				affichage_niveau(niveau);

				// Demande à l'utilisateur ses instructions
				printf("\n\nDéplacements (z, q, s, d) ou retour en arrière (a).\n> ");
				instruction = to_lower(saisie_car());

				printf("\n"); // évite un bug d'affichage

				// éxecution des instructions si elles sont valides
				if (instruction_valide(instruction))
					deplacement(hist, niveau, instruction);
				else if (instruction == 'a' && coup_precedent_possible(hist)) // retour en arrière
					niveau = coup_precedent(hist);
			} while(!niveau_termine(niveau));

			// affichage du niveau terminé
			system("clear");
			printf("\n\t%sB R A V O !   V O U S   A V E Z   R É U S S I !%s\n\n", color("yellow"), color(""));
			printf("\nNombre de pas :%s %d%s\n\n", color("green"), niveau->nb_pas, color(""));
			affichage_niveau(niveau);

			ecriture_du_score(stringToInt(cmd,1), niveau->nb_pas, pseudo);
			afficher_meilleur_score(cmd);

			liberation_du_niveau(niveau);
			liberer_historique(hist);
		}
	} while(!exit);

	system("clear && cat ./msg/bye.txt");

	free(pseudo);

	return 0;
}