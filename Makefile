all:
	# Positionnement dans le dossier contenant les sources.
	# Compilation des fichiers dans un executable placé dans le répertoire principal.
	# Confirmation de la réussite par un message et une alerte sonore
	cd src && \
	gcc -Wall -o ../sokoban main.c terrain.c perso.c input.c score.c historique.c commande.c utilitaire.c && \
	echo "\n\tCompilation réussie !\n\n\tPour lancer le programme, tapez ./sokoban [nom du joueur]\n\a"
	