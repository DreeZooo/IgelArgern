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
    char row, top, herisson;
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

    direction = 2;
    while (direction != 1 && direction != 0){
        printf("Dans quel direction voulez-vous déplacer votre herisson (1 pour haut et 0 pour bas) : ");
        scanf("%d", &direction);
        if (direction == 1 && line == 0){
            printf("Impossible de se déplacer vers le haut\n");
        }else if (direction == 0 && line == TAILLE_TABLEAU_LIGNE){
            printf("Impossible de se déplacer vers le bas\n");
        }else if (direction == 1){
            herisson = board_pop(board, line, row);
            board_push(board, line-1, row, herisson);
        }else if (direction == 0){
            herisson = board_pop(board, line, row);
            board_push(board, line-1, row, herisson);
        }else printf("Entrée invalide : 1 pour haut et 0 pour bas\n");
    }
}

int hedgehog_behind(board_t* board, int line, int row){
    int num_hedgehog_behind = 0;
    int j;
    for (j = 0; j < row+1; j++){
        if (board_top(board, line, j) != '0') num_hedgehog_behind++;
    }
    return num_hedgehog_behind;
}


void forward_move(board_t* board, int line, char team){
    char row, top, hedgehog;
    top = '0';
    while ( top != '0'){
        printf("Quel herisson voulez-vous déplacer vers l'avant : ");
        scanf("%c", &row);
        top = board_top(board, line-1, (int)(row - 'a'));
        if (top == '0'){
            printf("La case sélectionnée est vide\n");
        }
        else if (((board -> tableau[line][row]).flag) && hedgehog_behind(board, line, row)){
            printf("Impossible de déplacer un hérisson dans une case piègée tant qu'il y a d'autres hérissons dérière sur la même ligne\n");
        }
        else if ((int)(row - 'a') == TAILLE_TABLEAU_COLONNE){
            printf("Impossible de déplacer des hérissons qui sont arrivés à la fin\n");
        }
    }

    hedgehog = board_pop(board, line, row);
    board_push(board, line, row+1, hedgehog);

    if (row+1 == TAILLE_TABLEAU_COLONNE-1){
        board -> score_array[(int)hedgehog - 'A']++;
    }
}

int winning_condition(board_t* board){
    int number_winner = 0;
    char winner[NOMBRE_DE_JOUEUR];
    for (int i = 0; i < NOMBRE_DE_JOUEUR; i++){
        winner[i] = '0';
    }
    
    for (int i = 0; i < NOMBRE_DE_JOUEUR; i++){
        if (board -> score_array[i] == NOMBRE_HERISSON - 1) {number_winner++; winner[i] = 'A' + i;}
    }
    return number_winner;
}


void playgame(){
    srand(time(NULL));
    board_t* board = create_board();
    while (!winning_condition(board)){
        for (int i = 0; i < NOMBRE_DE_JOUEUR; i++){
            int random_tirage = lance_de();
            initgame(board, random_tirage);
            printf("Le dé est tombé sur  : %d\n", random_tirage);
            vertical_move(board, 'A'+i);
            initgame(board, random_tirage);
            forward_move(board, random_tirage, 'A'+i);
            initgame(board, random_tirage);
        }
    }
}