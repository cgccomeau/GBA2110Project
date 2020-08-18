#ifndef GAME_H
#define GAME_H

#include "gba.h"

typedef struct square {
    int row;
    int col;
    int rd;
    int cd;
    const u16 *image;
} Square;

typedef struct obstacle {
    int row;
    int col;
    int rd;
    int cd;
    const u16 *image;
} Obstacle;

#define MAXOBSTACLES 6

typedef struct playState {
    Square square;
    Obstacle obstacle[MAXOBSTACLES];
    int numOBS;
    int numDeaths;
} playState;

typedef enum {
  START,
  PLAY,
  WIN,
  LOSE,
} GBAState;

#endif
