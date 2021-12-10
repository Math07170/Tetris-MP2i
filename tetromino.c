#include "tetromino.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "grille.h"
#include "utils.h"
#include <ncurses.h>
#include <stdlib.h>

tetromino tab[7];

/* Initialise le tableau tab */ 
void init_tetrominos(){
	
	tetromino O = {
		3,
		0,
		0,
		{
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0}
			},
			{
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
			{
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
		},
		1
	};
	tab[0] = O;

	tetromino Z = {
		3,
		0,
		1,
		{
			{
				{0,0,0,0},
				{2,2,0,0},
				{0,2,2,0},
				{0,0,0,0}
			},
			{
				{0,2,0,0},
				{2,2,0,0},
				{2,0,0,0},
				{0,0,0,0}
			},
			{
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
		},
		2
	};
	tab[1] = Z;
	
	tetromino S = {
		3,
		0,
		1,
		{
			{
				{0,0,0,0},
				{0,3,3,0},
				{3,3,0,0},
				{0,0,0,0}
			},
			{
				{3,0,0,0},
				{3,3,0,0},
				{0,3,0,0},
				{0,0,0,0}
			},
			{
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
		},
		3
	};
	tab[2] = S;
	
	tetromino L = {
		3,
		0,
		3,
		{
			{
				{0,0,0,0},
				{4,4,4,0},
				{4,0,0,0},
				{0,0,0,0}
			},
			{
				{4,4,0,0},
				{0,4,0,0},
				{0,4,0,0},
				{0,0,0,0}
			},
			{
				{0,0,4,0},
				{4,4,4,0},
				{0,0,0,0},
				{0,0,0,0}
			},
			{
				{0,4,0,0},
				{0,4,0,0},
				{0,4,4,0},
				{0,0,0,0}
			},
		},
		4
	};
	tab[3] = L;
	
	tetromino J = {
		3,
		0,
		3,
		{
			{
				{0,0,0,0},
				{5,5,5,0},
				{0,0,5,0},
				{0,0,0,0}
			},
			{
				{0,5,0,0},
				{0,5,0,0},
				{5,5,0,0},
				{0,0,0,0}
			},
			{
				{5,0,0,0},
				{5,5,5,0},
				{0,0,0,0},
				{0,0,0,0}
			},
			{
				{0,5,5,0},
				{0,5,0,0},
				{0,5,0,0},
				{0,0,0,0}
			}
		},
		5
	};
	tab[4] = J;

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
                {0,6,0,0},
                {6,6,6,0},
                {0,0,0,0},
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
        1,
        {
            {
                {0,0,0,0},
                {7,7,7,7},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,7,0,0},
                {0,7,0,0},
                {0,7,0,0},
                {0,7,0,0}
            },
            {
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},		// Placeholder, sert à tester les rotations
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            },
        },
        7
    };
    tab[6] = I;
}
	
/* Efface une case de la grille */
void efface(int grille[20][10], int i, int j){
	grille[i][j] = 0;
}

/* Efface le tetromino en cours de descente */
void efface_tetromino(int grille[20][10], gamestate* p_state){
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
            if(tab[p_state -> block-1].rotations[p_state->rotation_index][i][j] != 0){
				efface(grille, p_state -> y+i, p_state -> x+j);
            }
		}
		
	}
}

/* Dessine sur une case de la grille */ 
void dessine(int grille[20][10], int i, int j, int bloc){
	grille[i][j] = bloc;
}

/* Affiche le tetromino en cours de descente */
void dessine_tetromino(int grille[20][10], gamestate* p_state){
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
            if(tab[p_state->block-1].rotations[p_state->rotation_index][i][j] != 0){				
				dessine(grille, p_state->y+i, p_state->x+j, p_state->block);
            }
		}
	}
}

/* Teste la validité de la position du tetromino */
bool mouvement_valide(int grille[20][10], gamestate state){
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
            if(tab[state.block-1].rotations[state.rotation_index][i][j] != 0){				
				if(case_disponible(grille, state.y+i, state.x+j) == true){
					continue;
				} 
				else{
					return(false);	
				}
            }
		}
	}
	return true;
}

/* Renvoie true si le tetromino peut descendre */
bool descente_possible(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.y++;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		return true;
	}else{
		return false;
	}
}

/* Fait descendre le tetromino, si c'est possible */
void descend(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.y++;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;
		dessine_tetromino(grille, p_state);
	}
	return;
}

/* Déplace le tetromino vers la droite (touche q) */
void deplace_droite(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.x++;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;		
	}
	dessine_tetromino(grille, p_state);
}

/* Déplace le tetromino vers la gauche (touche d) */
void deplace_gauche(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.x--;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;		
	}
	dessine_tetromino(grille, p_state);
}

/* Tourne le tetromino dans le sens direct (touche l) */
void tourne_direct(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.rotation_index = (temp.rotation_index + 3)%(tab[temp.block - 1].rotation_max + 1);
		efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;		
	}
	dessine_tetromino(grille, p_state);
}

/* Tourne le tetromino dans le sens indirect (touche p) */
void tourne_indirect(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.rotation_index = (temp.rotation_index + 1)%(tab[temp.block - 1].rotation_max + 1);
		efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;		
	}
	dessine_tetromino(grille, p_state);
}

/* Modifie l'état du jeu pour faire apparaître un tetromino aléatoire en haut de la grille de jeu
 * Renvoie 0 si le tetromino a pu apparaître et 2 sinon (partie perdue) */
int nouveau_tetromino(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;

	temp.block = (rand() % 7) + 1;
	temp.rotation_index = 0;
	temp.x = tab[temp.block-1].spawn_x;
	temp.y = tab[temp.block-1].spawn_y;

	if(mouvement_valide(grille, temp)){
		*p_state = temp;
		return 0;
	}else{
		return 2;
	}
}

/* Copie le tetromino du gamestate dans la grille de jeu */
void fixe_tetromino(gamestate state, int grille[20][10]){
	for(int i = 0; i <= 3; i++){
		for(int j = 0; j <= 3; j++){
			if(tab[state.block - 1].rotations[state.rotation_index][i][j] != 0){
				grille[state.y + i][state.x + j] = tab[state.block - 1].rotations[state.rotation_index][i][j];
			}
		}
	}
	return;
}

/* Vérifie toutes les lignes de la grille, supprime celles qui sont pleines et renvoie le nombre de lignes supprimées */
int nettoie_lignes(int grille[20][10]){
	bool ligne_pleine;
	int lignes_supprimees = 0;
	for(int i = 0; i < 20; i++){			// Pour toutes les lignes de la grille, de haut en bas...
		ligne_pleine = true;
		for(int j = 0; j < 10; j++){			// ...vérifie si la ligne est pleine...
			if(grille[i][j] == 0){
				ligne_pleine = false;
			}
		}
		if(ligne_pleine == true){			// ...et si oui, la supprime en faisant descendre d'une ligne les lignes supérieures
			lignes_supprimees++;
			for(int k = i; k > 0; k--){
				for(int l = 0; l < 10; l++){
					grille[k][l] = grille[k - 1][l];
				}
			}
		}
	}
	return lignes_supprimees;
}
