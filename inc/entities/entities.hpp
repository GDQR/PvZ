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
  static std::vector<std::unordered_map<unsigned int, unsigned int>>
      componentIndex;

  static unsigned int newID();
  static void deleteID(const unsigned int id);
  static void addComponent(const unsigned int id,
                           const unsigned int componentID,
                           const unsigned int componentIDIndex);
  static void removeComponent(const unsigned int id,
                              const unsigned int componentID);
  static void clearComponent(const unsigned int componentID);
  static unsigned int getComponent(const unsigned int id,
                                   const unsigned int componentID);
};

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<Zombie> zombie;
extern int player;
extern Reward reward;
extern bool rewardExist;