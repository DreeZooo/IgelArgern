#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "testUnitaire.h"
#include <time.h>

int de(){
    return rand() % 6 +1;
}
int main(){
    srand(time(NULL));
    board_t* board = create_board();
    int lance_de = de();
    initgame(board, lance_de);
}

