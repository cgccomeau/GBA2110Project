#ifndef FLOW_H
#define FLOW_H
#include "images/garbage.h"
#include "images/elon.h"
#include "images/pikachu.h"
#include "images/bart.h"
#include "images/gt.h"
#include "images/shibainu.h"
#include "gba.h"
#include "game.h"

void startFunction(u32 *prevButtons, u32 *currButtons, GBAState *state, playState *cs);
void playFunction(u32 *prevButtons, u32 *currButtons, GBAState *state, playState *cs);
void winFunction(u32 *prevButtons, u32 *currButtons, GBAState *state);
void loseFunction(u32 *prevButtons, u32 *currButtons, GBAState *state, playState *cs);
void playSetUp(u32 *prevButtons, u32 *currButtons, playState *cs, GBAState *state);


#endif