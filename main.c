#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include "grille.h"
#include "utils.h"
#include "tetromino.h"
#include "menus.h"

int grille[20][10];

gamestate state;

void init_gamestate(){
	state.block = 0;
	state.rotation_index = 0;
	state.x = 0;
	state.y = 0;
	state.game_speed = 5;
	state.reserve_utilisee = false;
	state.reserve = 0;
	state.suivants[0] = (rand() % 7);
	state.suivants[1] = (rand() % 7);
	state.suivants[2] = (rand() % 7);
	state.suivants[3] = (rand() % 7);
	state.statut = 0;
	state.descente_rapide = false;
	state.compte_ligne = 0;
	state.score = 0;
	state.level = 0;
}

/* Agit sur le tetromino en cours de chute, selon l'entrée clavier */		// À déplacer...
void interroge_commandes(gamestate* p_state, int grille[20][10]){
	char cmd = getch();
	if(cmd == 'd') deplace_droite(p_state, grille);
	else if (cmd == 'q') deplace_gauche(p_state, grille);
	else if (cmd == 'l') tourne_direct(p_state, grille);
	else if (cmd == 'p') tourne_indirect(p_state, grille);
	return;
}

int play = 0;		// 0 : Jeu en cours ; 1 : Pause ; 2 : Perdu

/* Contient le "jeu" de Tetris en lui-même */
void tick(){
	play = nouveau_tetromino(&state, grille);
	int tick_count = 0;
	bool avance_rapide = false;
	int lignes_supprimees = 0;
    while(play == 0){
		interroge_commandes(&state,grille);
		affiche_grille(grille,state);
		if(tick_count == state.game_speed){
			tick_count = 0;
			if(descente_possible(&state,grille) == true){
				descend(&state, grille);
			}else{
				fixe_tetromino(state, grille);
				state.compte_ligne += nettoie_lignes(grille);
				play = nouveau_tetromino(&state, grille);
			}
		}
		usleep(25000);	// 40 Ticks par seconde
		tick_count++;
	}
}

int main() {

    init_ncurses();
    srand(time(0));		// "Initialise l'aléatoire" de façon à avoir une suite de tetrominos différente à chaque exécution
    
	ecran_titre();		// TODO : affichage et modification des commandes
    
   	init_gamestate();
	init_tetrominos();
	initialise_grille(grille);
    
	tick();
	
	endwin();
	return 0;
}
