#ifndef TETROMINO_H
#define TETROMINO_H

#include "utils.h"
#include <stdbool.h>

typedef struct {
    int spawn_x;
    int spawn_y;
    int rotation_max;
    int rotations[4][4][4];
    int id;
} tetromino;

void init_tetrominos();
extern tetromino tab[];

bool descente_possible(gamestate* p_state, int grille[20][10]);
void descend(gamestate* state, int grille[20][10]);
void deplace_droite(gamestate* state, int grille[20][10]);
void deplace_gauche(gamestate* state, int grille[20][10]);
void tourne_direct(gamestate* p_state, int grille[20][10]);
void tourne_indirect(gamestate* p_state, int grille[20][10]);
void nouveau_tetromino(gamestate* p_state);
void fixe_tetromino(gamestate state, int grille[20][10]);
int nettoie_lignes(int grille[20][10]);

#endif
