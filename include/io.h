/**
 * \file io.h
 * \brief Header contenant les fonctions pour liées à l'affichage et aux entrées.
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
/**
 * \brief Affichage d'un trait horizontal pour la grille.
 * \param c Nombre de colonnes.
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
 * \brief Affichage d'une ligne verticale pour la grille.
 * \param c Nombre de colonnes.
 * \param ligne Pointeur vers le nombre de lignes.
 */
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
/**
 * \brief Affichage d'une grille.
 * \param g Grille à afficher.
 * \param mode Mode cyclique ou non cyclique.
 * \param v Avec vieillissement ou non.
 */
void affiche_grille (grille g, int mode, int v);

// effacement d'une grille
/**
 * \brief Effacement de l'affichage d'une grille.
 * \param g Grille à effacer.
 */
void efface_grille (grille g);

// debute le jeu
/**
 * \brief Debute le jeu de la vie.
 * \param g Pointeur vers la grille initiale.
 * \param gc Copie de g.
 * \param ga Grille contenant l'age des cellules.
 */
void debut_jeu(grille *g, grille *gc, grille *ga);

#endif
