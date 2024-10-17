#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "plateau.h"

int lance_de(){
    return rand() % TAILLE_TABLEAU_LIGNE +1;
}

void vertical_move(board_t* board, char team){
    int line;
    int direction = -1;
    char row, top, herisson;

    while (true){
        top = '0';
        printf("Quel herisson voulez-vous déplacer verticalement (format : ligne colonne) : ");
        scanf("%d %c", &line, &row);
        
        top = board_top(board, line - 1, (int)(row - 'a'));
        if (top == '0'){
            printf("La case sélectionnée est vide\n");
            continue;
        }
        else if (top != team){ 
            printf("Le herisson sélectionné n'est pas le votre\n");
            continue;
        }

        int line_array_position = line - 1;
        int row_array_position = row - 'a';

        printf("Dans quel direction voulez-vous déplacer votre herisson (1 pour haut et 0 pour bas) : ");
        scanf("%d", &direction);
        
        if (direction == 1){
            if (line_array_position == 0){
                printf("Impossible de se déplacer vers le haut, veuillez choisir un autre hérisson\n");
                continue;
            }else if(board_height(board, line_array_position - 1, row_array_position) <= TAILLE_MAX_PILE_HERISSON - 1){
                herisson = board_pop(board, line_array_position, row_array_position);
                board_push(board, line_array_position - 1, row_array_position, herisson);
                printf("Hérisson déplacé avec succès vers le haut !\n");
                break;
            }else{
                printf("Impossible de déplacer l'hérisson car la case est pleine...\n");
                continue;
            }
        }else if (direction == 0){
            if (line_array_position == TAILLE_TABLEAU_LIGNE - 1){
                printf("Impossible de se déplacer vers le bas, veuillez choisir un autre hérisson\n");
                continue;
            }else if(board_height(board, line_array_position + 1, row_array_position) <= TAILLE_MAX_PILE_HERISSON - 1){
                herisson = board_pop(board, line_array_position, row_array_position);
                board_push(board, line_array_position + 1, row_array_position, herisson);
                printf("Hérisson déplacé avec succès vers le bas !\n");
                break;
            }else{
                printf("Impossible de déplacer l'hérisson car la case est pleine...\n");
                continue;
            }
        }      
        else printf("Entrée invalide : 1 pour haut et 0 pour bas\n");
    }
}

bool hedgehog_behind(board_t* board, int line, int row){
    bool herisson_behind = false;
    for (int j = 0; j < row; j++){
        if (board_top(board, line, j) != '0'){herisson_behind = true;}
    }
    return herisson_behind;
}


void forward_move(board_t* board, int line, char team){
    char row, top, hedgehog;
    while (true){
        top = '0';
        printf("Quel herisson voulez-vous déplacer vers l'avant : ");
        scanf("%c", &row);
        
        top = board_top(board, line-1, (int)(row - 'a'));
        casePlateau* cell_traped = get_cell(board, line - 1, (int)(row - 'a'));
        printf("%d %d\n", line - 1, (int)(row - 'a'));
        printf("%c", board_top(board, line - 1, row - 'a'));
        bool state_of_cell = get_flag(cell_traped);

        if (top == '0'){
            printf("La case sélectionnée est vide\n");
            continue;
        }
        else if (state_of_cell && hedgehog_behind(board, line, row)){
            printf("Impossible de déplacer un hérisson dans une case piègée tant qu'il y a d'autres hérissons dérière sur la même ligne\n");
        }
        else if ((int)(row - 'a') == TAILLE_TABLEAU_COLONNE){
            printf("Impossible de déplacer des hérissons qui sont arrivés à la fin\n");
            continue;
        }else{
            if(row < TAILLE_TABLEAU_COLONNE - 1){
                hedgehog = board_pop(board, line, row);
                board_push(board, line, row+1, hedgehog);
                break;
            }
        }
    }

    

    /*if (row+1 == TAILLE_TABLEAU_COLONNE-1){
        board -> score_array[(int)hedgehog - 'A']++;
    }*/
}


/*
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
*/

void playgame(){
    srand(time(NULL));
    board_t* board = create_board();
    initgame(board);
    while (true){
        for (int i = 0; i < NOMBRE_DE_JOUEUR; i++){
            int random_tirage = lance_de();
            board_print(board, random_tirage);
            printf("Le dé est tombé sur  : %d\n", random_tirage);
            vertical_move(board, 'A'+i);
            //forward_move(board, random_tirage, 'A' + i);
        }
    }
}