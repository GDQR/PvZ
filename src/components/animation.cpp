#include "PVZ.hpp"
#include "renderSprite/animations.hpp"

int FrameCounter::update(){
  framesCounter += 1;
  if (framesCounter >= (36 / 12)) {
    framesCounter = 0;
    currentFrame += 1;

    if (currentFrame >= lastFrame) {
      currentFrame--;
      if(repeat == true){
        currentFrame = firstFrame;
      }
    }
    CheckEvent();
  }

  return framesCounter;
}

void FrameCounter::CheckEvent() {
  if(layerIndex == 0){
    if(animIndex == EnumAnimationIndex::ANIM_Zombie){
      if(currentFrame == 144 || currentFrame == 164){
        attackPlant(entityID);
      }
    }else if(animIndex == EnumAnimationIndex::ANIM_Zombie_PoleVaulter){
      if(currentFrame == 93){
        finishJump(entityID);
      }else if(currentFrame == 172 || currentFrame == 184){
        attackPlant(entityID);
      }
    }else if(animIndex == EnumAnimationIndex::ANIM_Chomper){
      if(currentFrame == 42){
        attackZombie(entityID);
      }
    }
  }
}

bool FrameCounter::IsLastframe(){
  if(currentFrame == lastFrame-1){
    return true;
  }
  return false;
}
