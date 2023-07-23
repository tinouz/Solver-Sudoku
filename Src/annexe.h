#ifndef ANNEXE
#define ANNEXE

#include <stdio.h>

// Efface l'écran et replace le curseur en haut à gauche
#define clrscr() printf("\033[H\033[2J")

// Sélection de couleurs
#define couleur(param) printf("\033[%sm",param)
#define rouge "31"
#define vert "32"
#define jaune "33"
#define bleu "34"
#define magenta "35"
#define cyan "36"
#define blanc "0"

// Vide le buffer stdin
void clean_stdin();


#endif
