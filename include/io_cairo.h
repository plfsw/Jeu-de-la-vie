#ifndef __IO_CAIRO_H
#define __IO_CAIRO_H

#include "grille.h"

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "grille.h"
#include "jeu.h"
#include <time.h>
#define SIZEX 400
#define SIZEY 400
#define SIZECELL 21
#define BLACK 0.22, 0.22, 0.22
#define GREY 0.88, 0.88, 0.88
#define BROWN 0.51, 0.41, 0.32



void paint(cairo_surface_t *surface);

void debut_jeu_cairo (grille *g, grille *gc, grille *ga);

void affiche_grille_cairo(grille g, int mode, int v, cairo_surface_t *surface, int cyclique, int vieillissement, grille ga, int p);

void draw_cell_cairo(int i, int j, cairo_surface_t *surface, grille g, grille ga, int vieillissement);

void read_string_cairo(char t[], Display* dpy, XEvent e, cairo_surface_t *surface);
#endif
