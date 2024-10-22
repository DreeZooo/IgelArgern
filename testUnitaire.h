#include "plateau.h"
#ifndef TEST_UNITAIRE_H
#define TEST_UNITAIRE_H

void run_tests();
void test_board_push(board_t* board, int line, int row, char ctn);
void test_board_pop(board_t* board, int line, int row);
void test_board_height(board_t* board, int line, int row);
void test_board_top(board_t* board, int line, int row);
void test_board_peek(board_t* board, int line, int row, int pos);

#endif /* TEST_UNITAIRE_H */
