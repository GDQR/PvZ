#pragma once
#include "debugPVZ/debug.hpp"
#include "renderSprite/animations.hpp"
#include "imageTools.hpp"
#include <map>
#include <tyra>
#include <vector>
 
/**
 * In this file exist the next things:
 * Entities
 * Components
 * Systems
 */

//----------------------------------------------------------------------------------
// Entities
//----------------------------------------------------------------------------------

class Entities {
 public:
  static unsigned int counter;
  static std::vector<unsigned int> aliveEntities;
  static std::vector<unsigned int> deadEntities;

  static unsigned int newID();
  static void deleteID(int& id);
  static void deleteID(unsigned int& id);
};

class BigSpriteJPG{
  public:
  std::vector<int> id;
  int rowTextures;
  void initJPG(const char* JPGfile, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight);
  void initJPG(Tyra::Texture* texture, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight);
  void move();
  void scale();
  void scaleTest(int width, int height);
};

class Player{
  public:
  // Player(Tyra::Vec2 cursorPos, Tyra::Vec2 deckCursorPos);
  int id;
  void init(Tyra::Vec2 cursorPos,Tyra::Vec2 deckPos);
  private:
  void initCursor(Tyra::Vec2 cursorPos);
  void initDeckCard(Tyra::Vec2 pos);
  void initPlant();
};

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
  Tyra::Color color;
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

enum sunCost { BigSun = 50, normalSun = 25, smallerSun = 15 };
extern int sunsCreated;
extern int sunCounter;
class Sun {
 public:
  int father;
  std::vector<int> id;
  int cost;
  void erase(const int cursorID);
};

class NaturalSun {
 public:
  int father;
  void move();
};

class SunManager {
 public:
  void update();
  void create(Tyra::Vec2 position, sunCost cost, bool createdByPlant);
  void createByTime();
  void erase(const int cursorID);
  void updateNaturalSun();
};

extern SunManager sunManager;

class Reward {
 public:
  int father;
  std::vector<int> id;
};

using Tyra::Sprite;

extern Tyra::Texture* projectilePea;
extern Tyra::Texture* projectileSnowPea;
extern Tyra::Texture* projectileExplosionPowie;
extern Tyra::Texture* projectileExplosionSpudow;
extern int plantsCreated;

enum Plant_Recharge_Time_enum { fast, slow, verySlow, enumMaxRecharge };

extern int plantRechargeTime[enumMaxRecharge];

enum Plant_State_enum {
  PeaShotter,
  SunFlower,
  CherryBomb,
  Wallnut,
  PotatoMine,
  SnowPea,
  Chomper,
  Repeater,
  PuffShroom,
  SunShroom,
  FumeShroom,
  GraveBuster,
  HypnoShroom,
  ScaredyShroom,
  IceShroom,
  DoomShroom,
  LilyPad,
  Squash,
  ThreePeater,
  Tanglekelp,
  Jalapeno,
  Spikeweed,
  Torchwood,
  Tallnut,
  SeaShroom,
  Plantern,
  Cactus,
  Blover,
  SplitPea,
  Starfruit,
  Pumpkin,
  Magnetshroom,
  Cabbagepult,
  FlowerPot,
  Kernelpult,
  CoffeeBean,
  Garlic,
  UmbrellaLeaf,
  Marigold,
  Melonpult,
  GatlingPea,
  TwinSunflower,
  GloomShroom,
  Cattail,
  WinterMelon,
  GoldMagnet,
  Spikerock,
  CobCannon,
  Imitator,
  enumMaxPlants,
  NonePlant
};

extern std::vector<int> plantCollisionID;

struct PlantAnimation{
  int id;
  std::vector<int> entity;
};

extern std::vector<PlantAnimation> plantAnims;

extern std::vector<PlantAnimation> cardsAnimations;

class Plant {
 public:
  // std::vector<int> id;

  Plant_State_enum type = NonePlant;
  int father;
  int row;
  int column;
  bool damaged = false;
  void newPlant(Plant_State_enum newType);
  int attack();
  void damage(const int entityID);
  int normalColor();
  void erase();
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

namespace Entity {
  extern int background;
  extern BigSpriteJPG backgroundIDs;
  extern BigSpriteJPG awardbackground;
  extern int sodRoll;
  extern int sodRollCap;
  extern int sodRollRow1;
  extern int sodRollRow1Alpha;
  extern int sod3Row;
  extern int sod3RowAlpha;
  extern Player player;
  extern Reward reward;
  extern int fullFlagMeter;
  extern int zombieFlagMeter;
}

bool createPlant(Plant_State_enum typePlant, const int row, const int column, int cost);
void loadPlantCost();
void loadPlantRechargeTime();
int getPlantCost(Plant_State_enum typePlant);
int getPlantRechargeTime(Plant_State_enum typePlant, bool isVersusMode);
bool startWithoutWait(Plant_State_enum typePlant, bool isVersusMode);

//----------------------------------------------------------------------------------
// Components
//----------------------------------------------------------------------------------

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
  int tileX = 0;
  int tileY = 0;
  int cursorTimer = 0;
  float cursorSpeed = 1;
  void move();
};

class DeckCursor {
 public:
  int id = -1;
  int pos = 0;
  void moveLeft(int playerID);
  void moveRight(int playerID);
};

class Card {
 public:
  int seed;
  int seedShadow;
  int seedShadowTimer;
  Plant_State_enum plant;
  int cost;
  int textID;
  int plantID;
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
extern std::unordered_map<int, std::vector<char*>> animNames;

template <class Key, class Type>
class ArrayKey {
 public:
  ArrayKey(enumComponents typeComponent);
  enumComponents type;
  std::vector<Key> first;
  std::vector<Type> second;
  std::unordered_map<unsigned int, Key> fastKey;
  void insert(const Key key, const Type value);
  int count(const Key key);
  void clear();
  void erase(const Key& key);
  Type& operator[](const Key key);
};

template <class Key, class Type>
ArrayKey<Key, Type>::ArrayKey(enumComponents typeComponent) {
  type = typeComponent;
}

template <class Key, class Type>
void ArrayKey<Key, Type>::insert(const Key key, const Type value) {
  fastKey[key] = first.size();
  first.push_back(key);
  second.push_back(value);
}

template <class Key, class Type>
int ArrayKey<Key, Type>::count(const Key key) {
  // for (auto& id : first) {
  //   if (id == key) {
  //     return 1;
  //   }
  // }
  // return 0;
  return fastKey.count(key);
}

template <class Key, class Type>
Type& ArrayKey<Key, Type>::operator[](const Key entityID) {
  TYRA_ASSERT(fastKey.count(entityID) == 1,
                "ERROR SEARCHING KEY, KEY NOT FOUNDED:", entityID,
                "COMPONENT:", type);
  unsigned int pos = fastKey[entityID];
  return second[pos];
}

template <class Key, class Type>
void ArrayKey<Key, Type>::clear() {
  first.clear();
  second.clear();
  fastKey.clear();
}

template <class Key, class Type>
void ArrayKey<Key, Type>::erase(const Key& key) {
  unsigned int size = first.size();
  for (unsigned int i = 0; i < size; i++) {
    if (first[i] == key) {
      first.erase(first.begin() + i);
      second.erase(second.begin() + i);
      fastKey.erase(key);
      size--;
      for(unsigned int j = i; j< size; j++){
        fastKey[first[j]] = j;
      }
      break;
    }
  }
}

// sparse array
extern std::vector<FrameCounter> frameCounterArray;
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
extern std::vector<ResponseCollisionSunCursor> responseCollisionSunCursor;
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

//----------------------------------------------------------------------------------
// Systems
//----------------------------------------------------------------------------------

void newPlayer(int* player);
void newProjectile(Tyra::Vec2 position, const int damage,
                   const enumProyectile projectileType);
void newExplosion(Tyra::Vec2 position, Tyra::Vec2 size, const int damage,
                  const enumProyectile projectileType);
void newFatherID(int* fatherID, int* childID);

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size, enumSpriteLayer layer);
void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle, enumSpriteLayer layer);
void createBoxCollider(int id, BoxColliderEnum type, BoxCollider collider);
void createLawnMower(const Tyra::Vec2 pos);
void createCard(Plant_State_enum typePlant, bool isVersusMode);
void createPlantCard(int& plantID,AnimIndex::Animation plantAnim, const Tyra::Vec2 pos, const Tyra::Vec2 size, const Tyra::Color color, const int frame);
void createReward(Tyra::Vec2 pos);
void eraseReward();
void deleteFatherIDChild(const int fatherID, const int* childID);
void deleteFatherID(const int entityID);
void deleteSprite(const int entityID);
void deletePosArray(const int entityID);
void deleteFinalPosArray(const int entityID);
void deleteTexPosArray(const int entityID);
BoxCollider& searchBoxCollider(int type,int id);
void GetTime();
void SetBigImage(BigSpriteJPG* entity, BigTexture* textures, Tyra::SpriteMode mode, float x, float y, float width, float height);

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------