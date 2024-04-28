#pragma once
#include <tyra>
#include <vector>
#include <map>
#include "debugPVZ/debug.hpp"
#include "entities/entities.hpp"
#include "renderSprite/textures.hpp"
#include "entities/plants.hpp"
#include "entities/zombie.hpp"
#include "entities/sun.hpp"

extern Tyra::Engine* engine;
extern Tyra::Renderer* renderer;
extern const Tyra::PadJoy* leftJoy;

enum enumAnimation {
  peaShooterHead,
  peaShooterBody,
  zombieWalk,
  zombieNormalAttack,
  sunAnim,
  sunAnim2
};

class FatherID {
 public:
  std::vector<int> id;
};

class Animation {
 public:
  Animation();
  Animation(enumAnimation anim);
  int time = 0;
  int animID = -1;
  unsigned int key = 0;
};

class AnimationData {
 public:
  std::vector<Tyra::Texture*> keys;
  std::vector<Tyra::Vec2*> position;
};

class Time {
 public:
  std::vector<int> seconds; // can't be 0 for animations
};

class BoxCollider {
 public:
  BoxCollider();
  BoxCollider(float x, float y, float width, float height);
  BoxCollider(float x, float y, float width, float height, float offsetX,
              float offsetY);
  float x;
  float y;
  float width;
  float height;
  float offsetX;
  float offsetY;
};

// sparse array
extern std::map<int, Animation>
    animationArray;  // Link the sprite with the texture
extern std::map<int, Time> animationTime;
extern std::unordered_map<int, AnimationData>
    animationDataArray;  // Save the animation textures
extern std::map<int, FatherID> fatherIDArray;
extern std::map<int, Tyra::Vec2> posArray;
extern std::map<int, Tyra::Vec2> finalPosArray;
extern std::map<int, Tyra::Sprite> spriteArray;
extern std::map<int, Tyra::Vec2> pointColliderArray;
extern std::map<int, BoxCollider> boxColliderArray;
extern std::map<int, int> damageArray;
extern std::map<int, int> lifeArray;

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Zombie> zombie;
extern std::vector<Sun> sun;
extern std::vector<int> projectile;

extern bool zombieCreateRow[5];
extern bool plantCreatedInMap[5][9];
extern BoxCollider mapCollider[5][9];

class AnimationManager {
 public:
  Tyra::TextureRepository* texRepo;
  void update();
  void position(const int entitieID);

  void debug();
  int debugAnim(const int entitieID);
  void debugChangeFrame(const int entitieID, const int key);
};

class RendererDebugSpritesManager {
 public:
  void update();
};

class RendererSprites {
 public:
  void updateChildPos();
  void update();
};

class ZombiesManager {
 public:
  int timer = 0;
  void update();
  int collision();
};

class ProjectileManager {
 public:
  void update();
  void zombieCollision();
};

extern AnimationManager animManager;

void newFatherID(int* fatherID, int* childID);
void newCursor(int* cursor, Tyra::Vec2 pos);
void newProjectile(Vec2 position);
void newDeckCursor(int* cursor, Tyra::Vec2 pos);
void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size);
void deleteSprite(const int id);
bool boxCollision(BoxCollider* col1, BoxCollider* col2);