#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "menu_gestion.h"

void addbutton(menu* m, int x, int y, char* label, void (*onclick)(int, void*)){
	m->nbr++;
	button b;
	b.x = x;
	b.y = y;
	b.label = label;
	b.onclick = onclick;
	b.id = m->nbr-1;
	m->buttons[m->nbr-1] = b;
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
}
