#include "PVZ.hpp"

int FrameCounter::update(){
  framesCounter += 1;
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame += 1;

    if (currentFrame >= lastFrame) {
      currentFrame--;
      if(repeat == true){
        currentFrame = firstFrame;
      }
    }

  }

  return framesCounter;
}

bool FrameCounter::IsLastframe(){
  if(currentFrame == lastFrame-1){
    return true;
  }
  return false;
}
