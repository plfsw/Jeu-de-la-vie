/**
 * \file jeu.h
 * \brief Header contenant les fonctions pour le fichier jeu.c
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#include "io_cairo.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
 * \brief Modulo modifié pour traiter correctement les bords i=0 j=0\
 * dans le calcul des voisins des bords cycliques.
 * \param i Dividende
 * \param m Diviseur
 * \return Reste de la disvion.
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
 * \brief Compte le nombre de voisins d'une cellule en mode cyclique.
 * \param i Ligne de la cellule dont un cherche les voisins.
 * \param j Colonne de la ligne dont on cherche les voisins.
 * \param g Grille dans laquelle la cellule se trouve.
 * \return Nombre de voisins de (i,j).
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);


/**
 * \brief Compte le nombre de vosisins d'une cellule en mode non-cyclique.
 * \param i Ligne de la cellule dont un cherche les voisins.
 * \param j Colonne de la ligne dont on cherche les voisins.
 * \param g Grille dans laquelle la cellule se trouve.
 * \return Nombre de voisins de (i,j).
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);


// fait évoluer la grille g d'un pas de temps
/** \brief Fait évoluer la grille g d'un pas dans le temps sans vieillissement.
 * \param *g Grille à faire évoluer.
 * \param *gc Copie de *g.
 * \param *ga Grille contenant l'age des cellules.
 * \param int (*pf)(int, int, grille) Fonction de comptage des voisins.
 */
void evolue (grille *g, grille *gc, grille *ga, int (*pf)(int, int, grille));

/** \brief Fait évoluer la grille g d'un pas dans le temps avec vieillissement.
 * \param *g Grille à faire évoluer.
 * \param *gc Copie de *g.
 * \param *ga Grille contenant l'age des cellules.
 * \param int (*pf)(int, int, grille) Fonction de comptage des voisins.
 */
void evolue_vi (grille *g, grille *gc, grille *ga, int (*pf)(int, int, grille));

/** \brief Fait vieillir les cellules de la grille ga.
 * \param g Grille contenant les cellules
 * \param ga Grille contenant l'age des cellules de g
 */
void vieillir(grille *g, grille *ga);
#endif
