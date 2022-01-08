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


/* Contient la partie "jeu" du programme */
void boucle_jeu(){
	state.statut = nouveau_tetromino(&state, grille);
	int compte_tick = 0;		// Variable servant à se repérer parmi les itérations de la boucle de jeu
	bool avance_rapide = false;
    while(state.statut == 0){
		interroge_commandes(&state,grille);
		affiche_grille(grille,state);
		if(compte_tick >= state.vitesse_jeu || state.descente_rapide){		// L'utilisation de >= permet d'éviter que dans certains cas, compte_tick devienne plus grand que vitesse_jeu, ce qui arrêterait la descente du tetromino
			compte_tick = 0;
			if(descente_possible(&state,grille)){
				descend(&state, grille);
			}else{
				suivant(&state,grille);		// S'occupe de tous les changements nécessaires au passage au prochain tetromino
				compte_tick = 0;		// Permet que chaque nouveau tetromino aie le vrai délai de descente avant sa 1ère descente
			}
			state.descente_rapide = false;
		}
		usleep(16667);	// 60 Ticks par seconde
		compte_tick++;
	}
}

int main() {
	// Initialisations...
	binding = load_config();
	srand(time(0));
    init_ncurses();
    init_tetrominos();
    bool lance_partie = true;
    
	ecran_titre(&binding);		// Écran titre et affichage des commandes
	
	while(lance_partie){		// La partie "jeu" se déroule ici
		init_grille(grille);
		init_gamestate(&state);
		boucle_jeu();
		lance_partie = fin_partie(state);		// Affiche l'écran de fin et permet éventuellement au joueur de lancer une nouvelle partie
	}
	
	endwin();		// Arrête "proprement" ncurses avant de fermer le jeu
	return 0;
}
