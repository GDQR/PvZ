#pragma once
#include <tyra>

class AnimationManager {
 private:
  unsigned int framesSpeed = 20;

 public:
  void update();
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
};

class PlantsManager {
  public:
  void create();
  void update();
};

class ProjectileManager {
 public:
  void update();
  void zombieCollision();
};

extern AnimationManager animManager;
extern ProjectileManager projectileManager;
extern RendererSprites renderSprites;
extern RendererDebugSpritesManager renderDebugSpritesManager;
extern ZombiesManager zombiesManager;
extern PlantsManager plantsManager;

void newProjectile(Tyra::Vec2 position);
void newFatherID(int* fatherID, int* childID);
void newCursor(int* cursor, Tyra::Vec2 pos);
void newDeckCursor(int* cursor, Tyra::Vec2 pos);
void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size);
void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle);
void deleteFatherID(int* fatherID, int* childID);
void deleteSprite(const int entityID);
void deleteAnimation(const int entityID);
void deletePosArray(const int entityID);
void deleteTexPosArray(const int entityID);