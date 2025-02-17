#include <stdbool.h>
#ifndef LOGIQUE_H
#define LOGIQUE_H

typedef struct casePlateau casePlateau;
typedef struct board board_t;

int lance_de();
void clean_buffer(void);
void find_other_portal(board_t *board, int line, int row, char herisson);
void seek_to_next_line( void );
void vertical_move(board_t* board, char team);
bool hedgehog_behind(board_t *board, int line, int row);
bool hedgehog_on_the_line(board_t *board, int line);
void forward_move(board_t* board, int line, char team);
int winning_condition(board_t* board);
void playgame();

#endif /* LOGIQUE_H */