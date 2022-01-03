#include <stdlib.h>
#include <ncurses.h>
#include "menus.c"


void menuloop(menu m){
    int running = 1;
    while(running == 1){
        char input = getch();
        if(input == KEY_UP){
            if(m.selected > 0) m.selected --;
        }
        if(input = KEY_DOWN){
            if(m.selected < m.nbr) m.selected ++;
        }
        if(input == KEY_ENTER){
            m.buttons[m.selected].onclick(m.selected);
        }
    }
}