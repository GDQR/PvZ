#pragma once
#include <tyra>
#include <vector>
enum Zombie_State_enum{
  NoneZombie,
  normalZombie,
  flagZombie,
  coneheadZombie,
  poleVaulterZombie,
  bucketHeadZombie
};

struct ZombieAnimation{
  int id;
  std::vector<int> entity;
};

extern std::vector<ZombieAnimation> zombieAnims;

class Zombie {
 private:
  void createSpace();

 public:
  int attackTimer = 0;

  int father;
  int boxColliderID;
  Zombie_State_enum type = NoneZombie;
  bool attack = false;
  bool damaged = false;
  bool explosion = false;
  void newZombie(Zombie_State_enum newType);
  bool explosionState();
  int move();
  int attackPlant();
  void damage(const int entityID);
  int normalColor();
  bool erase();
};

void createZombie(Tyra::Vec2 pos, const Zombie_State_enum type);
void createZombieMain();
void SetZombieAnimation(const int entityID, const int animID, const Zombie_State_enum type);

extern int maxZombies;
extern int zombiesDefeated;