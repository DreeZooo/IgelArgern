#ifndef PLATEAU_H
#define PLATEAU_H

#define TAILLE_MAX_PILE_HERISSON 5 
#define TAILLE_TABLEAU_LIGNE 6
#define TAILLE_TABLEAU_COLONNE 9

typedef struct casePlateau casePlateau;
typedef struct board board_t;

casePlateau* get_cell(board_t* b, int line, int row);
void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos);
void cell_print(board_t* b, int line, int row, int slice);
void board_print(board_t* b, int highlighted_line);

#endif /* PLATEAU_H */
