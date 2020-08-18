#include "flow.h"
#include <stdio.h>
#include <stdlib.h>

void startFunction(u32 *prevButtons, u32 *currButtons, GBAState *state, playState *cs) {
    drawFullScreenImageDMA(bart);
    char start[] = "Press START to begin";
    drawString(HEIGHT/4, WIDTH/4, start, BLUE);
    int startCond = 1;
    while(startCond) {
      *currButtons = BUTTONS;
      if (KEY_JUST_PRESSED(BUTTON_START, *currButtons, *prevButtons)) {
        *state = PLAY;
        startCond--;
      }
      *prevButtons = *currButtons;
    }
    cs->numDeaths = 0;

    playSetUp(prevButtons, currButtons, cs, state);
}

void playSetUp(u32 *prevButtons, u32 *currButtons, playState *cs, GBAState *state) {
    drawFullScreenImageDMA(elon);
    char play[] = "Press START to play";
    drawString(HEIGHT/8, WIDTH/4, play, RED);
    char death[11];
    sprintf(death, "DEATHS: %d", cs->numDeaths);
    drawString(7 * HEIGHT/8 + 5, WIDTH/4, death, RED);
    int test = 1;
    while(test) {
      *currButtons = BUTTONS;
      if (KEY_JUST_PRESSED(BUTTON_START, *currButtons, *prevButtons)) {
        drawRectDMA(HEIGHT/4, WIDTH/4, WIDTH/2, 15 * 6 + 7, RED);
        drawRectDMA(HEIGHT/4, WIDTH/8, WIDTH/8, WIDTH/8, YELLOW);
        drawRectDMA(15 * 6 + 7 - WIDTH/8 + HEIGHT/4, 3 * WIDTH/4, WIDTH/8, WIDTH/8, YELLOW);
        test--;
      }
      if (KEY_JUST_PRESSED(BUTTON_SELECT, *currButtons, *prevButtons)) {
        *state = START;
        test--;
        }
      *prevButtons = *currButtons;
    }
    cs->square.row = HEIGHT/4;
    cs->square.col = WIDTH/8;
    cs->square.image = gt;
    drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);

    for (int i = 0; i < MAXOBSTACLES; i++) {
        cs->obstacle[i].row = HEIGHT / 4 + 15 * i + 7;
        if (i % 2 == 0) {
            cs->obstacle[i].col = 3 * WIDTH / 4 - GARBAGE_WIDTH;
            cs->obstacle[i].cd = -1;
        } else {
            cs->obstacle[i].col = WIDTH / 4;
            cs->obstacle[i].cd = 1;
        }
        cs->obstacle[i].rd = 0;
        cs->obstacle[i].image = garbage;
        drawImageDMA(cs->obstacle[i].row, cs->obstacle[i].col, GARBAGE_WIDTH, GARBAGE_HEIGHT, garbage);
    }
}

void playFunction(u32 *prevButtons, u32 *currButtons, GBAState *state, playState *cs) {
    int tempPlay = 1;
    while(tempPlay) {
      *currButtons = BUTTONS;
      if (KEY_DOWN(BUTTON_UP, BUTTONS) && cs->square.row > HEIGHT/4
        && cs->square.col + 10 <= 3 * WIDTH/4) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.row -= 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_UP, BUTTONS) && cs->square.row > HEIGHT/2 + 28 &&
        cs->square.col + 10 <= 7 * WIDTH/8 && cs->square.col > 3 * WIDTH/4) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.row -= 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && cs->square.row + 10 < HEIGHT/4 + 15 * 6 + 7 &&
        cs->square.col >= WIDTH/4) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.row += 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && cs->square.row + 10 < HEIGHT/4 + WIDTH/8 &&
        cs->square.col < WIDTH/4) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.row += 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && cs->square.col > WIDTH/8
        && cs->square.row + 10 <= HEIGHT/4 + WIDTH/8) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.col -= 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && cs->square.col > WIDTH/4
        && cs->square.row + 10 > HEIGHT/4 + WIDTH/8) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.col -= 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) && cs->square.col + 10 < 3 * WIDTH / 4 &&
        cs->square.row + 10 < HEIGHT/2 + 35) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.col += 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) && cs->square.col + 10 < 7 * WIDTH / 8 &&
        cs->square.row + 10 >= HEIGHT/2 + 35) {
        drawRectDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, YELLOW);
        cs->square.col += 2;
        drawImageDMA(cs->square.row, cs->square.col, GT_WIDTH, GT_HEIGHT, gt);
      }
      for (int i = 0; i < MAXOBSTACLES; i++) {
        if (cs->obstacle[i].cd > 0) {
          drawRectDMA(cs->obstacle[i].row, cs->obstacle[i].col, GARBAGE_WIDTH, GARBAGE_HEIGHT, RED);
        } else {
          drawRectDMA(cs->obstacle[i].row, cs->obstacle[i].col, GARBAGE_WIDTH, GARBAGE_HEIGHT, BLACK);
        }
        cs->obstacle[i].col += cs->obstacle[i].cd;
        if (cs->obstacle[i].col < WIDTH / 4) {
          cs->obstacle[i].col = WIDTH / 4;
          cs->obstacle[i].cd = -cs->obstacle[i].cd;
        }
        if (cs->obstacle[i].col > 3 * WIDTH / 4 - GARBAGE_WIDTH) {
          cs->obstacle[i].col = 3 * WIDTH / 4 - GARBAGE_WIDTH;
          cs->obstacle[i].cd = -cs->obstacle[i].cd;
        }
        if (((cs->square.row >= cs->obstacle[i].row && cs->square.row <= cs->obstacle[i].row + 10) ||
              (cs->square.row + 10 >= cs->obstacle[i].row && cs->square.row + 10 <= cs->obstacle[i].row + 10)) &&
              ((cs->square.col >= cs->obstacle[i].col && cs->square.col <= cs->obstacle[i].col + 10) ||
              (cs->square.col + 10 >= cs->obstacle[i].col && cs->square.col + 10 <= cs->obstacle[i].col + 10))) {
          *state = LOSE;
          tempPlay--;
          cs->numDeaths++;
        }
        drawImageDMA(cs->obstacle[i].row, cs->obstacle[i].col, GARBAGE_WIDTH, GARBAGE_HEIGHT, garbage);
      }
      if (cs->square.col + 10 > 3 * WIDTH/4) {
        *state = WIN;
        tempPlay--;
      }
      if (KEY_JUST_PRESSED(BUTTON_SELECT, *currButtons, *prevButtons)) {
        *state = START;
        tempPlay--;
      }
      *prevButtons = *currButtons;
      waitForVBlank();
    }
}

void winFunction(u32 *prevButtons, u32 *currButtons, GBAState *state) {
    drawFullScreenImageDMA(shibainu);
    char winNote1[] = "Congrats, you won!";
    char winNote2[] = "Here's a shiba inu :)";
    char winNote3[] = "Press START to start again!";
    drawString(HEIGHT/16, WIDTH/4, winNote1, WHITE);
    drawString(HEIGHT/8, WIDTH/4, winNote2, WHITE);
    drawString(7 * HEIGHT/8, WIDTH/4, winNote3, WHITE);
    int tempWin = 1;
    while(tempWin) {
      *currButtons = BUTTONS;
      if (KEY_JUST_PRESSED(BUTTON_START, *currButtons, *prevButtons) ||
        KEY_JUST_PRESSED(BUTTON_SELECT, *currButtons, *prevButtons)) {
        *state = START;
        tempWin--;
      }
      *prevButtons = *currButtons;
    }
}


void loseFunction(u32 *prevButtons, u32 *currButtons, GBAState *state, playState *cs) {
    int tempLose = 1;
    drawFullScreenImageDMA(pikachu);
    char loseNote1[] = "Oh no you lost :O";
    char loseNote2[] = "Press START to try again!";
    drawString(HEIGHT/8, WIDTH/4, loseNote1, BLACK);
    drawString(HEIGHT/4, WIDTH/4, loseNote2, BLACK);
    while(tempLose) {
      *currButtons = BUTTONS;
      if (KEY_JUST_PRESSED(BUTTON_START, *currButtons, *prevButtons)) {
        *state = PLAY;
        tempLose--;
        playSetUp(prevButtons, currButtons, cs, state);
      }
      if (KEY_JUST_PRESSED(BUTTON_SELECT, *currButtons, *prevButtons)) {
        *state = START;
        tempLose--;
      }
      *prevButtons = *currButtons;
    }
    waitForVBlank();
}