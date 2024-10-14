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
        printf("Erreur dépassement de la pile");
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
        printf("Erreur : Impossible d'enlever un herisson car aucun dans la pile");
        exit(2);
    }
    return sortant;
}

int board_height(board_t* b, int line, int row){
    casePlateau* cell = get_cell(b, line, row);
    int hauteur = 0;
    if(cell->sommet >= 0){
        hauteur = cell -> sommet;
    }else{
        printf("La pile n'a pas de taille");
        exit(3);
    }
    return hauteur;
}

char board_top(board_t* b, int line, int row){
    casePlateau* cell = get_cell(b, line, row);
    char equipe;
    if(cell -> sommet > 0){
        equipe = cell -> pile[cell -> sommet-1];
    }else{
        printf("Erreur : Pas de herissons dans cette case");
        exit(3);
    }
    return equipe;
}
