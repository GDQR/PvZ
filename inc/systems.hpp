#pragma once
#include "components.hpp"
#include <tyra>


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
      onePlant.attack();
      onePlant.ability();
    }
  };
};

class BoxCollisionManager {
 public:
  void mapCollision();
  int projectileZombieCollision();
  void explosionZombieCollision();
  //  void testUpdate();
  inline void update() {
    mapCollision();
    projectileZombieCollision();
    explosionZombieCollision();
  }
};

class CameraManager {
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
extern RewardManager rewardManager;
extern CardManager cardManager;

void newPlayer(int* player);
void newProjectile(Tyra::Vec2 position, const int damage,
                   const enumProyectile projectileType);
void newExplosion(Tyra::Vec2 position, Tyra::Vec2 size, const int damage,
                  const enumProyectile projectileType);
void newFatherID(int* fatherID, int* childID);
void newCursor(int* player, Tyra::Vec2 pos);
void newDeckCursor(int* player, Tyra::Vec2 pos);
void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size);
void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle);
void createLawnMower(const Tyra::Vec2 pos);
void createCard(Plant_State_enum typePlant, Tyra::Vec2 pos, bool isVersusMode);
void createCardSunFlower(std::vector<int>& plantID, const Tyra::Vec2 pos);
void createReward(Tyra::Vec2 pos);
void eraseReward();
void drawCardCost();
void deleteFatherIDChild(const int* fatherID, const int* childID);
void deleteFatherID(const int* entityID);
void deleteSprite(const int entityID);
void deleteAnimation(const int entityID);
void deletePosArray(const int entityID);
void deleteFinalPosArray(const int entityID);
void deleteTexPosArray(const int entityID);