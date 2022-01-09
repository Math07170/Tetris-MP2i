#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "grille.h"
#include "utils.h"
#include "string.h"
#include "menu_gestion.h"

keybind * bind;


/* Les quatre fonctions suivantes renvoient les coordonnées maximum et minimum du rectangle qui accueillira la indice-ième lettre du menu
 * x représente l'indice de la colonne et y celui de la ligne
 * L'entier indice doit être compris entre 0 et 21 */
int min_x(int indice){
	return 2 + 8 * (indice % 11);
}

int max_x(int indice){
	return 2 + 8 * ((indice % 11)+ 1);
}

int min_y(int indice){
	if(indice < 11){
		return 4;
	}else{
		return 13;
	}
}

int max_y(int indice){
	if(indice < 11){
		return 13;
	}else{
		return 22;
	}
}

/* Remplit avec la couleur correspondant à l'indice "couleur" un rectangle de cases, avec les minimums inclus et les maximums exclus
 * Les arguments doivent être positifs, avec xmin < xmax et ymin < ymax */
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

/* Choisit aléatoirement une lettre du titre et change sa couleur 
 * Peut ne changer aucune couleur si l'indice choisi correspond à un espace, ou si la nouvelle couleur est la même que l'ancienne */
void change_couleur_lettre_titre(int clr[22]){
	int couleur_a_changer = rand() % 22;
	clr[couleur_a_changer] = (rand() % 6)+2;
	return;
}

/* Affiche l'écran titre du jeu à un instant donné 
 * Le tableau clr doit contenir des entiers compris entre 2 et 8, correspondant à certaines couleurs */
void affiche_ecran_titre(int clr[22]){
	
	attron(A_BOLD);
	mvprintw(2,29,"Mathias et Barnabé présentent...");
	attroff(A_BOLD);
	mvprintw(23,21,"Entrée : Jouer               Espace : Commandes");
	
	int indice = 0;		// Position de la lettre
	
	// PREMIÈRE LIGNE, y de 4 à 13
	
	// Espace, x de 2 à 10
	indice++;
	
	// L, x de 10 à 18
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// E, x de 18 à 26
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,min_y(indice)+4,max_y(indice)-4);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// S, etc.
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+2,min_y(indice)+4);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,max_y(indice)-4,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+4,max_y(indice)-4);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// Espace
	indice++;
	
	// B
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,min_y(indice)+2,min_y(indice)+4);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,max_y(indice)-4,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-2,min_y(indice)+4,max_y(indice)-4);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// L
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// O
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+2,max_y(indice)-2);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,min_y(indice)+2,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	indice++;
	// C
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+2,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	indice++;
	// S
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+2,min_y(indice)+4);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,max_y(indice)-4,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+4,max_y(indice)-4);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// Espace
	indice++;
	
	// DEUXIÈME LIGNE, y de 13 à 22
	
	// Q, à nouveau x de 10 à 18
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+2,max_y(indice)-2);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,min_y(indice)+2,max_y(indice)-3);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-1,max_y(indice)-2,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],max_x(indice)-4,max_x(indice)-2,max_y(indice)-3,max_y(indice)-2);
	indice++;
	// U
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+1,max_y(indice)-2);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,min_y(indice)+1,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// I
	remplit(clr[indice],min_x(indice)+3,max_x(indice)-3,min_y(indice)+3,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+3,max_x(indice)-3,min_y(indice)+1,min_y(indice)+2);
	indice++;
	// Espace
	indice++;
	
	// T
	remplit(clr[indice],min_x(indice)+1, max_x(indice)-1, min_y(indice)+1, min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+3,max_x(indice)-3,min_y(indice)+2,max_y(indice)-1);
	indice++;
	// O
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+2,max_y(indice)-2);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,min_y(indice)+2,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+2,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	indice++;
	// M
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+2,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],max_x(indice)-2,max_x(indice)-1,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+2,min_x(indice)+3,min_y(indice)+2,min_y(indice)+3);
	remplit(clr[indice],min_x(indice)+3,min_x(indice)+4,min_y(indice)+3,min_y(indice)+4);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-2,min_y(indice)+2,min_y(indice)+3);
	remplit(clr[indice],max_x(indice)-4,max_x(indice)-3,min_y(indice)+3,min_y(indice)+4);
	indice++;
	// B
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+3,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,min_y(indice)+2,min_y(indice)+4);
	remplit(clr[indice],max_x(indice)-3,max_x(indice)-1,max_y(indice)-4,max_y(indice)-2);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-2,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-2,min_y(indice)+4,max_y(indice)-4);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-2,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// E
	remplit(clr[indice],min_x(indice)+1, min_x(indice)+3, min_y(indice)+1, max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,min_y(indice)+1,min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,min_y(indice)+4,max_y(indice)-4);
	remplit(clr[indice],min_x(indice)+1,max_x(indice)-1,max_y(indice)-2,max_y(indice)-1);
	indice++;
	// N
	remplit(clr[indice],min_x(indice)+1,min_x(indice)+2,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],max_x(indice)-2,max_x(indice)-1,min_y(indice)+1,max_y(indice)-1);
	remplit(clr[indice],min_x(indice)+2,min_x(indice)+3,min_y(indice)+2,min_y(indice)+3);
	remplit(clr[indice],min_x(indice)+3,min_x(indice)+4,min_y(indice)+3,min_y(indice)+4);
	remplit(clr[indice],min_x(indice)+4,min_x(indice)+5,min_y(indice)+4,min_y(indice)+5);
	remplit(clr[indice],min_x(indice)+5,min_x(indice)+6,min_y(indice)+5,min_y(indice)+6);
	indice++;
	// T
	remplit(clr[indice],min_x(indice)+1, max_x(indice)-1, min_y(indice)+1, min_y(indice)+2);
	remplit(clr[indice],min_x(indice)+3,max_x(indice)-3,min_y(indice)+2,max_y(indice)-1);
	
	refresh();
	return;
}

void onclick(int selected, void* m){
	menu* me = m;
	setlabel(&(me->buttons[selected]), "Entrer la commande !");
	display(*me);
	char label[80];
	switch(selected){
		case 0: bind->tourne_direct = getchar(); 
			strcpy(label, "Rotation anti-horraire : "); 
			strncat(label, &bind->tourne_direct, 1);
			break;
		case 1: bind->tourne_indirect = getchar();
			strcpy(label, "Rotation horraire : "); 
			strncat(label, &bind->tourne_indirect, 1);
			break;
		case 2: bind->gauche = getchar();
			strcpy(label, "Translation gauche : "); 
			strncat(label, &bind->gauche, 1);
			break;
		case 3: bind->droite = getchar(); 
			strcpy(label, "Translation droite : "); 
			strncat(label, &bind->droite, 1);
			break;
		case 4: bind->descente_rapide = getchar(); 
			strcpy(label, "Descente rapide : "); 
			strncat(label, &bind->descente_rapide, 1);
			break;
		case 5: bind->descente_instantanee = getchar();
			strcpy(label, "Descente directe : "); 
			strncat(label, &bind->descente_instantanee, 1);
			break;
		case 6: bind->reserve = getchar();
			strcpy(label, "Reserve : "); 
			strncat(label, &bind->reserve, 1);
			break;
		
	}
	setlabel(&(me->buttons[selected]), label);
	save_config(*bind);
}

/* Affiche les commandes du jeu, ne permet pas encore de les modifier */
void affiche_commandes(keybind* bind){
	menu m = createMenu("COMMANDES", 7, 3, 4, 18); 
	char label[40] = "Rotation anti-horaire : ";
	addbutton(&m, 6, 17, strncat(label, &bind->tourne_direct, 1), onclick);
	char label1[40] = "Rotation horaire : ";
	addbutton(&m, 8, 17, strncat(label1, &bind->tourne_indirect, 1), onclick);
	char label2[40] = "Translation gauche : ";
	addbutton(&m, 10, 17, strncat(label2, &bind->gauche, 1), onclick);
	char label3[40] = "Translation droite : ";
	addbutton(&m, 12, 17, strncat(label3, &bind->droite, 1), onclick);
	char label4[40] = "Descente rapide : ";
	addbutton(&m, 14, 17, strncat(label4, &bind->descente_rapide, 1), onclick);
	char label5[40] = "Descente directe : ";
	addbutton(&m, 16, 17, strncat(label5, &bind->descente_instantanee, 1), onclick);
	char label6[40] = "Reserve : ";
	addbutton(&m, 18, 17, strncat(label6, &bind->reserve, 1), onclick);
	addTextbox(&m, 20, 17, "Les commandes sont Z S Espace et Entrer");
	display(m);
	menuloop(m);
	return;
}

/* Affiche l'écran titre du jeu tant que l'utilisateur n'appuie pas sur entrée ou sur espace */
void ecran_titre(keybind* bindp){
	bind=bindp;
	int tick_count = 0;
	int clr[22];
	for(int i = 0; i < 22; i++){
		clr[i] = (rand() % 6) + 2;
	}
	char cmd = getch();
	while((cmd != '\n') && (cmd != ' ')){
		affiche_ecran_titre(clr);
		usleep(16667);
		if(tick_count == 12){
			change_couleur_lettre_titre(clr);
			tick_count = 0;
		}
		refresh();
		tick_count++;
		cmd = getch();
	}
	if(cmd == ' '){		// Cas ou l'utilisateur a appuyé sur espace : affichage des commandes
		affiche_commandes(bind);
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
		usleep(16667);
		cmd = getch();
	}
	if(cmd == '\n'){
		return true;
	}else{
		return false;
	}
}
