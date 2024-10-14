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
        printf("Erreur : Pas de herissons dans cette case\n");
        exit(4);
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
        printf("Erreur : Pas de herissons à cette position dans la case\n");
        exit(5);
    }
    return team_at_pos;
}