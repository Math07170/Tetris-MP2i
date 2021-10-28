#ifndef UTILS_H
#define UTILS_H

#include <time.h>

typedef struct {
    int spawn_x;
    int spawn_y;
    int rotation_max;
    int rotations[4][4][4];
    int id;
} tetromino;

void wait(double time);
void init_tetrominos();

typedef struct {
    int block;
    int rotation_index;
    int x;
    int y;
    float game_speed;
} gamestate;

extern tetromino tab[];

#endif