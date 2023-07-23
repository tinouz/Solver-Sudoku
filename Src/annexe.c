#include "annexe.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void clean_stdin(){
	int c; 
    do{ 
        c = getchar(); 
    } while (c != '\n' && c != EOF); 
};