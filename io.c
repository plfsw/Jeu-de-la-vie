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

void affiche_grille (grille g, int mode){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	void afficher_age(int age);
	if(mode) printf("Mode cyclique\n");
	else printf("Mode non cyclique\n");
	printf("Temps d'évolution: %d\n", g.age);	
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 7);
	printf("\e[1;1H\e[2J");
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int cyclique = 1;
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				if(cyclique) evolue(g,gc, &compte_voisins_vivants_cyclique);
				else evolue(g, gc, &compte_voisins_vivants_non_cyclique); 	
				efface_grille(*g);
				affiche_grille(*g, cyclique);
				break;
			}
			case 'n' :
			{ // touche "n" pour charger une nouvelle grille
				char str[15];
				printf("Entrez le nouveau fichier: ");
				scanf(" %s", str);
				getchar();
				printf("%s\n", str);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(str, g);
				alloue_grille(g->nbl , g->nbc, gc);
				printf("\e[1;1H\e[2J");
				affiche_grille(*g, cyclique);
				break;
			}

			case 'c':
			{
				cyclique = (cyclique+1)%2;
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
