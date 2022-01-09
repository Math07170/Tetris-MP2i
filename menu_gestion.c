#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "menu_gestion.h"

menu createMenu(char* title, int nb_button, int x, int y){
    menu m;
    m.nbr = 0;
    m.nbr_max = nb_button;
    m.title = malloc(sizeof(char) * strlen(title) + 1);
    strcpy(m.title, title);
    m.x = x;
    m.y = y;
    button* buttons = malloc(nb_button * sizeof(button));
    m.buttons = buttons;
    m.selected = 0;
    return(m);
}
void addbutton(menu* m, int x, int y, char* label, void (*onclick)(int, void*)){
	m->nbr = (m->nbr)+1;
    if(m->nbr > m->nbr_max) {
        endwin();
        printf("Erreur le menu est trop petit !");
        exit(666);
    }
    
	button b;
	b.x = x;
	b.y = y;
	b.label = malloc(sizeof(char)* 40);
    strcpy(b.label, label);
	b.onclick = onclick;
	b.id = m->nbr-1;
	m->buttons[m->nbr-1] = b;
}
void setlabel(button* b, char* label){
    char* old = b->label;
    char* new_label = malloc(sizeof(char) * strlen(label) +1);
    strcpy(new_label, label);
    b->label = new_label;
    free(old);
}
void display(menu m){
    erase();
	attroff(COLOR_PAIR(1));
    attron(A_BOLD);
	mvprintw(m.x,m.y,m.title);
	attroff(A_BOLD);
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

void menuloop(menu m){
    int running = 1;
    while(running == 1){
        char input = getch();
		if(input == ' '){
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
            (m.buttons[m.selected].onclick(m.selected, &m));
			display(m);
        }
		
		usleep(16667);
    }
    for(int i = 0; i<m.nbr; i++){
        free(m.buttons[i].label);
    }
    free(m.buttons);
    free(m.title);
}
