#include "plateau.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lance_de() { return rand() % TAILLE_TABLEAU_LIGNE + 1; }

void vertical_move(board_t *board, char team) {
  char choice[10];
  bool valid_input = false;
  int line;
  int direction = -1;
  char row, top, herisson;

  while (true) {
    top = '0';
    while (valid_input != true) {
      printf("Quel herisson voulez-vous déplacer verticalement (format : ligne "
             "colonne) : ");
      fgets(choice, 10, stdin);

      if (sscanf(choice, "%d %c", &line, &row) != 2) {
        printf("Erreur veiller saisir des coordonées valide\n");
        continue;
      } else if (line < 1 || line > TAILLE_TABLEAU_LIGNE) {
        printf("Erreur, la ligne est en dehors du plateau\n");
        continue;
      } else if (row < 'a' || row > 'a' + TAILLE_TABLEAU_COLONNE - 1) {
        printf("Erreur, la colonne est en dehors du plateau\n");
        continue;
      } else {
        valid_input = true;
      }
    }

    top = board_top(board, line - 1, (int)(row - 'a'));
    if (top == '0') {
      printf("La case sélectionnée est vide\n");
      continue;
    } else if (top != team) {
      printf("Le herisson sélectionné n'est pas le votre\n");
      continue;
    }

    int line_array_position = line - 1;
    int row_array_position = row - 'a';

    valid_input = false;
    while (valid_input != true) {
      printf("Dans quel direction voulez-vous déplacer votre herisson (1 pour "
             "haut et 0 pour bas) : ");
      fgets(choice, 10, stdin);
      if (((choice[0] == '0') || (choice[0] == '1')) && choice[1] == '\n') {
        valid_input = true;
        direction = choice[0] - '0';
      } else {
        printf("Veuillez saisir 0 ou 1\n");
        continue;
      }
    }
    if (direction == 1) {
      if (line_array_position == 0) {
        printf("Impossible de se déplacer vers le haut, veuillez choisir un "
               "autre hérisson\n");
        continue;
      } else if (board_height(board, line_array_position - 1,
                              row_array_position) <=
                 TAILLE_MAX_PILE_HERISSON - 1) {
        herisson = board_pop(board, line_array_position, row_array_position);
        board_push(board, line_array_position - 1, row_array_position,
                   herisson);
        printf("Hérisson déplacé avec succès vers le haut !\n");
        break;
      } else {
        printf("Impossible de déplacer l'hérisson car la case est pleine...\n");
        continue;
      }
    } else if (direction == 0) {
      if (line_array_position == TAILLE_TABLEAU_LIGNE - 1) {
        printf("Impossible de se déplacer vers le bas, veuillez choisir un "
               "autre hérisson\n");
        continue;
      } else if (board_height(board, line_array_position + 1,
                              row_array_position) <=
                 TAILLE_MAX_PILE_HERISSON - 1) {
        herisson = board_pop(board, line_array_position, row_array_position);
        board_push(board, line_array_position + 1, row_array_position,
                   herisson);
        printf("Hérisson déplacé avec succès vers le bas !\n");
        break;
      } else {
        printf("Impossible de déplacer l'hérisson car la case est pleine...\n");
        continue;
      }
    } else
      printf("Entrée invalide : 1 pour haut et 0 pour bas\n");
  }
}

bool hedgehog_behind(board_t *board, int line, int row) {
  bool herisson_behind = false;
  for (int j = 0; j < row; j++) {
    if (board_top(board, line, j) != '0') {
      herisson_behind = true;
    }
  }
  return herisson_behind;
}

bool hedgehog_on_the_line(board_t *board, int line) {
  bool result = false;
  if (line < 0 || line > TAILLE_TABLEAU_LIGNE) {
    return false;
  } else {
    for (int i = 0; i < TAILLE_TABLEAU_COLONNE - 1; i++) {
      if (board_top(board, line - 1, i) != '0') {
        result = true;
        break;
      }
    }
  }
  return result;
}

void forward_move(board_t *board, int line, char team) {
  char row, top, hedgehog;
  char choice[10];
  bool valid_input = false;

  if (hedgehog_on_the_line(board, line) == false) {
    printf("Aucun hérisson déplacable sur la ligne\n");
    return;
  }

  while (true) {
    while (valid_input != true) {
      printf("Quel herisson voulez-vous déplacer vers l'avant : ");
      fgets(choice, 10, stdin);
      if (((choice[0] >= 'a' && choice[0] < 'a' + TAILLE_TABLEAU_COLONNE) ||
           (choice[0] >= 'A' && choice[0] < 'A' + TAILLE_TABLEAU_COLONNE)) &&
          choice[1] == '\n') {
        valid_input = true;
        row = choice[0];
      } else {
        printf("Veuillez saisir une colonne valide en minuscule \n");
        continue;
      }
    }
    int row_index = (row - 'a');
    int index_line = line - 1;
    top = board_top(board, index_line, row_index);
    bool state_of_cell = cell_trap(board, index_line, row_index);

    if (row_index < 0 || row_index >= TAILLE_TABLEAU_COLONNE) {
      printf("Erreur la colonne choisit est dans dehors du plateau de jeu.\n");
      continue;
    } else if (top == '0') {
      printf("La case sélectionnée est vide\n");
      continue;
    } else if (state_of_cell & hedgehog_behind(board, index_line, row_index)) {
      printf("Impossible de déplacer un hérisson dans une case piègée tant "
             "qu'il y a d'autres hérissons dérière sur la même ligne\n");
      continue;
    } else if (row_index == TAILLE_TABLEAU_COLONNE - 1) {
      printf(
          "Impossible de déplacer des hérissons qui sont arrivés à la fin\n");
      continue;
    } else {
      hedgehog = board_pop(board, line - 1, row_index);
      board_push(board, line - 1, row_index + 1, hedgehog);
      printf("Le herisson a avancé d'une case ! \n");
      if (row_index == TAILLE_TABLEAU_COLONNE - 2) {
        increase_winning_herisson(board, hedgehog);
      }
      break;
    }
  }
}

void playgame() {
  char menu_choice[10];
  int vertical_response;
  bool valid_input = false;
  srand(time(NULL));
  board_t *board = create_board();
  initgame(board);
  menu_affichage();

  while (1) {
    printf("Bienvenue dans le jeu : \n");
    printf("1. Jouer sans extension\n");
    printf("2. Jouer avec l'extension\n");
    printf("3. Credits\n");

    fgets(menu_choice, 10, stdin);

    if (menu_choice[0] == '1' && menu_choice[1] == '\n') {
      system("clear");
      printf("Que le jeu commence ! \n");
      break;
    } else if (menu_choice[0] == '2' && menu_choice[1] == '\n') {
      system("clear");
      printf("Dans cette extension, certains cases sont des portails, si vous "
             "placer dans hérisson dans un téléporteur il sera alors "
             "téléporter dans sur un autre portail\n");
      printf("Que le jeu commence ! \n");
      break;
    } else if (menu_choice[0] == '3' && menu_choice[1] == '\n') {
      system("clear");
      printf("Creators : Nowar & Benjamin :)\n");
      printf("\n\n\n\n\n");
    } else {
      printf("Entrée invalide. Veuillez entrer 1 ou 2.\n");
    }
  }

  while (!winning_condition(board)) {
    for (int i = 0; i < NOMBRE_DE_JOUEUR; i++) {
      valid_input = false;
      char choice[10];
      int random_tirage = lance_de();
      board_print(board, random_tirage);
      printf("Le dé est tombé sur  : %d\n", random_tirage);
      printf("L'équipe %c joue \n", i + 'A');

      while (valid_input == false) {
        printf("Voulez vous déplacer un hérisson verticalement (1 pour oui, 0 "
               "pour non) : ");
        fgets(choice, 10, stdin);
        if (((choice[0] == '0') || (choice[0] == '1')) && choice[1] == '\n') {
          valid_input = true;
          vertical_response = choice[0] - '0';
        } else {
          printf("Veuillez saisir 0 ou 1\n");
          continue;
        }
      }

      if (vertical_response == 1) {
        if (!(movable_herisson(board, i + 'A'))) {
          printf("Pas de hérisson déplacable verticalement\n");
        } else {
          vertical_move(board, 'A' + i);
        }
      }
      for (int i = 0; i < 20; i++) {
        printf("\n");
      }
      board_print(board, random_tirage);
      printf("L'équipe %c joue \n", i + 'A');
      forward_move(board, random_tirage, 'A' + i);

      for (int i = 0; i < 20; i++) {
        printf("\n");
      }
    }
  }

  // afficher les résultats
  int *score = get_score_array(board);
  int printed = 0;
  int place = 1;
  int max_herisson1 = NOMBRE_HERISSON - 1;
  int max_herisson2 = 0;
  int n = 0;
  while (printed < NOMBRE_DE_JOUEUR) {
    printf("- Place #%d : ", place);
    for (int i = 0; i < NOMBRE_DE_JOUEUR; i++) {
      if (score[i] == max_herisson1) {
        printf("équipe %c, ", 'A' + i);
        printed++;
        n++;
      } else if (max_herisson2 < score[i])
        max_herisson2 = score[i];
    }
    place += n;
    n = 0;
    printf("(avec %d hérissons);", max_herisson1);
    printf("\n");
    max_herisson1 = max_herisson2;
  }
}