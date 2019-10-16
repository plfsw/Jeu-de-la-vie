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
 * \fn void affiche_trait(int c)
 * \brief Affichage d'un trait horizontal pour la grille.
 * \param c Nombre de colonnes.
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
 * \fn void affiche_ligne(int c, int* ligne)
 * \brief Affichage d'une ligne verticale pour la grille.
 * \param c Nombre de colonnes.
 * \param l Pointeur vers le nombre de lignes.
 */
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
/**
 * \fn void affiche_grille(grille g)
 * \brief Affichage d'une grille.
 * \param g Grille à afficher.
 */
void affiche_grille (grille g);

// effacement d'une grille
/**
 * \fn void efface_grille(grille g)
 * \brief Effacement de l'affichage d'une grille.
 * \param g Grille à effacer.
 */
void efface_grille (grille g);

// debute le jeu
/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \brief Debute le jeu de la vie.
 * \param g Pointeur vers la grille initiale.
 * \param gc Copie de g.
 */
void debut_jeu(grille *g, grille *gc);

#endif
