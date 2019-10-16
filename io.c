/**
 * \file io.c
 * \brief Gestion de l'affichage.
 */

#include "io.h"
#include "grille.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5);
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ // touche "n" pour charger une nouvelle grille
				char str[15];
				printf("Entrez le nouveau fichier: ");
				scanf(" %s", str);
				printf("%s\n", str);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(str, g);
				alloue_grille(g->nbl , g->nbc, gc);
				printf("\e[1;1H\e[2J");
				affiche_grille(*g);
				break;
			}

			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	libere_grille(g);
	libere_grille(gc);
	return;
}
