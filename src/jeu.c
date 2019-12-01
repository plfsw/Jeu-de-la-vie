/**
 * \file jeu.c
 * \brief Fichier jeu.c
 */

#include "jeu.h"

//détermine la période d'une grille. 
//Si aucune période n'est trouvée, on cherche si la période commence plus tard dans l'évolution de la grille.
int periode(grille g, int (*compte_voisins_vivants)(int, int, grille)){
  int p = 1;
  grille gs, gs2;
  alloue_grille(g.nbl, g.nbc, &gs);
  copie_grille(g, gs);
  alloue_grille(g.nbl, g.nbc, &gs2);
  copie_grille(g, gs2);
  evolue(&gs, &gs2, &gs2, compte_voisins_vivants);
  
  grille tab[PMAX];
  int ftab = 0;
  
  //Recherche de la periode à partir de la position actuelle des cellules
  while(p < PMAX && !(sont_identiques(g, gs))) {
    if(toutes_mortes(gs)) return -1;
    evolue(&gs, &gs2, &gs2, compte_voisins_vivants);
    p++;
    tab[ftab] = gs;
    ftab++;
  }
  
  //Si la perioe n'a pas été trouvée, recherche à partir des positions suivantes
  for(int i = 0; i < PMAX && p == PMAX; i++)
    p = periode(tab[i], compte_voisins_vivants);
  
  if(p == PMAX) return -1;
  
  else return p;
 }


//fonction de comptage en mode cyclique
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

//fonction de comptage en mode non-cyclique
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

//fait vieillir une cellule, utilisée pour le vieillissement
void vieillir(grille *g, grille *ga){
  ga->age = g->age;
  for(int i = 0; i < g->nbl; i++){
    for(int j = 0; j < g->nbc; j++){
      if(!est_non_viable(i, j, *g)){
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

//fonction calculant l'évolution quand le vieillissement est activé
void evolue_vi (grille *g, grille *gc, grille *ga, int (*compte_voisins_vivants)(int, int, grille)){
    evolue(g, gc, ga, compte_voisins_vivants);
    vieillir (g, ga);
}

//fonction calculant l'évolution quand le vieillissement n'est pas activé
void evolue (grille *g, grille *gc, grille *ga, int (*compte_voisins_vivants)(int, int, grille)){
    copie_grille (*g,*gc); // copie temporaire de la grille
    int i,j,l=g->nbl, c = g->nbc, v;
    for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
		    if(!est_non_viable(i, j, *g)){
                v = compte_voisins_vivants(i, j, *gc);
                if (est_vivante(i,j,*g))
                { // evolution d'une cellule vivante
                    if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
                }
                else
                { // evolution d'une cellule morte
                    if ( v==3 ) {
                        set_vivante(i,j,*g);
                    }
                }
            }
	  }
  }
  g->age++;
  return;
}
