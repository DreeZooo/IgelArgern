#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "plateau.h"

int lance_de(){
    return rand() % 6 +1;
}PLATEAU_H

void move_player(){}

void playgame(){
    srand(time(NULL));
    board_t* board = create_board();
    int random_tirage = lance_de();
    initgame(board, random_tirage);
    printf("Le dé est tombé sur  : %d", random_tirage);
}