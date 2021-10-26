#include <ncurses.h>

/* Affiche la première version de la grille de jeu
 * Ne contient pas encore l'emplacement pour le bloc suivant, la réserve, etc.
 * N'est pas encore capable d'afficher les blocs dans la grille */
void affiche_grille(int haut, int bas, int gauche, int droite){
	for(int i = haut + 1; i < bas; i++){	//	Lignes verticales
		mvaddch(i,gauche,ACS_VLINE);
		mvaddch(i,droite,ACS_VLINE);
	}
	for(int i = gauche; i < droite; i++){	// Lignes horizontales
		mvaddch(haut,i,ACS_HLINE);
		mvaddch(bas,i,ACS_HLINE);
	}
	{	// Angles
		mvaddch(haut,gauche,ACS_ULCORNER);
		mvaddch(bas,gauche,ACS_LLCORNER);
		mvaddch(bas,droite,ACS_LRCORNER);
		mvaddch(haut,droite,ACS_URCORNER);
	}
	{	// Tests...
		for(int i = 1; i < (bas - haut); i++){
			if(i%2 == 0){
				attron(COLOR_PAIR(2));
				mvaddch(haut + i, gauche + 1,' ');
				attroff(COLOR_PAIR(2));
			}
		}
	}
	move(0,50);	// Sort le curseur de la grille (à optimiser...)
	refresh();
	return;
}

/* Test de affiche_grille + initialisations */
int main(){
	initscr();
	noecho();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);	// Couleur des contours (équivaut à pas de couleur du tout...)
	init_pair(2,COLOR_WHITE,COLOR_RED);		// Couleur des blocs Z
	init_pair(3,COLOR_WHITE,COLOR_GREEN);	// Couleur des blocs S
	init_pair(4,COLOR_WHITE,COLOR_YELLOW);	// Couleur des blocs L
	init_pair(5,COLOR_WHITE,COLOR_BLUE);	// Couleur des blocs J
	init_pair(6,COLOR_WHITE,COLOR_MAGENTA);	// Couleur des blocs T
	init_pair(7,COLOR_WHITE,COLOR_CYAN);	// Couleur des blocs I
	init_pair(8,COLOR_WHITE,COLOR_WHITE);	// Couleur des blocs O
	const int haut_grille = 1;
	const int bas_grille = 22;
	const int gauche_grille = 2;
	const int droite_grille = 13;
	affiche_grille(haut_grille,bas_grille,gauche_grille,droite_grille);
	char c = getch();	// Unique moyen que j'ai trouvé pour que l'affichage reste à l'écran...
	endwin();
	return 0;
}
