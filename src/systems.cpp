#include "systems.hpp"
#include "components.hpp"
#include "imageFiles.hpp"
#include "font/font.hpp"
#include "entities/entities.hpp"

int projectilesCreated = 0;
int explosionsCreated = 0;

PlayerControl playerControl;
BoxCollisionManager boxColliderManager;
AnimationManager animManager;
RendererSprites renderSprites;
RendererDebugSpritesManager renderDebugSpritesManager;
ZombiesManager zombiesManager;
PlantsManager plantsManager;
RewardManager rewardManager;
CardManager cardManager;
CameraManager cameraManager;
FontManager fontManager;
FrameManager frameManager;
LawnMoverManager lawnMoverManager;

void PlayerControl::update() {
  for (Controller& joystick: controller){
    joystick.update();
  }
}

void FrameManager::update(){
  // Se cuenta la cantidad de frames que pasaron
  // obtengo el frame correspondiente de cada animacion
  std::vector<FrameOut> frameArray;
  FrameOut frameOut;
  
  for(FrameCounter& frame: frameCounterArray){
    if(frame.update() == 0){
      // printf("Entity id: %d, animID: %d, frame: %d\n",frame.entityID,frame.animIndex,frame.currentFrame);
      frameOut.entityID = frame.entityID;
      frameOut.animIndex = frame.animIndex;
      frameOut.frame = frame.currentFrame;
      frameArray.push_back(frameOut);
      // if(frameOut.animIndex == 102){
      //   printf("ingresar Entity id: %d, animID: %d, frame: %d\n",frame.entityID,frame.animIndex,frame.currentFrame);
      // }
    }
  }

  if(frameArray.size() > 0){
    for(unsigned int i=0;i<frameArray.size();i++){
      // if(frameArray[i].entityID==201){
      //   printf("entity:%d, animID: %d, frame: %d\n",frameArray[i].entityID,frameArray[i].animIndex,frameArray[i].frame);
      // }
      // printf("entity:%d, animID: %d, frame: %d\n",frameArray[i].entityID,frameArray[i].animIndex,frameArray[i].frame);
      std::vector<AnimationProperty>& animProp = animationDataArray[frameArray[i].animIndex].property[frameArray[i].frame];
      for(unsigned int j=0; j< animProp.size();j++){
        // if(frameArray[i].animIndex ==44){
        // printf("type: %d, data: %d\n",animProp[j].type,animProp[j].dataIndex);

        // }
        // printf("type: %d, data: %d\n",animProp[j].type,animProp[j].dataIndex);
        if(animProp[j].type == ANIM_POSITION){
          // if(frameArray[i].animIndex ==22){
          //   printf("entity:%d, animID: %d, frame: %d\n",frameArray[i].entityID,frameArray[i].animIndex,frameArray[i].frame);
          //   positionFrame[animProp[j].dataIndex].print();

          // }
          texPosArray[frameArray[i].entityID] = positionFrame[animProp[j].dataIndex] * scaleTexture[frameArray[i].entityID];
        }else if(animProp[j].type == ANIM_TEXTURE){
          const int spriteID = spriteArray[frameArray[i].entityID].id;
          Tyra::Texture* oldTexture = texRepo->getBySpriteId(spriteID);
          Tyra::Texture* newTexture = texRepo->getByTextureId(textureFrame[animProp[j].dataIndex]);
          if (oldTexture != newTexture) {
            // printf("link sprite\n");
            if (oldTexture != nullptr) {
              // printf("unlink sprite id: %d\n", spriteArray[frameArray[i].entityID].id);
              oldTexture->removeLinkById(spriteID);
            }
          
            // Link new Texture to the sprite entitie
            newTexture->addLink(spriteID);
            spriteArray[frameArray[i].entityID].textureID = newTexture->id;
            originalSize[frameArray[i].entityID] =
                Vec2(newTexture->getWidth(), newTexture->getHeight());
          }
        }else if(animProp[j].type == ANIM_SCALE){
          spriteArray[frameArray[i].entityID].size = 
            originalSize[frameArray[i].entityID] * 
            scaleTexture.at(frameArray[i].entityID) * 
            scaleFrame[animProp[j].dataIndex];
        }else if(animProp[j].type == ANIM_ROTATION){
          // angleFrame[animProp[j].dataIndex].print();
          // if(frameArray[i].animIndex ==22){
          //   angleFrame[animProp[j].dataIndex].print();
          // }
          angleArray[frameArray[i].entityID] = angleFrame[animProp[j].dataIndex];
        } else if(animProp[j].type == ANIM_ALPHA){
          spriteArray[frameArray[i].entityID].color.a = alphaFrame[animProp[j].dataIndex];
        } else if (animProp[j].type == ANIM_DRAW){
          if (spriteRenderIDArray.count(frameArray[i].entityID) == 1 && drawFrame[animProp[j].dataIndex] == (int)enumDraw::noDraw) {
            spriteRenderIDArray.erase(frameArray[i].entityID);
            // spriteNormalIdStopRender.push_back(entityID);
          } else if (spriteRenderIDArray.count(frameArray[i].entityID) == 0 && drawFrame[animProp[j].dataIndex] == (int)enumDraw::draw) {
            spriteRenderIDArray.insert(frameArray[i].entityID, 0);
            int renderSize = spriteRenderIDArray.first.size();
            // printf("sorting\n");
            for(int j=renderSize-1;j>1;j--){
              if(spriteRenderIDArray.first[j] < spriteRenderIDArray.first[j-1]){          
                // printf("pos1: %d\n",spriteRenderIDArray.first[j]);
                // printf("pos2: %d\n",spriteRenderIDArray.first[j-1]);
                int aux= spriteRenderIDArray.first[j];
                spriteRenderIDArray.first[j] = spriteRenderIDArray.first[j-1];
                spriteRenderIDArray.first[j-1] = aux;
              }
            }
          }
        }
      }
    }
    // printf("sali\n");
  }
}

void AnimationManager::update() {
  int i = 0;
  for (auto& it : animationArray.first) {
    // printf("anim id: %d\n",it);
    // printf("anim pointer: %p\n",(void *) &it);
    animationArray.second[i].update(it);
    i++;
  }
}

void AnimationManager::debug() {
  for (unsigned int i = 0; i < animationArray.first.size(); i++) {
    animationArray.second[i].position(animationArray.first[i]);
  }
}

void AnimationManager::debugChangeFrame(const int entitieID, const int key) {
  // if (animationDataArray[animationArray[entitieID].animID].draw.count(
  //         animationArray[entitieID].currentFrame)) {
  //   animationArray[entitieID].draw =
  //       animationDataArray[animationArray[entitieID].animID]
  //           .draw[animationArray[entitieID].currentFrame];
  //   if (animationArray[entitieID].draw == (int)enumDraw::noDraw) {
  //     if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
  //       texRepo->getBySpriteId(spriteArray[entitieID].id)
  //           ->removeLinkById(spriteArray[entitieID].id);
  //       spriteRenderIDArray.erase(entitieID);
  //       // spriteNormalIdStopRender.push_back(entitieID);
  //     }

  //   } else {
  //     spriteRenderIDArray[entitieID] = entitieID;
  //   }
  // }

  // if (animationDataArray[animationArray[entitieID].animID].texture.count(
  //         animationArray[entitieID].currentFrame) == 1) {
  //   // Unlink Texture from the sprite entitie
  //   if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
  //     texRepo->getBySpriteId(spriteArray[entitieID].id)
  //         ->removeLinkById(spriteArray[entitieID].id);
  //   }

  //   // Link new Texture to the sprite entitie
  //   texRepo
  //       ->getByTextureId(animationDataArray[animationArray[entitieID].animID]
  //                            .texture[animationArray[entitieID].currentFrame])
  //       ->addLink(spriteArray[entitieID].id);
  // }

  // if (animationDataArray[animationArray[entitieID].animID].position.count(
  //         animationArray[entitieID].currentFrame) == 1) {
  //   texPosArray[entitieID] =
  //       animationDataArray[animationArray[entitieID].animID]
  //           .position[animationArray[entitieID].currentFrame];
  // }

  // if (animationDataArray[animationArray[entitieID].animID].alpha.count(
  //         animationArray[entitieID].currentFrame) == 1) {
  //   float alpha = animationDataArray[animationArray[entitieID].animID]
  //                     .alpha[animationArray[entitieID].currentFrame];
  //   spriteArray[entitieID].color.a = alpha;
  // }

  // if (animationDataArray[animationArray[entitieID].animID].scale.count(
  //         animationArray[entitieID].currentFrame) == 1) {
  //   spriteArray[entitieID].size =
  //       originalSize[entitieID] *
  //       animationDataArray[animationArray[entitieID].animID]
  //           .scale[animationArray[entitieID].currentFrame];
  // }

  // if (animationDataArray[animationArray[entitieID].animID].angle.count(
  //         animationArray[entitieID].currentFrame) == 1) {
  //   angleArray[entitieID] = animationDataArray[animationArray[entitieID].animID]
  //                               .angle[animationArray[entitieID].currentFrame];
  // }
}

void RendererDebugSpritesManager::update() {
  Tyra::Sprite debugSprite;
  debugSprite.mode =  Tyra::MODE_STRETCH;
  debugSprite.color = Tyra::Color(0,255,0,128);
  debugBoxTexture->addLink(debugSprite.id);
  debugSprite.textureID = debugBoxTexture->id;
  std::vector<BoxCollider> vec;
  vec = boxColliderArray[BOXCOLLIDER_PLAYER];
  for (unsigned int i = 0; i < vec.size();i++){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position =
        Vec2(vec[i].x, vec[i].y);
    debugSprite.size = Vec2(vec[i].width, vec[i].height);
    renderer->renderer2D.render(debugSprite);
  }

  vec = boxColliderArray[BOXCOLLIDER_PLANT];
  for (unsigned int i = 0; i < vec.size();i++){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position =
        Vec2(vec[i].x, vec[i].y);
    debugSprite.size = Vec2(vec[i].width, vec[i].height);
    renderer->renderer2D.render(debugSprite);
  }

  
  vec = boxColliderArray[BOXCOLLIDER_SUN];
  for (unsigned int i = 0; i < vec.size();i++){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position =
        Vec2(vec[i].x, vec[i].y);
    debugSprite.size = Vec2(vec[i].width, vec[i].height);
    renderer->renderer2D.render(debugSprite);
  }

  // vec = boxColliderArray[BOXCOLLIDER_MAP];
  // for (unsigned int i = 0; i < vec.size();i++){
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   debugSprite.position =
  //       Vec2(vec[i].x, vec[i].y);
  //   debugSprite.size = Vec2(vec[i].width, vec[i].height);
  //   renderer->renderer2D.render(debugSprite);
  // }
  
  for (BoxCollider& box: boxColliderZombie){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position = Vec2(box.x, box.y);
    debugSprite.size = Vec2(box.width, box.height);
    renderer->renderer2D.render(debugSprite);
  }

  
  for (BoxCollider& box: boxColliderProyectile){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position = Vec2(box.x, box.y);
    debugSprite.size = Vec2(box.width, box.height);
    renderer->renderer2D.render(debugSprite);
  }

  debugBoxTexture->removeLinkById(debugSprite.id);

  // std::map<int, Sprite>::iterator it;
  // auto& textureRepository = renderer->getTextureRepository();

  // printf("debug size: %d\n",debugSpriteBoxCollider.size());
  // for (it = dm_SpriteBoxCollider.begin(); it != dm_SpriteBoxCollider.end();
  //      it++) {
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   dm_SpriteBoxCollider[it->first].position =
  //       Vec2(boxColliderArray[it->first].x, boxColliderArray[it->first].y);
  //   renderer->renderer2D.render(dm_SpriteBoxCollider[it->first]);
  // }

  // for (it = dm_SpritePointCollider.begin(); it != dm_SpritePointCollider.end();
  //      it++) {
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   renderer->renderer2D.render(dm_SpritePointCollider[it->first]);
  // }

  // for (it = dm_SpriteNormal.begin(); it != dm_SpriteNormal.end(); it++) {
  //   // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
  //   dm_SpriteNormal[it->first].position = spriteArray[it->first].position;
  //   dm_SpriteNormal[it->first].scale = spriteArray[it->first].scale;
  //   dm_SpriteNormal[it->first].size = spriteArray[it->first].size;

  //   renderer->renderer2D.render(dm_SpriteNormal[it->first]);
  // }

  // TODO: delete this
  // for (it = dm_SpriteRotate.begin(); it != dm_SpriteRotate.end(); it++) {
  //   // printf("key: %d. sprite ID: %d\n", it->first, it->second.id);

  //   dm_SpriteRotate[it->first].position =
  //   rotationSprite[it->first].sprite.position;
  //   dm_SpriteRotate[it->first].scale =
  //   rotationSprite[it->first].sprite.scale; dm_SpriteRotate[it->first].size =
  //   rotationSprite[it->first].sprite.size;

  //   renderer->renderer2D.renderRotate(dm_SpriteRotate[it->first],
  //                                     rotationSprite[it->first].angle);
  // }

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
  //       rotationSprite[it->first].position;

  //   renderer->renderer2D.renderRotate(dm_SpriteRotatePivot[it->first],
  //                                     angles[it->first]);
  // }
}

void RendererSprites::resetFinalPos() {
  // std::map<int, Vec2>::iterator it;
  for (unsigned int i = 0; i < finalPosArray.second.size(); i++) {
    finalPosArray.second[i] = posArray[finalPosArray.first[i]];
  }
}

void RendererSprites::updateChildPos() {
  for (unsigned int i = 0; i < fatherIDArray.first.size(); i++) {
    fatherIDArray.second[i].update(fatherIDArray.first[i]);
  }
}

void RendererSprites::updateTexture() {
  int i = 0;
  for (auto it : texPosArray.first) {
    finalPosArray[it] += texPosArray.second[i];
    i++;
  }
}
void RendererSprites::updateRender() {
  // int k=0;
  // printf("sprite render size: %d\n",spriteRenderIDArray.first.size());
  std::vector<int>& keys = spriteRenderIDArray.first;
  for (int &it : keys) {
    
    // printf("pase: %d\n",k);
    // k++;
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];
    // sizeof(spriteRender)
    // printf("entity:%d sprite ID: %d\n",it,spriteRender.id);
    // if(it == 30 || it == 31 ){
    //   printf("IT: %d sprite pos: \n",it);
    //   spriteArray[it].position.print();
    //   spriteArray[it].color.print();
    if (angleArray.count(it) == 1) {
      // angleArray[it].print();
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
    // }
  }
}

void RendererSprites::update() {
  resetFinalPos();
  updateChildPos();
  updateTexture();
  // if(true == true){
  //   cameraManager.update();
  // }
  updateRender();
}

void ZombiesManager::update() {
  for(Zombie& it: zombie){
    if(it.type != NoneZombie){
    it.move();
    it.attackPlant();
    }
  }
  // std::vector<Zombie>::iterator it;
  // for (it = zombie.begin(); it < zombie.end();) {
  //   //if (it->explosion == false) {
  //     it->move();
  //     // it->attackPlant();
  //     // it->normalColor();
  //     it++;
  //   /*} else {
  //     if (it->explosionState() == true) {
  //       it = zombie.erase(it);
  //     } else {
  //       it++;
  //     }
  //   }*/
  // }
}

// int ZombiesManager::collision() {
//   std::vector<Zombie>::iterator it;

//   if (plantsCreated == 0) {
//     for (it = zombie.begin(); it < zombie.end(); it++) {
//       if (it->debug == true) {
//         continue;
//       }
//       it->attack = false;
//       animationArray[it->id[0]].animID = zombieWalk;
//     }
//     return 0;
//   }

//   for (it = zombie.begin(); it < zombie.end(); it++) {
//     if (it->debug == true) {
//       continue;
//     }
//     for (int i = 0; i < 45; i++) {
//       if (plant[i].type != NonePlant) {
//         //  printf("vec plant %f,%f. vec zombi %f,%f,%f,%f\n",
//         //  pointColliderArray[*plant[i].body[0]].x,
//         //  pointColliderArray[*plant[i].body[0]].y,
//         //  boxColliderArray[*zombie[j].body[0]].x,
//         //  boxColliderArray[*zombie[j].body[0]].y,
//         //  boxColliderArray[*zombie[j].body[0]].x +
//         //  boxColliderArray[*zombie[j].body[0]].width,
//         //  boxColliderArray[*zombie[j].body[0]].y +
//         //  boxColliderArray[*zombie[j].body[0]].height);

//         if
//         (boxColliderArray[plant[i].id[0]].collision(&boxColliderArray[it->id[0]])
//         == true) {
//           it->attack = true;
//           animationArray[it->id[0]].animID = zombieNormalAttack;
//           if (it->attackTimer > 0) {
//             it->attackTimer--;
//           } else {
//             it->attackTimer = 80;
//             printf("comiendo planta\n");
//             lifeArray[plant[i].id[0]] -= damageArray[it->id[0]];

//             if (lifeArray[plant[i].id[0]] <= 0) {
//               printf("borre planta id: %d\n", plant[i].id[0]);
//               if (plant[i].type == PeaShotter) {
//                 deletePeashotter(i);
//               } else if (plant[i].type == SunFlower) {
//                 deleteSunflower(i);
//               }

//               it->attack = false;
//               animationArray[it->id[0]].animID = zombieWalk;
//             }
//           }
//         } else {
//           it->attack = false;
//           animationArray[it->id[0]].animID = zombieWalk;
//         }
//       }
//     }
//   }

//   return 1;
// }

void PlantsManager::create(int playerId) {
  if (debugMode == false) {
    if (mapEnable[(int)cursor[playerId].cursorTile.x] == true) {
      if (sunCounter >= cards[deckCursor[playerId].pos].cost &&
          plantsCreated < maxPlants &&
          timerArray[cards[deckCursor[playerId].pos].seedShadowTimer]
                  .counterMS >=
              timerArray[cards[deckCursor[playerId].pos].seedShadowTimer]
                  .maxMS) {
        // sunCounter -= cards[deckCursor[playerId].pos].cost;
        // textArray[sunCounterText].text = std::to_string(sunCounter);
        timerArray[cards[deckCursor[playerId].pos].seedShadowTimer]
            .resetCounter();
        spriteArray[cards[deckCursor[playerId].pos].seedShadowTimer].size.y =
            70;
        createPlant(cards[deckCursor[playerId].pos].plant,
                    cursor[playerId].cursorTile.x,
                    cursor[playerId].cursorTile.y,cards[deckCursor[playerId].pos].cost);
      } else {
        printf("can't create plants now\n");
      }
    }
  }
}

void RewardManager::update() {
  if (rewardExist == true) {
    if (searchBoxCollider(BOXCOLLIDER_PLAYER,cursor[Entity::player.id].id).collision(
      &searchBoxCollider(BOXCOLLIDER_REWARD,Entity::reward.father))) {
      eraseReward();
      
      // load award
      JpgScaleData textures2 = JpgImageScale::load(Tyra::FileUtils::fromCwd(AwardScreen_Back).c_str(),TextureScale::Tex128,TextureScale::Tex128);
      SetBigImage(&Entity::awardbackground, &textures2,Tyra::SpriteMode::MODE_STRETCH,0,0,81,95);

      while (textures2.data.size()!=0)
      {
        delete textures2.data[0];
        textures2.data.erase(textures2.data.begin()+0);
      }
    }
  }
  // if (rewardExist == true) {
  //   if (boxColliderArray[BOXCOLLIDER_PLAYER][boxColliderArrayID[cursor[Entity::player.id].id]].collision(
  //           &boxColliderArray[Entity::reward.father])) {
  //     eraseReward();
      
  //     // load award
  //     JpgScaleData textures2 = JpgImageScale::load(Tyra::FileUtils::fromCwd(AwardScreen_Back).c_str(),TextureScale::Tex128,TextureScale::Tex128);
  //     SetBigImage(&Entity::awardbackground, &textures2,Tyra::SpriteMode::MODE_STRETCH,0,0,81,95);

  //     while (textures2.data.size()!=0)
  //     {
  //       delete textures2.data[0];
  //       textures2.data.erase(textures2.data.begin()+0);
  //     }
  //   }
  // }
}

void BoxCollisionManager::mapCollision() {
  BoxCollider boxColPlayer = boxColliderArray[BOXCOLLIDER_PLAYER][boxColliderArrayID[cursor[Entity::player.id].id]];
  std::vector<BoxCollider> vec = boxColliderArray[BOXCOLLIDER_MAP];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxColPlayer.collision(&vec[boxColliderArrayID[map[i][j]]]) ==
          true) {
        cursor[Entity::player.id].cursorTile = Vec2(i, j);
        i = 5;
        j = 9;
      }
    }
  }
  // printf("cursor i:%f j:%f\n",cursor[Entity::player.id].cursorTile.x,cursor[Entity::player.id].cursorTile.y);
}

int BoxCollisionManager::projectileZombieCollision() {
  std::vector<int> proyectileEraseID;
  std::vector<int> zombieEraseID;

  for(BoxCollider &it: boxColliderProyectile){
    for(BoxCollider &it2: boxColliderZombie){
      if(it.collision(&it2) == true){
        // printf("colision\n");
        proyectileEraseID.push_back(it.id);
        zombieEraseID.push_back(it2.id);
        break;
      }
    }
      // printf("loop 1\n");
  }
  // printf("fin loop\n");

  unsigned int size;
  unsigned int sizeProyectile;
  
  size = zombieEraseID.size();

  for(size_t i=0;i<size;i++){
    printf("zombie erase[%d]: %d\n",i,zombieEraseID[i]);
  }

  size = zombie.size();
  bool zombieNotFound;
  while (zombieEraseID.size() > 0)
  {  
    zombieNotFound = false;
    // printf("zombie erase size: %d\n",zombieEraseID.size());
    sizeProyectile = zombieEraseID.size()-1;
    for(unsigned int i=0; i < size; i++){
      // printf("box collider:%d searched:%d\n",zombie[i].boxColliderID,zombieEraseID[sizeProyectile]);
      if(zombie[i].boxColliderID == zombieEraseID[sizeProyectile]){
        // printf("zombie colision\n");
        zombie[i].damage(proyectileEraseID[sizeProyectile]);
        if(zombie[i].erase() == true){
          zombie.erase(zombie.begin()+i);
        }
         /*else if (proyectile.type == enumProyectile::snowPea) {
          speedArray[zombie[i].father] = 0.5f;
        }*/
        // proyectileEraseID.erase(proyectileEraseID.begin() + zombieEraseID.size()-1);
        zombieEraseID.erase(zombieEraseID.begin() + sizeProyectile);
        zombieNotFound = true;
        break;
      } 
    }
    if(zombieNotFound == false){
      zombieEraseID.erase(zombieEraseID.begin() + sizeProyectile);
    }
  }

  size = projectile.size();
  // printf("size moveproyecile: %d\n",size);
  for(unsigned int i=0;i < size;i++){
    // printf("move: %d\n",i);
    if(projectile[i].move() == true){
      // printf("new size: %d\n",size);
      proyectileEraseID.push_back(projectile[i].id);
    }
  }
  
  while(proyectileEraseID.size() > 0 ){
    size = projectile.size();
    sizeProyectile = proyectileEraseID.size()-1;
    for(unsigned int i=0;i < size;i++){
      if(proyectileEraseID[sizeProyectile] == projectile[i].id){
        projectile[i].erase();
        projectile[i] = projectile[size-1];
        projectile.erase(projectile.begin() + size-1);
        proyectileEraseID.erase(proyectileEraseID.begin()+sizeProyectile);
        projectilesCreated--;
        break;
      }
    }
  }

  return 0;
}

void BoxCollisionManager::explosionZombieCollision() {
  std::vector<int> explosionEraseID;
  std::vector<int> zombieEraseID;

  for(BoxCollider &it: boxColliderExplosion){
    for(BoxCollider &it2: boxColliderZombie){
      if(it.collision(&it2) == true){
        // printf("colision\n");
        explosionEraseID.push_back(it.id);
        zombieEraseID.push_back(it2.id);
      }
    }
      // printf("loop 1\n");
  }
  // printf("fin loop\n");

  unsigned int size;
  unsigned int sizeProyectile;
  
  // size = zombieEraseID.size();

  // for(size_t i=0;i<size;i++){
  //   printf("zombie erase[%d]: %d\n",i,zombieEraseID[i]);
  // }

  size = zombie.size();
  bool zombieNotFound;
  while (zombieEraseID.size() > 0)
  {  
    zombieNotFound = false;
    // printf("zombie erase size: %d\n",zombieEraseID.size());
    sizeProyectile = zombieEraseID.size()-1;
    for(unsigned int i=0; i < size; i++){
      // printf("box collider:%d searched:%d\n",zombie[i].boxColliderID,zombieEraseID[sizeProyectile]);
      if(zombie[i].boxColliderID == zombieEraseID[sizeProyectile]){
        // printf("zombie colision\n");
        zombie[i].damage(explosionEraseID[sizeProyectile]);
        if(zombie[i].erase() == true){
          zombie.erase(zombie.begin()+i);
        }
        zombieEraseID.erase(zombieEraseID.begin() + sizeProyectile);
        zombieNotFound = true;
        break;
      } 
    }
    if(zombieNotFound == false){
      zombieEraseID.erase(zombieEraseID.begin() + sizeProyectile);
    }
  }

}

void BoxCollisionManager::lawnCollision(){
  std::vector<int> lawnMoverEraseID;
  std::vector<int> zombieEraseID;

  for(BoxCollider &it: boxColliderLawnmower){
    for(BoxCollider &it2: boxColliderZombie){
      if(it.collision(&it2) == true){
        // printf("colision\n");
        lawnMoverEraseID.push_back(it.id);
        zombieEraseID.push_back(it2.id);
      }
    }
      // printf("loop 1\n");
  }
  // printf("fin loop\n");
  
  for(int& col: lawnMoverEraseID){
    for(LawnMower& lawnMowerEntity : lawnMower){
      if(col == lawnMowerEntity.id[0]){
        lawnMowerEntity.canMove = true;
        break;
      }
    }
  }

  unsigned int size;
  unsigned int sizeProyectile;
  
  // size = zombieEraseID.size();

  // for(size_t i=0;i<size;i++){
  //   printf("zombie erase[%d]: %d\n",i,zombieEraseID[i]);
  // }

  size = zombie.size();
  bool zombieNotFound;
  while (zombieEraseID.size() > 0)
  {  
    zombieNotFound = false;
    // printf("zombie erase size: %d\n",zombieEraseID.size());
    sizeProyectile = zombieEraseID.size()-1;
    for(unsigned int i=0; i < size; i++){
      // printf("box collider:%d searched:%d\n",zombie[i].boxColliderID,zombieEraseID[sizeProyectile]);
      if(zombie[i].boxColliderID == zombieEraseID[sizeProyectile]){
        // printf("zombie colision\n");
        // zombie[i].damage(lawnMoverEraseID[sizeProyectile]);
        lifeArray[zombie[i].father] = 0;
        if(zombie[i].erase() == true){
          zombie.erase(zombie.begin()+i);
        }
        zombieEraseID.erase(zombieEraseID.begin() + sizeProyectile);
        zombieNotFound = true;
        break;
      } 
    }
    if(zombieNotFound == false){
      zombieEraseID.erase(zombieEraseID.begin() + sizeProyectile);
    }
  }
}

void BoxCollisionManager::plantZombieCollision(){
  responseCollisionZombiePlant.clear();

  ResponseCollisionZombiePlant res;
  for(BoxCollider &it: boxColliderZombie){
    for(BoxCollider &it2: boxColliderPlant){
      if(it.collision(&it2) == true){
        // printf("colision\n");
        res.plantID = it2.id;
        res.zombieID = it.id;
        responseCollisionZombiePlant.push_back(res);
        break;
      }
    }
      // printf("loop 1\n");
  }
}

void BoxCollisionManager::testUpdate(){
  unsigned int size = boxColliderArray.size();

  for(unsigned int i=0; i < size; i++){
    resultBoxCollider[i].idBoxCol.clear();
  }

  plantCollisionID.clear();
  
  // std::vector<BoxCollider> plantBox = boxColliderArray[BOXCOLLIDER_PLANT];
  // std::vector<BoxCollider> zombieBox = boxColliderArray[BOXCOLLIDER_ZOMBIE];
  std::vector<BoxCollider>& zombieBox = boxColliderZombie;
  for(unsigned int i=0;i<45;i++){
    if (plant[i].type == PeaShotter || plant[i].type == SnowPea || plant[i].type == Repeater){
      for(unsigned int j=0;j<zombieBox.size();j++){
        if (zombieBox[j].pointCollision(&pointColliderArray[plant[i].father])){
          plantCollisionID.push_back(i);
        }
      }
    }
  }

  // for(unsigned int i=0; i < size; i++){
  //   BoxCollider& box1 = boxColliderArray[i];
  //   for(unsigned int j=i+1; j < size; j++){
  //     if(box1.collision(&boxColliderArray[j]) == true){
  //       resultBoxCollider[i].idBoxCol.push_back(j);
  //       resultBoxCollider[j].idBoxCol.push_back(i);
  //     }
  //   }
  // }
}

void LawnMoverManager::update(){
  for(LawnMower& lawnMowerEntity: lawnMower){
    lawnMowerEntity.move();
  }
}

void CameraManager::update() {
  if(cameraPos.x > -150){

    cameraPos.x--;
    
  }
  for(auto &it: finalPosArray.second){
    it += cameraPos;
  }
}

void FontManager::update(){
  int size = textArray.size();
  for(int i=0; i < size; i++){
    // printf("texto: %s\n",textArray[i].text.c_str());
    // printf("fuente[%d]: %d, textureID: %d\n",i,textArray[i].fontID,fonts[textArray[i].fontID].textureID);
    drawText(&fonts[textArray[i].fontID], textArray[i].text,textArray[i].x,textArray[i].y);
  }
}

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size) {
  spriteArray.insert(id, Sprite());
  posArray.insert(id, position);
  finalPosArray.insert(id, Vec2(0, 0));
  loadSprite(&spriteArray[id], mode, Vec2(0.0f, 0.0f), size);
  spriteRenderIDArray.insert(id, 0);
}

void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle) {
  angleArray.insert(id, angle);
  createSprite(id, mode, position, size);
}
void createBoxCollider(int id, BoxColliderEnum type, BoxCollider collider){
  if(type == BOXCOLLIDER_PROYECTILE){
    boxColliderProyectile.push_back(collider) ;
  } else if(type == BOXCOLLIDER_ZOMBIE){
    boxColliderZombie.push_back(collider);
  } else if(type == BOXCOLLIDER_EXPLOSION){
    boxColliderExplosion.push_back(collider);
  } else if(type == BOXCOLLIDER_LAWNMOWER){
    boxColliderLawnmower.push_back(collider);
  } else if(type == BOXCOLLIDER_PLANT){
    boxColliderPlant.push_back(collider);
  } else{
    // boxColliderArray[id] = collider;
    boxColliderArrayID[id] = boxColliderArray[type].size();
    // boxColliderArrayTypeID[type][id] = boxColliderArray[type].size();
    boxColliderArray[type].push_back(collider);
  }
}

void deleteSprite(const int entityID) {
  Tyra::Texture* textureID = texRepo->getBySpriteId(spriteArray[entityID].id);
  if (textureID != nullptr) {
    textureID->removeLinkById(spriteArray[entityID].id);
  }

  spriteArray.erase(entityID);

  spriteRenderIDArray.erase(entityID);

  angleArray.erase(entityID);
}
void deleteAnimation(const int entityID) { animationArray.erase(entityID); }

void deletePosArray(const int entityID) { posArray.erase(entityID); }
void deleteFinalPosArray(const int entityID) { finalPosArray.erase(entityID); }

void deleteTexPosArray(const int entityID) { texPosArray.erase(entityID); }

void newPlayer(int* player) {
  // static int countPlayer = 0;
  // *player = Entities::newID();
  // controller[*player].index = countPlayer;
  // countPlayer++;
}

void newProjectile(Vec2 position, const int damage,
                   const enumProyectile projectileType) {
  if (projectilesCreated < 100) {
    Proyectile projectileData;
    projectileData.id = Entities::newID();
    projectileData.type = projectileType;

    projectile.insert(projectile.begin() + projectilesCreated, projectileData);
    int* id = &projectile[projectilesCreated].id;

    position.y -= 15.0f;
    createSprite(*id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    if (projectileType == enumProyectile::pea) {
      projectilePea->addLink(spriteArray[*id].id);
      spriteArray[*id].textureID = projectilePea->id;
    } else if (projectileType == enumProyectile::snowPea) {
      projectileSnowPea->addLink(spriteArray[*id].id);
      spriteArray[*id].textureID = projectileSnowPea->id;
    }

    // damage
    damageArray[*id] = damage;
    // hitbox
    createBoxCollider(*id,BoxColliderEnum::BOXCOLLIDER_PROYECTILE,BoxCollider(*id,posArray[*id].x, posArray[*id].y, spriteArray[*id].size.x,
                    spriteArray[*id].size.y));
    createDebugBoxCollider(*id,BoxColliderEnum::BOXCOLLIDER_PROYECTILE, Tyra::MODE_STRETCH);
    projectilesCreated++;
  }
}

void newExplosion(Vec2 position, Vec2 size, const int damage,
                  const enumProyectile projectileType) {
  if (explosionsCreated < 100) {
    Explosion explosionData;
    explosionData.id = Entities::newID();
    explosionData.type = projectileType;

    explosion.insert(explosion.begin() + explosionsCreated, explosionData);
    int* id = &explosion[explosionsCreated].id;
    // TODO: Fix position for sprite
    createSprite(*id, Tyra::MODE_STRETCH, position - size / 2 / 2,
                 Vec2(256 / 1.6f, 256 / 1.6f));
    printf("sprite explosion id: %d\n",spriteArray[*id].id);
    if (projectileType == enumProyectile::ExplosionPowie) {
      projectileExplosionPowie->addLink(spriteArray[*id].id);
      spriteArray[*id].textureID = projectileExplosionPowie->id;
    } else if (projectileType == enumProyectile::ExplosionSpudow) {
      projectileExplosionSpudow->addLink(spriteArray[*id].id);
      spriteArray[*id].textureID = projectileExplosionSpudow->id;
    }
    position -= size / 2 / 2;

    // damage
    damageArray[*id] = damage;
    // hitbox
    createBoxCollider(*id,BoxColliderEnum::BOXCOLLIDER_EXPLOSION, BoxCollider(*id, position.x, position.y, size.x, size.y));
    // createDebugBoxCollider(*id,BoxColliderEnum::BOXCOLLIDER_EXPLOSION, Tyra::MODE_STRETCH);
    explosionsCreated++;
  }
}

void newFatherID(int* fatherID, int* childID) {
  fatherIDArray[*fatherID].id.push_back(*childID);
}

void deleteFatherIDChild(const int* fatherID, const int* childID) {
  std::vector<int>::iterator it =
      find(fatherIDArray[*fatherID].id.begin(),
           fatherIDArray[*fatherID].id.end(), *childID);
  fatherIDArray[*fatherID].id.erase(it);
}

void deleteFatherID(const int* entityID) { fatherIDArray.erase(*entityID); }

void createLawnMower(const Tyra::Vec2 pos) {
  LawnMower entity;
  entity.id.push_back(Entities::newID());
  posArray.insert(entity.id[0], pos);
  fatherIDArray.insert(entity.id[0], FatherID());
  int entityID;
  int animID;
  for (unsigned int i = 0; i < m_animID[AnimIndex::LawnMower].size(); i++) {
    entityID = Entities::newID();
    entity.id.push_back(entityID);
    animID = m_animID[AnimIndex::LawnMower][i];
    // printf("plant ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&entity.id[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             Tyra::Vec2(0.7f, 0.7f), 1, 1);
  }

  // HitBox
  createBoxCollider(entity.id[0],BOXCOLLIDER_LAWNMOWER, BoxCollider(entity.id[0],pos.x + 10, pos.y + 20, 45, 38));
  createDebugBoxCollider(entity.id[0],BoxColliderEnum::BOXCOLLIDER_LAWNMOWER, Tyra::MODE_STRETCH);
  lawnMower.push_back(entity);
}

void SetBigImage(BackgroundEntity* entity, JpgScaleData* textures, Tyra::SpriteMode mode,float x,float y, float width, float height){
  int j=0;
  int k=0;

  for(unsigned int i=0;i<textures->data.size();i++){
    entity->id.push_back(Entities::newID());
    printf("pos x,y: %f,%f\n",j*width+(j)+x,k*height+k+y);
    createSprite(entity->id[i], mode, Vec2(j*width+(j)+x, k*height+k+y),
               Vec2(width, height));
               //award
    // createSprite(backgroundIDs.id[i], Tyra::MODE_STRETCH, Vec2(j*81+(j), k*94+k),
    //            Vec2(81, 94));
    Tyra::Texture* texture = new Tyra::Texture(textures->data[i]);
    texture->addLink(spriteArray[entity->id[i]].id);
    spriteArray[entity->id[i]].textureID = texture->id;
    texRepo->add(texture);

    j++;
    if(j==textures->width){
        k++;
        j=0;
    }
  }
}

// void SetBigImage(BackgroundEntity* entity, Tyra::TextureBuilderData* texture, Tyra::SpriteMode mode,float x,float y, float width, float height){
//   int j=0;
//   int k=0;

//   int widthTexture = texture->width;
//   int heightTexture = texture->g;

//   for(unsigned int i=0;i<textures.size();i++){
//     entity->id.push_back(Entities::newID());
    
//     createSprite(entity->id[i], mode, Vec2(j*width+(j)+x, k*height+k+y),
//                Vec2(width, height));
//                //award
//     // createSprite(backgroundIDs.id[i], Tyra::MODE_STRETCH, Vec2(j*81+(j), k*94+k),
//     //            Vec2(81, 94));
//     Tyra::Texture* texture = new Tyra::Texture(textures[i]);
//     texture->addLink(spriteArray[entity->id[i]].id);
//     texRepo->add(texture);

//     j++;
//     if(j==textures->width){
//         k++;
//         j=0;
//     }
//   }
// }