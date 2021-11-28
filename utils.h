#ifndef UTILS_H
#define UTILS_H

#include <time.h>

typedef struct {
    int block;
    int rotation_index;
    int x;
    int y;
    float game_speed;
} gamestate;

void wait(double time);

#endif
