tetris: utils.o main.o grille.o tetromino.o menus.o menu_gestion.o
	gcc utils.o main.o grille.o tetromino.o menus.o menu_gestion.o -o tetris -lncurses
main.o: main.c grille.h utils.h menus.h
	gcc -c main.c -lncurses
grille.o: grille.c utils.h tetromino.h
	gcc -c grille.c -lncurses
menus.o: menus.c grille.h utils.h menu_gestion.h
	gcc -c menus.c -lncurses
utils.o: utils.c tetromino.h
	gcc -c utils.c -lncurses
tetromino.o: tetromino.c utils.h
	gcc -c tetromino.c -lncurses
menu_gestion.o: menu_gestion.c menu_gestion.h
	gcc -c menu_gestion.c -lncurses
clean:
	rm -f *.o
	rm -f tetris
