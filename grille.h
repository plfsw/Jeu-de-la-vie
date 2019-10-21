/**
 * \file grille.h
 * \brief Header contenant les fonctions liées aux grills.
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \brief Structure des grilles.
 */
typedef struct {
    int nbl; //!< Nombre de lignes de la structure.
    int nbc; //!< Nombre de colonnes de la strucutre.
    int **cellules; //!< Tableau à deux dimensions contenant les cellules de la grille.
    int age; //!< Age de la grille.
    } grille;

/**
 * \brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes.
 * \param l Nombre de lignes de la grille.
 * \param c Nombre de colonnes de la grille.
 * \param g Grille a allouer.
 */
void alloue_grille (int l, int c, grille* g);

/**
 * \brief Libère une grille.
 * \param g Grille à libérer.
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/**
 * \brief Alloue et initialise la grille g à partir d'un fichier.
 * \param filename Nom du fichier source contenant la grille.
 * \param g Grille à initialiser.
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
 * \brief Rend vivante la cellule (i,j) de la grille g.
 * \param i Ligne de la cellule à rendre vivante.
 * \param j Colonne de la cellule à rendre vivante.
 * \param g Grille dans laquelle rendre une cellule vivante.
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

// rend morte la cellule (i,j) de la grille g
/**
 * \brief Rend morete la cellule (i,j) de la grille g.
 * \param i Ligne de la cellule à rendre vivante.
 * \param j Colonne de la cellule à rendre vivante.
 * \param g Grille dans laquelle rendre une cellule vivante.
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
/**
 * \brief Teste si la cellule (i, j) de la grille g est vivante.
 * \param i Ligne de la cellule à rendre vivante.
 * \param j Colonne de la cellule à rendre vivante.
 * \param g Grille dans laquelle rendre une cellule vivante.
 * \return 1 si la cellule est vivante, 0 sinon.
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

/**
 * \brief Augmente l'age de la cellule (i,j) de 1.
 * \param i Ligne de la cellule à rendre plus vielle.
 * \param j Colonne de la cellule à rendre plus vielle.
 * \param g Grille dans laquelle se trouve la cellule.
 */
static inline void rend_plus_vielle(int i, int j, grille g){g.cellules[i][j]++;};

/**
 * \brief Renvoie l'age de la cellule (i,j).
 * \param i Ligne de la cellule dont on veut avoir l'âge.
 * \param j Colonne de la cellule dont on veut avoir l'âge.
 * \param g Grille dans laquelle se trouve la cellule.
 * \return Renvoie l'age de la cellule (i,j).
 */
static inline int get_age(int i, int j, grille g){return g.cellules[i][j];}

// recopie gs dans gd (sans allocation)
/**
 * \brief Recopie la grille gs dans la grille gd (sans faire d'allocation).
 * \param gs Grille à copier.
 * \param gd Grille copiée.
 */
void copie_grille (grille gs, grille gd);


#endif
