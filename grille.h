#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>

void init_ncurses();
bool case_disponible(int grille[20][10], int x, int y);
void affiche_grille(int grille[20][10]);
void initialise_grille(int grille[20][10]);

#endif
