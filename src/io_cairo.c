#include "io_cairo.h"
#include "jeu.h"

void draw_cell_cairo(int i, int j, cairo_surface_t *surface){
    int x = 80, y = 80;
    cairo_t *cr;
    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr,x+(i * SIZECELL)+4,y+(j * SIZECELL)+4,13, 13);
    cairo_fill(cr);
    cairo_destroy(cr);
}

void read_string_cairo(char t[], Display* dpy, XEvent e){
    int nbre;
    char chaine[20];
    for(int i = 0; i < 20; i++) {
        chaine[i] = 0;
        t[i] = 0;
    }
    KeySym touche;
    int i = 0;
    while(chaine[0] != 13){
        XNextEvent(dpy, &e);
        if(e.type == KeyPress){
        nbre = XLookupString(&e.xkey, chaine, 20, &touche, 0);
        if(chaine[0] != 0){
            chaine[nbre] = 0;
            printf("%c\n", chaine[0]);
            t[i] = chaine[0];
            //if(chaine[0] == '\n') printf("chaine: %s\nchar: %s\n", t, "bs n");
            //printf("chaine: %s\nchar: %c\n", t, chaine[0]);
            i++;
        }
        }
    }
    t[i-1] = '\0';
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
    void (*pt_evolue)(grille*, grille*, grille*, int (*)(int, int, grille)) = evolue_vi;
    int (*pt_voisins)(int, int, grille) = compte_voisins_vivants_cyclique;
    int nbre;
    char chaine[20];
    KeySym touche;
    int cyclique = 1, vieillissement = 1;
    char t[30];
    
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
    affiche_grille_cairo(*g, 1, 1, cs);
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			affiche_grille_cairo(*g, 1, 1, cs);
		} else if(e.type==ButtonPress){
			if(e.xbutton.button == 1) pt_evolue(g, gc, ga, pt_voisins);
			else break;
		} else if(e.type==KeyPress){
            nbre = XLookupString(&e.xkey, chaine, 20, &touche, 0);
            chaine[nbre] = 0;
            switch(chaine[0]){
                case 'c':
                { // touche "c" pour basculer d'un mode de comptage à l'autre
                    cyclique = !cyclique;
                    if(cyclique) pt_voisins = &compte_voisins_vivants_cyclique;
                    else pt_voisins = &compte_voisins_vivants_non_cyclique;
                    break;
                }
                case 'v':
                { // touche "v" pour activer/désactiver le vieillissement
                    vieillissement = !vieillissement;
                    if(vieillissement) {
                        pt_evolue = evolue_vi;
                        copie_grille(*g, *ga);
                        ga->age = g->age;
                    }
                    else {
                        pt_evolue = evolue;
                    }
                    break;

                }
                case 'n':
                {
                    read_string_cairo(t, dpy, e);
                    printf("%s\n", t);
                    break;
                }
                default :
                {
                    break;
                }
        }
            
        }
		affiche_grille_cairo(*g, 1, 1, cs);
    }

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return ;
}
