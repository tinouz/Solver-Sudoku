#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "regles.h"
#include "annexe.h"

void R1 (T_case * c, bool* modif, bool* modloc){
	
	if(c->n_candidats == 1)
	{
		c->val = c->candidats[0];
		c->candidats[0] = 0;
		c->n_candidats = 0;
		*modif = true;
		*modloc = true;
	}
};

void check_ligne(T_sudoku* plateau, T_case * c, int indice_ligne, bool* modif_ligne){
	
	int occ, num_case;
	for (int indice_colone = 0; indice_colone < 9; ++indice_colone)
	{
		num_case = numero_case(indice_ligne, indice_colone);
		occ = recherche_dans_tableau(&c->candidats[0], c->n_candidats, plateau->grille[num_case].val);
			
			// Si valeur présente sur ligne et dans liste candidats
			if (occ != c->n_candidats)
			{	
				suppression_dans_tableau(&c->candidats[0], c->n_candidats, plateau->grille[num_case].val);
				decalage_candidat(c);
				c->n_candidats--;
				*modif_ligne = true; 
			}
	}
};

void check_ligne_candidats(T_sudoku* plateau, T_case * c, int indice_ligne, bool* modif_ligne){
	
	int occ, num_case;
	bool deja_present;

	// On teste pour chaque candidat de la case en paramètre
	for (int cdt = 0; cdt < c->n_candidats; ++cdt)
	{
		deja_present = false;
		occ = c->candidats[cdt];
		int nb_apparition = 0;
		deja_present = present_sur_ligne(*plateau, indice_ligne, occ);
		
		// Valeur non présente sur la ligne
		if(!deja_present)
		{
			for (int indice_colone = 0; indice_colone < 9; ++indice_colone)
			{
				num_case = numero_case(indice_ligne, indice_colone);
				
				// Comptage d'apparition sur la ligne
				if(recherche_dans_tableau(&plateau->grille[num_case].candidats[0], plateau->grille[num_case].n_candidats, occ) !=  plateau->grille[num_case].n_candidats)
					nb_apparition++;
				if(nb_apparition > 1)
					break;
			}
		}

		// Un candidat n'apparait qu'une seule fois dans la ligne
		if(nb_apparition < 2 && !deja_present)
		{
			c->val = occ;
			c->n_candidats = 0;
			*modif_ligne = true;
			break;
		}
	}	
};


void check_colone(T_sudoku* plateau, T_case * c, int indice_colone, bool* modif_colone){
	
	int occ, num_case;
	for (int indice_ligne = 0; indice_ligne < 9; ++indice_ligne)
	{
		num_case = numero_case(indice_ligne, indice_colone);
		occ = recherche_dans_tableau(&c->candidats[0], c->n_candidats, plateau->grille[num_case].val);
			
			// Si valeur présente sur colone et dans liste candidats
			if (occ != c->n_candidats)
			{	
				suppression_dans_tableau(&c->candidats[0], c->n_candidats, plateau->grille[num_case].val);
				decalage_candidat(c);
				c->n_candidats--;
				*modif_colone = true;
			}
	}
};


void check_colone_candidats(T_sudoku* plateau, T_case * c, int indice_colone, bool* modif_colone){
	
	int occ, num_case;
	bool deja_present;

	// On teste pour chaque candidat de la case en paramètre
	for (int cdt = 0; cdt < c->n_candidats; ++cdt)
	{
		deja_present = false;
		occ = c->candidats[cdt];
		int nb_apparition = 0;

		deja_present = present_sur_colone(*plateau, indice_colone, occ);
		
		// Valeur non présente sur la colone
		if(!deja_present)
		{
			for (int indice_ligne = 0; indice_ligne < 9; ++indice_ligne)
			{
				num_case = numero_case(indice_ligne, indice_colone);
				
				// Comptage d'apparition sur la colone
				if(recherche_dans_tableau(&plateau->grille[num_case].candidats[0], plateau->grille[num_case].n_candidats, occ) !=  plateau->grille[num_case].n_candidats)
					nb_apparition++;
				if(nb_apparition > 1)
					break;
			}
		}

		// Un candidat n'apparait qu'une seule fois dans la colone
		if(nb_apparition < 2 && !deja_present)
		{
			c->val = occ;
			c->n_candidats = 0;
			*modif_colone = true;
			break;
		}
	}	
};


void check_region(T_sudoku* plateau, T_case* c, int indice_ligne_HG, int indice_colone_HG, bool* modif_region){

	int id_ligne_max = indice_ligne_HG + 2;
	int id_colone_max = indice_colone_HG + 2;
	int occ, num_case;

	for (int i = indice_ligne_HG; i <= id_ligne_max; ++i)
	{
		for (int j = indice_colone_HG;  j <= id_colone_max; ++j)
		{
			num_case = numero_case(i,j);
			occ = recherche_dans_tableau(&c->candidats[0], c->n_candidats, plateau->grille[num_case].val);
			
			// Si valeur présente sur région et dans liste candidats
			if (occ != c->n_candidats)
			{	
				suppression_dans_tableau(c->candidats, c->n_candidats, plateau->grille[num_case].val);
				decalage_candidat(c);
				c->n_candidats--;
				*modif_region = true; 
			}
		}
	}

};

void check_region_candidats(T_sudoku* plateau, T_case* c, int indice_ligne_HG, int indice_colone_HG, bool* modif_region){

	int id_ligne_max = indice_ligne_HG + 2;
	int id_colone_max = indice_colone_HG + 2;
	
	int occ, num_case;
	bool deja_present;

	// On teste pour chaque candidat de la case en paramètre
	for (int cdt = 0; cdt < c->n_candidats; ++cdt)
	{
		deja_present = false;
		occ = c->candidats[cdt];
		int nb_apparition = 0;

		deja_present = present_sur_region(*plateau, indice_ligne_HG, indice_colone_HG, occ);
		
		// Valeur non présente sur la région
		if(!deja_present)
		{
			for (int i = indice_ligne_HG; i <= id_ligne_max; ++i)
			{
				for (int j = indice_colone_HG;  j <= id_colone_max; ++j)
				{
					num_case = numero_case(i,j);
					
					// Comptage d'apparition sur la région
					if(recherche_dans_tableau(&plateau->grille[num_case].candidats[0], plateau->grille[num_case].n_candidats, occ) !=  plateau->grille[num_case].n_candidats)
						nb_apparition++;
					if(nb_apparition > 1)
						break;
				}
			}
		}
		
		// Un candidat n'apparait qu'une seule fois dans la région
		if(nb_apparition < 2 && !deja_present)
		{
			c->val = occ;
			c->n_candidats = 0;
			*modif_region = true;
			break;
		}
	}
};


void R2 (T_sudoku* plateau, T_case* c, int numero_case, bool* modif){
	
	bool modif_ligne = false;
	bool modif_colone = false;
	bool modif_region = false;
	int lig = indice_ligne(numero_case);
	int col = indice_colone(numero_case);
	int reg = numero_region(lig,col);
	coordonnees_case_HG(reg, &lig, &col);


	check_ligne(plateau, c, indice_ligne(numero_case), &modif_ligne);
	check_colone(plateau, c, indice_colone(numero_case), &modif_colone);
	check_region(plateau, c, lig, col, &modif_region);

	if((modif_ligne) || (modif_colone) || (modif_region))
		*modif = true;
	else
		*modif = false;
};



void R3 (T_sudoku* plateau, T_case* c, int numero_case, bool* modif, bool* modloc){

	bool modif_ligne = false;
	bool modif_colone = false;
	bool modif_region = false;
	int lig = indice_ligne(numero_case);
	int col = indice_colone(numero_case);
	int reg = numero_region(lig,col);
	coordonnees_case_HG(reg, &lig, &col);

	check_ligne_candidats(plateau, c, indice_ligne(numero_case), &modif_ligne);
	check_colone_candidats(plateau, c, indice_colone(numero_case), &modif_colone);
	check_region_candidats(plateau, c, lig, col, &modif_region);

	if((modif_ligne) || (modif_colone) || (modif_region))
	{
		*modif = true;
		*modloc = true;
	}
	else
		*modif = false;
};


void R4_ligne (T_sudoku* plateau, T_case* c, int num_region, int indice_ligne_HG, int indice_colone_HG, bool* modif_region){

	int occ, l1, l2, l3;
	int id_ligne_max = indice_ligne_HG + 2;
	int id_colone_max = indice_colone_HG + 2;

	// Pour tous les candidats de la case en paramètre
	for (int i = 0; i < c->n_candidats; ++i)
	{
		l1 = 0;
		l2 = 0;
		l3 = 0;
		occ = c->candidats[i];
		assert(occ != 0);

		// Exploration de toutes les cases de la région
		for (int j = indice_ligne_HG; j <= id_ligne_max; ++j)
		{
			for (int k = indice_colone_HG;  k <= id_colone_max; ++k)
			{
				// Incrémentation de la ligne contenant le candidat en test 
				if(recherche_dans_tableau(&plateau->grille[numero_case(j,k)].candidats[0], plateau->grille[numero_case(j,k)].n_candidats, occ) != (plateau->grille[numero_case(j,k)].n_candidats) && plateau->grille[numero_case(j,k)].val == 0)
				{
					int ligne_loc = j%3;
					switch(ligne_loc)
					{
						case 0: l1++;
						break;

						case 1: l2++;
						break;

						case 2: l3++;
						break;

						default: break;
					}
				}
			}
		}


		// Candidat présent uniquement dans des cases d'une seule ligne de la région
		if((l1 != 0 && l2 == 0 && l3 == 0) || (l1 == 0 && l2 != 0 && l3 == 0) || (l1 == 0 && l2 == 0 && l3 != 0))
		{
			int ligne_choisie;
			if(l1 != 0)
				ligne_choisie = indice_ligne_HG;
			if(l2 != 0)
				ligne_choisie = indice_ligne_HG + 1;
			if(l3 != 0)
				ligne_choisie = indice_ligne_HG +2;

			for (int id_c = 0; id_c < 9; ++id_c)
			{
				int n_region = numero_region(ligne_choisie, id_c);

				// Suppression des candidats sur la ligne contenant les candidats trouvés mais hors de la région de test
				if(n_region != num_region && plateau->grille[numero_case(ligne_choisie, id_c)].val == 0 && recherche_dans_tableau(&plateau->grille[numero_case(ligne_choisie, id_c)].candidats[0], plateau->grille[numero_case(ligne_choisie, id_c)].n_candidats, occ) != plateau->grille[numero_case(ligne_choisie, id_c)].n_candidats)
				{
					suppression_dans_tableau(&plateau->grille[numero_case(ligne_choisie, id_c)].candidats[0], plateau->grille[numero_case(ligne_choisie, id_c)].n_candidats, occ);
					decalage_candidat(&plateau->grille[numero_case(ligne_choisie, id_c)]);
					plateau->grille[numero_case(ligne_choisie, id_c)].n_candidats--;
					*modif_region = true;
				}  
			}
		}
	}
};

void R4_colone (T_sudoku* plateau, T_case* c, int num_region, int indice_ligne_HG, int indice_colone_HG, bool* modif_region){

	int occ, c1, c2, c3;
	int id_ligne_max = indice_ligne_HG + 2;
	int id_colone_max = indice_colone_HG + 2;

	// Pour tous les candidats de la case en paramètre
	for (int i = 0; i < c->n_candidats; ++i)
	{
		c1 = 0;
		c2 = 0;
		c3 = 0;
		occ = c->candidats[i];
		assert(occ != 0);

		// Exploration de toutes les cases de la région
		for (int j = indice_ligne_HG; j <= id_ligne_max; ++j)
		{
			for (int k = indice_colone_HG;  k <= id_colone_max; ++k)
			{
				// Incrémentation de la ligne contenant le candidat en test 
				if((recherche_dans_tableau(&plateau->grille[numero_case(j,k)].candidats[0],plateau->grille[numero_case(j,k)].n_candidats, occ) != (plateau->grille[numero_case(j,k)].n_candidats) && plateau->grille[numero_case(j,k)].val == 0)) 
				{
					int colone_loc = k%3;
					switch(colone_loc)
					{
						case 0: c1++;
						break;

						case 1: c2++;
						break;

						case 2: c3++;
						break;

						default: break;
					}
				}
			}
		}

		// Candidat présent uniquement dans des cases d'une seule ligne de la région
		if((c1 != 0 && c2 == 0 && c3 == 0) || (c1 == 0 && c2 != 0 && c3 == 0) || (c1 == 0 && c2 == 0 && c3 != 0))
		{
			int colone_choisie;
			if(c1 != 0)
				colone_choisie = indice_colone_HG;
			if(c2 != 0)
				colone_choisie = indice_colone_HG + 1;
			if(c3 != 0)
				colone_choisie = indice_colone_HG +2;

			for (int id_l = 0; id_l < 9; ++id_l)
			{
				int n_region = numero_region(id_l, colone_choisie);

				// Suppression des candidats sur la ligne contenant les candidats trouvés mais hors de la région de test
				if(n_region != num_region && plateau->grille[numero_case(id_l, colone_choisie)].val == 0 && recherche_dans_tableau(&plateau->grille[numero_case(id_l, colone_choisie)].candidats[0], plateau->grille[numero_case(id_l, colone_choisie)].n_candidats, occ) != plateau->grille[numero_case(id_l, colone_choisie)].n_candidats)
				{
					suppression_dans_tableau(&plateau->grille[numero_case(id_l, colone_choisie)].candidats[0], plateau->grille[numero_case(id_l, colone_choisie)].n_candidats, occ);
					decalage_candidat(&plateau->grille[numero_case(id_l, colone_choisie)]);
					plateau->grille[numero_case(id_l, colone_choisie)].n_candidats--;
					*modif_region = true;
				}  
			}
		}
	}
};

void R4 (T_sudoku* plateau, T_case* c, int numero_case, bool* modif){

	bool modif_ligne = false;
	bool modif_colone = false;
	int num_region = numero_region(indice_ligne(numero_case), indice_colone(numero_case));
	int HG_l, HG_c;
	coordonnees_case_HG(num_region, &HG_l, &HG_c); 

	if(c->val == 0)
	{
		R4_ligne(plateau, c, num_region, HG_l, HG_c, &modif_ligne);
		R4_colone(plateau, c, num_region, HG_l, HG_c, &modif_colone);
	}

	if((modif_ligne) || (modif_colone))
		*modif = true;
	else
		*modif = false;
};


void colone_ligne(T_sudoku* plateau, bool* modif){

	// On teste pour tous les candidats possibles
	for(int cd = 1; cd <= 9; ++cd)
	{
		int nb_colone_ok = 0;
		int occ_dans_colone = 0;
		int coord[8];
		int d = -1;

		for (int c = 0; c < 9; ++c)
		{
			occ_dans_colone = 0;
			
			// Nombre d'apparition du candidat dans la colone
			for (int l = 0; l < 9; ++l)
				if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
					occ_dans_colone++;

			if(occ_dans_colone == 2)
			{
				nb_colone_ok++;
				for (int j = 0; j < 9; ++j)
				{
					// Récupération des cordonnées des cases succeptibles de former une configuration en "X"
					if( plateau->grille[numero_case(j,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(j,c)].candidats[0], plateau->grille[numero_case(j,c)].n_candidats, cd) != plateau->grille[numero_case(j,c)].n_candidats))
					{
						coord[++d] = j;
						coord[++d] = c;
					}
				}
			}
			if(nb_colone_ok == 2)
				break;

		} 
		
		if (nb_colone_ok == 2)
		{
			// Si c'est une configuaration en "X"
			if (coord[0] == coord[4] && coord[2] == coord[6])
			{
				int ligne1 = coord[0];
				int ligne2 = coord[2];
				int colone1 = coord[1];
				int colone2 = coord[5];

				// Suppression des candidats dans les colones 
				for (int x = 0; x < 9; ++x)
				{
					if(plateau->grille[numero_case(ligne1,x)].val == 0 && x != colone1 && x != colone2 && recherche_dans_tableau(&plateau->grille[numero_case(ligne1,x)].candidats[0], plateau->grille[numero_case(ligne1,x)].n_candidats, cd) != plateau->grille[numero_case(ligne1,x)].n_candidats)
					{
						suppression_dans_tableau(&plateau->grille[numero_case(ligne1,x)].candidats[0], plateau->grille[numero_case(ligne1,x)].n_candidats, cd);
						decalage_candidat(&plateau->grille[numero_case(ligne1,x)]);
						plateau->grille[numero_case(ligne1,x)].n_candidats--;
						*modif = true;
					}

					if(plateau->grille[numero_case(ligne2,x)].val == 0 && x != colone1 && x != colone2 && recherche_dans_tableau(&plateau->grille[numero_case(ligne2,x)].candidats[0], plateau->grille[numero_case(ligne2,x)].n_candidats, cd) != plateau->grille[numero_case(ligne2,x)].n_candidats)
					{
						suppression_dans_tableau(&plateau->grille[numero_case(ligne2,x)].candidats[0], plateau->grille[numero_case(ligne2,x)].n_candidats, cd);
						decalage_candidat(&plateau->grille[numero_case(ligne2,x)]);
						plateau->grille[numero_case(ligne2,x)].n_candidats--;
						*modif = true;
					}
				}
			}
		} 
	
	}

};

void ligne_colone(T_sudoku* plateau, bool* modif){

	// On teste pour tous les candidats possibles
	for(int cd = 1; cd <= 9; ++cd)
	{
		int nb_ligne_ok = 0;
		int occ_dans_ligne = 0;
		int coord[8];
		int d = -1;

		for (int l = 0; l < 9; ++l)
		{
			occ_dans_ligne = 0;
			
			// Nombre d'apparition du candidat dans la ligne
			for (int c = 0; c < 9; ++c)
				if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
					occ_dans_ligne++;

			if(occ_dans_ligne == 2)
			{
				nb_ligne_ok++;
				for (int j = 0; j < 9; ++j)
				{
					// Récupération des cordonnées des cases succeptibles de former une configuration en "X"
					if( plateau->grille[numero_case(l,j)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,j)].candidats[0], plateau->grille[numero_case(l,j)].n_candidats, cd) != plateau->grille[numero_case(l,j)].n_candidats))
					{
						coord[++d] = l;
						coord[++d] = j;
					}
				}
			}
			if(nb_ligne_ok == 2)
				break;
			
		} 

		if (nb_ligne_ok == 2)
		{
			// Si c'est une configuaration en "X"
			if (coord[1] == coord[5] && coord[3] == coord[7])
			{
				int ligne1 = coord[0];
				int ligne2 = coord[4];
				int colone1 = coord[1];
				int colone2 = coord[3];

				// Suppression des candidats dans les lignes 
				for (int x = 0; x < 9; ++x)
				{
					if(plateau->grille[numero_case(x,colone1)].val == 0 && x != ligne1 && x != ligne2 && recherche_dans_tableau(&plateau->grille[numero_case(x,colone1)].candidats[0], plateau->grille[numero_case(x,colone1)].n_candidats, cd) != plateau->grille[numero_case(x,colone1)].n_candidats)
					{
						suppression_dans_tableau(&plateau->grille[numero_case(x,colone1)].candidats[0], plateau->grille[numero_case(x,colone1)].n_candidats, cd);
						decalage_candidat(&plateau->grille[numero_case(x,colone1)]);
						plateau->grille[numero_case(x,colone1)].n_candidats--;
						*modif = true;
					}

					if(plateau->grille[numero_case(x,colone2)].val == 0 && x != ligne1 && x != ligne2 && recherche_dans_tableau(&plateau->grille[numero_case(x,colone2)].candidats[0], plateau->grille[numero_case(x,colone2)].n_candidats, cd) != plateau->grille[numero_case(x,colone2)].n_candidats)
					{
						suppression_dans_tableau(&plateau->grille[numero_case(x,colone2)].candidats[0], plateau->grille[numero_case(x,colone2)].n_candidats, cd);
						decalage_candidat(&plateau->grille[numero_case(x,colone2)]);
						plateau->grille[numero_case(x,colone2)].n_candidats--;
						*modif = true;
					}
				}
			}
		} 
	
	}

};

void ligne_region(T_sudoku* plateau, bool* modif){

	// On teste pour tous les candidats possibles
	for(int cd = 1; cd <= 9; ++cd)
	{
		int nb_ligne_ok = 0;
		int occ_dans_ligne = 0;
		int coord[50];
		int n_region[50];
		int d = -1;
		int e = -1;

		for (int l = 0; l < 9; ++l)
		{
			occ_dans_ligne = 0;
			
			// Nombre d'apparition du candidat dans la ligne
			for (int c = 0; c < 9; ++c)
				if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
					occ_dans_ligne++;

			if(occ_dans_ligne == 2)
			{
				nb_ligne_ok++;
				for (int j = 0; j < 9; ++j)
				{
					// Récupération des cordonnées des cases succeptibles de former une configuration en "X"
					if( plateau->grille[numero_case(l,j)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,j)].candidats[0], plateau->grille[numero_case(l,j)].n_candidats, cd) != plateau->grille[numero_case(l,j)].n_candidats))
					{
						coord[++d] = l;
						coord[++d] = j;
						n_region[++e] = numero_region(l,j);
					}
				}
			}

			if(nb_ligne_ok == 2)
				break;
		}

		if (nb_ligne_ok == 2)
		{
			// Si c'est une configuaration en "X"
			if (n_region[0] == n_region[2] && n_region[1] == n_region[3] && n_region[0] != n_region[1])
			{
				int ligne1 = coord[0];
				int ligne2 = coord[4];
				int HGl, HGc;
				coordonnees_case_HG(n_region[0], &HGl, &HGc);

				// Suppression des candidats  
				for (int m = HGl; m <= HGl+2; ++m)
				{
					for (int n = 0; n < 9; ++n)
					{
						if (plateau->grille[numero_case(m,n)].val == 0 && m != ligne1 && m != ligne2 && (numero_region(m,n) == n_region[0] || numero_region(m,n) == n_region[1]) && recherche_dans_tableau(&plateau->grille[numero_case(m,n)].candidats[0], plateau->grille[numero_case(m,n)].n_candidats, cd) != plateau->grille[numero_case(m,n)].n_candidats)
						{
							suppression_dans_tableau(&plateau->grille[numero_case(m,n)].candidats[0], plateau->grille[numero_case(m,n)].n_candidats, cd);
							decalage_candidat(&plateau->grille[numero_case(m,n)]);
							plateau->grille[numero_case(m,n)].n_candidats--;
							*modif = true;
						}
					}
				}
			}
		}

	}
};


void colone_region(T_sudoku* plateau, bool* modif){

	// On teste pour tous les candidats possibles
	for(int cd = 1; cd <= 9; ++cd)
	{
		int nb_colone_ok = 0;
		int occ_dans_colone = 0;
		int coord[50];
		int n_region[50];
		int d = -1;
		int e = -1;

		for (int c = 0; c < 9; ++c)
		{
			occ_dans_colone = 0;
			
			// Nombre d'apparition du candidat dans la colone
			for (int l = 0; l < 9; ++l)
				if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
					occ_dans_colone++;

			if(occ_dans_colone == 2)
			{
				nb_colone_ok++;
				for (int j = 0; j < 9; ++j)
				{
					// Récupération des cordonnées des cases succeptibles de former une configuration en "X"
					if( plateau->grille[numero_case(j,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(j,c)].candidats[0], plateau->grille[numero_case(j,c)].n_candidats, cd) != plateau->grille[numero_case(j,c)].n_candidats))
					{
						coord[++d] = j;
						coord[++d] = c;
						n_region[++e] = numero_region(j,c);
					}
				}
			}

			if(nb_colone_ok == 2)
				break;
		} 
		
		if (nb_colone_ok == 2)
		{
			// Si c'est une configuaration en "X"
			if (n_region[0] == n_region[2] && n_region[1] == n_region[3] && n_region[0] != n_region[1])
			{
				int colone1 = coord[1];
				int colone2 = coord[5];
				int HGl, HGc;
				coordonnees_case_HG(n_region[0], &HGl, &HGc);

				// Suppression des candidats 
				for (int m = HGc; m <= HGc+2; ++m)
				{
					for (int n = 0; n < 9; ++n)
					{
						if (plateau->grille[numero_case(n,m)].val == 0 && m != colone1 && m != colone2 && (numero_region(n,m) == n_region[0] || numero_region(n,m) == n_region[1]) && recherche_dans_tableau(&plateau->grille[numero_case(n,m)].candidats[0], plateau->grille[numero_case(n,m)].n_candidats, cd) != plateau->grille[numero_case(n,m)].n_candidats)
						{
							suppression_dans_tableau(&plateau->grille[numero_case(n,m)].candidats[0], plateau->grille[numero_case(n,m)].n_candidats, cd);
							decalage_candidat(&plateau->grille[numero_case(n,m)]);
							plateau->grille[numero_case(n,m)].n_candidats--;
							*modif = true;
						}
					}
				}
			}
		} 
	
	}
};

void region_ligne(T_sudoku* plateau, bool* modif){

	// On teste pour tous les candidats possibles
	for(int cd = 1; cd <= 9; ++cd)
	{
		int nb_region_ok = 0;
		int occ_dans_region = 0;
		int coordHG[18] = {0,0,0,3,0,6,3,0,3,3,3,6,6,0,6,3,6,6}; //Coordonnées des coins Haut_Gauche de chaque région
		int coord[50];
		int n_region[50];
		int e = -1;
		int d = -1;
		int suivi = -1;
		int HG_l, HG_c;
		
		
		for(int z = 0; z < 9; ++z)
		{	
			HG_l = coordHG[++suivi];
			HG_c = coordHG[++suivi];
			occ_dans_region = 0;
			
			// Nombre d'apparition du candidat dans la région
			for (int l = HG_l; l <= HG_l+2; ++l)
				for (int c = HG_c; c <= HG_c+2; ++c)
					if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
						occ_dans_region++;
				
			if(occ_dans_region == 2)
			{
					nb_region_ok++;
					
					for (int l = HG_l; l <= HG_l+2; ++l)
						for (int c = HG_c; c <= HG_c+2; ++c)
							// Récupération des cordonnées des cases succeptibles de former une configuration en "X"
							if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
							{	
								coord[++d] = l;
								coord[++d] = c;
								n_region[++e] = numero_region(l,c);
							}
						
			}

			if(nb_region_ok == 2)
					break;	

		}

		if (nb_region_ok == 2)
		{	
			// Si c'est une configuaration en "X"
			if ( (coord[0] == coord[4] || coord[0] == coord[6]) && (coord[2] == coord[6] || coord[2] == coord[4]) && n_region[0] == n_region[1] && n_region[2] == n_region[3] && n_region[0] != n_region[2])
			{
				int ligne1 = coord[0];
				int ligne2 = coord[2];
				int HGl, HGc;
				coordonnees_case_HG(n_region[0], &HGl, &HGc);

				// Suppression des candidats 
				for (int m = HGl; m <= HGl+2; ++m)
				{
					for (int n = 0; n < 9; ++n)
					{
						if (plateau->grille[numero_case(m,n)].val == 0 && (m == ligne1 || m == ligne2) && (numero_region(m,n) != n_region[0] && numero_region(m,n) != n_region[2]) && recherche_dans_tableau(&plateau->grille[numero_case(m,n)].candidats[0], plateau->grille[numero_case(m,n)].n_candidats, cd) != plateau->grille[numero_case(m,n)].n_candidats)
						{
							suppression_dans_tableau(&plateau->grille[numero_case(m,n)].candidats[0], plateau->grille[numero_case(m,n)].n_candidats, cd);
							decalage_candidat(&plateau->grille[numero_case(m,n)]);
							plateau->grille[numero_case(m,n)].n_candidats--;
							*modif = true;
						}
					}
				}
			}
		} 
	} 
};

void region_colone(T_sudoku* plateau, bool* modif){

	// On teste pour tous les candidats possibles
	for(int cd = 1; cd <= 9; ++cd)
	{
		int nb_region_ok = 0;
		int occ_dans_region = 0;
		int coordHG[18] = {0,0,0,3,0,6,3,0,3,3,3,6,6,0,6,3,6,6}; //Coordonnées des coins Haut_Gauche de chaque région
		int coord[50];
		int n_region[50];
		int e = -1;
		int d = -1;
		int suivi = -1;
		int HG_l, HG_c;
		

		for(int z = 0; z < 9; ++z)
		{	
			HG_l = coordHG[++suivi];
			HG_c = coordHG[++suivi];
			occ_dans_region = 0;
			
			// Nombre d'apparition du candidat dans la région
			for (int l = HG_l; l <= HG_l+2; ++l)
				for (int c = HG_c; c <= HG_c+2; ++c)
					if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
						occ_dans_region++;
				
			if(occ_dans_region == 2)
			{
					nb_region_ok++;
					
					for (int l = HG_l; l <= HG_l+2; ++l)
						for (int c = HG_c; c <= HG_c+2; ++c)
							// Récupération des cordonnées des cases succeptibles de former une configuration en "X"
							if( plateau->grille[numero_case(l,c)].val == 0 && (recherche_dans_tableau(&plateau->grille[numero_case(l,c)].candidats[0], plateau->grille[numero_case(l,c)].n_candidats, cd) != plateau->grille[numero_case(l,c)].n_candidats))
							{	
								coord[++d] = l;
								coord[++d] = c;
								n_region[++e] = numero_region(l,c);
							}
						
			}

			if(nb_region_ok == 2)
					break;	

		}

		if (nb_region_ok == 2)
		{		
			// Si c'est une configuaration en "X"
			if ( (coord[1] == coord[7] || coord[1] == coord[5]) && (coord[3] == coord[5] || coord[3] == coord[7]) && n_region[0] == n_region[1] && n_region[2] == n_region[3] && n_region[0] != n_region[2])
			{
				int colone1 = coord[1];
				int colone2 = coord[3];
				int HGl, HGc;
				coordonnees_case_HG(n_region[0], &HGl, &HGc);

				// Suppression des candidats
				for (int m = 0; m < 9; ++m)
				{
					for (int n = HGc; n <= HGc+2; ++n)
					{
						if (plateau->grille[numero_case(m,n)].val == 0 && (n == colone1 || n == colone2) && (numero_region(m,n) != n_region[0] && numero_region(m,n) != n_region[2]) && recherche_dans_tableau(&plateau->grille[numero_case(m,n)].candidats[0], plateau->grille[numero_case(m,n)].n_candidats, cd) != plateau->grille[numero_case(m,n)].n_candidats)
						{
							suppression_dans_tableau(&plateau->grille[numero_case(m,n)].candidats[0], plateau->grille[numero_case(m,n)].n_candidats, cd);
							decalage_candidat(&plateau->grille[numero_case(m,n)]);
							plateau->grille[numero_case(m,n)].n_candidats--;
							*modif = true;
						}
					}
				}
			}
		} 
	} 
};

void R5 (T_sudoku* plateau, bool* modif){
	
	bool modif_colone_ligne = false;
	bool modif_ligne_colone = false;
	bool modif_ligne_region = false;
	bool modif_colone_region = false;
	bool modif_region_ligne = false;
	bool modif_region_colone = false;
	
	colone_ligne(plateau, &modif_colone_ligne); 
	ligne_colone(plateau, &modif_ligne_colone);
	ligne_region(plateau, &modif_ligne_region);
	colone_region(plateau, &modif_colone_region);
	region_ligne(plateau, & modif_region_ligne);
	region_colone(plateau, & modif_region_colone);
	
	if((modif_colone_ligne) || (modif_ligne_colone) || (modif_ligne_region) || (modif_colone_region) || (modif_region_ligne) || (modif_region_colone))
		*modif = true;
	else
		*modif = false;

};


bool recherche_exhaustive(T_sudoku* plateau, int position){

	if(position == 81)
		return true;

	if(plateau->grille[position].val != 0)
		return recherche_exhaustive(plateau, position+1);

	for (int k = 1; k <= 9; ++k)
	{
		int a,b;
		coordonnees_case_HG((numero_region(indice_ligne(position), indice_colone(position))), &a, &b);
		
		if((!present_sur_ligne(*plateau, indice_ligne(position), k)) && (!present_sur_colone(*plateau, indice_colone(position), k) && (!present_sur_region(*plateau, a, b, k))))
		{
			plateau->grille[position].val = k;
			plateau->grille[position].n_candidats = 0;
			if(recherche_exhaustive(plateau, position+1))
				return true;
		}
	}
	plateau->grille[position].val = 0;

	return false;
};





