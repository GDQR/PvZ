#pragma once
#include <tyra>
#include "debugPVZ/menuDebugCommands.hpp"

extern bool startSpriteDebug;

class DebugSpriteMode{
 public:
 std::string name;
 void menu();
 void drawMenu();
 void firstMenu();
 void drawFirstMenu();
 void secondMenu();
 void drawSecondMenu();
};

extern DebugSpriteMode debugSpriteMode;