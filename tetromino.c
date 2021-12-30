#include "tetromino.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "grille.h"
#include "utils.h"
#include <ncurses.h>
#include <stdlib.h>

tetromino tetrominos[7];

/* Initialise le tableau contenant les tetrominos */ 
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
		0
	};
	tetrominos[0] = O;

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
		1
	};
	tetrominos[1] = Z;
	
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
		2
	};
	tetrominos[2] = S;
	
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
		3
	};
	tetrominos[3] = L;
	
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
		4
	};
	tetrominos[4] = J;

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
        5
    };
    tetrominos[5] = T;
    
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
        6
    };
    tetrominos[6] = I;
}
	
/* Efface une case de la grille */
void efface(int grille[20][10], int i, int j){
	grille[i][j] = 0;
}

/* Efface le tetromino en cours de descente */
void efface_tetromino(int grille[20][10], gamestate* p_state){
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
            if(tetrominos[p_state -> block].rotations[p_state->rotation_index][i][j] != 0){
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
            if(tetrominos[p_state->block].rotations[p_state->rotation_index][i][j] != 0){				
				dessine(grille, p_state->y+i, p_state->x+j, tetrominos[p_state->block].rotations[p_state->rotation_index][i][j]);
            }
		}
	}
}

/* Teste la validité de la position du tetromino */
bool mouvement_valide(int grille[20][10], gamestate state){
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
            if(tetrominos[state.block].rotations[state.rotation_index][i][j] != 0){				
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
	temp.rotation_index = (temp.rotation_index + 3)%(tetrominos[temp.block].rotation_max + 1);
		efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;		
	}
	dessine_tetromino(grille, p_state);
}

/* Tourne le tetromino dans le sens indirect (touche p) */
void tourne_indirect(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;
	temp.rotation_index = (temp.rotation_index + 1)%(tetrominos[temp.block].rotation_max + 1);
		efface_tetromino(grille, p_state);
	if(mouvement_valide(grille, temp)){
		*p_state = temp;		
	}
	dessine_tetromino(grille, p_state);
}

/* Fait descendre le tetromino en cours de chute jusqu'à ce qu'il rencontre un obstacle, instantanément et sans interruption */
void descente_instantanee(gamestate* p_state, int grille[20][10]){
	p_state -> descente_instantanee = true;
	return;
}

/* Modifie l'état du jeu pour faire apparaître le tetromino suivant en haut de la grille de jeu
 * Fait monter les autres tetrominos suivants, et génère un nouveau 4ème tetromino suivant
 * Renvoie 0 si le tetromino a pu apparaître et 2 sinon (partie perdue) */
int nouveau_tetromino(gamestate* p_state, int grille[20][10]){
	gamestate temp = *p_state;

	temp.block = temp.suivants[0];
	temp.suivants[0] = temp.suivants[1];
	temp.suivants[1] = temp.suivants[2];
	temp.suivants[2] = temp.suivants[3];
	temp.suivants[3] = (rand() % 7);
	temp.rotation_index = 0;
	temp.x = tetrominos[temp.block].spawn_x;
	temp.y = tetrominos[temp.block].spawn_y;
	temp.reserve_utilisee = false;
	temp.descente_instantanee = false;

	if(mouvement_valide(grille, temp)){
		*p_state = temp;
		dessine_tetromino(grille,p_state);		// Sert à ce que le prochain tetromino soit affiché directement
		return 0;
	}else{
		return 2;
	}
}

/* Agit uniquement si le tetromino en cours de chute ne provient pas lui-même de la réserve
 * Modifie l'état du jeu pour mettre le tetromino en cours de chute dans la réserve, et le remplacer par le tetromino de la réserve
 * Renvoie 0 si le tetromino de la reserve a pu apparaître dans la grille et 2 sinon (partie perdue)*/
int reserve(gamestate* p_state,int grille[20][10]){
	if(!p_state -> reserve_utilisee){
		gamestate temp = *p_state;
		
		efface_tetromino(grille,&temp);
		int bloctmp = temp.block;
		temp.block = temp.reserve;
		temp.reserve = bloctmp;
		temp.rotation_index = 0;
		temp.x = tetrominos[temp.block].spawn_x;
		temp.y = tetrominos[temp.block].spawn_y;
		temp.reserve_utilisee = true;
		
		if(mouvement_valide(grille, temp)){
			*p_state = temp;
			return 0;
		}else{
			return 2;
		}
	}
}

/* Copie le tetromino du gamestate dans la grille de jeu */
void fixe_tetromino(gamestate state, int grille[20][10]){
	for(int i = 0; i <= 3; i++){
		for(int j = 0; j <= 3; j++){
			if(tetrominos[state.block].rotations[state.rotation_index][i][j] != 0){
				grille[state.y + i][state.x + j] = tetrominos[state.block].rotations[state.rotation_index][i][j];
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
