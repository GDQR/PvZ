#pragma once

#include "plants.hpp"
#include "reward.hpp"
#include "sun.hpp"
#include "zombie.hpp"
#include "imageTools.hpp"
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

class BackgroundEntity{
  public:
  std::vector<int> id;
  int rowTextures;
  void initJPG(const char* JPGfile, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight);
  void initJPG(Tyra::Texture* texture, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight);
  void move();
  void scale();
  void scaleTest(int width, int height);
};


const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<Zombie> zombie;
extern std::vector<Zombie> deadZombie;
extern std::vector<Zombie> damagedZombie;

extern bool rewardExist;
extern Tyra::Vec2 cameraPos;

class Player{
  public:
  // Player(Tyra::Vec2 cursorPos, Tyra::Vec2 deckCursorPos);
  void init();
  void initCursor(Tyra::Vec2 cursorPos);
  void initDeckCard(Tyra::Vec2 pos);
  int id;
};

namespace Entity {
  extern int background;
  extern BackgroundEntity backgroundIDs;
  extern BackgroundEntity awardbackground;
  extern int sodRoll;
  extern int sodRollCap;
  extern int sodRollRow1;
  extern int sodRollRow1Alpha;
  extern int sod3Row;
  extern int sod3RowAlpha;
  extern Player player;
  extern Reward reward;
}