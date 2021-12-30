#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>

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
    //bool descente_instantanee_utilisee;		// TEST
    int compte_ligne;
    int score;
    int niveau;
} gamestate;
void wait(double time);

#endif
