#pragma once
#include <tyra>
#include "components.hpp"

class PlayerControl {
 public:
  void update();
};

class AnimationManager {
 private:
  unsigned int framesSpeed = 20;

 public:
  void update();
  void debug();
  void debugChangeFrame(const int entitieID, const int key);
};

class RendererDebugSpritesManager {
 public:
  void update();
};

class RendererSprites {
 public:
  void resetFinalPos();
  void updateChildPos();
  void updateTexture();
  void update();
};

class ZombiesManager {
 public:
  int timer = 0;
  void update();
};

class ProjectileManager {
 public:
  int update();
  void zombieCollision();
};

class ExplosionManager {
 public:
  void zombieCollision();
};

extern PlayerControl playerControl;
extern AnimationManager animManager;
extern ProjectileManager projectileManager;
extern ExplosionManager explosionManager;
extern RendererSprites renderSprites;
extern RendererDebugSpritesManager renderDebugSpritesManager;
extern ZombiesManager zombiesManager;

void newPlayer(int* player);
void newProjectile(Tyra::Vec2 position, const int damage,
                   const enumProyectile projectileType);
void newExplosion(Tyra::Vec2 position, Vec2 size, const int damage,
                  const enumProyectile projectileType);
void newFatherID(int* fatherID, int* childID);
void newCursor(int* player, Tyra::Vec2 pos);
void newDeckCursor(int* player, Tyra::Vec2 pos);
void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size);
void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle);
void createLawnMower(const Tyra::Vec2 pos);
void createCard(Plant_State_enum typePlant, Vec2 pos, bool isVersusMode);
void deleteFatherIDChild(int* fatherID, int* childID);
void deleteFatherID(const int* entityID);
void deleteSprite(const int entityID);
void deleteAnimation(const int entityID);
void deletePosArray(const int entityID);
void deleteFinalPosArray(const int entityID);
void deleteTexPosArray(const int entityID);