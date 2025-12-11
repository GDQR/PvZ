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
  fatherID,
  COMPONENTS_MAX
};

struct IndexComponent{
  bool component[COMPONENTS_MAX] = {false};
};

extern std::vector<IndexComponent> entityComponents;
extern std::vector<unsigned int> entityKeySparse[COMPONENTS_MAX];
extern std::vector<unsigned int> entityKeyDense[COMPONENTS_MAX];

class Entities {
 public:
  static unsigned int counter;
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
  int cursorID;
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
  bucketHeadZombie,
  CHARRED_ZOMBIE
};

struct ZombieAnimation{
  int id;
  std::vector<int> entity;
};

extern std::vector<ZombieAnimation> zombieAnims;

enum DamageType : unsigned char{
  Bullet,
  SNOW_BULLET,
  EXPLOSION,
  Bowling
};

class Zombie {
 private:
  void createSpace();

 public:
  int attackTimer = 0;

  int father;
  int boxColliderID;
  Zombie_State_enum type = NoneZombie;
  Tyra::Color color;
  bool damaged = false;
  bool explosion = false;
  void newZombie(Zombie_State_enum newType);
  void SetZombieAnimation(const int entityID, const int nameID, const Zombie_State_enum type);
  void setNormalZombieAnimation();
  void setConeheadAnimation(int entityID);
  void setBucketheadAnimation(int entityID);
  bool animWalk();
  bool animAttackPlant();
  bool explosionState();
  int move();
  bool damage(const int entityID, DamageType damageType);
  int normalColor();
  bool erase();
  void deleteData();
};

void createNormalCharredZombie(int& fatherID, Tyra::Vec2 pos);
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
  WallnutBowlingExplosion,
  WallnutBowling,
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
  Plant_State_enum type = NonePlant;
  int father;
  int row;
  int column;
  bool collision = false;
  bool damaged = false;
  void newPlant(Plant_State_enum newType);
  void setWallnutAnimation();
  int attack();
  void damage(const int entityID);
  int normalColor();
  void erase();
};
void attackZombie(int entityID);


const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<Zombie> zombie;
extern std::vector<Zombie> zombieAttackState;
extern std::vector<Zombie> deadZombie;
extern std::vector<Zombie> charredZombie;
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

class Controller {
 public:
  unsigned int playerID;
  unsigned int cursorID;
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
extern std::unordered_map<int, std::vector<char*>> layerAnimNames;
extern std::unordered_map<int, enumSpriteLayer> layerID;

// sparse array
extern std::vector<FrameCounter> frameCounterArray;

// extern std::vector<int> spriteNormalIdStopRender; useless maybe
// extern std::vector<int> animationIdStopRender; useless maybe
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
extern std::vector<ResponseCollisionZombiePlant> previousResponseCollisionZombiePlant;
extern std::vector<ResponseCollisionZombiePlant> stopResponseCollisionZombiePlant;
extern std::vector<ResponseCollisionZombiePlant> enterResponseCollisionZombiePlant;
extern std::vector<ResponseCollisionSunCursor> responseCollisionSunCursor;
extern std::unordered_map<int, TriggerBoxCollider> resultBoxCollider;
extern std::unordered_map<int, float> speedArray;
extern std::unordered_map<int, int> damageArray;
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

void setEntityComponent(const int id, const enumComponents component);
void deleteEntityComponent(const int id, const enumComponents component);
bool hasEntityComponent(const int id, const enumComponents component);
void deleteEntity(const int id);
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
void createCardMinigame(const Plant_State_enum typePlant);
void createPlantCard(int& plantID,EnumAnimationIndex plantAnim, const Tyra::Vec2 pos, const Tyra::Vec2 size, const Tyra::Color color, const int frame);
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
bool CollisionEnterPlant(int boxCollider);
bool CollisionStopPlant(int boxCollider);
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------

template <class Type>
class ArrayKey {
 public:
  ArrayKey(enumComponents typeComponent);
  enumComponents type;
  std::vector<Type> second;
  void insert(const unsigned int key, const Type value);
  std::vector<unsigned int>& getSparceData();
  std::vector<unsigned int>& getDenseData();
  const char* getTypeName();
  bool count(const unsigned int key);
  void clear();
  void erase(const unsigned int key);
  Type& operator[](const unsigned int key);
};

template <class Type>
ArrayKey<Type>::ArrayKey(enumComponents typeComponent) {
  type = typeComponent;
}

template <class Type>
void ArrayKey<Type>::insert(const unsigned int key, const Type value) {
  // TYRA_ASSERT(key!=0,"ERROR KEY CAN'T BE 0");
  setEntityComponent(key,type);
  // printf("insert key: %d\n",key);
  entityKeyDense[type].push_back(key); // dense array
  std::vector<unsigned int>& keySparse = getSparceData();
  while (keySparse.size() <= key)
  {
    keySparse.push_back(0);
  }
  // printf("entityKeyDense type: %d size: %d\n",type, entityKeyDense[type].size());
  keySparse[key] = entityKeyDense[type].size();

  second.push_back(value);
}

template <class Type>
std::vector<unsigned int>& ArrayKey<Type>::getSparceData() {
  return entityKeySparse[type];
}

template <class Type>
std::vector<unsigned int>& ArrayKey<Type>::getDenseData() {
  return entityKeyDense[type];
}

template <class Type>
const char* ArrayKey<Type>::getTypeName() {
  if(type == enumComponents::angle){
    return "ANGLE";
  }else if(type == enumComponents::animation){
    return "ANIMATION";
  }else if(type == enumComponents::fatherID){
    return "fatherID";
  }else if(type == enumComponents::finalPos){
    return "finalPos";
  }else if(type == enumComponents::life){
    return "life";
  }else if(type == enumComponents::pos){
    return "pos";
  }else if(type == enumComponents::sprite){
    return "sprite";
  }else if(type == enumComponents::spriteRender){
    return "spriteRender";
  }else if(type == enumComponents::texPos){
    return "texPos";
  }else if(type == enumComponents::timer){
    return "timer";
  }
  return "TYPE NOT INCLUDED";
}

template <class Type>
bool ArrayKey<Type>::count(const unsigned int key) {
  return hasEntityComponent(key,type);
}

template <class Type>
Type& ArrayKey<Type>::operator[](const unsigned int entityID) {
  std::vector<unsigned int>& keySparse = getSparceData();
  if(entityID >= keySparse.size()){
    TYRA_TRAP("ERROR SEARCHING KEY, KEY IS BIGGER THAN EXPECTED:", entityID,
                "COMPONENT:", type, getTypeName());
  }

  int pos = keySparse[entityID];
  if(pos == 0){
    TYRA_TRAP("ERROR SEARCHING KEY, KEY NOT FOUNDED:", entityID,
                "COMPONENT:", type, getTypeName());
  }
  return second[pos-1];
}

template <class Type>
void ArrayKey<Type>::clear() {
  entityKeyDense[type].clear();
  entityKeySparse[type].clear();
  second.clear();
}

size_t GetIndexToErase(const unsigned int key, const enumComponents type);

template <class Type>
void ArrayKey<Type>::erase(const unsigned int key) {
  size_t eraseIndex = GetIndexToErase(key,type);
  std::vector<unsigned int>& keyDense = getDenseData();
  unsigned int size = keyDense.size();
  // printf("erase size:%d type:%s key: %d\n",size,getTypeName(),key);
  if(eraseIndex == size){
    return;
  }
  keyDense[eraseIndex] = keyDense[size-1];
  keyDense.pop_back();
  second[eraseIndex] = second[size-1];
  second.pop_back();
  getSparceData()[keyDense[size-1]] = eraseIndex+1;
  deleteEntityComponent(key,type);
  // printf("keyDense[%d] = %d\n",eraseIndex,keyDense[eraseIndex]);
  // printf("keySparse[%d] = %d\n",keyDense[size-1],getSparceData()[keyDense[size-1]]);
}

extern ArrayKey<FatherID> fatherIDArray;
extern ArrayKey<Tyra::Vec2> texPosArray;
extern ArrayKey<Tyra::Vec2> posArray;
extern ArrayKey<Tyra::Vec2> finalPosArray;
extern ArrayKey<Tyra::Sprite> spriteArray;
extern ArrayKey<int> spriteRenderIDArray;
extern ArrayKey<Tyra::Vec2> angleArray;
extern ArrayKey<PS2Timer> timerArray;
extern ArrayKey<int> lifeArray;