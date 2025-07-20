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
  unsigned int playerID;
  void update();
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
  int textID;
  std::vector<int> plantID;
  void update();
};

class LawnMower {
 public:
  std::vector<int> id;
  bool canMove = false;
  void move();
};

enum BoxColliderEnum {
  BOXCOLLIDER_PLAYER,
  BOXCOLLIDER_MAP,
  BOXCOLLIDER_PLANT,
  BOXCOLLIDER_ZOMBIE,
  BOXCOLLIDER_PROYECTILE,
  BOXCOLLIDER_EXPLOSION,
  BOXCOLLIDER_LAWNMOWER,
  BOXCOLLIDER_SUN,
  BOXCOLLIDER_REWARD
};

class BoxCollider {
 public:
  BoxCollider();
  BoxCollider(int id, float x, float y, float width, float height);
  BoxCollider(float x, float y, float width, float height);

  void move(const int entityID, float offsetX, float offsetY);
  bool collision(const BoxCollider* box);
  bool pointCollision(const Tyra::Vec2* point);
  int id;
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
  bool attack();
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
  u32 lastTime;
  u32 actualTime;
  u32 counterMS = 0;
  u32 maxMS = 1000;
  void setLastTime();
  u32 getTimeInMS();
  void resetCounter();
  void addMSinCounter();
};

class ZombieRow {
 public:
  int zombiesInRow = 0;
  int maxZombiesInRow = 0;
};

struct ResponseCollisionProjectile{
  int projectileID;
  int zombieID;
};

struct ResponseCollisionZombiePlant{
  int zombieID;
  int plantID;
};

struct ResponseCollisionSunCursor{
  int sunID;
  int cursorID;
};

extern Tyra::Engine* engine;
extern Tyra::Renderer* renderer;
extern Tyra::Renderer2D* renderer2D;
extern Tyra::Pad* pad;
extern const Tyra::PadJoy* leftJoy;
extern Tyra::TextureRepository* texRepo;
extern std::unordered_map<int, std::vector<int>> m_animID;

// sparse array
extern std::vector<FrameCounter> frameCounterArray;
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
extern std::unordered_map<int, int> boxColliderArrayID;
extern std::unordered_map<int, std::vector<BoxCollider>> boxColliderArray;
extern std::vector<BoxCollider> boxColliderPlant;
extern std::vector<BoxCollider> boxColliderZombie;
extern std::vector<BoxCollider> boxColliderProyectile;
extern std::vector<BoxCollider> boxColliderExplosion;
extern std::vector<BoxCollider> boxColliderLawnmower;
extern std::vector<BoxCollider> boxColliderSun;
extern std::vector<BoxCollider> boxColliderPlayer;
extern std::vector<ResponseCollisionProjectile> responseCollisionZombieProjectile;
extern std::vector<ResponseCollisionZombiePlant> responseCollisionZombiePlant;
extern std::unordered_map<int, TriggerBoxCollider> resultBoxCollider;
extern ArrayKey<int, PS2Timer> timerArray;
extern std::unordered_map<int, float> speedArray;
extern std::unordered_map<int, int> damageArray;
extern ArrayKey<int, int> lifeArray;
extern std::map<int, Tyra::Vec2> pivot;
extern std::vector<Controller> controller;

extern std::vector<Proyectile> projectile;
extern std::vector<Explosion> explosion;
extern std::vector<Card> cards;
extern std::vector<LawnMower> lawnMower;
extern std::vector<Cursor> cursor;
extern std::vector<DeckCursor> deckCursor;

extern int zombiescreated;
extern ZombieRow zombieCreateRow[5];
extern bool mapEnable[5];
extern bool plantCreatedInMap[5][9];
extern int map[5][9];
extern BoxCollider mapCollider[5][9];

extern int sunCounterText;