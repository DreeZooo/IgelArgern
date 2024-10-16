#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "plateau.h"

int lance_de(){
    return rand() % 6 +1;
}

void vertical_move(board_t* board, char team){
    int line;
    char row, top;
    top = '0';
    while ( top != team){
        printf("Quel herisson voulez-vous déplacer verticalement : ");
        scanf("%d %c", &line, &row);
        printf("%d %d\n", line-1, (int)(row - 'a'));
        top = board_top(board, line-1, (int)(row - 'a'));
        if (top == '0'){
            printf("La case sélectionnée est vide\n");
        }
        else if (top != team) printf("Le herisson sélectionné n'est pas le votre\n");

    }
    
}

void move_player(board_t* board, int line, char team){}

void playgame(){
    srand(time(NULL));
    board_t* board = create_board();
    int random_tirage = lance_de();
    initgame(board, random_tirage);
    printf("Le dé est tombé sur  : %d\n", random_tirage);
    vertical_move(board, 'A');
}