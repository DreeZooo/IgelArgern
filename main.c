#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "testUnitaire.h"

int main(){
    board_t* board = create_board();
    run_tests(board);
}

