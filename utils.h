#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void wait(double time);
typedef struct tetrominos {
    int spawn_x;
    int spawn_y;
    int rotation_max;
    int rotations[9][4][4];
    int id;
} tetromino;

typedef struct gamestates{
    int block;
    int rotation_index;
    int x;
    int y;
    float game_speed;
} gamestate;
extern tetromino I;

#endif