/**
 * \file io.c
 * \brief Gestion de l'affichage.
 */

#include "io.h"
#include "grille.h"


//fonction utilisée pour l'affichage de la grille, affiche un trait
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

//fonction utilisée pour l'affichage de la grille, affiche une ligne
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   ");
		else {
            if(ligne[i] == -1) printf ("| X ");
            else printf ("| %d ", ligne[i]);
		}
	printf("|\n");
	return;
}

/* fonction qui affiche la grille ainsi que le emps d'évolution, le mode de
de comptage des voisins et lde monde de vieillissement
*/
void affiche_grille (grille g, int mode, int v){
	int i, l=g.nbl, c=g.nbc;
	efface_ecran();
	if(mode) printf("Mode cyclique");
	else printf("Mode non cyclique");
    if(v) {
        printf(", vieillissement activé\n");
    }
    else printf(", vieillissement desactivé\n");
	printf("Temps d'évolution: %d\n", g.age);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

/* fonction qui efface l'écran, rempli le même rôle qu'efface_grille mais fourni
un résultat plus "propre".
*/
void efface_ecran(){
	printf("\e[1;1H\e[2J");
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 7);
}

void debut_jeu(grille *g, grille *gc, grille *ga){
	char str[40];
	char c = getchar();
	int cyclique = 1, vieillissement = 1;
    void (*pt_evolue)(grille*, grille*, grille*, int (*)(int, int, grille)) = evolue_vi;
    int (*pt_voisins)(int, int, grille) = compte_voisins_vivants_cyclique;
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
            case '\n' :
            { // touche "entree" pour évoluer
                pt_evolue(g, gc, ga, pt_voisins);
                break;
            }
            case 'n' :
            { // touche "n" pour charger une nouvelle grille


                printf("Entrez le nouveau fichier: ");
                scanf(" %s", str);
                getchar();

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
                { // touche "c" pour basculer d'un mode de comptage à l'autre
                cyclique = !cyclique;
                if(cyclique) pt_voisins = &compte_voisins_vivants_cyclique;
                else pt_voisins = &compte_voisins_vivants_non_cyclique;
                getchar ();
                break;
                }

            case 'v':
            { // touche "v" pour activer/désactiver le vieillissement
                vieillissement = !vieillissement;
                if(vieillissement) {
                    pt_evolue = evolue_vi;
                    copie_grille(*g, *ga);
                    ga->age = g->age;
                }
                else {
                    pt_evolue = evolue;
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
				// appel différent de affiche_grille en fonction de vieillissement
        if(vieillissement) affiche_grille(*ga, cyclique, vieillissement);
        else affiche_grille (*g, cyclique, vieillissement);
        c = getchar();
	}
	return;
}
