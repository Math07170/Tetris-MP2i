#include "utils.h"
#include <unistd.h>
#include <stdio.h>

tetromino tab[7];
void init_tetrominos(){


    tetromino T = {
        3,
        0,
        3,
        {
            {
                {0,0,0,0},
                {6,6,6,0},
                {0,6,0,0},
                {0,0,0,0}
            },
            {
                {0,6,0,0},
                {6,6,0,0},
                {0,6,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,6,0,0},
                {6,6,6,0},
                {0,0,0,0}
            },
            {
                {0,6,0,0},
                {0,6,6,0},
                {0,6,0,0},
                {0,0,0,0}
            }

        },
        6
    };
    tab[5] = T;
    tetromino I = {
        3,
        0,
        2,
        {
            {
                {0,0,0,0},
                {7,7,7,7},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,7,0},
                {0,0,7,0},
                {0,0,7,0},
                {0,0,7,0}
            },
            {
                {0,0,0,0},
                {7,7,7,7},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,7,0},
                {0,0,7,0},
                {0,0,7,0},
                {0,0,7,0}
            }
        },
        1
    };
    tab[6]=I;
}


void wait(double towait){
    clock_t end = time(NULL) + towait;
    clock_t current = time(NULL);
    while(difftime(end,current)>=0.0){
        sleep( difftime(end, current) *(99.0/100.0) );
        current = time(NULL);
    }

}