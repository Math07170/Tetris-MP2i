#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void wait(double time);

typedef struct {
    int block;
    int rotation_index;
    int x;
    int y;
    float game_speed;
} gamestate;

#endif
