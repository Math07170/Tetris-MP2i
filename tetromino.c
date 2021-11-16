#include "tetromino.h"
#include <stdio.h>
#include "utils.h"

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

/* Efface le tetromino en cours de descente */
void efface(gamestate state, int grille[20][10]){
    for(int i =0; i<4; i++){
		for(int j = 0; j<4; j++){
            if(tab[state.block-1].rotations[state.rotation_index][i][j] != 0){
                grille[state.y+i][state.x+j] = 0;
            }
		}
	}
}

/* Affiche le tetromino en cours de descente */
void dessine(gamestate state, int grille[20][10]){
    for(int i =0; i<4; i++){
		for(int j = 0; j<4; j++){
            if(tab[state.block-1].rotations[state.rotation_index][i][j] != 0){
                grille[state.y+i][state.x+j] = state.block;
            }
		}
	}
}
