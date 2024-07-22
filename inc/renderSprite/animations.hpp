#pragma once
#include <vector>
#include <string>

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

extern AnimationState animationStateVector[enumMaxAnimationState];

void setSprite(const int entityID, const int animID, const bool draw);
void setAnimationState(const int entityID, enumAnimationState animationState);
void activeAnimation(const int entityID, const int animID, const int firstFrame, const int lastFrame);
void loadAnimationStates();
void loadAnimationSprite(const int entityID, const int animID);
void loadAnimation(std::string animName);
