#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plateau.h"
#include "testUnitaire.h"
#include "logique.h"



int main(){
    srand(time(NULL));
    board_t* board = create_board();
    int random_tirage = lance_de();
    initgame(board, random_tirage);
}

