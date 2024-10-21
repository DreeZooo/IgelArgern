#include <stdbool.h>
#ifndef PLATEAU_H
#define PLATEAU_H

#define TAILLE_MAX_PILE_HERISSON 5 
#define TAILLE_TABLEAU_LIGNE 6
#define TAILLE_TABLEAU_COLONNE 9
#define NOMBRE_DE_JOUEUR 2
#define NOMBRE_HERISSON 2

typedef struct casePlateau casePlateau;
typedef struct board board_t;

void initgame(board_t* b);
board_t* create_board(bool extension);
casePlateau* get_cell(board_t* b, int line, int row);
int winning_condition(board_t* board);
int* get_score_array(board_t* board);
bool get_flag(casePlateau* cell);
bool get_portal(casePlateau *cell);
int movable_herisson(board_t* board, char team);
void increase_winning_herisson(board_t* board, char team);
bool cell_trap(board_t*, int line, int row);
void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos);
void cell_print(board_t* b, int line, int row, int slice);
void board_print(board_t* b, int highlighted_line);
void menu_affichage();


#endif /* PLATEAU_H */