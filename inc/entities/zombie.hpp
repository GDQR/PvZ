#pragma once
#include <tyra>
#include <vector>
enum Zombie_State_enum { NoneZombie, ZombieNormal };

class Zombie {
 private:
  void createSpace();
 public:
  Zombie_State_enum type = NoneZombie;

  int timer = 0;
  int attackTimer = 0;
  bool attack = false;
  bool debug = false;

  int father;
  std::vector<int> id;
  void newZombie(Zombie_State_enum newType);
  int move();
  void animation(const int entityID, const int animID);
  void damage(const int entityID);
  bool erase();
};

void createZombie(Tyra::Vec2 pos);
void createDebugZombie(Tyra::Vec2 pos);