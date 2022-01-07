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
keybind binding;

/* Agit sur le tetromino en cours de chute, selon l'entrée clavier */		// À déplacer...
void interroge_commandes(gamestate* p_state, int grille[20][10]){
	char cmd = getch();
	if(cmd == binding.droite) deplace_droite(p_state, grille);
	else if (cmd == binding.gauche) deplace_gauche(p_state, grille);
	else if (cmd == binding.tourne_direct) tourne_direct(p_state, grille);
	else if (cmd == binding.tourne_indirect) tourne_indirect(p_state, grille);
	else if (cmd == binding.reserve) reserve(p_state, grille);
	else if (cmd == binding.descente_rapide) p_state -> descente_rapide = true;
	else if (cmd == binding.descente_instantanee) descente_instantanee(p_state, grille);
	return;
}


/* Contient le "jeu" de Tetris en lui-même */
void tick(){
	state.statut = nouveau_tetromino(&state, grille);
	int tick_count = 0;
	bool avance_rapide = false;
	int lignes_supprimees = 0;
    while(state.statut == 0){
		interroge_commandes(&state,grille);
		affiche_grille(grille,state);
		if(tick_count >= state.game_speed || state.descente_rapide){
			tick_count = 0;
			if(descente_possible(&state,grille)){
				descend(&state, grille);
			}else{
				suivant(&state,grille);
			}
			state.descente_rapide = false;
		}
		usleep(16667);	// 60 Ticks par seconde
		tick_count++;
	}
}

int main() {
	binding = load_config();

    init_ncurses();
    srand(time(0));		// "Initialise l'aléatoire" de façon à avoir une suite de tetrominos différente à chaque exécution
    
	ecran_titre(&binding);		// TODO : modification des commandes
    
	init_tetrominos();		// N'a pas besoin d'être initialisé à chaque partie, une initialisation au lancement du programme est suffisante
	bool lance_partie = true;
	
	while(lance_partie){
		initialise_grille(grille);
		init_gamestate(&state);
		tick();
		lance_partie = fin_partie(state);
	}
	
	endwin();
	return 0;
}
