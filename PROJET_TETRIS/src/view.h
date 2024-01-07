#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>
#include "model.h"

void display_board(WINDOW *w, tetris_game *obj);
void display_piece(WINDOW *w, tetris_block block);
void display_score(WINDOW *w, tetris_game *tg);
void boss_mode(void);
void save(tetris_game *game, WINDOW *w);
void init_colors(void);

#endif /* VIEW_H */
