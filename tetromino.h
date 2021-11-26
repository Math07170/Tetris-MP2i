#ifndef TETROMINO_H
#define TETROMINO_H
#include "utils.h"


typedef struct {
    int spawn_x;
    int spawn_y;
    int rotation_max;
    int rotations[4][4][4];
    int id;
} tetromino;

void init_tetrominos();

extern tetromino tab[];

void descend(gamestate* state, int grille[20][10]);
void deplace_droite(gamestate* state, int grille[20][10]);
#endif
