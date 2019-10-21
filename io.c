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
	if(mode) printf("Mode cyclique");
	else printf("Mode non cyclique");
    if(v) {
        printf(", viellisement activé\n");
    }
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
    void (*pt_evolue)(grille*, grille*, grille*, int (*)(int, int, grille)) = &evolue_vi;
    int (*pt_voisins)(int, int, grille) = &compte_voisins_vivants_cyclique;
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
            case '\n' :
            { // touche "entree" pour évoluer
                pt_evolue(g,gc, ga, pt_voisins);
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
                copie_grille(*g, *ga);
                break;
            }
            case 'c':
                {
                cyclique = (cyclique+1)%2;
                if(cyclique) pt_voisins = &compte_voisins_vivants_cyclique;
                else pt_voisins = &compte_voisins_vivants_non_cyclique;
                getchar ();
                break;
                }

            case 'v':
            {
            viellissement = (viellissement+1)%2;
            if(viellissement) {
                    pt_evolue = &evolue_vi;
                    alloue_grille(g->nbl, g->nbc, ga);
                    copie_grille(*g, *ga);
                    ga->age = g->age;
            }
            else {
                    pt_evolue = &evolue;
                    libere_grille(ga);
            }
            getchar ();
            break;

        }
            default :
            {
                printf("\n\e[1A");
                break;
            }
    }
        printf("\e[1;1H\e[2J");
        if(viellissement) affiche_grille(*ga, cyclique, viellissement);
        else affiche_grille (*g, cyclique, viellissement);
        c = getchar();
	}
	return;
}
