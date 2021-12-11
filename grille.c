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

/* Affiche la grille de jeu, à deux colonnes du bord gauche et une ligne du bord supérieur du terminal */
void affiche_grille(int grille[20][10]){
	erase();
	
	{		// Affiche la grille de jeu principale, et les blocs qu'elle contient
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
	{		// Emplacement des blocs suivants, vide pour l'instant
		cadre(26,35,2,22);
		mvprintw(1,27,"Suivants");
	}
	{		// Emplacement de la réserve, vide pour l'instant
		cadre(38,47,2,7);
		mvprintw(1,39,"Réserve");
	}
	{		// Emplacement du score, vide pour l'instant
		cadre(38,47,11,13);
		mvprintw(10,39,"Score");
	}
	{		// Emplacement du nombre de lignes, vide pour l'instant
		cadre(38,47,17,19);
		mvprintw(16,39,"Lignes");
	}
	
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
