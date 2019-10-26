/**
 * \file grille.c
 * \brief Gestion des grilles.
 */

#include "grille.h"

//fonction qui initie une grille à partir d'un fichier
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);

	int i,j,n,l,c,vivantes=0;

	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);

	alloue_grille(l,c,g);

	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fclose (pfile);

	g->age = 0;
	return;
}

//fonction qui copie la grille gd vers la grille gs
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) {gd.cellules[i][j] = gs.cellules[i][j]; //printf("%d %d\n", i, j);}
	}
	return;
}

//fonction qui aloue une grille dans le tas
void alloue_grille(int l, int c, grille*  g){
	g -> nbl = l;
	g -> nbc = c;
    g->age = 0;
	g -> cellules = calloc(g-> nbl, sizeof(int*));
	for(int i = 0; i < g -> nbl; ++i) {
		g-> cellules[i] = calloc(g-> nbc, sizeof(int));
	}
}

//fonction qui libere l'emplacement mémoire utilisé par une grille
void libere_grille(grille* g){
	for(int i = 0; i < g -> nbl; ++i){
		free(g->cellules[i]);
	}
	free(g->cellules);
}
