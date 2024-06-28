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

extern std::map<std::string, std::vector<int>> m_animID;
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

class Animation {
 public:
  Animation();
  Animation(enumAnimation anim);
  int animID = -1;
  unsigned int framesCounter = 0; // es el time
  unsigned int currentFrame = 0; // es el key
};

class AnimationData {
 public:
  unsigned int maxFrame;
  std::map<unsigned int, Tyra::Texture*> texture;
  std::map<unsigned int, Tyra::Vec2> position;
  std::map<unsigned int, float> scale;  
  std::map<unsigned int, float> angle;  
  std::map<unsigned int, float> alpha;  
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
extern std::unordered_map<int, AnimationData>
    animationDataArray;  // Save the animation textures
extern std::map<int, FatherID> fatherIDArray;
extern std::map<int, Tyra::Vec2> texPosArray;
extern std::map<int, Tyra::Vec2> posArray;
extern std::map<int, Tyra::Vec2> finalPosArray;
extern std::map<int, Tyra::Sprite> spriteArray;
extern std::map<int, Tyra::Sprite*> spritesNormalRender;
extern std::map<int, Tyra::Sprite> spritesRotate;
extern std::map<int, Tyra::Sprite*> spritesRotateRender;
extern std::map<int, float> angles;
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

class AnimationManager {
 private:
  unsigned int framesSpeed=20;
 public:
  Tyra::TextureRepository* texRepo;
  void update();
  void position(const int entitieID);
  void angle(const int entitieID);
  void alpha(const int entitieID);
  void scale(const int entitieID);
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
  void updateRotate();
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
void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size, const float angle);

void deleteFatherID(int* fatherID, int* childID);
void deleteSprite(const int entitieID);
bool boxCollision(BoxCollider* col1, BoxCollider* col2);