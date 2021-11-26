#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
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
    
    while(play == 0){
		char a = getch();
		if(a =='d') deplace_droite(&state, grille);
		affiche_grille(grille);
		descend(&state, grille);
		sleep(1);
	}
}
int main() {
	init_tetrominos();
	state.block = 1;
	state.x = tab[state.block-1].spawn_x;
	state.y = tab[state.block-1].spawn_y;
    init_ncurses();
    initialise_grille(grille);

	grille[16][9] = 7; // Test avec la couleur cyan (bloc I)
	grille[17][9] = 7;
	grille[18][9] = 7;
	grille[19][9] = 7;
	
	grille[19][8] = 6; // Test avec la couleur magenta (bloc T)
	grille[19][7] = 6;
	grille[19][6] = 6;
	grille[18][7] = 6;
	
	grille[19][0] = 9; // Test avec une couleur invalide
	
	grille[0][0] = 1;	// Test avec divers blocs un peu partout
	grille[0][9] = 2;
	grille[19][0] = 3;
	grille[5][7] = 4;
	grille[13][4] = 5;
	grille[13][5] = 5;
	
	tick();
	endwin();
	return 0;
}
