#include "plateau.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct casePlateau {
  char pile[TAILLE_MAX_PILE_HERISSON];
  int sommet;
  bool flag;
  bool portal;
};

struct board {
  struct casePlateau tableau[TAILLE_TABLEAU_LIGNE][TAILLE_TABLEAU_COLONNE];
  int score_array[NOMBRE_DE_JOUEUR];
};

casePlateau *get_cell(board_t *b, int line, int row) {
  return &(b->tableau[line][row]);
}

int *get_score_array(board_t *board) { return (board->score_array); }

bool get_flag(casePlateau *cell) { return (cell->flag); }

bool get_portal(casePlateau *cell) { return (cell->portal); }

int movable_herisson(board_t *board, char team) {
  for (int i = 0; i < TAILLE_TABLEAU_LIGNE; i++) {
    for (int j = 0; j < TAILLE_TABLEAU_COLONNE - 1; j++) {
      if (board_top(board, i, j) == team) {
        return 1;
        break;
      }
    }
  }
  return 0;
}
void increase_winning_herisson(board_t *board, char team) {
  board->score_array[(int)team - 'A']++;
}

bool cell_trap(board_t *, int line, int row) {
  if ((line == 0 && row == 2) | (line == 1 && row == 6) |
      (line == 2 && row == 4) | (line == 3 && row == 5) |
      (line == 4 && row == 3) | (line == 5 && row == 7)) {
    return true;
  }
  return false;
}

int winning_condition(board_t *board) {
  int number_winner = 0;
  for (int i = 0; i < NOMBRE_DE_JOUEUR; i++) {
    if (board->score_array[i] == NOMBRE_HERISSON - 1) {
      number_winner++;
    }
  }
  return number_winner;
}

void initgame(board_t *b) {
  char players[NOMBRE_DE_JOUEUR];
  bool insert_in_stack = false;
  for (int i = 0; i < NOMBRE_DE_JOUEUR; i++) {
    players[i] = 'A' + i;
  }
  for (int j = 0; j < NOMBRE_DE_JOUEUR; j++) {
    for (int k = 0; k < NOMBRE_HERISSON; k++) {
      while (insert_in_stack == false) {
        int number_random = rand() % TAILLE_TABLEAU_LIGNE;
        if (board_height(b, number_random, 0) < TAILLE_MAX_PILE_HERISSON) {
          board_push(b, number_random, 0, players[j]);
          insert_in_stack = true;
        }
      }
      insert_in_stack = false;
    }
  }
}

board_t *create_board(bool extension) {
  board_t *board = (board_t *)malloc(sizeof(board_t));
  srand(time(NULL));
  for (int line = 0; line < TAILLE_TABLEAU_LIGNE; line++) {
    for (int row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
      board->tableau[line][row].sommet = 0;
      if ((line == 0 && row == 2) | (line == 1 && row == 6) |
          (line == 2 && row == 4) | (line == 3 && row == 5) |
          (line == 4 && row == 3) | (line == 5 && row == 7)) {
        board->tableau[line][row].flag = false;
      } else {
        board->tableau[line][row].flag = true;
      }
      board->tableau[line][row].portal = false;
    }
  }
  if (extension) {
    int line_portal1 = rand() % TAILLE_TABLEAU_LIGNE;
    int line_portal2 = rand() % TAILLE_TABLEAU_LIGNE;
    int row_portal1 = rand() % TAILLE_TABLEAU_COLONNE;
    int row_portal2 = rand() % TAILLE_TABLEAU_COLONNE;
    while (line_portal2 == line_portal1 && row_portal2 == row_portal1) {
      row_portal1 = rand() % TAILLE_TABLEAU_COLONNE;
      row_portal2 = rand() % TAILLE_TABLEAU_COLONNE;
    }

    board->tableau[line_portal1][row_portal1].portal = true;
    board->tableau[line_portal2][row_portal2].portal = true;
  }

  for (int i = 0; i < NOMBRE_DE_JOUEUR; i++) {
    board->score_array[i] = 0;
  }

  return board;
}

void board_push(board_t *b, int line, int row, char ctn) {
  casePlateau *cell = get_cell(b, line, row);
  if (cell->sommet < TAILLE_MAX_PILE_HERISSON) {
    cell->pile[cell->sommet] = ctn;
    cell->sommet++;
  } else {
    printf("Erreur dépassement de la pile\n");
    exit(1);
  }
}

char board_pop(board_t *b, int line, int row) {
  casePlateau *cell = get_cell(b, line, row);
  char sortant;
  if (cell->sommet > 0) {
    sortant = cell->pile[cell->sommet - 1];
    cell->sommet--;
  } else {
    printf(
        "Erreur : Impossible d'enlever un herisson car aucun dans la pile\n");
    exit(2);
  }
  return sortant;
}

int board_height(board_t *b, int line, int row) {
  casePlateau *cell = get_cell(b, line, row);
  int height = 0;
  if (cell->sommet >= 0) {
    height = cell->sommet;
  } else {
    printf("La pile n'a pas de taille\n");
    exit(3);
  }
  return height;
}

char board_top(board_t *b, int line, int row) {
  casePlateau *cell = get_cell(b, line, row);
  char team;
  if (cell->sommet > 0) {
    team = cell->pile[cell->sommet - 1];
  } else {
    team = '0';
  }
  return team;
}

// Pos 0 = top
char board_peek(board_t *b, int line, int row, int pos) {
  casePlateau *cell = get_cell(b, line, row);
  char team_at_pos;
  int height_stack = board_height(b, line, row);
  if (cell->sommet > 0 && pos < height_stack) {
    team_at_pos = cell->pile[cell->sommet - 1 - pos];
  } else {
    team_at_pos = '0';
  }
  return team_at_pos;
}

// slice = 0 -> bord nord, slice = 1 -> la ligne de contenu du haut, etc.

void cell_print(board_t *b, int line, int row, int slice) {
  switch (slice) {
  case 0:
    // vérifier si la case est un piège
    if (b->tableau[line][row].flag == false) {
      printf(" vvv ");
    } else if (b->tableau[line][row].portal == true) {
      printf(" /-\\ ");
    } else
      printf(" --- ");
    break;
  case 1:
    char team = board_top(b, line, row);
    if (b->tableau[line][row].flag == false) {
      if (team == '0') {
        printf(">   <");
      } else {
        printf(">%c%c%c<", team, team, team);
      }
    } else {
      if (team == '0') {
        printf("|   |");
      } else
        printf("|%c%c%c|", team, team, team);
    }
    break;
  case 2:
    char team1 = board_peek(b, line, row, 1);
    char team2 = board_peek(b, line, row, 2);
    char team3 = board_peek(b, line, row, 3);

    if (b->tableau[line][row].flag == false) {
      if (team1 == '0') {
        char team = board_top(b, line, row);
        if (team == '0') {
          printf((">   <"));
        } else {
          printf(">%c%c%c<", team, team, team);
        }
      } else if (team2 == '0') {
        printf(">");
        printf("%c%c%c", team1 - 'A' + 'a', team1 - 'A' + 'a',
               team1 - 'A' + 'a');
        printf(">");
      } else if (team3 == '0') {
        printf(">%c %c<", team1 - 'A' + 'a', team2 - 'A' + 'a');
      } else {
        printf(">%c%c%c<", team1 - 'A' + 'a', team2 - 'A' + 'a',
               team3 - 'A' + 'a');
      }
    } else {
      if (team1 == '0') {

        char team = board_top(b, line, row);
        if (team == '0') {
          printf("|   |");
        } else
          printf("|%c%c%c|", team, team, team);
      }

      else if (team2 == '0') {
        printf("|");
        printf("%c%c%c", team1 - 'A' + 'a', team1 - 'A' + 'a',
               team1 - 'A' + 'a');
        printf("|");

      }

      else if (team3 == '0') {
        printf("|%c %c|", team1 - 'A' + 'a', team2 - 'A' + 'a');
      }

      else
        printf("|%c%c%c|", team1 - 'A' + 'a', team2 - 'A' + 'a',
               team3 - 'A' + 'a');
    }

    break;

  case 3:
    if (b->tableau[line][row].flag == false) {
      printf(" ^^^ ");
    }

    else if (b->tableau[line][row].portal == true) {
      printf(" \\_/ ");

    } else {

      int hieght_stack = board_height(b, line, row);
      if (hieght_stack > 1) {
        printf(" -%d- ", hieght_stack);
      } else
        printf(" --- ");
    }

    break;

  default:
    break;
  }
}

void board_print(board_t *b, int highlighted_line) {
  int line, row;
  printf("   ");
  for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
    printf("  %c  ", 'a' + row);
    printf("   ");
  }
  printf("\n");
  for (line = 0; line < TAILLE_TABLEAU_LIGNE; line++) {
    printf("   ");

    for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
      cell_print(b, line, row, 0);
      printf("   ");
    }

    printf("\n");
    if (line + 1 == highlighted_line) {
      printf(" > ");
    } else
      printf("   ");

    for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
      cell_print(b, line, row, 1);
      printf("   ");
    }

    printf("\n");
    if (line + 1 == highlighted_line) {
      printf("%d> ", line + 1);
    } else
      printf("%d  ", line + 1);

    for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
      cell_print(b, line, row, 2);
      printf("   ");
    }

    printf("\n");
    if (line + 1 == highlighted_line) {
      printf(" > ");
    } else
      printf("   ");

    for (row = 0; row < TAILLE_TABLEAU_COLONNE; row++) {
      cell_print(b, line, row, 3);
      printf("   ");
    }
    printf("\n");
  }
}

void menu_affichage() {
  printf(" ________________                                                  "
         "____________                                                         "
         "      \n");
  printf("|                |                             ___                /  "
         "          \\                                                         "
         "     \n");
  printf("|____       _____|                            |   |              /   "
         "  _____    \\                                                        "
         "     \n");
  printf("     |     |                                  |   |             /    "
         " |     |    \\                                                       "
         "     \n");
  printf("     |     |                                  |   |            /     "
         " |     |     \\ ______                                               "
         "    \n");
  printf("     |     |                                  |   |            |     "
         " |_____|     ||    _  \\                                             "
         "     \n");
  printf("     |     |        __________     _______    |   |            |     "
         "             ||   | |  |    _________     _______    _________       "
         "   \n");
  printf("     |     |       /          \\   /  ___  \\   |   |            |   "
         "   ______      ||   |_|  /   /         \\   /  ___  \\  /         \\ "
         "        \n");
  printf("     |     |      /    __      \\ /  /   \\  \\  |   |            |  "
         "   |      |     ||    ___/   /    __     \\ /  /   \\  \\ |    __   "
         "|         \n");
  printf("     |     |      |   /  \\     ||   \\___/   / |   |            |   "
         "  |      |     ||   |   \\  |    /  \\    ||   \\___/  / |   /  \\  "
         "|         \n");
  printf(" ____|     |_____ \\   \\__/     ||        ___/_|   |______      |   "
         "  |      |     ||   |    \\  \\   \\__/    ||      ___/_ |   |  |  | "
         " __     \n");
  printf("|                | \\           | \\           ||          |     |   "
         "  |      |     ||   |\\    \\  \\          | \\          ||   |  |  "
         "| /  \\    \n");
  printf("|________________|  |______    |  \\__________||__________|     "
         "|_____|      |_____||___| \\____\\  |_____    |  \\_________||___|  "
         "|__| \\__/    \n");
  printf(
      "		           |   |                                               "
      "                        |   |                                 \n");
  printf(
      "			   |   |                                               "
      "                        |   |                                 \n");
  printf(
      "	                   |   |                                               "
      "                        |   |                                 \n");
  printf(
      "			   |   |                                               "
      "                        |   |                                  \n");
  printf(
      "			   |   |                                               "
      "                        |   |                                 \n");
  printf(
      "			   |   |                                               "
      "                        |   |                                 \n");
  printf(
      "			    \\__/                                              "
      "                          \\__/                                 \n");
  printf("------------------------------------------------MENU-----------------"
         "-------------------------------\n");
}
