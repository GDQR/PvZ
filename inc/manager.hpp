#pragma once
#include "PVZ.hpp"

class PlayerControl {
 public:
  void update();
};

class FrameManager {
 public:
  void update();
};

class AnimationManager {
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
  void updateRender();
  void update();
};

class ZombiesManager {
 public:
  int timer = 0;
  void update();
};

class RewardManager {
 public:
  void update();
};

class CardManager {
 public:
  inline void update() {  // implicitly inline i know, just i don't care
    for (Card& card : cards) {
      card.update();
    }
  };
};

class PlantsManager {
 public:
  void create(int playerId);
  inline void update() {
    for (Plant& onePlant : plant) {
      onePlant.erase();
      onePlant.attack();
      onePlant.normalColor();
    }
  };
};

extern int projectilesCreated;
class ProjectileManager {
  public:
  void update();
};

class BoxCollisionManager {
 public:
  void mapCollision();
  void projectileZombieCollision();
  void explosionZombieCollision();
  void lawnCollision();
  void plantZombieCollision();
  void sunCollision();
  void testUpdate();
  inline void update() {
    // testUpdate();
    mapCollision();
    projectileZombieCollision();
    explosionZombieCollision();
    plantZombieCollision();
    lawnCollision();
    sunCollision();
  }
};

class LawnMoverManager{
  public:
  void update();
};

enum enumCameraState{
  cameraShowEnemies,
  cameraDelay,
  cameraShowHouse
};

class CameraManager {
 private:
  enumCameraState state = cameraShowEnemies;
 public:
  void update();
  bool intro();
};

class FontManager {
 public:
 void update();
};

class ParticleManager{
    public:
    void update();
};

extern PlayerControl playerControl;
extern BoxCollisionManager boxColliderManager;
extern AnimationManager animManager;
extern RendererSprites renderSprites;
extern RendererDebugSpritesManager renderDebugSpritesManager;
extern ZombiesManager zombiesManager;
extern PlantsManager plantsManager;
extern ProjectileManager projectileManager;
extern RewardManager rewardManager;
extern CardManager cardManager;
extern CameraManager cameraManager;
extern FontManager fontManager;
extern FrameManager frameManager;
extern LawnMoverManager lawnMoverManager;
extern ParticleManager particleManager;