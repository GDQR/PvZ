#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <tyra>
#include "linearArrayKey.hpp"

enum class enumDraw { draw = 0, noDraw = -1 };

enum enumAnimationState {
  normalZombieWalk,
  normalZombieAttack,
  poleVaulterWalk,
  explodeCherryBomb,
  enumMaxAnimationState
};

enum enumAnimName {
  PeashooterSingleAnimName,
  SunFlowerAnimName,
  CherryBombAnimName,
  WallnutAnimName,
  PotatoMineAnimName,
  SnowPeaAnimName,
  ChomperAnimName,
  PeaShooterAnimName,
  SunAnimName,
  ZombieAnimName,
  ZombiePoleVaulterAnimName,
  ZombieBucketHeadAnimName
};

class AnimationState {
 public:
  AnimationState();
  AnimationState(const unsigned int firstFrame, const unsigned int lastFrame);
  unsigned int firstFrame;
  unsigned int lastFrame;
};

class Animation {
 public:
  Animation();
  Animation(const int anim);
  void update(const int entityID);
  void activeDrawNormalSprites(const int entityID);
  void updateSprites(const int entityID);
  void updateAngle(const int entityID);
  void setAnimation(enumAnimationState animationState);
  void position(const int entityID);
  int debugAnim(const int entitieID);

  int animID = -1;
  int draw = (int)enumDraw::draw;
  unsigned int framesCounter = 0;
  unsigned int currentFrame = 1;
  unsigned int framesSpeed = 20;
  unsigned int firstFrame = 1;
  unsigned int lastFrame = 1;
};

class AnimationData {
 public:
  unsigned int maxFrame;
  std::string name;
  LinearArrayKey<unsigned int, int> texture;
  LinearArrayKey<unsigned int, Tyra::Vec2> position;
  LinearArrayKey<unsigned int, Tyra::Vec2> scale;
  std::unordered_map<unsigned int, float> angleX;
  std::unordered_map<unsigned int, float> angleY;
  LinearArrayKey<unsigned int, float> alpha;
  LinearArrayKey<unsigned int, int> draw;
  void loadAnimation(const int entityID, const int animID,
                     enumAnimationState animationState);
  void loadAnimation(const int entityID, const int animID, const int firstFrame,
                     const int lastFrame);
  int activeAnimation(const int entityID, const unsigned int firstFrame,
                      const unsigned int lastFrame);
  void setAnimationState(const int entityID, enumAnimationState animationState);
};

extern AnimationState animationStateVector[enumMaxAnimationState];

void setSprite(const int entityID, const int draw);
void loadAnimationStates();
void loadAnimation(const enumAnimName animNameID, std::string animName);
