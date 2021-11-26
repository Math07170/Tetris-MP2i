#include "tetromino.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "grille.h"
#include "utils.h"
#include <ncurses.h>
tetromino tab[7];

/* Initialise le tableau tab */ 
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
        1,
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
        },
        7
    };
    tab[6] = I;
    
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
		},
		3
	};
	tab[2] = S;
	
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
		},
		2
	};
	tab[1] = Z;
	
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
		},
		1
	};
	tab[0] = O;
}
/* Efface une case de la grille */
void efface(int grille[20][10], int i, int j){
	grille[i][j] = 0;
}
/* Efface le tetromino en cours de descente */
void efface_tetromino(int grille[20][10], gamestate* p_state){
	for(int i =4; i>=0; i--){
		for(int j = 4; j>=0; j--){
            if(tab[p_state->block-1].rotations[p_state->rotation_index][i][j] != 0){
				efface(grille, p_state->y+i, p_state->x+j);
            }
		}
		
	}
}

/* Dessine sur une case de la grille */ 
void dessine(int grille[20][10], int i, int j, int block){
	grille[i][j] = block;
}
/* Affiche le tetromino en cours de descente */
void dessine_tetromino(int grille[20][10], gamestate* p_state){
	for(int i =4; i>=0; i--){
		for(int j = 4; j>=0; j--){
            if(tab[p_state->block-1].rotations[p_state->rotation_index][i][j] != 0){				
				dessine(grille, p_state->y+i, p_state->x+j, p_state->block);
            }
		}
	}
}

/* Teste la validité d'une position */
bool mouvement_valide(int grille[20][10], gamestate state){
	for(int i =4; i>=0; i--){
		for(int j = 4; j>=0; j--){
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

void descend(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.y++;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;
	}
	else{
		/* TODO : Arrêt du block spawn d'un nouveau */
	}
	dessine_tetromino(grille, p_state);	

	
}
/* Déplace le tetromino vers la droite */
void deplace_droite(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.x++;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;
		
	}
	dessine_tetromino(grille, p_state);
}

/* Déplace le tetromino vers la gauche */
void deplace_gauche(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.x--;
	efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;
		
	}
	dessine_tetromino(grille, p_state);
}

/* Tourne le tetromino dans le sens horaire */
void tourne_horaire(gamestate* p_state, int grille[20][10]){

}

/* Tourne le tetromino dans le sens anti horaire */
void tourne_antihorraire(gamestate* p_state, int grille[20][10]){

}

