#pragma once
#include <tyra>
#include <vector>
#include <map>
#include "arrayKey.hpp"
#include "debugPVZ/debug.hpp"
#include "renderSprite/textures.hpp"
#include "renderSprite/animations.hpp"
#include "entities/plants.hpp"
#include "entities/zombie.hpp"
#include "entities/sun.hpp"

// enum enumAnimation {
//   zombieWalk,
//   zombieNormalAttack
// };
// enum enumCommands {
//   level1,
//   debug
// };

class Controller {
 public:
  unsigned int index;
  void update(const int entityID);
};

class FatherID {
 public:
  std::vector<int> id;
  void update(const int entityID);
};

class Cursor {
 public:
  int id = -1;
  Vec2 cursorTile;
  int cursorTimer = 0;
  float cursorSpeed = 1;
  void move();
};

class DeckCursor {
 public:
  int id = -1;
  int pos = 0;
  void moveLeft();
  void moveRight();
};

class Card {
 public:
  int seed;
  int seedShadow;
  int seedShadowTimer;
  Plant_State_enum plant;
  int cost;
  void update();
};

class LawnMower {
 public:
  std::vector<int> id;
};

class BoxCollider {
 public:
  BoxCollider();
  BoxCollider(float x, float y, float width, float height);
  BoxCollider(float x, float y, float width, float height, float offsetX,
              float offsetY);
  void move(const int entityID);
  bool collision(BoxCollider* box);
  float x;
  float y;
  float width;
  float height;
  float offsetX;
  float offsetY;
};

class PlantsManager {
 public:
  void create();
  void update();
};

enum enumProyectile { pea, snowPea, ExplosionPowie, ExplosionSpudow};

class Proyectile {
 public:
  int id;
  enumProyectile type;
  bool move();
  void erase();
};

class Explosion {
 public:
  int id;
  enumProyectile type;
  void erase();
};

class PS2Timer {
 public:
  PS2Timer();
  u64 lastTime;
  u64 actualTime;
  u64 counterMS = 0;
  u64 maxMS = 1000;
  void setLastTime();
  u64 getTimeInMS();
  void resetCounter();
  void addMSinCounter();
};

extern Tyra::Engine* engine;
extern Tyra::Renderer* renderer;
extern const Tyra::PadJoy* leftJoy;
extern Tyra::TextureRepository* texRepo;
extern std::unordered_map<int, std::vector<int>> m_animID;

// sparse array
extern ArrayKey<int, Animation>
    animationArray;  // Link the sprite with the texture
extern std::unordered_map<int, AnimationData>
    animationDataArray;  // Save the animation textures
extern std::map<int, FatherID> fatherIDArray;
extern ArrayKey<int, Tyra::Vec2> texPosArray;
extern ArrayKey<int, Tyra::Vec2> posArray;
extern ArrayKey<int, Tyra::Vec2> finalPosArray;
extern ArrayKey<int, Tyra::Sprite> spriteArray;
extern ArrayKey<int, int> spriteRenderIDArray;
extern std::vector<int> spriteNormalIdStopRender;
extern std::vector<int> animationIdStopRender;
extern ArrayKey<int, Tyra::Vec2> angleArray;
extern std::unordered_map<int, Tyra::Vec2> originalSize;
extern std::unordered_map<int, Tyra::Vec2> scaleTexture;
extern std::map<int, Tyra::Vec2> pointColliderArray;
extern std::map<int, BoxCollider> boxColliderArray;
extern ArrayKey<int, PS2Timer> timerArray;
extern std::map<int, float> speedArray;
extern std::map<int, int> damageArray;
extern ArrayKey<int, int> lifeArray;
extern std::map<int, Tyra::Vec2> pivot;
extern std::map<int, Controller> controller;

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Zombie> zombie;
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<Proyectile> projectile;
extern std::vector<Explosion> explosion;
extern std::vector<Card> cards;
extern std::vector<LawnMower> lawnMower;
extern int player;
extern std::map<int, Cursor> cursor;
extern std::map<int, DeckCursor> deckCursor;

extern int zombiescreated;
extern bool zombieCreateRow[5];
extern bool plantCreatedInMap[5][9];
extern BoxCollider mapCollider[5][9];

extern PlantsManager plantsManager;

void createCard(Plant_State_enum typePlant, Vec2 pos, bool isVersusMode);