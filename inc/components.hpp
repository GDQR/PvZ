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

enum enumAnimation {
  peaShooterHead,
  peaShooterBody,
  deb_zombieWalk,
  deb_zombieNormalAttack,
  zombieWalk,
  zombieNormalAttack,
  sunAnim,
  sunAnim2,
  Sun1,
  Sun2,
  Sun3,
  SunFlowerHead
};

class FatherID {
 public:
  std::vector<int> id;
};

class Cursor {
 public:
  int id = -1;
  Sprite sprite;
  Vec2 cursorTile;
};

class DeckCursor {
 public:
  int id = -1;
  int pos = 0;
};

class Card {
 public:
  int seed;
  int seedShadow;
  int seedShadowTimer;
  int seedTimer;
  Plant_State_enum plant;
  int cost;
};

class Animation {
 public:
  Animation();
  Animation(enumAnimation anim);
  int animID = -1;
  bool draw = true;
  unsigned int framesCounter = 0;
  unsigned int currentFrame = 0;
};

class AnimationData {
 public:
  unsigned int maxFrame;
  std::string name;
  std::map<unsigned int, Tyra::Texture*> texture;
  std::map<unsigned int, Tyra::Vec2> position;
  std::map<unsigned int, Tyra::Vec2> scale;
  std::map<unsigned int, Tyra::Vec2> angle;
  std::map<unsigned int, float> alpha;
  std::map<unsigned int, bool> draw;
};

class Time {
 public:
  std::vector<int> seconds;  // can't be 0 for animations
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

extern Tyra::Engine* engine;
extern Tyra::Renderer* renderer;

extern std::map<std::string, std::vector<int>> m_animID;

// sparse array
extern std::map<int, Animation>
    animationArray;  // Link the sprite with the texture
extern std::unordered_map<int, AnimationData>
    animationDataArray;  // Save the animation textures
extern std::map<int, FatherID> fatherIDArray;
extern std::map<int, Tyra::Vec2> texPosArray;
extern std::map<int, Tyra::Vec2> posArray;
extern std::map<int, Tyra::Vec2> finalPosArray;
extern std::map<int, Tyra::Sprite> spriteArray;
extern std::map<int, Tyra::Sprite*> spritesNormalRender;
extern std::vector<int> spriteNormalIdStopRender;
extern std::vector<int> animationIdStopRender;
extern std::map<int, Tyra::Sprite> spritesRotate;
extern std::map<int, Tyra::Sprite*> spritesRotateRender;
extern std::vector<int> spritesRotateIdStopRender;
extern std::map<int, Tyra::Vec2> angles;
extern std::map<int, Tyra::Vec2> originalSize;
extern std::map<int, Tyra::Vec2> scaleTexture;
extern std::map<int, Tyra::Vec2> pointColliderArray;
extern std::map<int, BoxCollider> boxColliderArray;
extern std::map<int, int> damageArray;
extern std::map<int, int> lifeArray;
extern std::map<int, Tyra::Vec2> pivot;

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Zombie> zombie;
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<int> projectile;

extern bool zombieCreateRow[5];
extern bool plantCreatedInMap[5][9];
extern BoxCollider mapCollider[5][9];