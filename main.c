/** \file main.c
 * \brief Fichier main.
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	grille g, gc, ga;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
  alloue_grille (g.nbl, g.nbc, &ga);
	affiche_grille(g, 1, 1);
	
	debut_jeu(&g, &gc, &ga);

	libere_grille(&g);
	libere_grille(&gc);
  libere_grille (&ga);
	return 0;
}
