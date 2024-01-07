#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h> 
#include <stdbool.h> 

/*
  Convertisser un type tétromino en sa cellule correspondante.
 */
#define TYPE_TO_CELL(x) ((x)+1)

/*
  Chaînes expliquant comment afficher un tableau Tetris.
 */
#define TC_EMPTY_STR " "
#define TC_BLOCK_STR "\u2588"

#define TC_IS_EMPTY(x) ((x) == TC_EMPTY)
#define TC_IS_FILLED(x) (!TC_IS_EMPTY(x))

/*
  NB cellule
 */
#define TETRIS 4
/*
  NB tetrominos?
 */
#define NUM_TETROMINOS 7
/*
  NB d'orientations d'un tétromino
 */
#define NUM_ORIENTATIONS 4

/*
  Constantes de niveau.
 */
#define MAX_LEVEL 19
#define LINES_PER_LEVEL 10

/*
  Une cellule est un bloc 1x1 dans un tableau Tetris.
 */
typedef enum {
  TC_EMPTY, TC_CELLI, TC_CELLJ, TC_CELLL, TC_CELLO, TC_CELLS, TC_CELLT, TC_CELLZ
} tetris_cell;

/*
  Un type est un type/forme d'un tétromino. Sans compter l'orientation.
 */
typedef enum {
  TET_I, TET_J, TET_L, TET_O, TET_S, TET_T, TET_Z
} tetris_type;

/*
  Une paire de lignes et de colonnes. Les nombres négatifs sont autorisés, car nous en avons besoin pour
  compensations.
 */
typedef struct {
  int row;
  int col;
} tetris_location;

/*
  Un bloc est une structure qui contient des informations sur un tétromino.
  Plus précisément, de quel type il s’agit, quelle orientation il a et où il se trouve.
 */
typedef struct {
  int typ;
  int ori;
  tetris_location loc;
} tetris_block;

/*
  Tous les mouvements possibles à donner en entrée au jeu.
 */
typedef enum {
  TM_LEFT, TM_RIGHT, TM_CLOCK, TM_COUNTER, TM_DROP, TM_HOLD, TM_NONE
} tetris_move;

typedef struct {
  /*
    Objets du plateau de jeu :
   */
  int rows;
  int cols;
  char *board;
  /*
    Informations de Score :
   */
  int points;
  int level;
  /*
    Le bloc qui tombe est celui qui descend actuellement. Le bloc suivant est celui qui
    va tomber après celui-ci. Le bloc que vous pouvez échanger est stocké.
   */
  tetris_block falling;
  tetris_block next;
  tetris_block stored;
  /*
    Nombre de ticks de jeu jusqu'à ce que le bloc descende.
   */
  int ticks_till_gravity;
  /*
    Nombre de lignes jusqu'à ce que vous passiez au niveau suivant.
   */
  int lines_remaining;

  bool running;
} tetris_game;


/*
  Ce tableau stocke toutes les informations nécessaires sur les cellules remplies par
  chaque tétromino. Le premier indice est le type du tétromino (c'est-à-dire la forme,
  par exemple. I, J, Z, etc.). L'indice suivant est l'orientation (0-3). Le final
  Le tableau contient 4 objets tetris_location, chacun correspondant à un décalage par rapport à un
  point en haut à gauche qui est "l'origine" du tétromino.
 */
extern tetris_location TETROMINOS[NUM_TETROMINOS][NUM_ORIENTATIONS][TETRIS];

/*
  Ce tableau vous indique le nombre de ticks par gravité et par niveau. Diminue avec le niveau
  augmente, pour ajouter de la difficulté.
 */
extern int GRAVITY_LEVEL[MAX_LEVEL+1];

// Manipulation de la structure des données.
void tg_init(tetris_game *obj, int rows, int cols);
tetris_game *tg_create(int rows, int cols);
void tg_destroy(tetris_game *obj);
void tg_delete(tetris_game *obj);
tetris_game *tg_load(FILE *f);
void tg_save(tetris_game *obj, FILE *f);

// Méthodes publiques non liées à la mémoire :
char tg_get(tetris_game *obj, int row, int col);
bool tg_check(tetris_game *obj, int row, int col);
bool tg_tick(tetris_game *obj, tetris_move move);
void tg_print(tetris_game *obj, FILE *f);
void tg_move(tetris_game *obj, int direction); 
void tg_rotate(tetris_game *obj, int direction);
void tg_down(tetris_game *obj);

#endif 
