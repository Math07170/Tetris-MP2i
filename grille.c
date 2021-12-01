#include <ncurses.h>
#include <stdbool.h>

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

/* Affiche la grille de jeu, à deux colonnes du bord gauche et une ligne du bord supérieur du terminal */
void affiche_grille(int grille[20][10]){
	erase();
	
	{		// Affiche la grille de jeu principale et les blocs qu'elle contient
		for(int i = 2; i < 22; i++){
			mvaddch(i,2,ACS_VLINE);
			mvaddch(i,23,ACS_VLINE);
		}
		for(int i = 3; i < 23; i++){
			mvaddch(1,i,ACS_HLINE);
			mvaddch(22,i,ACS_HLINE);
		}
		{
			mvaddch(1,2,ACS_ULCORNER);
			mvaddch(22,2,ACS_LLCORNER);
			mvaddch(22,23,ACS_LRCORNER);
			mvaddch(1,23,ACS_URCORNER);
		}
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
	
	// Ici : Blocs suivants et réserve à afficher
	
	refresh();
	return;
}

/* Vide la grille (la remplit de zéros) */
void initialise_grille(int grille[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j ++){
			grille[i][j] = 0;
		}
	}
}
