#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

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
/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
*
*
*
*
* Example of a struct to hold state machine data:
*
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

#endif
