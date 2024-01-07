#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "model.h"
#include <ncurses.h>
#include "util.h"

#define COLS_PER_CELL 2

#define ADD_BLOCK(w,x) waddch((w),' '|A_REVERSE|COLOR_PAIR(x));     \
                       waddch((w),' '|A_REVERSE|COLOR_PAIR(x))
#define ADD_EMPTY(w) waddch((w), ' '); waddch((w), ' ')


tetris_move gestionDesEntrees(tetris_game *tg, WINDOW *board) {
    tetris_move move = TM_NONE;
    int input = getch();

    switch (input) {
        case KEY_LEFT:
            move = TM_LEFT;
            break;
        case KEY_RIGHT:
            move = TM_RIGHT;
            break;
        case KEY_UP:
            move = TM_CLOCK;
            break;
        case KEY_DOWN:
            move = TM_DROP;
            break;
        case 'q':
            tg->running = false;
            move = TM_NONE;
            break;
        case 'p':
            wclear(board);
            box(board, 0, 0);
            wmove(board, tg->rows/2, (tg->cols*COLS_PER_CELL-6)/2);
            wprintw(board, "PAUSED");
            wrefresh(board);
            timeout(-1);
            getch();
            timeout(0);
            move = TM_NONE;
            break;
        case 's':
            save(tg, board);
            move = TM_NONE;
            break;
        case ' ':
            move = TM_HOLD;
            break;
        default:
            move = TM_NONE;
    }
 return move;
}