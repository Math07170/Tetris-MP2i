#include <ncurses.h>
#include <stdbool.h>
#include "utils.h"
#include "tetromino.h"

int reserve[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};		// Test/placeholder, ne sera plus nécessaire nécessaire après l'impémentation complète de la réserve

/* Initialise ncurses */
void init_ncurses(){
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	cbreak();
	curs_set(0);
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_WHITE);	// Couleur des blocs O
	init_pair(2,COLOR_WHITE,COLOR_RED);		// Couleur des blocs Z
	init_pair(3,COLOR_WHITE,COLOR_GREEN);	// Couleur des blocs S
	init_pair(4,COLOR_WHITE,COLOR_YELLOW);	// Couleur des blocs L
	init_pair(5,COLOR_WHITE,COLOR_BLUE);	// Couleur des blocs J
	init_pair(6,COLOR_WHITE,COLOR_MAGENTA);	// Couleur des blocs T
	init_pair(7,COLOR_WHITE,COLOR_CYAN);	// Couleur des blocs I
	init_pair(8,COLOR_WHITE,COLOR_BLACK);	// Couleur des contours (équivaut à pas de couleur du tout...)
}

/* Vérifie qu'une case fait partie de la grille et est disponible (qu'elle contient la valeur 0) */
bool case_disponible(int grille[20][10], int i, int j){
	if(i<0 || i>=20 || j>=10 || j < 0) return false;
	else if (grille[i][j] == 0) return true;
	else{
		return false;
	} 
}

/* Affiche un cadre vide sur le terminal, de xmin à xmax en abscisse et de ymin à ymax en ordonnée */
void cadre(int xmin, int xmax, int ymin, int ymax){
	for(int x = xmin + 1; x < xmax; x++){
		mvaddch(ymin,x,ACS_HLINE);
		mvaddch(ymax,x,ACS_HLINE);
	}
	for(int y = ymin + 1; y < ymax; y++){
		mvaddch(y,xmin,ACS_VLINE);
		mvaddch(y,xmax,ACS_VLINE);
	}
	mvaddch(ymin,xmin,ACS_ULCORNER);
	mvaddch(ymin,xmax,ACS_URCORNER);
	mvaddch(ymax,xmin,ACS_LLCORNER);
	mvaddch(ymax,xmax,ACS_LRCORNER);
	return;
}

/* "Remplit" un espace de 4x4 blocs, repéré par les coordonnées de son angle supérieur gauche, avec les blocs d'un tableau source */
void remplit_cadre(int xmin, int ymin, int source[4][4]){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j ++){
			int couleur = source[i][j];
			if((couleur <= 7) && (couleur >= 1)){
				attron(COLOR_PAIR(couleur));
				mvaddch(xmin+1+i,ymin+1+(2*j),' ');
				mvaddch(xmin+1+i,ymin+2+(2*j),' ');
				attroff(COLOR_PAIR(couleur));
			}
		}
	}
}

/* Affiche la grille de jeu, à deux colonnes du bord gauche et une ligne du bord supérieur du terminal */
void affiche_grille(int grille[20][10],gamestate state){
	erase();
	
	{		// Grille de jeu principale
		cadre(2,23,1,22);
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 10; j ++){
				int couleur = grille[i][j];
				if((couleur <= 7) && (couleur >= 1)){
					attron(COLOR_PAIR(couleur));
					mvaddch(2+i,3+(2*j),' ');
					mvaddch(2+i,4+(2*j),' ');
					attroff(COLOR_PAIR(couleur));
				}
			}
		}
	}
	{		// Emplacement des 4 blocs suivants
		cadre(26,35,2,22);
		mvprintw(1,27,"Suivants");
		remplit_cadre(2,26,tetrominos[state.suivants[0]].rotations[0]);
		remplit_cadre(7,26,tetrominos[state.suivants[1]].rotations[0]);
		remplit_cadre(12,26,tetrominos[state.suivants[2]].rotations[0]);
		remplit_cadre(17,26,tetrominos[state.suivants[3]].rotations[0]);
	}
	{		// Emplacement de la réserve
		cadre(38,47,2,7);
		mvprintw(1,39,"Réserve");
		remplit_cadre(2,38,reserve);
	}
	{		// Emplacement du score, vide pour l'instant
		cadre(38,47,10,12);
		mvprintw(9,39,"Score");
	}
	{		// Emplacement du niveau, vide pour l'instant
		cadre(38,47,15,17);
		mvprintw(14,39,"Niveau");
	}
	{		// Emplacement du nombre de lignes, vide pour l'instant
		cadre(38,47,20,22);
		mvprintw(19,39,"Lignes");
	}

	
	refresh();
	return;
}

/* Vide le tableau grille (la remplit de zéros) */
void initialise_grille(int grille[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j ++){
			grille[i][j] = 0;
		}
	}
}
