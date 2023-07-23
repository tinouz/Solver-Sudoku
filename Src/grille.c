#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "grille.h"
#include "annexe.h"

void saisie_grille(T_sudoku* plateau){
	printf("Rentrer les valeurs en suivant la numérotation des cases\n");
	for (int i = 0; i < 81; ++i)
	{
		printf("Case %i:  ", i);
		scanf("%d", &(plateau->grille[i].val));
	}
};


void affichage_grille(T_sudoku plateau, int num_modif, int miss){
	
	if(miss != 1)
	{
		couleur(magenta);
		printf(" -----------------------\n");
		couleur(cyan);
		printf("| ");
		couleur(blanc);
		
		for (int i = 0; i < 81; ++i)
		{
			couleur(cyan);
			if(i%9 == 0 && i != 0)
				printf("|\n| ");

			if((i%9 == 3) || (i%9 == 6)) 
				printf("| ");
			couleur(blanc);
			
			if(i == num_modif)
			{
				couleur(bleu);
				printf("%d ",plateau.grille[i].val);
				couleur(blanc);
			}
			else
			{
				couleur(jaune);
				printf("%d ",plateau.grille[i].val);
				couleur(blanc);
			}

			
			if(i == 26 || i == 53)
			{
				couleur(cyan);
				printf("|");	
				printf("\n|");
				couleur(magenta);
				printf("-----------------------");
				couleur(blanc);
			}
			
		}

		couleur(cyan);
		printf("| ");
		couleur(magenta);
		printf("\n -----------------------\n");
		couleur(blanc);
		printf("\n");
	}
	else
	{
		couleur(magenta);
		printf(" -----------------------\n");
		couleur(cyan);
		printf("| ");
		couleur(blanc);
		
		for (int i = 0; i < 81; ++i)
		{
			couleur(cyan);
			if(i%9 == 0 && i != 0)
				printf("|\n| ");

			if((i%9 == 3) || (i%9 == 6)) 
				printf("| ");
			couleur(blanc);
			
			if(plateau.grille[i].val == 0)
			{
				couleur(bleu);
				printf("%d ",plateau.grille[i].val);
				couleur(blanc);
			}
			else
			{
				couleur(jaune);
				printf("%d ",plateau.grille[i].val);
				couleur(blanc);
			}

			
			if(i == 26 || i == 53)
			{
				couleur(cyan);
				printf("|");	
				printf("\n|");
				couleur(magenta);
				printf("-----------------------");
				couleur(blanc);
			}
			
		}

		couleur(cyan);
		printf("| ");
		couleur(magenta);
		printf("\n -----------------------\n");
		couleur(blanc);
		printf("\n");
	}
};


void mise_a_zero(T_sudoku* plateau){
	for (int i = 0; i < 81; ++i)
	{
		plateau->grille[i].val = 0;
		plateau->grille[i].n_candidats = 0;
	}
};

void ajout_candidat_dans_grille(T_sudoku* plateau, T_case* c, int i){

		if (plateau->grille[i].val == 0)
			for (int j = 1; j <= 9; ++j)
			{
				 c->candidats[c->n_candidats] = j;
				c->n_candidats++; 
			} 
		else
			c->n_candidats = 0;
};

bool grille_resolue(T_sudoku plateau){
	bool resolue = true;
	for (int i = 0; i < 81; ++i)
		if(plateau.grille[i].val == 0)
			return false;
	return resolue;
};

bool present_sur_ligne(T_sudoku plateau, int num_ligne, int chiffre){

	int num_case;
	for (int i = 0; i < 9; ++i)
	{
		num_case = numero_case(num_ligne, i);
		if(plateau.grille[num_case].val == chiffre)
			return true;
	}
	return false;
};

bool present_sur_colone(T_sudoku plateau, int num_colone, int chiffre){

	int num_case;
	for (int i = 0; i < 9; ++i)
	{
		num_case = numero_case(i, num_colone);
		if(plateau.grille[num_case].val == chiffre)
			return true;
	}
	return false;
};

bool present_sur_region(T_sudoku plateau, int li_HG, int co_HG, int chiffre){

	int id_ligne_max = li_HG + 2;
	int id_colone_max = co_HG + 2;
	int num_case;

	for (int i = li_HG; i <= id_ligne_max; ++i)
	{
		for (int j = co_HG;  j <= id_colone_max; ++j)
		{
			num_case = numero_case(i, j);
			if(plateau.grille[num_case].val == chiffre)
				return true;
		}
	}
	return false;
};


