#include<stdio.h>
#include<stdlib.h>
#include "plateau.h"

struct casePlateau{
    char pile[TAILLE_MAX_PILE_HERISSON];
    int sommet;
};

struct board{
    casePlateau tableau[TAILLE_TABLEAU_LIGNE][TAILLE_TABLEAU_COLONNE];
};


//Initialiser le plateau ????

void board_push(board_t* b, int line, int row, char ctn){
    casePlateau* cellule = &b -> tableau[line][row];
    
    if (cellule -> sommet < TAILLE_MAX_PILE_HERISSON){
    cellule ->pile[cellule->sommet] = ctn;
    cellule -> sommet++;
    }else{
        printf("Erreur dépassement de la pile");
        exit(1);
    }
}

char board_pop(board_t* b, int line, int row){
    casePlateau* cellule = &b -> tableau[line][row];
    char sortant;
    if(cellule -> sommet > 0){
        sortant = cellule -> pile[cellule -> sommet-1];
    }else{
        printf("Erreur : Impossible d'enlever un herisson car aucun dans la pile");
        exit(2);
    }
    return sortant;
}

int board_height(board_t* b, int line, int row){
    casePlateau* cellule = &b -> tableau[line][row];
    int hauteur = 0;
    if(cellule->sommet >= 0){
        hauteur = cellule -> sommet;
    }else{
        printf("La pile n'a pas de taille");
        exit(3);
    }
    return hauteur;
}

char board_top(board_t* b, int line, int row){
    casePlateau* cellule = &b -> tableau[line][row];
    char equipe;
    if(cellule -> sommet > 0){
        equipe = cellule -> pile[cellule -> sommet-1];
    }else{
        printf("Erreur : Pas de herissons dans cette case");
        exit(3);
    }
    return equipe;
}