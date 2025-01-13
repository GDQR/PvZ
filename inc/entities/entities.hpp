#pragma once

#include "plants.hpp"
#include "reward.hpp"
#include "sun.hpp"
#include "zombie.hpp"
#include <unordered_map>
#include <vector>

enum enumComponents {
  pos,
  finalPos,
  texPos,
  angle,
  sprite,
  spriteRender,
  animation,
  timer,
  life,
  fatherID
};

class Entities {
 public:
  static unsigned int counter;
  static std::vector<unsigned int> aliveEntities;
  static std::vector<unsigned int> deadEntities;

  static unsigned int newID();
  static void deleteID(int& id);
  static void deleteID(unsigned int& id);
};

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<Zombie> zombie;
extern int player;
extern Reward reward;
extern bool rewardExist;
extern Tyra::Vec2 cameraPos;