tetris: utils.o main.o grille.o
	gcc utils.o main.o grille.o -o tetris -lncurses
main.o: main.c grille.h
	gcc -c main.c -lncurses
grille.o: grille.c
	gcc -c grille.c -lncurses
utils.o: utils.c
	gcc -c utils.c -lncurses
clean:
	rm -f *.o
	rm -f tetris