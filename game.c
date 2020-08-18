#include "game.h"
#include "images/garbage.h"
#include "images/elon.h"
#include "images/pikachu.h"
#include "images/bart.h"
#include "images/gt.h"
#include "images/shibainu.h"
#include <stdio.h>
#include <stdlib.h>

#include "flow.h"
#include "gba.h"


int main(void) {
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial game state
  GBAState state = START;
  playState cs;

  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons
    waitForVBlank();

    switch (state) {
      case START:
        startFunction(&previousButtons, &currentButtons, &state, &cs);
        break;
      case PLAY:
        playFunction(&previousButtons, &currentButtons, &state, &cs);
        break;
      case WIN:
        winFunction(&previousButtons, &currentButtons, &state);
        break;
      case LOSE:
        loseFunction(&previousButtons, &currentButtons, &state, &cs);
        break;
    }

    previousButtons = currentButtons;  // Store the current state of the buttons
  }

  return 0;
}