#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "grille.h"
#include "utils.h"

/* Renvoie la colonne de la plus à gauche disponible pour écrire la indice-ième lettre de l'écran titre */
int min_x(int indice){
	return 2 + 16 * indice;
}

/* Renvoie la colonne à droite de l'espace disponible pour écrire la indice-ième lettre de l'écran titre */
int max_x(int indice){
	return 2 + 16 * (indice + 1);
}

/* Remplit avec la couleur correspondant à l'indice "couleur" un rectangle de cases, avec les minimums inclus et les maximums exclus */
void remplit(int couleur,int xmin,int xmax,int ymin,int ymax){
	attron(COLOR_PAIR(couleur));
	for(int x = xmin; x < xmax; x++){
		for(int y = ymin; y < ymax; y++){
			mvaddch(y,x,' ');
		}
	}
	attroff(COLOR_PAIR(couleur));
	return;
}

/* Choisit aléatoirement une lettre du titre et change sa couleur */
void change_couleur_lettre_titre(int clr[6]){
	int couleur_a_changer = rand() % 6;
	clr[couleur_a_changer] = (rand() % 6)+2;
	return;
}

/* Affiche l'écran titre du jeu à un instant donné */
void affiche_ecran_titre(int clr[6]){
	
	attron(A_BOLD);
	mvprintw(2,33,"Mathias et Barnabé présentent...");
	attroff(A_BOLD);
	mvprintw(21,13,"Appuyez sur entrée pour démarrer, ou sur espace pour voir les commandes.");
	
	int indice = 0;		// Position de la lettre
	
	// T, x de 2 à 18
	remplit(clr[0],min_x(indice) + 2, max_x(indice) - 2, 5, 7);
	remplit(clr[0],min_x(indice)+6,max_x(indice)-6,7,19);
	indice++;
	
	// E, x de 18 à 34
	remplit(clr[1],min_x(indice) + 2, max_x(indice) - 2, 5, 7);
	remplit(clr[1],min_x(indice) + 2, max_x(indice) - 2, 11, 13);
	remplit(clr[1],min_x(indice) + 2, max_x(indice) - 2, 17, 19);
	remplit(clr[1],min_x(indice) + 2, max_x(indice) - 10, 7, 19);
	indice++;
	
	// T, x de 34 à 50
	remplit(clr[2],min_x(indice) + 2, max_x(indice) - 2, 5, 7);
	remplit(clr[2],min_x(indice)+6,max_x(indice)-6,7,19);
	indice++;;
	
	// R, x de 50 à 66
	remplit(clr[3],min_x(indice)+2,max_x(indice)-4,5,7);
	remplit(clr[3],min_x(indice)+2,max_x(indice)-4,11,13);
	remplit(clr[3],min_x(indice)+2,max_x(indice)-10,7,19);
	remplit(clr[3],min_x(indice)+10,max_x(indice)-2,7,11);
	remplit(clr[3],min_x(indice)+6,max_x(indice)-6,13,15);
	remplit(clr[3],min_x(indice)+8,max_x(indice)-4,15,17);
	remplit(clr[3],min_x(indice)+10,max_x(indice)-2,17,19);
	indice++;
	
	// I, x de 66 à 82
	remplit(clr[4],min_x(indice)+6,max_x(indice)-6,5,7);
	remplit(clr[4],min_x(indice)+6,max_x(indice)-6,9,19);
	indice++;
	
	// S, x de 82 à 98
	remplit(clr[5],min_x(indice)+2,max_x(indice)-2,5,7);
	remplit(clr[5],min_x(indice)+2,max_x(indice)-2,11,13);
	remplit(clr[5],min_x(indice)+2,max_x(indice)-2,17,19);
	remplit(clr[5],min_x(indice)+2,max_x(indice)-10,7,11);
	remplit(clr[5],min_x(indice)+10,max_x(indice)-2,13,19);
	
	refresh();
	return;
}

/* Affiche les commandes du jeu, ne permet pas encore de les modifier */
void affiche_commandes(){
	erase();
	cadre(5,41,2,20);
	
	attron(A_BOLD);
	mvprintw(4,18,"COMMANDES");
	attroff(A_BOLD);
			
	attron(COLOR_PAIR(9));
	mvaddch(6,9,'L');
	mvaddch(8,9,'P');
	mvaddch(10,9,'Q');
	mvaddch(12,9,'D');
	mvaddch(14,9,'S');
	mvaddch(16,9,'Z');
	mvprintw(18,7,"Espace");
	attroff(COLOR_PAIR(9));
	
			// Usage des accents avec ncurses à investiguer
	mvprintw(6,17,"Rotation anti-horaire");
	mvprintw(8,17,"Rotation horaire");
	mvprintw(10,17,"Translation gauche");
	mvprintw(12,17,"Translation droite");
	mvprintw(14,17,"Descente rapide");
	mvprintw(16,17,"Descente directe");
	mvprintw(18,17,"Reserve");		// Écrire "réserve" avec un accent pose problème, il faut trouver un synonyme...
	
	refresh();
	while(getch() != '\n'){
		usleep(25000);		// 40 TPS
	}
	return;
}

/* Affiche l'écran titre du jeu tant que l'utilisateur n'appuie pas sur entrée */		// TODO : affichage et modification des commandes
void ecran_titre(){
	int tick_count = 0;
	int clr[6] = {(rand()%6) + 2,(rand()%6) + 2,(rand()%6) + 2,(rand()%6) + 2,(rand()%6) + 2,(rand()%6) + 2};
	char cmd = getch();
	while((cmd != '\n') && (cmd != ' ')){
		affiche_ecran_titre(clr);
		usleep(25000);		// 40 TPS
		if(tick_count == 20){
			change_couleur_lettre_titre(clr);
			tick_count = 0;
		}
		refresh();
		tick_count++;
		cmd = getch();
	}
	if(cmd == ' '){		// Cas ou l'utilisateur a appuyé sur espace : affichage des commandes
		affiche_commandes();
		return;
	}else{		// Cas où l'utilisateur a appuyé sur entrée : démarre directement le jeu
		return;
	}
}

/* Affiche le texte de fin de partie */
bool fin_partie(gamestate state){
	erase();
	
	attron(A_BOLD);
	mvprintw(5,31,"PERDU !");
	mvprintw(7,26,"Essayez encore !");
	attroff(A_BOLD);
	
	mvprintw(13,24,"Score : ");
	affiche_nombre(6,state.score,13,31);
	
	affiche_nombre(3,state.compte_ligne,15,23);
	mvprintw(15,28,"lignes, niveau");
	affiche_nombre(2,state.niveau,15,42);
	
	mvprintw(21,11,"Entrée : Rejouer");
	mvprintw(21,41,"Q : Fermer le jeu");
	
	refresh();
	
	char cmd = getch();
	while((cmd != '\n') && (cmd != 'q')){
		usleep(25000);		// 40 TPS
		cmd = getch();
	}
	if(cmd == '\n'){
		return true;
	}else{
		return false;
	}
}
