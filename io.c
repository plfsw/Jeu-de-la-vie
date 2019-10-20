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
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ", ligne[i]);
	printf("|\n");
	return;
}

void affiche_grille (grille g, int mode, int v){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	void afficher_age(int age);
	if(mode) printf("Mode cyclique ");
	else printf("Mode non cyclique ");
  if(v) printf(", viellisement activé\n");
  else printf(", viellisement desactivé\n");
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

void debut_jeu(grille *g, grille *gc, grille *ga){
	char c = getchar();
	int cyclique = 1;
  int viellissement = 1;
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				if(cyclique) evolue(g,gc, ga, &compte_voisins_vivants_cyclique, viellissement);
				else evolue(g, gc, ga, &compte_voisins_vivants_non_cyclique, viellissement);
				//efface_grille(*g);
				//affiche_grille(*g, cyclique, viellissement);
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
        libere_grille (ga);
				init_grille_from_file(str, g);
				alloue_grille(g->nbl , g->nbc, gc);
        alloue_grille(g->nbl , g->nbc, ga);
				//printf("\e[1;1H\e[2J");
        cyclique = 1;
				//affiche_grille(*g, cyclique, viellissement);
				break;
			}
      case 'c':
			{
				cyclique = (cyclique+1)%2;
        getchar ();
        //printf("\e[1;1H\e[2J");
				//affiche_grille(*g, cyclique, viellissement);
				break;
			}

      case 'v':
      {
        viellissement = (viellissement+1)%2;
        getchar ();
        //printf("\e[1;1H\e[2J");
        break;

      }
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
    printf("\e[1;1H\e[2J");
    //efface_grille(*g);
    if(viellissement)
		  affiche_grille(*ga, cyclique, viellissement);
    else
      affiche_grille (*g, cyclique, viellissement);
		c = getchar();
	}

	//libere_grille(g);
	//libere_grille(gc);
	return;
}
