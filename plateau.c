#include<stdio.h>
#include<stdlib.h>
#include "plateau.h"

struct casePlateau{
    char pile[TAILLE_MAX_PILE_HERISSON];
    int sommet;
};

struct board{
    struct casePlateau tableau[TAILLE_TABLEAU_LIGNE][TAILLE_TABLEAU_COLONNE];
};

casePlateau* get_cell(board_t* b, int line, int row) {
    return &(b -> tableau[line][row]);
}

void initgame(board_t* b, int hg){
    board_print(b, hg);
}


board_t* create_board() {
    board_t* board = (board_t*)malloc(sizeof(board_t));
        for (int line = 0; line < TAILLE_TABLEAU_LIGNE; line++) {
            for (int row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
                if((line == 0 && row == 2) | (line == 1 && row == 6) | (line == 2 && row == 4) | (line == 3 && row == 5) | (line == 4 && row == 3) | (line == 5 && row == 7)){
                    board->tableau[line][row].sommet = -1;
                }else{
                    board->tableau[line][row].sommet = 0;
                }
            }
        }
    return board;
}


void board_push(board_t* b, int line, int row, char ctn){
    casePlateau* cell = get_cell(b, line, row);
    if (cell -> sommet < TAILLE_MAX_PILE_HERISSON){
    cell->pile[cell->sommet] = ctn;
    cell -> sommet++;
    }else{
        printf("Erreur dépassement de la pile\n");
        exit(1);
    }
}

char board_pop(board_t* b, int line, int row){
    casePlateau* cell = get_cell(b, line, row);
    char sortant;
    if(cell -> sommet > 0){
        sortant = cell -> pile[cell -> sommet - 1];
        cell -> sommet--;
    }else{
        printf("Erreur : Impossible d'enlever un herisson car aucun dans la pile\n");
        exit(2);
    }
    return sortant;
}

int board_height(board_t* b, int line, int row){
    casePlateau* cell = get_cell(b, line, row);
    int height = 0;
    if(cell->sommet >= 0){
        height = cell -> sommet;
    }else{
        printf("La pile n'a pas de taille\n");
        exit(3);
    }
    return height;
}

char board_top(board_t* b, int line, int row){
    casePlateau* cell = get_cell(b, line, row);
    char team;
    if(cell -> sommet > 0){
        team = cell -> pile[cell -> sommet -1 ];
    }else{
        team = '0';
    }
    return team;
}

//Pos 0 = top 
char board_peek(board_t* b, int line, int row, int pos){
    casePlateau* cell = get_cell(b, line, row);
    char team_at_pos;
    int height_stack = board_height(b, line, row);
    if(cell -> sommet > 0 && pos < height_stack){
        team_at_pos = cell -> pile[cell -> sommet - 1 - pos];
    }else{
        team_at_pos = '0';
    }
    return team_at_pos;
}

//slice = 0 -> bord nord, slice = 1 -> la ligne de contenu du haut, etc.

void cell_print(board_t* b, int line, int row, int slice){
    switch (slice)
    {
    case 0:
        //vérifier si la case est un piège
        if (b -> tableau[line][row].sommet == -1){
            printf(" vvv ");
        }
        else printf(" --- ");
        break;
    case 1:
        if (b -> tableau[line][row].sommet == -1){
            printf(">   <");
        }
        else{
            char team = board_top(b, line, row);
            if (team == '0'){
                printf("|   |");
            }
            else printf("|%c%c%c|", team, team, team);
        }
        break;
    case 2:
        if (b -> tableau[line][row].sommet == -1){
            printf(">   <");
        }

        else{
            char team1 = board_peek(b, line, row, 1);
            char team2 = board_peek(b, line, row, 2);
            char team3 = board_peek(b, line, row, 3);

            if (team1 == '0'){

                char team = board_top(b, line, row);
                if (team == '0'){
                    printf("|   |");
                }
                else printf("|%c%c%c|", team, team , team);
            }

            else if (team2 == '0'){
                printf("|");
                printf("%c%c%c", team1 - 'A' + 'a', team1 - 'A' + 'a', team1 - 'A' + 'a');
                printf("|");

            }
            
            else if (team3 == '0'){
                printf("|%c %c|", team1 - 'A' + 'a', team2 - 'A' + 'a');
            }

            else printf("|%c%c%c|", team1 - 'A' + 'a', team2 - 'A' + 'a', team3 - 'A' + 'a');

        }

        break;
    
    case 3:
        if (b -> tableau[line][row].sommet == -1){
            printf(" ^^^ ");
        }
        
        else{
            
            int hieght_stack = board_height(b, line, row);
            if (hieght_stack > 1){
                printf(" -%d- ", hieght_stack);
            }
            else printf(" --- ");

        }

        break;

    default:
        break;
    }
}


void board_print(board_t* b, int highlighted_line){
    int line, row;
    printf("   ");
    for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++){
        printf("  %c  ", 'a' + row);
        printf("   ");
    }
    printf("\n");
    for (line = 0; line < TAILLE_TABLEAU_LIGNE; line++){
        printf("   ");

        for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++){
            cell_print(b, line, row, 0);
            printf("   ");
        }

        printf("\n");
        if (line+1 == highlighted_line){
            printf(" > ");
        }
        else printf("   ");

        for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++){
            cell_print(b, line, row, 1);
            printf("   ");
        }

        printf("\n");
        if (line+1 == highlighted_line){
            printf("%d> ", line + 1);
        }
        else printf("%d  ", line + 1);

        for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++){
            cell_print(b, line, row, 2);
            printf("   ");
        }

        printf("\n");
        if (line+1 == highlighted_line){
            printf(" > ");
        }
        else printf("   ");

        for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++){
            cell_print(b, line, row, 3);
            printf("   ");
        }
        printf("\n");
    }

    
    
}

