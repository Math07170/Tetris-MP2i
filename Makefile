tetris: utils.o main.o grille.o tetromino.o
	gcc utils.o main.o grille.o tetromino.o -o tetris -lncurses
main.o: main.c grille.h utils.h
	gcc -c main.c -lncurses
grille.o: grille.c
	gcc -c grille.c -lncurses
utils.o: utils.c
	gcc -c utils.c -lncurses
tetromino.o: tetromino.c
	gcc -c tetromino.c -lncurses
clean:
	rm -f *.o
	rm -f tetris