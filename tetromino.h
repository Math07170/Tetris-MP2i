#ifndef TETROMINO_H
#define TETROMINO_H

#include "utils.h"
#include <stdbool.h>

typedef struct {
    int spawn_x;
    int spawn_y;
    int rotation_max;
    int rotations[4][4][4];
    int id;		// Contient l'indice du tetromino dans le tableau des tetrominos, et non pas la couleur de ses blocs
} tetromino;

void init_tetrominos();
extern tetromino tetrominos[];

bool descente_possible(gamestate* p_state, int grille[20][10]);
void descend(gamestate* p_state, int grille[20][10]);
void deplace_droite(gamestate* state, int grille[20][10]);
void deplace_gauche(gamestate* state, int grille[20][10]);
void tourne_direct(gamestate* p_state, int grille[20][10]);
void tourne_indirect(gamestate* p_state, int grille[20][10]);
void descente_instantanee(gamestate* p_state, int grille[20][10]);
int nouveau_tetromino(gamestate* p_state, int grille[20][10]);
int reserve(gamestate* p_state,int grille[20][10]);
void fixe_tetromino(gamestate state, int grille[20][10]);
int nettoie_lignes(int grille[20][10]);

#endif
