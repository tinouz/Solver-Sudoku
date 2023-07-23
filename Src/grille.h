#ifndef DEF_GRILLE
#define DEF_GRILLE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "case.h"


typedef struct
{
	T_case grille[81] ; /*vecteur de 81 cases*/
} T_sudoku ;



/* Saisie manuelle des valeurs du plateau */
void saisie_grille(T_sudoku* plateau);

/* -1 pour afficher le plateau normal ou 0 <= num_modif >= 80 pour avoir le numéro de case coloré */
void affichage_grille(T_sudoku plateau, int num_modif, int miss);

/* Remplit toutes les cases à "0" */
void mise_a_zero(T_sudoku* plateau);

/* Rajoute les candidats possibles aux cases vide */
void ajout_candidat_dans_grille(T_sudoku* plateau, T_case* c, int i);

/* true => grille complète */
bool grille_resolue(T_sudoku plateau); 


bool present_sur_ligne(T_sudoku plateau, int num_ligne, int chiffre);


bool present_sur_colone(T_sudoku plateau, int colone, int chiffre);


bool present_sur_region(T_sudoku plateau, int li_HG, int co_HG, int chiffre);

#endif