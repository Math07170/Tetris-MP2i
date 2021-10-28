#ifndef TETROMINO_H
#define TETROMINO_H


typedef struct {
    int spawn_x;
    int spawn_y;
    int rotation_max;
    int rotations[4][4][4];
    int id;
} tetromino;

void init_tetrominos();

extern tetromino tab[];
#endif