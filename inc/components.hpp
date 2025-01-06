#pragma once
#include "arrayKey.hpp"
#include "debugPVZ/debug.hpp"
#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include <map>
#include <tyra>
#include <vector>


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
  std::vector<int> plantID;
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

  void move(const int entityID, float offsetX, float offsetY);
  bool collision(const BoxCollider* box);
  bool pointCollision(const Tyra::Vec2* point);
  float x;
  float y;
  float width;
  float height;
};

struct TriggerBoxCollider {
 public:
  std::vector<int> idBoxCol;
};

enum enumProyectile { pea, snowPea, ExplosionPowie, ExplosionSpudow };

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

class ZombieRow {
 public:
  int zombiesInRow = 0;
  int maxZombiesInRow = 0;
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
extern ArrayKey<int, FatherID> fatherIDArray;
extern ArrayKey<int, Tyra::Vec2> texPosArray;
extern ArrayKey<int, Tyra::Vec2> posArray;
extern ArrayKey<int, Tyra::Vec2> finalPosArray;
extern ArrayKey<int, Tyra::Sprite> spriteArray;
extern ArrayKey<int, int> spriteRenderIDArray;
// extern std::vector<int> spriteNormalIdStopRender; useless maybe
// extern std::vector<int> animationIdStopRender; useless maybe
extern ArrayKey<int, Tyra::Vec2> angleArray;
extern std::unordered_map<int, Tyra::Vec2>
    originalSize;  // Is the size of the Texture animation
extern std::unordered_map<int, Tyra::Vec2>
    scaleTexture;  // This multiply the size of the texture animation
extern std::unordered_map<int, Tyra::Vec2> pointColliderArray;
extern std::unordered_map<int, BoxCollider> boxColliderArray;
extern std::unordered_map<int, TriggerBoxCollider> resultBoxCollider;
extern ArrayKey<int, PS2Timer> timerArray;
extern std::unordered_map<int, float> speedArray;
extern std::unordered_map<int, int> damageArray;
extern ArrayKey<int, int> lifeArray;
extern std::map<int, Tyra::Vec2> pivot;
extern std::map<int, Controller> controller;

extern std::vector<Proyectile> projectile;
extern std::vector<Explosion> explosion;
extern std::vector<Card> cards;
extern std::vector<LawnMower> lawnMower;
extern std::map<int, Cursor> cursor;
extern std::map<int, DeckCursor> deckCursor;

extern int zombiescreated;
extern ZombieRow zombieCreateRow[5];
extern bool mapEnable[5];
extern bool plantCreatedInMap[5][9];
extern BoxCollider mapCollider[5][9];
extern Tyra::Vec2 camera;
