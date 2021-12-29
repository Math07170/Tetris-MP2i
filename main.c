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
	state.game_speed = 48;
	state.reserve_utilisee = false;
	state.reserve = (rand() % 7);		// Temporairement, le tetromino dans la réserve est généré aléatoirement en début de partie
	state.suivants[0] = (rand() % 7);
	state.suivants[1] = (rand() % 7);
	state.suivants[2] = (rand() % 7);
	state.suivants[3] = (rand() % 7);
	state.statut = 0;		// 0 -> Jeu en cours ; 1 -> Jeu en pause ; 2 -> Partie perdue
	state.descente_rapide = false;
	state.compte_ligne = 0;
	state.score = 0;
	state.niveau = 0;
}

/* Agit sur le tetromino en cours de chute, selon l'entrée clavier */		// À déplacer...
void interroge_commandes(gamestate* p_state, int grille[20][10]){
	char cmd = getch();
	if(cmd == 'd') deplace_droite(p_state, grille);
	else if (cmd == 'q') deplace_gauche(p_state, grille);
	else if (cmd == 'l') tourne_direct(p_state, grille);
	else if (cmd == 'p') tourne_indirect(p_state, grille);
	else if (cmd == ' ') reserve(p_state, grille);
	else if (cmd == 's') p_state->descente_rapide = true;
	else if (cmd == 'z') descente_instantanee(p_state, grille);
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
		if(tick_count == state.game_speed || state.descente_rapide){
			tick_count = tick_count%state.game_speed;
			if(descente_possible(&state,grille) == true){
				descend(&state, grille);
			}else{
				fixe_tetromino(state, grille);
				int nbline = nettoie_lignes(grille);
				switch(nbline){
					case 1: state.score += 40 * (state.niveau+1); break;
					case 2: state.score += 100 * (state.niveau+1); break;
					case 3: state.score += 300 * (state.niveau+1); break;
					case 4: state.score += 1200 * (state.niveau+1); break;
				}
				
				state.compte_ligne += nbline;
				int niveau = state.compte_ligne/10;
				if(state.niveau != niveau){
					state.niveau = state.compte_ligne/10;
					switch(niveau){
						case 0 : state.game_speed = 48; break;
						case 1 : state.game_speed = 43; break;
						case 2 : state.game_speed = 38; break;
						case 3 : state.game_speed = 33; break;
						case 4 : state.game_speed = 28; break;
						case 5 : state.game_speed = 23; break;
						case 6 : state.game_speed = 18; break;
						case 7 : state.game_speed = 13; break;
						case 8 : state.game_speed = 8;  break;
						case 9 : state.game_speed = 6;  break;
						default:
							if(niveau > 9 && niveau <=12) state.game_speed = 5;
							else if(niveau > 12 && niveau <=15) state.game_speed = 4; 
							else if(niveau > 15 && niveau <=18) state.game_speed = 3; 
							else if(niveau > 18 && niveau <=28) state.game_speed = 2;
							else state.game_speed = 1;
						break;
					}
				}
				
				state.statut = nouveau_tetromino(&state, grille);
			}
			state.descente_rapide = false;
		}
		usleep(16670);	// 40 Ticks par seconde
		tick_count++;
	}
}

int main() {

    init_ncurses();
    srand(time(0));		// "Initialise l'aléatoire" de façon à avoir une suite de tetrominos différente à chaque exécution
    
	ecran_titre();		// TODO : modification des commandes
    
	init_tetrominos();		// N'a pas besoin d'être initialisé à chaque partie
	bool lance_partie = true;
	
	while(lance_partie){
		initialise_grille(grille);
		init_gamestate();
		tick();
		lance_partie = fin_partie(state);
	}
	
	endwin();
	return 0;
}
