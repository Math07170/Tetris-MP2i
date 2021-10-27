#include <ncurses.h>

void init_ncurses(){
	initscr();
	noecho();
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

/* Affiche la deuxième version de la grille de jeu (pouvant contenir des blocs)
 * La grille est à deux colonnes du bord supérieur et une ligne du bord supérieur du terminal
 * Ne contient pas encore l'emplacement pour le bloc suivant, la réserve, etc. */
void affiche_grille(int grille[20][10]){
	erase();
	for(int i = 2; i < 22; i++){	//	Lignes verticales
		mvaddch(i,2,ACS_VLINE);
		mvaddch(i,23,ACS_VLINE);
	}
	for(int i = 3; i < 23; i++){	// Lignes horizontales
		mvaddch(1,i,ACS_HLINE);
		mvaddch(22,i,ACS_HLINE);
	}
	{	// Angles
		mvaddch(1,2,ACS_ULCORNER);
		mvaddch(22,2,ACS_LLCORNER);
		mvaddch(22,23,ACS_LRCORNER);
		mvaddch(1,23,ACS_URCORNER);
	}
	for(int i = 0; i < 20; i++){ // Affichage des blocs, en couleur
		for(int j = 0; j < 10; j ++){
			int tmp = grille[i][j];
			if((tmp <= 7) && (tmp >= 1)){	// Elimine les valeurs invalides et l'absence de bloc
				attron(COLOR_PAIR(tmp));
				mvaddch(2+i,3+(2*j),' ');
				mvaddch(2+i,4+(2*j),' ');
				attroff(COLOR_PAIR(tmp));
				
			}
		}
	} 
	move(0,50);	// Sort le curseur de la grille (à optimiser...)
	refresh();
	return;
}
void initialise_grille(int grille[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j ++){
			grille[i][j] = 0;
		}
	}
}