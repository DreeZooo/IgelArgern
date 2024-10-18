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
        scanf(" %d %c", &line, &row);
        
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
        scanf(" %d", &direction);
        
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
        if (board_top(board, line, j) != '0'){
            herisson_behind = true;
        }
    }
    return herisson_behind;
}

bool hedgehog_on_the_line(board_t* board, int line){
    bool result =  false;
    if (line < 0 || line > TAILLE_TABLEAU_LIGNE){
        return false;
    }else{
        for (int i = 0; i < TAILLE_TABLEAU_COLONNE - 1; i++){
            if(board_top(board, line - 1, i) != '0'){
                result = true;
                break;
            }
        }
    }
    return result;
}


void forward_move(board_t* board, int line, char team){
    char row, top, hedgehog;

    if (hedgehog_on_the_line(board, line) == false){
        printf("Aucun hérisson déplacable sur la ligne\n");
        return;
    }


        while(true){
            printf("Quel herisson voulez-vous déplacer vers l'avant : ");
            scanf(" %c", &row);

            int row_index = (row - 'a');
            int index_line = line - 1;
            top = board_top(board, index_line, row_index);
            bool state_of_cell = cell_trap(board, index_line, row_index);

            if(row_index < 0 || row_index >= TAILLE_TABLEAU_COLONNE){
                printf("Erreur la colonne choisit est dans dehors du plateau de jeu.\n");
                continue;
            }else if (top == '0'){
                printf("La case sélectionnée est vide\n");
                continue;
            }else if (state_of_cell & hedgehog_behind(board, index_line, row_index)){
                printf("Impossible de déplacer un hérisson dans une case piègée tant qu'il y a d'autres hérissons dérière sur la même ligne\n");
                continue;
            }else if(row_index == TAILLE_TABLEAU_COLONNE -1){
                printf("Impossible de déplacer des hérissons qui sont arrivés à la fin\n");
                continue;
            }else{
                hedgehog = board_pop(board, line - 1, row_index);
                board_push(board, line - 1, row_index +1, hedgehog);
                printf("Le herisson a avancé d'une case ! \n");
                if(row_index == TAILLE_TABLEAU_COLONNE -2){
                    increase_winning_herisson(board, hedgehog);
                }
                break;
            }                                          
        }
}


void playgame(){
    int vertical_response;
    srand(time(NULL));
    board_t* board = create_board();
    initgame(board);
    while (!winning_condition(board)){
        for (int i = 0; i < NOMBRE_DE_JOUEUR; i++){
            int random_tirage = lance_de();
            board_print(board, random_tirage);
            printf("Le dé est tombé sur  : %d\n", random_tirage);
            printf("L'équipe %c joue \n", i +'A');
            printf("Voulez vous déplacer un hérisson verticalement (1 pour oui, 0 pour non) : ");
            scanf(" %d", &vertical_response);
            if (vertical_response == 1){
                if(!(movable_herisson(board, i + 'A'))){
                    printf("Pas de hérisson déplacable verticalement\n");
                }else{
                    vertical_move(board, 'A'+i);
                }
            }            
            board_print(board, random_tirage);
            forward_move(board, random_tirage, 'A' + i);
        }
    }
}