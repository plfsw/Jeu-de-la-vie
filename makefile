0CC = gcc
OBJ = main.o grille.o io.o jeu.o
DEP = grille.h io.h jeu.h
CFLAGS = -Wall -I. -g

%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o main

doc:
	doxygen

dist:
	tar Jcvf $(shell basename $(shell pwd)).tar.xz --transform="s, ^, $(Name)/," *.c *.h

distclean:
	rm -r doc
	rm -r *.tar.xz


