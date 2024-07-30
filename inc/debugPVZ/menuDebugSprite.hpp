#pragma once
#include <tyra>
#include "debugPVZ/menuDebugCommands.hpp"

enum enumDebugSpriteMode {firstMenu, secondMenu };
extern bool startSpriteDebug;

class DebugSpriteMode{
 public:
 enumDebugSpriteMode drawState = enumDebugSpriteMode::firstMenu; 
 int init();
 void menu();
 void drawMenu();
 void firstMenu();
 void drawFirstMenu();
 void secondMenu();
 void drawSecondMenu();
};

extern DebugSpriteMode debugSpriteMode;