0CC = gcc
OBJ = main.o grille.o io.o jeu.o
DEP = grille.h io.h jeu.h
CFLAGS = -Wall -I include -g

vpath %.c src/
vpath %.h include/
vpath %.o obj/

%.o: %.c $(DEP)
	@$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@mkdir -p obj
	@mv *.o obj/

clean:
	@rm main
	@rm obj/*

doc:
	@doxygen

dist:
	@tar -Jcvf LafossePierre-GoL-v0.1.tar.xz makefile Doxyfile src/ include/ README.md

distclean:
	@rm -r doc
	@rm -r *.tar.xz
