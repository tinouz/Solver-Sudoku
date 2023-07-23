#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "case.h"
#include "annexe.h"

void decalage_candidat(T_case * c){
	for (int i = 0; i < 9; i++)
	{
		if(c->candidats[i] == 0)
		{
			int next = 0;
			for (int j = i+1; j < 9; ++j)
			{
				if(c->candidats[j] != 0)
				{
					next = c->candidats[j];
					c->candidats[j] = 0;
					break;
				}
			}
			c->candidats[i] = next;
		}
	}
};

int recherche_dans_tableau(int* t, int n, int v){
	for (int i = 0; i < n; ++i)
		if(t[i] == v)
			return i;
	return n;
};

void suppression_dans_tableau(int* t, int n, int v){
	for (int i = 0; i < n; ++i)
	{
		if(t[i] == v)
		{
			t[i] = 0;
			break;
		}
	}
};


void coordonnees_case_HG(int region, int* lig, int* col){
	assert(region >= 0 && region <= 8);
	*lig = 3*(region/3);
	*col = 3*(region%3);
};

int numero_region(int lig, int col){
	assert(lig >= 0 && lig <= 8);
	assert(col >= 0 && col <= 8);
	return(3*(lig/3)+(col/3));
};


int numero_case(int lig, int col){
	assert(lig >= 0 && lig <= 8);
	assert(col >= 0 && col <= 8);
	return(9*lig + col);
};


int indice_ligne(int numero_case){
	assert(numero_case >= 0 && numero_case <= 80);
	return(numero_case/9);
};

int indice_colone(int numero_case){
	assert(numero_case >= 0 && numero_case <= 80);
	return(numero_case%9);
};