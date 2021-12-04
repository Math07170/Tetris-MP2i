#include "utils.h"
#include <unistd.h>
#include <stdio.h>

/* Permet d'attendre un temps donné */
void wait(double towait){
    time_t end = time(NULL) + towait;
    time_t current = time(NULL);
    while(difftime(end,current) >= 0.0){
        usleep( (difftime(end, current) * (5.0 / 100.0))/(1000000) );
        current = time(NULL);
	}
}
