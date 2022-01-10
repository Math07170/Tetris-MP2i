#ifndef MENU_GESTION_H
#define MENU_GESTION_H

#include <stdbool.h>

//Structure boutton contient les informations relative au boutton
typedef struct {
    char* label;
    int x;
    int y;
    int id;
    void (*onclick)(int, void*);
} button;

//Structure textbox contient les infos relative à une zone de texte
typedef struct {
    char* text;
    int x;
    int y;
    int id;
}textbox; 


//Structure menu contient toutes les infos du menu
typedef struct{
    int nbr; // nombre de boutton du menu
    int nbr_text; // nombre de textbox du menu
    int nbr_max; // nombre de boutton max du menu
    int nbr_max_text; // nombre de textbox max du menu
    char* title; // titre du menu
    int x; // emplacement en x du titre
    int y; // emplacement en y du titre
    button* buttons; // tableau contenant l'intégralité des bouttons
    textbox* texts; // tableau contenantt l'intégralité des textbox
    int selected; // indice du boutton actuellement séléctionné
} menu;

void menuloop(menu m);
void display(menu m);
void addbutton(menu* m, int x, int y, char* label, void (*onclick)(int, void*));
void setlabel(button* b, char* label);
menu createMenu(char* title, int nb_button, int nb_textbox, int x, int y);
void addTextbox(menu* m, int x, int y, char* text);
#endif