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

	int i,j,n,l,c,vivantes,non_viables=0;

	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);

	alloue_grille(l,c,g);

	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile, "%d", & non_viables);
	for (n=0; n < non_viables; ++n){
        fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
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
	if(g->cellules != NULL){
        for(int i = 0; i < g -> nbl; ++i) {
            g-> cellules[i] = calloc(g-> nbc, sizeof(int));
            if (g->cellules[i] == NULL) {
              printf("Impossible d'allouer de la mémoire.\n");
              exit(0);
            }
        }
	}
	else{
        printf("Impossible d'allouer de la mémoire.\n");
        exit(0);
	}
}

//fonction qui libere l'emplacement mémoire utilisé par une grille
void libere_grille(grille* g){
	for(int i = 0; i < g -> nbl; ++i){
		free(g->cellules[i]);
	}
	free(g->cellules);
}

//verifie si toutes les cellules sont mortes
int toutes_mortes(grille g){
  for(int i = 0; i < g.nbl; i++){
    for(int j = 0; j < g.nbc; j++){
      if(est_vivante(i, j, g)) return 0;
    }
  }
  return 1;
}

//verifie si deux grilles sont identiques, si toutes les cellules vivantes
//de la premiere grilles sont aussi vivantes dans le seconde.
int sont_identiques(grille g, grille g2){
  for(int i = 0; i < g.nbl; i++){
    for(int j = 0; j < g.nbc; j++){
      if(est_vivante(i, j, g) != est_vivante(i, j, g2)) return 0;
    }
  }
  return 1;
}
