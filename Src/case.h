#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int val ; /* Valeur de la case (0 si vide)*/
	int n_candidats ; /* Nombre de candidats possibles */ 
	int candidats[9] ; /* Liste de candidats */
} T_case;


/* Supprime les "trous = 0" dans le tableau des candidats */
void decalage_candidat(T_case * c); 


/* PE  : (0 < N ≤ 9) ∧ T[0..N-1] ∧ ∀I, 0 ≤ I < N-1, T[I] < T[I+1] */
/* INV : (0 ≤ i < N) ∧ (i != N-1)								  */
/* PS  : (0 ≤ p ≤ N-1) ∧ ∃p, (T[p] == X → p) ∨ (T[p] != X → N)    */ 
int recherche_dans_tableau(int* t, int n, int v);


/* PE  : (0 < N ≤ 9) ∧ T[0..N-1] ∧ ∀I, 0 ≤ I < N-1, T[I] < T[I+1] */
/* INV : (0 ≤ i < N) ∧ (T[i] != X)							      */
/* PS  : (0 ≤ p ≤ N-1) ∧ ∃p, (T[p] == X) → (T[p] = 0)             */
void suppression_dans_tableau(int* t, int n, int v);


/* PE: 0 ≤  X < 9 										     */
/* PS: (0 ≤  S < 9) ʌ S = 3*(X/3) ʌ 0 ≤  T < 9 ʌ T = 3*(X%3) */
void coordonnees_case_HG(int region, int* lig, int* col); 


/* PE: (0 ≤  X < 9) ʌ (0 ≤  Y < 9) */
/* PS: S = 3*(X/3)+(Y/3)		   */
int numero_region(int lig, int col);	


/* PE: (0 ≤  X < 9) ʌ (0 ≤  Y < 9) */
/* PS: S = 9*X + Y				   */
int numero_case(int lig, int col);		


/* PE: 0 ≤  X < 81 */
/* PS: S = X/9	   */
int indice_ligne(int numero_case);		


/* PE: 0 ≤  X < 81 */
/* PS: S = X%9	   */
int indice_colone(int numero_case);
