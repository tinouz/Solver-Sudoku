#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "annexe.h"
#include "regles.h"


int main(int argc, char*argv[]){

clrscr();
T_sudoku plateau;
mise_a_zero(&plateau);

assert(argc <= 2);


/*-----------------------------------------------------------------------------------------------*/


// Remplissage du plateau 
if (argc == 2)
{
	FILE* fichier = NULL;
	fichier = fopen(argv[1], "r"); 
	int i = 0;
	while(!feof(fichier))
	{
		fscanf(fichier, "%d", &plateau.grille[i].val);
		i++;
	}
	fclose(fichier);
}
else
{
	affichage_grille(plateau, -1, -1);
	saisie_grille(&plateau);
}

for(int t = 0; t < 81; ++t)
	ajout_candidat_dans_grille(&plateau, &plateau.grille[t], t);

affichage_grille(plateau, -1, 1);


/*-----------------------------------------------------------------------------------------------*/


// Choix du mode classique ou "pas à pas" 
int choixMode = 0;
while(choixMode != 1 && choixMode != 2)
{
	couleur(vert);
	printf("Mode classique   :");
	couleur(blanc);
	printf(" appuyer sur ");
	couleur(vert);
	printf("1");
	couleur(blanc);
	printf(" puis sur la touche Entrée\n");
	couleur(rouge);
	printf("Mode 'pas à pas' : ");
	couleur(blanc);
	printf("appuyer sur ");
	couleur(rouge);
	printf("2");
	couleur(blanc);
	printf(" puis sur la touche Entrée\n");
	printf("\nChoix : ");
	scanf("%d", &choixMode);
	printf("\n");

}


/*-----------------------------------------------------------------------------------------------*/


// Mode Classique 
if(choixMode == 1)
{
	
	bool modif;
	bool modification;
	bool modloc, modloc2;
	

		do{
			
			modification = false;
			
			for (int i = 0; i < 81; ++i)
			{
				if(grille_resolue(plateau))
				{
					modification = false;
					break;
				}

				R1(&plateau.grille[i], &modif, &modloc);
				if(modif)
					modification = true;

				R2(&plateau, &plateau.grille[i], i, &modif);
				if(modif)
					modification = true;

				R3(&plateau, &plateau.grille[i], i, &modif, &modloc2);
				if(modif)
					modification = true;  

				R4(&plateau, &plateau.grille[i], i, &modif);
				if(modif)
					modification = true; 

			}
			
			if(!modification)
				R5(&plateau, &modification); 
			
		}while(modification);

	if(!grille_resolue(plateau))
		recherche_exhaustive(&plateau, 0);

	clrscr();
	printf("\nVoici la grille résolue au maximum !\n\n");
	affichage_grille(plateau, -1, 1);
}


/*-----------------------------------------------------------------------------------------------*/


// Mode "pas à pas" 
else 
{
	clean_stdin();
	printf("Appuyer sur la touche Entrée pour continuer\n");
	clean_stdin();
	clrscr();

	bool modif;
	bool modification;
	bool modloc = false;
	bool modloc2 = false;
	int num_modif;
	
	do{
		modification = false;

		for (int i = 0; i < 81; ++i)
		{
			if(grille_resolue(plateau))
			{
				modification = false;
				break;
			}

		R1(&plateau.grille[i], &modif, &modloc);
			if(modloc)
			{
				num_modif = i;
				affichage_grille(plateau, num_modif, -1);
				modloc = false;
				num_modif = -1;
				char c = 'p';
				do{
					printf("Appuyer sur la touche Entrée pour continuer\n");
					scanf("%c",&c);
				}while (c != '\n');
				clrscr();
			}
			if(modif)
				modification = true;

			R2(&plateau, &plateau.grille[i], i, &modif);
			if(modif)
				modification = true;

			R3(&plateau, &plateau.grille[i], i, &modif, &modloc2);
			if(modloc2)
			{
				num_modif = i;
				affichage_grille(plateau, num_modif, -1);
				modloc2 = false;
				num_modif = -1;
				char c = 'p';
				do{
					printf("Appuyer sur la touche Entrée pour continuer\n");
					scanf("%c",&c);
				}while (c != '\n');
				clrscr();
			}
			if(modif)
				modification = true; 

			R4(&plateau, &plateau.grille[i], i, &modif);
			if(modif)
				modification = true;

		}
		
		if(!modification)
			R5(&plateau, &modification);

	}while(modification);

	if(!grille_resolue(plateau)){
		printf("(Recherche exhaustive ....)\n");
		recherche_exhaustive(&plateau, 0);
	}
		
	printf("\nVoici la grille résolue au maximum !\n\n");
	affichage_grille(plateau, -1, 1);

} 
	
	return 0;
}