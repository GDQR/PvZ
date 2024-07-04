#include "components.hpp"
#include <iostream>

// sparse array
std::map<std::string, std::vector<int>> m_animID;
std::map<int, Animation> animationArray;
std::unordered_map<int, AnimationData> animationDataArray;
std::map<int, FatherID> fatherIDArray;
std::map<int, Tyra::Vec2> posArray;
std::map<int, Tyra::Vec2> texPosArray;
std::map<int, Tyra::Vec2> finalPosArray;
std::map<int, Tyra::Sprite> spriteArray;
std::map<int, Tyra::Sprite*> spritesNormalRender;
std::vector<int> spriteNormalIdStopRender;
std::vector<int> animationIdStopRender;
std::map<int, Tyra::Sprite> spritesRotate;
std::map<int, Tyra::Sprite*> spritesRotateRender;
std::vector<int> spritesRotateIdStopRender;
std::map<int, Tyra::Vec2> angles;
std::map<int, Tyra::Vec2> originalSize;
std::map<int, Tyra::Vec2> scaleTexture;
std::map<int, Tyra::Vec2> pointColliderArray;
std::map<int, BoxCollider> boxColliderArray;
std::map<int, int> damageArray;
std::map<int, int> lifeArray;
std::map<int, Tyra::Vec2> pivot;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
std::vector<Sun> sun;
std::vector<NaturalSun> naturalSun;
std::vector<int> projectile;
int projectilesCreated = 0;

bool zombieCreateRow[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

std::map<int, Tyra::Sprite> dm_SpritePointCollider;
std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpriteNormal;
std::map<int, Tyra::Sprite> dm_SpriteRotate;
std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;
std::map<int, Tyra::Sprite> dm_SpriteRotatePivot;

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size) {
  spriteArray[id] = Sprite();
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  // printf("nuevo sprite id: %d. pos: %d\n",spriteArray[id].id,id);
  loadSprite(&spriteArray[id], mode, Vec2(0.0f, 0.0f), size);
  spritesNormalRender[id] = &spriteArray[id];
}

void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle) {
  spritesRotate[id] = Sprite();
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  // printf("nuevo sprite id: %d. pos: %d\n",spritesRotate[id].id,id);
  angles[id] = angle;
  loadSprite(&spritesRotate[id], mode, Vec2(0.0f, 0.0f), size);
  spritesRotateRender[id] = &spritesRotate[id];
}

void deleteSprite(const int entitieID) {
  if (spriteArray.count(entitieID) == 1) {
    engine->renderer.getTextureRepository()
        .getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);
    spriteArray.erase(entitieID);
    if (spritesNormalRender.count(entitieID)) {
      spritesNormalRender.erase(entitieID);
    }
  } else {
    engine->renderer.getTextureRepository()
        .getBySpriteId(spritesRotate[entitieID].id)
        ->removeLinkById(spritesRotate[entitieID].id);
    spritesRotate.erase(entitieID);
    if (spritesRotateRender.count(entitieID)) {
      spritesRotateRender.erase(entitieID);
    }
  }
}

/*
 * @return True if collision exist
 */
bool boxCollision(BoxCollider* col1, BoxCollider* col2) {
  if (col1->x + col1->width >= col2->x && col2->x + col2->width >= col1->x &&
      col1->y + col1->height >= col2->y && col2->y + col2->height >= col1->y) {
    return true;
  }
  return false;
}

BoxCollider::BoxCollider() {}
BoxCollider::BoxCollider(float x, float y, float width, float height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}
BoxCollider::BoxCollider(float x, float y, float width, float height,
                         float offsetX, float offsetY) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->offsetX = offsetX;
  this->offsetY = offsetY;
}

Animation::Animation() {}

Animation::Animation(enumAnimation anim) { animID = anim; }

void AnimationManager::update() {
  std::map<int, Animation>::iterator it;

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    if (it->second.framesCounter >= (60 / framesSpeed)) {
      it->second.framesCounter = 0;
      it->second.currentFrame++;

      if (it->second.currentFrame >=
          animationDataArray[it->second.animID].maxFrame) {
        it->second.currentFrame = 0;
      }
      // printf("AnimID: %d, currentFrame: %d\n",
      // animationArray[it->first].animID,
      //        it->second.currentFrame);
      draw(it->first, it->second.animID, it->second.currentFrame);
      angle(it->first);
      alpha(it->first);
      scale(it->first);
    }
    position(it->first);
    it->second.framesCounter++;
  }
}

// TODO: hacerlo para los rotate
void AnimationManager::draw(const int entitieID, const int animID,
                            const int currentFrame) {
  if (animationDataArray[animID].draw.count(currentFrame)) {
    animationArray[entitieID].draw =
        animationDataArray[animID].draw[currentFrame];
    if(spriteArray.count(entitieID) == 1){
      // printf("Key: %d change Draw: %d, currentFrame: %d\n",entitieID,animationArray[entitieID].draw,currentFrame);
      if (animationArray[entitieID].draw == false ) {
        // if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
          // texRepo->getBySpriteId(spriteArray[entitieID].id)
          //     ->removeLinkById(spriteArray[entitieID].id);
          spritesNormalRender.erase(entitieID);
          spriteNormalIdStopRender.push_back(entitieID);
        // }
      } else {
        spritesNormalRender[entitieID] = &spriteArray[entitieID];
      }
    }else{
      // printf("Key: %d change Draw: %d, currentFrame: %d\n",entitieID,animationArray[entitieID].draw,currentFrame);
      if (animationArray[entitieID].draw == false ) {
        // if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
          // texRepo->getBySpriteId(spriteArray[entitieID].id)
          //     ->removeLinkById(spriteArray[entitieID].id);
          spritesRotateRender.erase(entitieID);
          spritesRotateIdStopRender.push_back(entitieID);
        // }
      } else {
        spritesRotateRender[entitieID] = &spritesRotate[entitieID];
      }
    }
    
  }

  if (spriteArray.count(entitieID) == 1 &&
      animationDataArray[animID].texture.count(currentFrame) == 1 &&
      animationArray[entitieID].draw == true) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entitieID].id);
      texRepo->getBySpriteId(spriteArray[entitieID].id)
          ->removeLinkById(spriteArray[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animID].texture[currentFrame]->addLink(
        spriteArray[entitieID].id);
  } else if (animationDataArray[animID].texture.count(currentFrame) == 1 &&
             animationArray[entitieID].draw == true) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spritesRotate[entitieID].id) != nullptr) {
    // printf("unlink sprite rotate id: %d\n", spritesRotate[entitieID].id);
      texRepo->getBySpriteId(spritesRotate[entitieID].id)
          ->removeLinkById(spritesRotate[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animID].texture[currentFrame]->addLink(
        spritesRotate[entitieID].id);
  }
}

void AnimationManager::position(const int entitieID) {
  // finalPos += animPos

  if (animationDataArray[animationArray[entitieID].animID].position.count(
          animationArray[entitieID].currentFrame)) {
    texPosArray[entitieID] =
        animationDataArray[animationArray[entitieID].animID]
            .position[animationArray[entitieID].currentFrame];
    // if (animationArray[entitieID].animID == 22) {
    //   printf("cambie la posicion en frame: %d. AnimID:%d\n",
    //          animationArray[entitieID].currentFrame,
    //          animationArray[entitieID].animID);
    //   // finalPosArray[entitieID].print();
    // }
  }
  // if (animationArray[entitieID].animID == 22) {
  //     printf("posicion en frame: %d. AnimID:%d\n",
  //            animationArray[entitieID].currentFrame,
  //            animationArray[entitieID].animID);
  //     finalPosArray[entitieID].print();
  //   }
}

void AnimationManager::angle(const int entitieID) {
  if (animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    angles[entitieID] = animationDataArray[animationArray[entitieID].animID]
                            .angle[animationArray[entitieID].currentFrame];

    // if (animationArray[entitieID].animID == 21) {
    //   printf("cambie el angle en frame: %d. AnimID:%d, angle: %f\n",
    //          animationArray[entitieID].currentFrame,
    //          animationArray[entitieID].animID, angles[entitieID]);
    // }
  }
}
void AnimationManager::alpha(const int entitieID) {
  if (animationDataArray[animationArray[entitieID].animID].alpha.count(
          animationArray[entitieID].currentFrame) == 1) {
    // if(animationArray[entitieID].animID == 20){
    //   printf("cambie el alpha en frame: %d. AnimID:%d\n",
    //        animationArray[entitieID].currentFrame,
    //        animationArray[entitieID].animID);
    // }

    float alpha = animationDataArray[animationArray[entitieID].animID]
                      .alpha[animationArray[entitieID].currentFrame] *
                  128;
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].color.a = alpha;
    } else {
      spritesRotate[entitieID].color.a = alpha;
    }
  }
}

void AnimationManager::scale(const int entitieID) {
  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
      // spriteArray[entitieID].scale =
      //     animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame];
      // if(entitieID == 68){
      // printf("key 68 sprite size: %s. current Frame: %d\n", spriteArray[entitieID].size.getPrint().c_str(),animationArray[entitieID].currentFrame);
      // printf("original size: %s\n",originalSize[entitieID].getPrint().c_str());
      // printf("scale: %s\n",animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame].getPrint().c_str());
      // }
    } else {
      spritesRotate[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
      if(entitieID == 63){
        printf("frame: %d size: %s\n",animationArray[entitieID].currentFrame,spritesRotate[entitieID].size.getPrint().c_str());
      }
      // spritesRotate[entitieID].scale =
      //     animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame];
      // printf("key: %d, scale: %f, frame:%d\n", entitieID,spritesRotate[entitieID].scale,animationArray[entitieID].currentFrame);

    }
    
  }else{
    // printf("key: %d no found\n", entitieID);
  }
}

void AnimationManager::debug() {
  std::map<int, Animation>::iterator it;

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    position(it->first);
  }
}

int AnimationManager::debugAnim(const int entitieID) {
  auto& textureRepository = renderer->getTextureRepository();

  if (animationArray[entitieID].framesCounter < (60 / framesSpeed)) {
    animationArray[entitieID].framesCounter++;
    return 1;
  }
  printf("pase por debug anim\n");

  animationArray[entitieID].currentFrame++;
  animationArray[entitieID].framesCounter = 0;

  if (animationArray[entitieID].currentFrame >=
      animationDataArray[animationArray[entitieID].animID].maxFrame) {
    animationArray[entitieID].currentFrame = 0;
  }

  if (spriteArray.count(entitieID) == 1 &&
      animationDataArray[animationArray[entitieID].animID].texture.count(
          animationArray[entitieID].currentFrame) == 1) {
    textureRepository.getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);

    animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame]
        ->addLink(spriteArray[entitieID].id);
  } else if (animationDataArray[animationArray[entitieID].animID].texture.count(
                 animationArray[entitieID].currentFrame) == 1) {
    textureRepository.getBySpriteId(spritesRotate[entitieID].id)
        ->removeLinkById(spritesRotate[entitieID].id);

    animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame]
        ->addLink(spritesRotate[entitieID].id);
  }

  if (animationDataArray[animationArray[entitieID].animID].position.count(
          animationArray[entitieID].currentFrame) == 1) {
    texPosArray[entitieID] =
        animationDataArray[animationArray[entitieID].animID]
            .position[animationArray[entitieID].currentFrame];
  }

  if (animationDataArray[animationArray[entitieID].animID].alpha.count(
          animationArray[entitieID].currentFrame) == 1) {
    float alpha = animationDataArray[animationArray[entitieID].animID]
                      .alpha[animationArray[entitieID].currentFrame] *
                  128;
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].color.a = alpha;
    } else {
      spritesRotate[entitieID].color.a = alpha;
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
      // spriteArray[entitieID].scale =
      //     animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame];
    } else {
      spritesRotate[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
      // spritesRotate[entitieID].scale =
      //     animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame];
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    angles[entitieID] = animationDataArray[animationArray[entitieID].animID]
                            .angle[animationArray[entitieID].currentFrame];
    // printf("entitie ID: %d, frame:%d, angle:%f\n", entitieID,
    //        animationArray[entitieID].currentFrame, angles[entitieID]);
  }

  return 0;
}

void AnimationManager::debugChangeFrame(const int entitieID, const int key) {
  auto& textureRepository = renderer->getTextureRepository();

  if (animationDataArray[animationArray[entitieID].animID].draw.count(animationArray[entitieID].currentFrame)) {
    animationArray[entitieID].draw =
        animationDataArray[animationArray[entitieID].animID].draw[animationArray[entitieID].currentFrame];
    if (animationArray[entitieID].draw == false) {
      if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
        texRepo->getBySpriteId(spriteArray[entitieID].id)
            ->removeLinkById(spriteArray[entitieID].id);
        spritesNormalRender.erase(entitieID);
        spriteNormalIdStopRender.push_back(entitieID);
      }

    } else {
      spritesNormalRender[entitieID] = &spriteArray[entitieID];
    }
  }

  if (spriteArray.count(entitieID) == 1 &&
      animationDataArray[animationArray[entitieID].animID].texture.count(
          animationArray[entitieID].currentFrame) == 1) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
      textureRepository.getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame]
        ->addLink(spriteArray[entitieID].id);
  } else if (animationDataArray[animationArray[entitieID].animID].texture.count(
                 animationArray[entitieID].currentFrame) == 1) {
    // Unlink Texture from the sprite entitie
    textureRepository.getBySpriteId(spritesRotate[entitieID].id)
        ->removeLinkById(spritesRotate[entitieID].id);

    // Link new Texture to the sprite entitie
    animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame]
        ->addLink(spritesRotate[entitieID].id);
  }

  if (animationDataArray[animationArray[entitieID].animID].position.count(
          animationArray[entitieID].currentFrame) == 1) {
    texPosArray[entitieID] =
        animationDataArray[animationArray[entitieID].animID]
            .position[animationArray[entitieID].currentFrame];
  }

  if (animationDataArray[animationArray[entitieID].animID].alpha.count(
          animationArray[entitieID].currentFrame) == 1) {
    float alpha = animationDataArray[animationArray[entitieID].animID]
                      .alpha[animationArray[entitieID].currentFrame] *
                  128;
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].color.a = alpha;
    } else {
      printf("entitie ID: %d, frame:%d, alpha:%f\n", entitieID,
             animationArray[entitieID].currentFrame, alpha);
      spritesRotate[entitieID].color.a = alpha;
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
      // spriteArray[entitieID].scale =
      //     animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame];
    } else {
      spritesRotate[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];

      // spritesRotate[entitieID].scale =
      //     animationDataArray[animationArray[entitieID].animID]
      //         .scale[animationArray[entitieID].currentFrame];
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    angles[entitieID] = animationDataArray[animationArray[entitieID].animID]
                            .angle[animationArray[entitieID].currentFrame];
    // printf("entitie ID: %d, frame:%d, angle:%f\n", entitieID,
    //        animationArray[entitieID].currentFrame, angles[entitieID]);
  }
}

void RendererDebugSpritesManager::update() {
  std::map<int, Sprite>::iterator it;
  // auto& textureRepository = renderer->getTextureRepository();
  // TYRA_LOG("Render Debug");
  // printf("debug size: %d\n",debugSpriteBoxCollider.size());
  // for (it = dm_SpriteBoxCollider.begin(); it != dm_SpriteBoxCollider.end();
  //      it++) {
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   renderer->renderer2D.render(dm_SpriteBoxCollider[it->first]);
  // }

  // TYRA_LOG("Render Debug Point");

  for (it = dm_SpritePointCollider.begin(); it != dm_SpritePointCollider.end();
       it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    renderer->renderer2D.render(dm_SpritePointCollider[it->first]);
  }

  // for (it = dm_SpriteNormal.begin(); it != dm_SpriteNormal.end(); it++) {
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   dm_SpriteNormal[it->first].position = spriteArray[it->first].position;
  //   dm_SpriteNormal[it->first].scale = spriteArray[it->first].scale;
  //   dm_SpriteNormal[it->first].size = spriteArray[it->first].size;

  //   renderer->renderer2D.render(dm_SpriteNormal[it->first]);
  // }

  for (it = dm_SpriteRotate.begin(); it != dm_SpriteRotate.end(); it++) {
    // printf("key: %d. sprite ID: %d\n", it->first, it->second.id);

    dm_SpriteRotate[it->first].position = spritesRotate[it->first].position;
    dm_SpriteRotate[it->first].scale = spritesRotate[it->first].scale;
    dm_SpriteRotate[it->first].size = spritesRotate[it->first].size;

    renderer->renderer2D.renderRotate(dm_SpriteRotate[it->first],
                                      angles[it->first]);
  }

  // for (it = dm_SpriteNormalPivot.begin(); it != dm_SpriteNormalPivot.end();
  //      it++) {
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   dm_SpriteNormalPivot[it->first].position =
  //   spriteArray[it->first].position; dm_SpriteNormalPivot[it->first].scale =
  //   spriteArray[it->first].scale;

  //   renderer->renderer2D.render(dm_SpriteNormalPivot[it->first]);
  // }

  // for (it = dm_SpriteRotatePivot.begin(); it != dm_SpriteRotatePivot.end();
  //      it++) {
  //   // printf("pase\n");
  //   // printf("key: %d. sprite ID: %d\n", it->first, it->second.id);

  //   dm_SpriteRotatePivot[it->first].position =
  //       spritesRotate[it->first].position;

  //   renderer->renderer2D.renderRotate(dm_SpriteRotatePivot[it->first],
  //                                     angles[it->first]);
  // }
}

void RendererSprites::updateChildPos() {
  std::map<int, FatherID>::iterator it;
  for (it = fatherIDArray.begin(); it != fatherIDArray.end(); it++) {
    for (unsigned int i = 0; i < it->second.id.size(); i++) {
      // finalPos += fatherPos

      finalPosArray[it->second.id[i]].x += posArray[it->first].x;
      finalPosArray[it->second.id[i]].y += posArray[it->first].y;
    }
  }
}

void RendererSprites::update() {
  std::map<int, Sprite*>::iterator it;
  // printf("size: %d\n", spriteArray.size());
  for (it = spritesNormalRender.begin(); it != spritesNormalRender.end();
       it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second->id);

    // finalPos += entitiePos

    finalPosArray[it->first] +=
        texPosArray[it->first] * scaleTexture[it->first];

    finalPosArray[it->first] += posArray[it->first];

    if (finalPosArray[it->first].x != it->second->position.x ||
        finalPosArray[it->first].y != it->second->position.y) {
      it->second->position = finalPosArray[it->first];
      // printf("key: %d. sprite pos:%f,%f texture pos:%f,%f size: %s\n", it->first,
      //        it->second->position.x, it->second->position.y,
      //        texPosArray[it->first].x, texPosArray[it->first].y,it->second->size.getPrint().c_str());
    }

    // if(it->first == 61){
    //   printf("key: %d. size: %s\n", it->first,it->second->size.getPrint().c_str());
    // }

    renderer->renderer2D.render(it->second);
    finalPosArray[it->first] = Vec2(0.0f, 0.0f);
  }
  // printf("Render Finish\n");
}

void RendererSprites::updateRotate() {
  std::map<int, Sprite*>::iterator it;
  // TYRA_LOG("Update Rotate");

  for (it = spritesRotateRender.begin(); it != spritesRotateRender.end();
       it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second->id);

    // finalPos += texPosArray
    // finalPos += entitiePos

    // if(texPosArray.count())

    finalPosArray[it->first] +=
        texPosArray[it->first] * scaleTexture[it->first];

    finalPosArray[it->first] += posArray[it->first];

    if (finalPosArray[it->first].x != it->second->position.x ||
        finalPosArray[it->first].y != it->second->position.y) {
      it->second->position = finalPosArray[it->first];
      // printf("key: %d. sprite pos: %f,%f\n", it->first,
      // it->second->position.x,
      //        it->second->position.y);
      // printf("scale: %f\n", it->second->scale);
    }
    // if(it->first == 63){
    //   printf("key 63, angle: %s\n", angles[it->first].getPrint().c_str());
    // }

    renderer->renderer2D.renderRotate(*it->second, angles[it->first]);
    finalPosArray[it->first] = Vec2(0.0f, 0.0f);
  }
  // printf("Render Finish\n");
}

void ZombiesManager::update() {
  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); it++) {
    if (it->debug == true) {
      continue;
    }
    if (it->timer > 0) {
      it->timer--;
    } else if (it->attack == false) {
      it->timer = 12;
      // printf("projectile id: %d\n", *it);
      // printf("position: %f,%f\n",
      // spriteArray[*it->body[0]].position.x,spriteArray[*it->body[0]].position.y);
      // printf("box: %f,%f\n",
      // boxColliderArray[*it->body[0]].x,boxColliderArray[*it->body[0]].y);
      posArray[*it->father].x--;

      boxColliderArray[*it->body[0]].x =
          posArray[*it->father].x + posArray[*it->body[0]].x + 60;
      dm_SpriteBoxCollider[*it->body[0]].position.x =
          boxColliderArray[*it->body[0]].x;
      // printf("box: %f,%f\n",
      // boxColliderArray[*it->body[0]].x,boxColliderArray[*it->body[0]].y);
    }
  }
}

int ZombiesManager::collision() {
  std::vector<Zombie>::iterator it;

  if (plantsCreated == 0) {
    for (it = zombie.begin(); it < zombie.end(); it++) {
      if (it->debug == true) {
        continue;
      }
      it->attack = false;
      animationArray[*it->body[0]].animID = zombieWalk;
    }
    return 0;
  }

  for (it = zombie.begin(); it < zombie.end(); it++) {
    // printf("hay una planta en %d\n",i);
    if (it->debug == true) {
      continue;
    }
    for (int i = 0; i < 45; i++) {
      if (plant[i].type != NonePlant) {
        //  printf("vec plant %f,%f. vec zombi %f,%f,%f,%f\n",
        //  pointColliderArray[*plant[i].body[0]].x,
        //  pointColliderArray[*plant[i].body[0]].y,
        //  boxColliderArray[*zombie[j].body[0]].x,
        //  boxColliderArray[*zombie[j].body[0]].y,
        //  boxColliderArray[*zombie[j].body[0]].x +
        //  boxColliderArray[*zombie[j].body[0]].width,
        //  boxColliderArray[*zombie[j].body[0]].y +
        //  boxColliderArray[*zombie[j].body[0]].height);
        // static int timerprueba = 0;
        // static int contador = 0;

        // if(timerprueba>0){
        //     timerprueba--;
        // }else{
        //     timerprueba = 59;
        //     contador++;
        //     printf("sec %d\n",contador);
        //     if(contador >= 7){
        //         contador = 0;
        //     }
        // }

        if (boxCollision(&boxColliderArray[plant[i].id[0]],
                         &boxColliderArray[*(it)->body[0]]) == true) {
          it->attack = true;
          animationArray[*it->body[0]].animID = zombieNormalAttack;
          if (it->attackTimer > 0) {
            it->attackTimer--;
          } else {
            it->attackTimer = 80;
            printf("comiendo planta\n");
            lifeArray[plant[i].id[0]] -= damageArray[it->id[0]];

            if (lifeArray[plant[i].id[0]] <= 0) {
              printf("borre planta id: %d\n", plant[i].id[0]);
              if (plant[i].type == PeaShotter) {
                deletePeashotter(i);
              } else if (plant[i].type == SunFlower) {
                deleteSunflower(i);
              }

              it->attack = false;
              animationArray[*it->body[0]].animID = zombieWalk;
            }
          }
        } else {
          it->attack = false;
          animationArray[*it->body[0]].animID = zombieWalk;
        }
      }
    }
  }

  return 1;
}

void ProjectileManager::update() {
  std::vector<int>::iterator it;

  for (it = projectile.begin(); it < projectile.end(); it++) {
    // printf("projectile id: %d\n", *it);
    posArray[*it].x++;
    // printf("proyectile pos: %f,%f\n", posArray[*it].x, posArray[*it].y);
    // printf("position: %f,%f\n",
    // spriteArray[*it].position.x,spriteArray[*it].position.y);
    boxColliderArray[*it].x = posArray[*it].x;
    dm_SpriteBoxCollider[*it].position.x = boxColliderArray[*it].x;
    if (posArray[*it].x >= 580) {
      // delete projectile
      printf("borrando proyectil\n");
      deleteSprite(*it);
      boxColliderArray.erase(*it);
      posArray.erase(*it);
      deleteDebugBoxCollider(*it);
      Entities::deleteID(*it);
      it = projectile.erase(it);
      projectilesCreated--;
    }
  }
}

void ProjectileManager::zombieCollision() {
  std::vector<int>::iterator it;
  std::vector<Zombie>::iterator it2;
  auto& textureRepository = renderer->getTextureRepository();
  for (it = projectile.begin(); it < projectile.end(); it++) {
    for (it2 = zombie.begin(); it2 < zombie.end(); it2++) {
      if (boxCollision(&boxColliderArray[*it],
                       &boxColliderArray[*(it2)->body[0]])) {
        // printf("choque con zombie\n");
        // printf("sprite ID: %d\n", spriteArray[*it].id);
        // printf("borre ID: %d\n", *it);

        // damage zombie
        lifeArray[*it2->body[0]] -= damageArray[*it];
        // printf("zombie id: %d\n",*it2->body[0]);
        // delete zombie
        if (lifeArray[*it2->body[0]] <= 0) {
          posArray.erase(*it2->father);
          posArray.erase(*it2->body[0]);
          // posArray.erase(*it2->body[1]);

          deleteFatherID(it2->father, it2->body[0]);
          // deleteFatherID(*it2->father,*it2->body[1]);
          deleteSprite(*it2->body[0]);
          animationArray.erase(*it2->body[0]);
          lifeArray.erase(*it2->body[0]);
          boxColliderArray.erase(*it2->body[0]);
          deleteDebugBoxCollider(*it2->body[0]);
          Entities::deleteID(*it2->father);
          Entities::deleteID(*it2->body[0]);
          it2 = zombie.erase(it2);

          // zombiesCreated--;
        }

        // delete projectile

        // printf("borrando proyectil\n");
        // printf("it: %d\n",*it);
        // printf("it end: %d\n\n",*projectile.end());
        Tyra::Texture* text =
            textureRepository.getBySpriteId(spriteArray[*it].id);
        TYRA_ASSERT(text,
                    "No se encontro la textura del proyectil with id: ", *it);
        deleteSprite(*it);
        boxColliderArray.erase(*it);
        deleteDebugBoxCollider(*it);
        Entities::deleteID(*it);
        it = projectile.erase(it);

        // Break projectile loop if exist another zombie
        if (it == projectile.end()) {
          it2 = zombie.end();
        }

        projectilesCreated--;
      }
    }
  }
}

void newFatherID(int* fatherID, int* childID) {
  // printf("new father: %d, child: %d\n", *fatherID, *childID);
  fatherIDArray[*fatherID].id.push_back(*childID);
}

void deleteFatherID(int* fatherID, int* childID) {
  // printf("delete father: %d, child: %d\n", *fatherID, *childID);
  std::vector<int>::iterator it =
      find(fatherIDArray[*fatherID].id.begin(),
           fatherIDArray[*fatherID].id.end(), *childID);
  fatherIDArray[*fatherID].id.erase(it);
}

void newCursor(int* cursor, Tyra::Vec2 pos) {
  *cursor = Entities::newID();
  printf("cursor id: %d\n", *cursor);
  createSprite(*cursor, Tyra::MODE_STRETCH, pos, Vec2(56, 48));
  createTexture(*cursor, "cursor6.png");
  boxColliderArray[*cursor] = BoxCollider(pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  texPosArray[*cursor] = Vec2(0.0f, 0.0f);
  scaleTexture[*cursor] = Vec2(1.0f, 1.0f);
  createDebugBoxCollider(*cursor, Tyra::MODE_STRETCH);
}

void newDeckCursor(int* cursor, Tyra::Vec2 pos) {
  *cursor = Entities::newID();
  printf("deck cursor id: %d\n", *cursor);
  createSprite(*cursor, Tyra::MODE_STRETCH, pos, Vec2(56, 48));
  createTexture(*cursor, "cursor6.png");
  texPosArray[*cursor] = Vec2(0.0f, 0.0f);
  scaleTexture[*cursor] = Vec2(1.0f, 1.0f);
  // boxColliderArray[*cursor] = BoxCollider(
  //     pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  // createDebugBoxCollider(*cursor, Tyra::MODE_STRETCH);
}

void newProjectile(Vec2 position) {
  if (projectilesCreated < 100) {
    projectile.insert(projectile.begin() + projectilesCreated,
                      Entities::newID());
    int* id = &projectile[projectilesCreated];
    // printf("projectile ID: %d\n", *id);
    // printf("projectile pos %f,%f\n", position.x,position.y);

    position.y -= 15.0f;
    createSprite(*id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    // Sprite* spriteProjectile = &spriteArray[*id];
    projectilePea->addLink(spriteArray[*id].id);

    // damage
    damageArray[*id] = 20;
    // hitbox
    boxColliderArray[*id] =
        BoxCollider(posArray[*id].x, posArray[*id].y, spriteArray[*id].size.x,
                    spriteArray[*id].size.y);
    createDebugBoxCollider(*id, Tyra::MODE_STRETCH);
    projectilesCreated++;
  }
}