tetris: utils.o main.o grille.o tetromino.o menus.o
	gcc utils.o main.o grille.o tetromino.o menus.o -o tetris -lncurses
main.o: main.c grille.h utils.h menus.h
	gcc -c main.c -lncurses
grille.o: grille.c
	gcc -c grille.c -lncurses
menus.o: menus.c grille.h
	gcc -c menus.c -lncurses
utils.o: utils.c
	gcc -c utils.c -lncurses
tetromino.o: tetromino.c
	gcc -c tetromino.c -lncurses
clean:
	rm -f *.o
	rm -f tetris
