#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grille.h"


/* modif => true si un candidat est unique et choisi  */
/* modloc => true si un candidat est unique et choisi */
void R1 (T_case* c, bool* modif, bool* modloc);


/* modif => true si éléminination de candidat(s) */
void R2 (T_sudoku* plateau, T_case* c, int numero_case, bool* modif);


/* modif => true si un candidat est choisit parmi plusieurs  */
/* modloc => true si un candidat est choisit parmi plusieurs */
void R3 (T_sudoku* plateau, T_case* c, int numero_case, bool* modif, bool* modloc);


/* modif => true si éléminination de candidat(s) */
void R4 (T_sudoku* plateau, T_case* c, int numero_case, bool* modif);


/* modif => true si éléminination de candidat(s) */
void R5 (T_sudoku* plateau, bool* modif);




/* ------------------------------------------R2-------------------------------------------- */

/* Vérifie si un candidat peut être éliminé en regardant la ligne de la case */
/* modif_ligne => true si un candidat est éliminé 							 */
void check_ligne(T_sudoku* plateau, T_case* c, int indice_ligne, bool* modif_ligne);


/* Vérifie si un candidat peut être éliminé en regardant la colone de la case */
/* modif_colone => true si un candidat est éliminé 							  */
void check_colone(T_sudoku* plateau, T_case * c, int indice_colone, bool* modif_colone);


/* Vérifie si un candidat peut être éliminé en regardant la région de la case */
/* modif_region => true si un candidat est éliminé 							  */
void check_region(T_sudoku* plateau, T_case* c, int indice_ligne_HG, int indice_colone_HG, bool* modif_region);




/* ------------------------------------------R3-------------------------------------------- */

/* Vérifie si un candidat peut être éliminé en regardant les candidats des autres cases de la ligne */
/* modif_ligne => true si un candidat est éliminé 												    */
void check_ligne_candidats(T_sudoku* plateau, T_case * c, int indice_ligne, bool* modif_ligne);


/* Vérifie si un candidat peut être éliminé en regardant les candidats des autres cases de la colone */
/* modif_colone => true si un candidat est éliminé 												     */
void check_colone_candidats(T_sudoku* plateau, T_case * c, int indice_colone, bool* modif_colone);


/* Vérifie si un candidat peut être éliminé en regardant les candidats des autres cases de la région */
/* modif_region => true si un candidat est éliminé 												     */
void check_region_candidats(T_sudoku* plateau, T_case* c, int indice_ligne_HG, int indice_colone_HG, bool* modif_region);




/* ------------------------------------------R4-------------------------------------------- */

/* Technique R4 avec les régions prisent en ligne  												*/
/* modif_region => true si un candidat est éliminé sur une ligne et hors de la région de départ */
void R4_ligne (T_sudoku* plateau, T_case* c, int num_region, int indice_ligne_HG, int indice_colone_HG, bool* modif_region);


/* Technique R4 avec les régions prisent en colone  										  */
/* modif_region => true si un candidat est éliminé sur une colone et hors la région de départ */
void R4_colone (T_sudoku* plateau, T_case* c, int num_region, int indice_ligne_HG, int indice_colone_HG, bool* modif_region);




/* ------------------------------------------R5-------------------------------------------- */

/* modif = true => Si au moins un candidat est éliminé */
void colone_ligne(T_sudoku* plateau, bool* modif);


/* modif = true => Si au moins un candidat est éliminé */
void ligne_colone(T_sudoku* plateau, bool* modif);


/* modif = true => Si au moins un candidat est éliminé */
void ligne_region(T_sudoku* plateau, bool* modif);


/* modif = true => Si au moins un candidat est éliminé */
void colone_region(T_sudoku* plateau, bool* modif);


/* modif = true => Si au moins un candidat est éliminé */
void region_ligne(T_sudoku* plateau, bool* modif);


/* modif = true => Si au moins un candidat est éliminé */
void region_colone(T_sudoku* plateau, bool* modif);




/* ---------------------------------Recherche exhaustive----------------------------------- */

/* fonction réscursive qui résout le Sudoku exhaustivement */
bool recherche_exhaustive(T_sudoku* plateau, int position);






