#include "PVZ.hpp"

Animation::Animation() {}

Animation::Animation(const int anim) { animID = anim; }

void Animation::update(const int entityID) {
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > lastFrame) {
      currentFrame = firstFrame;
    }

    activeDrawNormalSprites(entityID);
    if (draw == (int)enumDraw::draw) {
      updateSprites(entityID);
      if (angleArray.count(entityID) == 1) {
        updateAngle(entityID);
      }
    }
  }

  framesCounter++;
}

int FrameCounter::update(){
  framesCounter += 1;
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame += 1;

    if (currentFrame > lastFrame) {
      currentFrame = firstFrame;
    }
  }

  return framesCounter;
}

void Animation::position(const int entityID) {
  // // finalPos += animPos
  // if (animationDataArray[animID].position.count(currentFrame)) {
  //   texPosArray[entityID] = animationDataArray[animID].position[currentFrame];
  // }
}

void Animation::activeDrawNormalSprites(const int entityID) {
  // if (dataIndex.drawIndex == currentFrame){
  //   draw = animationDataArray[animID].draw[dataIndex.drawIndex].data;
  //   if (draw == (int)enumDraw::noDraw) {
  //     spriteRenderIDArray.erase(entityID);
  //     // spriteNormalIdStopRender.push_back(entityID);
  //   } else if (spriteRenderIDArray.count(entityID) == 0) {
  //     spriteRenderIDArray.insert(entityID, 0);
  //   }
  //   dataIndex.drawIndex = animationDataArray[animID].draw[dataIndex.drawIndex].frame;
  // }
  // int index = animationDataArray[animID].draw.getIndex(currentFrame);
  // if (index != -1) {
  //   draw = animationDataArray[animID].draw.second[index];
  //   if (draw == (int)enumDraw::noDraw) {
  //     spriteRenderIDArray.erase(entityID);
  //     // spriteNormalIdStopRender.push_back(entityID);
  //   } else if (spriteRenderIDArray.count(entityID) == 0) {
  //     spriteRenderIDArray.insert(entityID, 0);
  //   }
  // }
}

void Animation::updateSprites(const int entityID) {
  
  // printf("entity: %d, animID:%d textureIndex: %d, frame: %d\n",entityID,animID,animationDataArray[animID].texture[dataIndex.textureIndex].frame, currentFrame);
  // if(dataIndex.textureIndex == currentFrame){
  //   Tyra::Texture* texture = texRepo->getBySpriteId(spriteArray[entityID].id);
  //   // Unlink Texture from the sprite entitie
  //   if (texture != nullptr) {
  //     // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
  //     texture->removeLinkById(spriteArray[entityID].id);
  //   }

  //   // Link new Texture to the sprite entitie
  //   texture = texRepo->getByTextureId(animationDataArray[animID].texture[dataIndex.textureIndex].data);
  //   printf("sprite id: %d\n", animationDataArray[animID].texture[dataIndex.textureIndex].data);
  //   if(texture == nullptr){
  //     TYRA_TRAP("error");
  //   }
  //   texture->addLink(spriteArray[entityID].id);
  //   originalSize[entityID] = Vec2(texture->getWidth(), texture->getHeight());
  //   dataIndex.textureIndex = animationDataArray[animID].texture[dataIndex.textureIndex].frame;
  // }

  // if (dataIndex.posIndex == currentFrame) {
  //   texPosArray[entityID] =
  //       animationDataArray[animID].position[dataIndex.posIndex].data *
  //       scaleTexture.at(entityID);
  //   dataIndex.posIndex = animationDataArray[animID].position[dataIndex.posIndex].frame;
  // }

  // if (dataIndex.alphaIndex == currentFrame) {
  //   spriteArray[entityID].color.a = animationDataArray[animID].alpha[dataIndex.alphaIndex].data;
  //   dataIndex.alphaIndex = animationDataArray[animID].alpha[dataIndex.alphaIndex].frame;
  // }

  // if (dataIndex.scaleIndex == currentFrame) {
  //   spriteArray[entityID].size =
  //       originalSize[entityID] *
  //       animationDataArray[animID].scale[dataIndex.scaleIndex].data *
  //       scaleTexture.at(entityID);
  //   dataIndex.scaleIndex = animationDataArray[animID].scale[dataIndex.scaleIndex].frame;
  // }


  // int myindex = animationDataArray[animID].texture.getIndex(currentFrame);
  // if (myindex != -1) {
  //   Tyra::Texture* texture = texRepo->getBySpriteId(spriteArray[entityID].id);
  //   // Unlink Texture from the sprite entitie
  //   if (texture != nullptr) {
  //     // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
  //     texture->removeLinkById(spriteArray[entityID].id);
  //   }

  //   // Link new Texture to the sprite entitie
  //   texture = texRepo->getByTextureId(
  //       animationDataArray[animID].texture.second[myindex]);
  //   texture->addLink(spriteArray[entityID].id);
  //   originalSize[entityID] = Vec2(texture->getWidth(), texture->getHeight());
  // }
  // myindex = animationDataArray[animID].position.getIndex(currentFrame);
  // // printf("currentFrame: %d\n",currentFrame);
  // // printf("index: %d\n",myindex);
  // if (myindex != -1) {
  //   texPosArray[entityID] =
  //       animationDataArray[animID].position.second[myindex] *
  //       scaleTexture.at(entityID);
  // }

  // myindex = animationDataArray[animID].alpha.getIndex(currentFrame);
  // if (myindex != -1) {
  //   spriteArray[entityID].color.a =
  //       animationDataArray[animID].alpha.second[myindex];
  // }

  // myindex = animationDataArray[animID].scale.getIndex(currentFrame);
  // if (myindex != -1) {
  //   spriteArray[entityID].size =
  //       originalSize[entityID] *
  //       animationDataArray[animID].scale.second[myindex] *
  //       scaleTexture.at(entityID);
  // }
}

void Animation::updateAngle(const int entityID) {
  // int myindex = animationDataArray[animID].angle.getIndex(currentFrame);
  // if (myindex != -1) {
  //   angleArray[entityID] = animationDataArray[animID].angle.second[myindex];
  // }
}

int Animation::debugAnim(const int entitieID) {
  if (framesCounter < (60 / framesSpeed)) {
    framesCounter++;
    return 1;
  }

  currentFrame++;
  framesCounter = 0;

  if (currentFrame > lastFrame) {
    currentFrame = firstFrame;
  }

  // if (spriteArray.count(entitieID) == 1 &&
  //     animationDataArray[animID].texture.count(currentFrame) == 1) {
  //   texRepo->getBySpriteId(spriteArray[entitieID].id)
  //       ->removeLinkById(spriteArray[entitieID].id);

  //   texRepo->getByTextureId(animationDataArray[animID].texture[currentFrame])
  //       ->addLink(spriteArray[entitieID].id);
  // }
  // int myindex = animationDataArray[animID].position.getIndex(currentFrame);
  // if (myindex != 1) {
  //   texPosArray[entitieID] =
  //       animationDataArray[animID].position.second[currentFrame];
  // }

  // if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
  //   spriteArray[entitieID].color.a =
  //       animationDataArray[animID].alpha[currentFrame];
  // }
  // myindex = animationDataArray[animID].scale.getIndex(currentFrame);
  // if (myindex != -1) {
  //   spriteArray[entitieID].size =
  //       originalSize[entitieID] *
  //       animationDataArray[animID].scale.second[myindex];
  // }

  // if (animationDataArray[animID].angle.count(currentFrame) == 1) {
  //   angleArray[entitieID] = animationDataArray[animID].angle[currentFrame];
  // }

  return 0;
}