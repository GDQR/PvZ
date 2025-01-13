#pragma once

#include <iostream>
#include <string>
#include <vector>


enum Game_States_enum {main, level1, level2, lastGameState };

// estructura que guarda los nombres de los diferentes estados/niveles
// funciona como una escena/scene
struct States {
  std::vector<std::string> name;
  std::vector<bool> isActive;
};

extern States states;
extern int actualState;
