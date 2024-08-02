#pragma once
#include <vector>
#include <string>
#include <unordered_map>

enum enumAnimationState {
    normalZombieWalk,
    normalZombieAttack,
    enumMaxAnimationState
};

class AnimationState{
    public:
    AnimationState();
    AnimationState(const unsigned int firstFrame,const unsigned int lastFrame);
    unsigned int firstFrame;
    unsigned int lastFrame;
};

class Animation {
 public:
  Animation();
  Animation(const int anim);
  void update(const int entityID);
  void activeDrawNormalSprites(const int entityID);
  void updateNormalSprites(const int entityID);
  void activeDrawRotationSprites(const int entityID);
  void updateRotationSprites(const int entityID);
  void position(const int entityID);
  int debugAnim(const int entitieID);

  int animID = -1;
  bool draw = true;
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
  std::unordered_map<unsigned int, int> texture;
  std::unordered_map<unsigned int, float> x;
  std::unordered_map<unsigned int, float> y;
  std::unordered_map<unsigned int, float> scaleX;
  std::unordered_map<unsigned int, float> scaleY;
  std::unordered_map<unsigned int, float> angleX;
  std::unordered_map<unsigned int, float> angleY;
  std::unordered_map<unsigned int, float> alpha;
  std::unordered_map<unsigned int, bool> draw;
 
  void loadAnimation(const int entityID, const int animID, enumAnimationState animationState);
  void loadAnimation(const int entityID, const int animID, const int firstFrame, const int lastFrame);
  void activeAnimation(const int entityID, const int firstFrame, const int lastFrame);
  void setAnimationState(const int entityID, enumAnimationState animationState);
};

extern AnimationState animationStateVector[enumMaxAnimationState];

void setSprite(const int entityID, const bool draw);
void loadAnimationStates();
void loadAnimation(std::string animName);
