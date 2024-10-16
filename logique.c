#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "plateau.h"

int lance_de(){
    return rand() % 6 +1;
}

void vertical_move(board_t* board, char team){
    int line, direction;
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
    /*
    printf("Dans quel direction voulez-vous déplacer votre herisson (1 pour haut et 0 pour bas) : ");
    scanf("%d", &direction);
    if (direction == 1 && line == 0){
        printf("Impossible de se déplacer vers le haut");
    }else if (direction == 0 && line == TAILLE_TABLEAU_LIGNE){
        printf("Impossible de se déplacer vers le bas");
    }else if (direction == 1){
        
    }
    */
}

int hedgehog_behind(board_t* board, int line, int row){
    int num_hedgehog_behind = 0;
    int j;
    for (j = 0; j < row+1; j++){
        if (board_top(board, line, j) != '0') num_hedgehog_behind++;
    }
    return num_hedgehog_behind
}


void forward_move(board_t* board, int line, char team){
    int line;
    char row, top, hedgehog;
    top = '0';
    while ( top != '0'){
        printf("Quel herisson voulez-vous déplacer vers l'avant : ");
        scanf("%d %c", &line, &row);
        top = board_top(board, line-1, (int)(row - 'a'));
        if (top == '0'){
            printf("La case sélectionnée est vide\n");
        }
        else if (board -> tableau[line][row].flag && hedgehog_behind(board, line, row)){
            printf("Impossible de déplacer un hérisson dans une case piègée tant qu'il y a d'autres hérissons dérière sur la même ligne\n");
        }
        else if ((int)(row - 'a') == TAILLE_TABLEAU_COLONNE){
            printf("Impossible de déplacer des hérissons qui sont arrivés à la fin\n");
        }
    }

    hedgehog = board_pop(board, line, row);
    board_push(board, line, row+1, hedgehog);

    /*
    if (row+1 == TAILLE_TABLEAU_COLONNE){
        board.A++
    }
    */
}

void playgame(){
    srand(time(NULL));
    board_t* board = create_board();
    int random_tirage = lance_de();
    initgame(board, random_tirage);
    printf("Le dé est tombé sur  : %d\n", random_tirage);
    vertical_move(board, 'A');
}