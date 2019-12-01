/**
 * \file io_cairo.h
 * \brief Header des fonctions io du mode graphique.
 */


#ifndef __IO_CAIRO_H
#define __IO_CAIRO_H

#include "grille.h"

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <unistd.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "grille.h"
#include "jeu.h"
#define SIZEX 400
#define SIZEY 400
#define SIZECELL 21
#define BLACK 0.22, 0.22, 0.22
#define GREY 0.88, 0.88, 0.88
#define BROWN 0.51, 0.41, 0.32
#define SIZERECT 13
#define MAXSTRINGLENGTH 50

/**
 * \brief Débute le jeu de la vie.
 * \param *g Pointeur sur la grille initiale.
 * \param *gc Pointeur sur une copie de la grille initiale.
 * \param *ga Pointeur sur la grille des ages.
 * \return Reste de la disvion.
 */
void debut_jeu_cairo (grille *g, grille *gc, grille *ga);

/**
 * \brief Affiche la grille et les informations liées à la grille sur la
 * fenêtre.
 * \param *g Pointeur sur la grille initiale.
 * \param *gc Pointeur sur une copie de la grille initiale.
 * \param *ga Pointeur sur la grille des ages.
 * \return Affichage dans la fenêtre. (pas de valeur)
 */
void affiche_grille_cairo(grille g, grille ga, cairo_surface_t *surface, int cyclique, int vieillissement, int p);

/**
 * \brief Affichage d'une cellule dans la grille.
 * \param g Grille à afficher.
 * \param ga Grille contenant l'âge des cellules à afficher.
 * \param i Coordonée sur l'axe des ordonnées de la cellule à afficher.
 * \param j Coordonée sur l'axe des abscisses de la cellule à afficher.
 * \param *surface Surface cairo sur laquelle afficher la cellule.
 * \param vieillissement Indique si le vieillissement est activé ou pas.
 * \return Affichage dans la fenêtre. (pas de valeur)
 */
void draw_cell_cairo(grille g, grille ga, int i, int j, cairo_surface_t *surface, int vieillissement);

/**
 * \brief Lis une nouvelle grille au clavier à travers la fenêtre, sans
 * passer par le terminal.
 * \param t Chaine de caractères contenant le chemin vers la grille.
 * \param *dpy Pointeur sur un "Display" utilisé pour les évenements.
 * \param e Evenelment X11.
 * \param *surface Surface cairo sur laquelle afficher du texte.
 * \return Chaine de caractères contenant le chemin vers la grille dans t.
 */
void read_string_cairo(char t[], Display* dpy, XEvent e, cairo_surface_t *surface);


/**
 * \brief Affiche des informations sur la grille en cours d'évolution sur la fenêtre.
 * \param *cr Pointeur sur la surface cairo sur laquelle les informations seront affichées.
 * \param vieillissement Indique si le vieillissement est activié ou pas.
 * \param cyclique Indique si le mode cyclique est activé ou pas.
 * \param p Information sur la periodicité de la grille.
 * \param per Chaine de caractères contenant la periode pour l'affichage.
 * \param age Chaine de caractères contenant l'âge de la grille pour l'affichage.
 * \param e Evenelment X11.
 * \param *surface Surface cairo sur laquelle afficher du texte.
 * \return Chaine de caractères contenant le chemin vers la grille dans t.
 */
void affiche_infos_cairo(cairo_t *cr, int vieillissement, int cyclique, 
  int p,char *per, char* age);
#endif
