#include <stdlib.h>
#include <ncurses.h>
#include "grille.h"

int main() {
    init_ncurses();
    int grille[20][10];
    initialise_grille(grille);



	grille[16][9] = 7; // Test avec la couleur cyan (bloc I)
	grille[17][9] = 7;
	grille[18][9] = 7;
	grille[19][9] = 7;
	
	grille[19][8] = 6; // Test avec la couleur magenta (bloc T)
	grille[19][7] = 6;
	grille[19][6] = 6;
	grille[18][7] = 6;
	
	grille[19][0] = 9; // Test avec une couleur invalide
	
	grille[0][0] = 1;	// Test avec divers blocs un peu partout
	grille[0][9] = 2;
	grille[19][0] = 3;
	grille[5][7] = 4;
	grille[13][4] = 5;
	grille[13][5] = 5;
	
	affiche_grille(grille);
	char c = getch();	// Unique moyen que j'ai trouvé pour que l'affichage reste à l'écran...
	endwin();
	return 0;
}