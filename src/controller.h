#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "model.h"

tetris_move gestionDesEntrees(tetris_game *tg, WINDOW *board);

#endif 
