#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>
#include "utils.h"

void init_ncurses();
bool case_disponible(int grille[20][10], int x, int y);
void cadre(int xmin, int xmax, int ymin, int ymax);
void affiche_grille(int grille[20][10],gamestate state);
void init_grille(int grille[20][10]);
void affiche_nombre(int n, int source, int y, int x);

#endif
