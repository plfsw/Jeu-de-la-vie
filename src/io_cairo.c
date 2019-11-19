#include "io_cairo.h"

void draw_cell_cairo(int i, int j, cairo_surface_t *surface){
    int x = 80, y = 80;
    cairo_t *cr;
    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr,x+(i * SIZECELL)+4,y+(j * SIZECELL)+4,13, 13);
    cairo_fill(cr);
    cairo_destroy(cr);
}
void affiche_grille_cairo(grille g, int mode, int v, cairo_surface_t *surface){
    int l=g.nbl, c=g.nbc;
    int x = 80, y = 80;

    cairo_t *cr;
    cr = cairo_create(surface);

    // background
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    for(int i = 0; i <= c; i++){
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x, y+l*SIZECELL);
        cairo_stroke (cr);
        x += SIZECELL;
    }

    x = 80, y = 80;
    for(int i = 0; i <= l; i++){
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x+c*SIZECELL, y);
        cairo_stroke (cr);
        y += SIZECELL;
    }

    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            if(g.cellules[i][j] != 0) draw_cell_cairo(j, i, surface);
        }
    }

    cairo_destroy(cr);

}
void paint(cairo_surface_t *surface)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
	cairo_paint(cr);

	// line
	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	cairo_move_to (cr, 10.0, 50.0);
	cairo_line_to(cr, 100.0,50.0);
	cairo_set_line_width (cr, 1);
	cairo_stroke (cr);

	// filled rectangle
	cairo_rectangle(cr,30,30,50,50);
	cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
	cairo_fill(cr);

	cairo_destroy(cr); // destroy cairo mask
}

void debut_jeu_cairo (grille *g, grille *gc, grille *ga){
// X11 display
Display *dpy;
Window rootwin;
Window win;
XEvent e;
int scr;

// init the display
    if(!(dpy=XOpenDisplay(NULL))){
        fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
    }

    scr = DefaultScreen(dpy);
    rootwin = RootWindow(dpy, scr);

    win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
                              BlackPixel(dpy, scr), BlackPixel(dpy, scr));

    XStoreName(dpy, win, "Free hong kong");
    XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask );
    XMapWindow(dpy, win);

    // Create cairo surface
    cairo_surface_t *cs;
    cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

    // run the even loop
    // run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			affiche_grille_cairo(*g, 1, 1, cs);
		} else if(e.type==ButtonPress) break;
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return ;
}
