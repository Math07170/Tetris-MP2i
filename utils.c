#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Permet d'attendre un temps donné mais ne fonctionne pas */
/* void wait(double towait){
    time_t end = time(NULL) + towait;
    time_t current = time(NULL);
    while(difftime(end,current) >= 0.0){
        usleep( (difftime(end, current) * (5.0 / 100.0))/(1000000) );
        current = time(NULL);
	}
}*/

/* Initialise l'état du jeu aux valeurs qu'il doit avoir à chaque début de partie */
void init_gamestate(gamestate* p_state){
	p_state -> block = 0;
	p_state -> rotation_index = 0;
	p_state -> x = 0;
	p_state -> y = 0;
	p_state -> game_speed = 48;
	p_state -> reserve_utilisee = false;
	p_state -> reserve = (rand() % 7);		// Temporairement, le tetromino dans la réserve est généré aléatoirement en début de partie
	p_state -> suivants[0] = (rand() % 7);
	p_state -> suivants[1] = (rand() % 7);
	p_state -> suivants[2] = (rand() % 7);
	p_state -> suivants[3] = (rand() % 7);
	p_state -> statut = 0;		// 0 -> Jeu en cours ; 1 -> Jeu en pause ; 2 -> Partie perdue
	p_state -> descente_rapide = false;
	p_state -> descente_instantanee = false;
	p_state -> compte_ligne = 0;
	p_state -> score = 0;
	p_state -> niveau = 0;
}

/* Change la valeur du niveau selon l'état du jeu */
void change_niveau(gamestate* p_state){
	int niveau = p_state -> compte_ligne / 10;
	if(p_state -> niveau != niveau){
					p_state -> niveau = p_state -> compte_ligne/10;
					switch(niveau){
						case 0 : p_state -> game_speed = 48; break;
						case 1 : p_state -> game_speed = 43; break;
						case 2 : p_state -> game_speed = 38; break;
						case 3 : p_state -> game_speed = 33; break;
						case 4 : p_state -> game_speed = 28; break;
						case 5 : p_state -> game_speed = 23; break;
						case 6 : p_state -> game_speed = 18; break;
						case 7 : p_state -> game_speed = 13; break;
						case 8 : p_state -> game_speed = 8;  break;
						case 9 : p_state -> game_speed = 6;  break;
						default:
							if(niveau > 9 && niveau <=12) p_state -> game_speed = 5;
							else if(niveau > 12 && niveau <=15) p_state -> game_speed = 4; 
							else if(niveau > 15 && niveau <=18) p_state -> game_speed = 3; 
							else if(niveau > 18 && niveau <=28) p_state -> game_speed = 2;
							else p_state -> game_speed = 1;
						break;
					}
				}
	return;
}

/* Augmente le score (ou pas) selon nbligne, le nombre de lignes précédemment supprimées
 * nbligne doit être compris entre 0 et 4 */
void augmente_score(gamestate* p_state, int nbligne){
	switch(nbligne){
		case 1: p_state -> score += 40 * (p_state -> niveau+1); break;
		case 2: p_state -> score += 100 * (p_state -> niveau+1); break;
		case 3: p_state -> score += 300 * (p_state -> niveau+1); break;
		case 4: p_state -> score += 1200 * (p_state -> niveau+1); break;
	}
	return;	
}
