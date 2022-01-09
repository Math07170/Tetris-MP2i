#ifndef MENU_GESTION_H
#define MENU_GESTION_H

#include <stdbool.h>

typedef struct {
    char* label;
    int x;
    int y;
    int id;
    void (*onclick)(int, void*);
} button;

typedef struct{
    int nbr;
    int nbr_max;
    char* title;
    int x;
    int y;
    button* buttons;
    int selected;
} menu;

void menuloop(menu m);
void display(menu m);
void addbutton(menu* m, int x, int y, char* label, void (*onclick)(int, void*));
void setlabel(button* b, char* label);
menu createMenu(char* title, int nb_button, int x, int y);
#endif