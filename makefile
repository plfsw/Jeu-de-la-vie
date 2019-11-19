0CC = gcc
OBJ = main.o grille.o io.o jeu.o io_cairo.o
DEP = grille.h io.h jeu.h
CFLAGS = -Wall -I include -g -lcairo -lm -lX11 -Iinclude -I/usr/include/cairo


vpath %.c src/
vpath %.h include/
vpath %.o obj/

%.o: %.c $(DEP)
	@$(CC) -c -o $@ $< $(CFLAGS)
	@mkdir -p bin

main: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@mkdir -p obj
	@mv *.o obj/
	@mkdir -p bin
	@mv main bin/

clean:
	@rm bin/main
	@rm obj/*

doc:
	@doxygen

dist:
	@tar -Jcvf LafossePierre-GoL-v0.1.tar.xz makefile Doxyfile src/ include/

distclean:
	@rm -r doc
	@rm -r *.tar.xz
