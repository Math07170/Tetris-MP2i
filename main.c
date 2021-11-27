#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include "grille.h"
#include "utils.h"
#include "tetromino.h"

int grille[20][10];

gamestate state = {
	0,
	0,
	0,
	0,
	1.0
};

int play = 0;
int tick_count = 0;

void tick(){
	nettoie_grille(grille);			// Ne fonctionne pas...
	nouveau_tetromino(&state);
	bool descente_possible = true;
    while(play == 0){
		char a = getch();
		if(a == 'd') deplace_droite(&state, grille);
		else if (a == 'q') deplace_gauche(&state, grille);
		else if (a == 'l') tourne_direct(&state, grille);
		else if (a == 'p') tourne_indirect(&state, grille);
		affiche_grille(grille);
		if(descente_possible == true){
			descente_possible = descend(&state, grille);
		}else{
			fixe_tetromino(state, grille);
			nouveau_tetromino(&state);
			descente_possible = true;
		}
		usleep(166666);
	}
}

int main() {
	init_tetrominos();
    init_ncurses();
    initialise_grille(grille);

	//grille[16][9] = 7;
	//grille[17][9] = 7;
	//grille[18][9] = 7;
	//grille[19][9] = 7;
	//grille[19][8] = 6;
	//grille[19][7] = 6;
	//grille[19][6] = 6;
	//grille[18][7] = 6;
	//grille[19][0] = 3;
	//grille[5][7] = 4;
	//grille[13][4] = 5;
	//grille[13][5] = 5;
	
	tick();
	endwin();
	return 0;
}
