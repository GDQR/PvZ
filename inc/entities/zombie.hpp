#pragma once
#include <tyra>
#include <vector>
enum Zombie_State_enum { NoneZombie, normalZombie, flagZombie };

class Zombie {
 private:
  void createSpace();
 public:
  Zombie_State_enum type = NoneZombie;

  int timer = 0;
  int attackTimer = 0;

  int father;
  std::vector<int> id;
  bool attack = false;
  bool damaged = false;
  bool debug = false;
  void newZombie(Zombie_State_enum newType);
  int move();
  void animation(const int entityID, const int animID);
  int attackPlant();
  void damage(const int entityID);
  int normalColor();
  bool erase();
};

void createZombie(Tyra::Vec2 pos, const Zombie_State_enum type);