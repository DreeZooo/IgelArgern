#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "plateau.c"


// TODO Renommage de aux 
// Corriger les autres fonctions
// Faire le makeFile

int main(){
    struct casePlateau c = {.pile = {'aaa'}, .sommet = 2};
    board_t b = {c};
    casePlateau* d =  aux(&b, 0, 0);
    printf("%p\n", d);

}
