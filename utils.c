#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void wait(unsigned int towait){
    clock_t end = time(NULL) + towait;
    clock_t current = time(NULL);

    while(difftime(current,end)<=0){
        sleep( difftime(end, current) *(99.0/100.0) );
        current = time(NULL);
    }

}