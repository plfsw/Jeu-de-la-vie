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
#define SIZEX 600
#define SIZEY 600
#define SIZECELL 21

void paint(cairo_surface_t *surface);

void debut_jeu_cairo (grille *g, grille *gc, grille *ga);

void affiche_grille_cairo(grille g, int mode, int v, cairo_surface_t *surface);

void draw_cell_cairo(int i, int j, cairo_surface_t *surface);
#endif
