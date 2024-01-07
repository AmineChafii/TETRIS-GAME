#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

#include "controller.h"
#include "view.h"
#include "model.h"
#include "util.h"


#define COLS_PER_CELL 2
/*
  Macro pour une cellule d'un type spécifique dans une fenêtre.
 */
#define ADD_BLOCK(w,x) waddch((w),' '|A_REVERSE|COLOR_PAIR(x));     \
                       waddch((w),' '|A_REVERSE|COLOR_PAIR(x))
#define ADD_EMPTY(w) waddch((w), ' '); waddch((w), ' ')


int main(int argc, char **argv)
{
  tetris_game *tg;
  tetris_move move = TM_NONE;
  bool running = true;
  WINDOW *board, *next, *hold, *score;

  // Charger le fichier si on lui donne un nom de fichier.
  if (argc >= 2) {
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("tetris");
      exit(EXIT_FAILURE);
    }
    tg = tg_load(f);
    fclose(f);
  } else {
    // Sinon, créez un nouveau jeu.
    tg = tg_create(22, 10);
  }

  // Initialisation NCURSES :
  initscr();             // initialiser les malédictions
  cbreak();              // passer la touche enfoncée pour programmer, mais pas de signaux
  noecho();              // ne pas affihcer aux pressions sur les touches pour afficher l'écran
  keypad(stdscr, TRUE);  // autoriser les touches fléchées
  timeout(0);            // pas de blocage sur getch()
  curs_set(0);           // mettre le curseur sur invisible
  init_colors();         // configurer les couleurs de Tetris

  // Créer des fenêtres pour chaque section de l'interface.
  board = newwin(tg->rows + 2, 2 * tg->cols + 2, 0, 0);
  next  = newwin(6, 10, 0, 2 * (tg->cols + 1) + 1);
  hold  = newwin(6, 10, 7, 2 * (tg->cols + 1) + 1);
  score = newwin(6, 10, 14, 2 * (tg->cols + 1 ) + 1);

  // Game loop
  while (running) {
    move = gestionDesEntrees(tg, board);
    running = tg_tick(tg, move);
    display_board(board, tg);
    display_piece(next, tg->next);
    display_piece(hold, tg->stored);
    display_score(score, tg);
    doupdate();
    sleep_milli(10);
  }
  //Désinitialiser Ncurses
  wclear(stdscr);
  endwin();

  // Fin de la sortie Message de fin
  printf("Game over!\n");
  printf("You finished with %d points on level %d.\n", tg->points, tg->level);

  // Désinitialiser Tetris
  tg_delete(tg);
  return 0;
}