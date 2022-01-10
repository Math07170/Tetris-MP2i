#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "menu_gestion.h"


/* Crée un menu prend en argument sont titre, son nombre max de boutton de textbox et les coordonnée en x y du titre */
menu createMenu(char* title, int nb_button, int nb_textbox, int x, int y){
    menu m;
    
    m.nbr = 0;
    m.nbr_max = nb_button;
    m.nbr_text = 0;
    m.nbr_max_text = nb_textbox;

    m.title = malloc(sizeof(char) * strlen(title) + 1);
    strcpy(m.title, title);

    m.x = x;
    m.y = y;

    button* buttons = malloc(nb_button * sizeof(button));
    textbox* texts = malloc(nb_textbox * sizeof(textbox));

    m.texts = texts;
    m.buttons = buttons;
    m.selected = 0;

    return(m);
}
//Crée une nouvelle textbox 
void addTextbox(menu* m, int x, int y, char* text){
    m->nbr_text = (m->nbr_text)+1;

    //Erreur en cas de dépassement de tableau
    if(m->nbr_text > m->nbr_max_text) {
        endwin();
        printf("Dépassement de tableau ! Horreur !");
        exit(666);
    }
    
	textbox t;

	t.x = x;
	t.y = y;

	t.text = malloc(sizeof(char)* strlen(text)+1);
    strcpy(t.text, text);

	t.id = m->nbr_text-1;
	m->texts[m->nbr_text-1] = t;
}

/* 
Crée un nouveau boutton dans le menu
x et y sont des entiers positifs
label est un "string"
onclick est une fonction 
*/
void addbutton(menu* m, int x, int y, char* label, void (*onclick)(int, void*)){
	m->nbr = (m->nbr)+1;

    //Erreur en cas de dépassement de tableau 
    if(m->nbr > m->nbr_max) {
        endwin();
        printf("Dépassement de tableau ! Horreur !");
        exit(666);
    }
    
	button b;

	b.x = x;
	b.y = y;

	b.label = malloc(sizeof(char)* strlen(label) + 1);
    strcpy(b.label, label);

	b.onclick = onclick;
    
	b.id = m->nbr-1;
	m->buttons[m->nbr-1] = b;
}

// Change le label d'un boutton gestion de la mémoire dynamique
void setlabel(button* b, char* label){
    char* old = b->label;
    char* new_label = malloc(sizeof(char) * strlen(label) +1);
    strcpy(new_label, label);
    b->label = new_label;
    free(old);
}

// Affiche le menu pris en argument
// Nécessite l'initialisation préalable de NCURSES
void display(menu m){
    erase();
	attroff(COLOR_PAIR(1));
    attron(A_BOLD);
	mvprintw(m.x,m.y,m.title);
	attroff(A_BOLD);
    for(int i = 0; i<m.nbr_text; i++){
        textbox t = m.texts[i];
        mvprintw(t.x, t.y, t.text);
    }
    for(int i = 0; i<m.nbr; i++){
        button b = m.buttons[i];
		attroff(COLOR_PAIR(9));
        if(m.selected == b.id){
            attron(COLOR_PAIR(9));
        }
        mvprintw(b.x, b.y, b.label);
    }
    refresh();
	
}
/* 
Boucle du menu éxécutée 60 fois par seconde
On vérifie les entrée clavier et on réaffiche le menu si des changement ont été effectué
Libère la mémoire réservée à quand le menu est fermé 
*/
void menuloop(menu m){
    int running = 1;
    while(running == 1){
        char input = getch();
		if(input == ' '){
            //On sort alors du menu
			running = 0;
		}
        else if(input == 'z'){
            if(m.selected > 0) m.selected --;
			display(m);
        }
        else if(input == 's'){
            if(m.selected < m.nbr-1) m.selected ++;
			display(m);
        }
        else if(input == '\n'){
            //Si le boutton est cliké la fonction associé est appelé
            //La fonction reçois l'id du boutton séléctionner et un pointeur vers le menu
            //Cela permet d'avoir le contexte du boutton
            (m.buttons[m.selected].onclick(m.selected, &m));
			display(m);
        }
		
		usleep(16667);
    }
    /* Libération de la mémoire réservée */
    for(int i = 0; i<m.nbr; i++){
        free(m.buttons[i].label);
    }
    for(int i = 0; i<m.nbr_text; i++){
        free(m.texts[i].text);
    }
    free(m.texts);
    free(m.buttons);
    free(m.title);
}
