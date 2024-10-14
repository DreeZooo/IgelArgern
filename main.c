#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "plateau.c"



int main(){
    struct casePlateau c = {.pile = {'aaa'}, .sommet = 2};
    board_t b = {c};
    casePlateau* d =  aux(&b, 0, 0);
    printf("%p\n", d);

}
