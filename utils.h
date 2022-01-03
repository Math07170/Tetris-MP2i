#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>

typedef struct {
    char descente_rapide;
    char descente_instantanee;
    char reserve;
    char gauche;
    char droite;
    char tourne_direct;
    char tourne_indirect;   
} keybind;

typedef struct {
    int block;
    int rotation_index;
    int x;
    int y;
    int game_speed;
    bool reserve_utilisee;
    int reserve;
    int suivants[4];
    int statut;
    bool descente_rapide;
    int compte_ligne;
    int score;
    int niveau;
} gamestate;

//void wait(double time);	?
void save_config(keybind tosave);
keybind load_config();
void init_gamestate(gamestate* p_state);
void change_niveau(gamestate* p_state);
void augmente_score(gamestate* p_state, int nbligne);
void suivant(gamestate* p_state,int grille[20][10]);

#endif
