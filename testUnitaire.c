#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "testUnitaire.h"


void test_board_push(board_t* board, int line, int row, char ctn) {
    printf("Pushing '%c' ; ", ctn);
    board_push(board, line, row, ctn);
    printf("Current height: %d\n", board_height(board, line, row));
}

void test_board_pop(board_t* board, int line, int row) {
    char result = board_pop(board, line, row);
    printf("Pop '%c' ; ", result);
}

void test_board_height(board_t* board, int line, int row) {
    int height = board_height(board, line, row);
    printf("Height: %d\n", height);
}

void test_board_top(board_t* board, int line, int row) {
    char result = board_top(board, line, row);
    printf("String : %c\n", result);
}

void test_board_peek(board_t* board, int line, int row, int pos){
    char result = board_peek(board, line, row, pos);
    printf("String at the position %d :  %c\n" , pos, result);
}

void test_board_cell_print(board_t* board, int line, int row, int slice){
    cell_print(board, line, row, slice);
}

void test_board_board_print(board_t* b, int hg){
    board_print(b, hg);
}

void run_tests(board_t* board) {
    printf("----------Test of push----------\n");
    test_board_push(board, 0, 0, 'A');
    test_board_push(board, 0, 0, 'B');
    test_board_push(board, 0, 0, 'C');
    printf("\n");

    printf("----------Test of pop----------\n");
    test_board_pop(board, 0, 0);
    test_board_height(board, 0,0);
    test_board_pop(board, 0, 0);
    test_board_height(board, 0,0);
    test_board_pop(board, 0, 0);
    test_board_height(board, 0,0);
    printf("\n");

    printf("----------Test of top----------\n");
    test_board_push(board, 0, 0, 'A');
    test_board_top(board, 0,0);
    test_board_push(board, 0, 0, 'B');
    test_board_top(board, 0,0); 
    test_board_push(board, 0, 0, 'C');
    printf("\n");

    printf("----------Test of peek----------\n");
    test_board_peek(board,0, 0, 0);
    test_board_peek(board,0, 0, 1);
    test_board_peek(board,0, 0, 2);

    printf("----------Test of cell----------\n");
    test_board_cell_print(board, 0, 0, 0);
    test_board_cell_print(board, 0, 0, 1);
    test_board_cell_print(board, 0, 0, 2);
    test_board_cell_print(board, 0, 0, 3);
    printf("\n");

    printf("----------Test of cell----------\n");
    test_board_board_print(board, 3);

}