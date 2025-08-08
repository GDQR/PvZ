#pragma once

#include <iostream>
#include <string>
#include <vector>

enum Game_States_enum {sceneSelectorScreen, level1, level2, level3, level4, level5, lastGameState };

struct States {
  std::vector<bool> isActive;
};

void setScene(Game_States_enum newState);