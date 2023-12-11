#pragma once
#include <stdio.h>

enum debugModes { AnimationDebug, testDebug, debugModesSize};

extern unsigned int debugOption;

extern bool debugMode ;
extern bool debugAnimation ;
extern bool stopAnimation;

void debugMenu();
void activeDebugMode();
void deactiveDebugMode();