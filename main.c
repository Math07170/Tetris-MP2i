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

/* Agit sur le tetromino en cours de chute, selon l'entrée clavier */		// À déplacer...
void interroge_commandes(gamestate* p_state, int grille[20][10]){
	char cmd = getch();
	if(cmd == 'd') deplace_droite(p_state, grille);
	else if (cmd == 'q') deplace_gauche(p_state, grille);
	else if (cmd == 'l') tourne_direct(p_state, grille);
	else if (cmd == 'p') tourne_indirect(p_state, grille);
	return;
}

int play = 0;		// 0 : Jeu en cours ; 1 Pause ; 2 Perdu

void tick(){
	play = nouveau_tetromino(&state, grille);
	int tick_count = 0;
	int delai_descentes = 7;
	bool avance_rapide = false;
	int lignes_supprimees = 0;
    while(play == 0){
		interroge_commandes(&state,grille);
		affiche_grille(grille);
		if(tick_count == delai_descentes){
			tick_count = 0;
			if(descente_possible(&state,grille) == true){
				descend(&state, grille);
			}else{
				fixe_tetromino(state, grille);
				lignes_supprimees += nettoie_lignes(grille);
				play = nouveau_tetromino(&state, grille);
			}
		}
		usleep(25000);	// 40 Ticks par seconde
		tick_count++;
	}
}

int main() {
	init_tetrominos();
    init_ncurses();
    initialise_grille(grille);
    srand(time(0));		// "Initialise l'aléatoire" de façon à avoir une suite de tetrominos différente à chaque exécution
    
	tick();
	
	endwin();
	return 0;
}
