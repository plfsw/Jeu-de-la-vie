/**
 * \file jeu.c
 * \brief Fichier jeu.c
 */

#include "jeu.h"

int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_non_cyclique(int i, int j, grille g){
	int v = 0, l = g.nbl, c = g.nbc;
	v += i > 0 && j > 0 && est_vivante(i-1, j-1, g);
	v += i > 0 && est_vivante(i-1, j, g);
	v += i > 0 && j < c && est_vivante(i-1, j+1, g);
	v += j > 0 && est_vivante(i, j-1, g);
	v += j < c && est_vivante(i, j+1, g);
	v += i < l -1 && j > 0 && est_vivante(i+1, j-1, g);
	v += i < l -1 && est_vivante(i+1, j, g);
	v += i < l -1 && j < c && est_vivante(i+1, j+1, g);
	return v;
}

void vieillir(grille *g, grille *ga, int v){
  if(v){
  ga->age++;
  printf("%d ",g->age);
  for(int i = 0; i < g->nbl; i++){
    for(int j = 0; j < g->nbc; j++){
      if(est_vivante (i, j, *g)) rend_plus_vielle (i, j, *ga);
      if(!est_vivante (i, j, *g)) set_morte (i, j, *ga);
      if(get_age (i, j, *ga) > 8)
        {
        set_morte (i, j, *ga);
        set_morte (i, j, *g);
      }
    }
  }
  }
}

void evolue (grille *g, grille *gc, grille *ga, int (*compte_voisins_vivants)(int, int, grille), int vi){
  copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc, v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants(i, j, *gc);
			if (est_vivante(i,j,*g))
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
        /*else {
          rend_plus_vielle (i, j, *ga);
          if (get_age (i, j, *ga) > 8) set_morte (i, j, *g);
        }*/
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) {
        set_vivante(i,j,*g);
        }
      }
	  }
  }
  vieillir (g, ga, vi);
	g->age++;
	return;
}
