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
ProjectileManager projectileManager;
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


void RendererDebugSpritesManager::update() {
  Tyra::Sprite debugSprite;
  debugSprite.mode =  Tyra::MODE_STRETCH;
  debugSprite.color = Tyra::Color(0,255,0,128);
  debugBoxTexture->addLink(debugSprite.id);
  debugSprite.textureID = debugBoxTexture->id;
  std::vector<BoxCollider> vec;

  for (BoxCollider& box: boxColliderPlayer){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position =
        Vec2(box.x, box.y);
    debugSprite.size = Vec2(box.width, box.height);
    renderer->renderer2D.render(debugSprite);
  }

  for (BoxCollider& box: boxColliderPlant){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position =
        Vec2(box.x, box.y);
    debugSprite.size = Vec2(box.width, box.height);
    renderer->renderer2D.render(debugSprite);
  }

  for (BoxCollider& box: boxColliderSun){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position =
        Vec2(box.x, box.y);
    debugSprite.size = Vec2(box.width, box.height);
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

  for (BoxCollider& box: boxColliderLawnmower){
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    debugSprite.position = Vec2(box.x, box.y);
    debugSprite.size = Vec2(box.width, box.height);
    renderer->renderer2D.render(debugSprite);
  }

  debugBoxTexture->removeLinkById(debugSprite.id);
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
    it.normalColor();
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
    Card& card = cards[deckCursor[playerId].pos];
    if (mapEnable[(int)cursor[playerId].cursorTile.x] == true) {
      PS2Timer& timer = timerArray[card.seedShadowTimer];
      if (sunCounter >= card.cost &&
          plantsCreated < maxPlants &&
          timer.counterMS >= timer.maxMS) {
        if(createPlant(card.plant,
                    cursor[playerId].cursorTile.x,
                    cursor[playerId].cursorTile.y,card.cost) == true){
          timerArray[card.seedShadowTimer].resetCounter();
          Tyra::Sprite& spr = spriteArray[card.seedShadowTimer];
          spr.size.x = 50;
          spr.size.y = 70;
        }
      } else {
        printf("can't create plants now\n");
      }
    }
  }
}

void RewardManager::update() {
  if (rewardExist == true) {
    BoxCollider boxPlayer;
    for(size_t i=0; i < boxColliderPlayer.size();i++){
      if(boxColliderPlayer[i].id == cursor[Entity::player.id].id){
        boxPlayer = boxColliderPlayer[i];
        break;
      }
    }
    if (boxPlayer.collision(
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
}

void BoxCollisionManager::mapCollision() {
  BoxCollider boxColPlayer;
  for(size_t i=0;i<boxColliderPlayer.size();i++){
    if(boxColliderPlayer[i].id == cursor[Entity::player.id].id){
      boxColPlayer = boxColliderPlayer[i];
      break;
    }
  }
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

void BoxCollisionManager::projectileZombieCollision() {
  responseCollisionZombieProjectile.clear();

  ResponseCollisionProjectile res;

  for(BoxCollider &it: boxColliderProyectile){
    for(BoxCollider &it2: boxColliderZombie){
      if(it.collision(&it2) == true){
        res.projectileID = it.id;
        res.zombieID = it2.id;
        responseCollisionZombieProjectile.push_back(res);
        break;
      }
    }
  }
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

void BoxCollisionManager::sunCollision(){
  responseCollisionSunCursor.clear();
  
  ResponseCollisionSunCursor res;
  for(BoxCollider &it: boxColliderPlayer){
    for(BoxCollider &it2: boxColliderSun){
      if(it.collision(&it2) == true){
        // printf("colision\n");
        res.sunID = it2.id;
        res.cursorID = it.id;
        responseCollisionSunCursor.push_back(res);
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
  // spriteRenderIDArray.insert(id, 0);
  setSprite(id,(int)enumDraw::draw);
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
  } else if(type == BOXCOLLIDER_SUN){
    boxColliderSun.push_back(collider);
  } else if(type == BOXCOLLIDER_PLAYER){
    boxColliderPlayer.push_back(collider);
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
  
  if(angleArray.count(entityID) == 1){
    angleArray.erase(entityID);
  }
}

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

    projectile.push_back(projectileData);
    int& id = projectile[projectile.size()-1].id; //projectile[projectilesCreated].id;

    position.y -= 15.0f;
    createSprite(id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    if (projectileType == enumProyectile::pea) {
      projectilePea->addLink(spriteArray[id].id);
      spriteArray[id].textureID = projectilePea->id;
    } else if (projectileType == enumProyectile::snowPea) {
      projectileSnowPea->addLink(spriteArray[id].id);
      spriteArray[id].textureID = projectileSnowPea->id;
    }

    // damage
    damageArray[id] = damage;
    // hitbox
    createBoxCollider(id,BoxColliderEnum::BOXCOLLIDER_PROYECTILE,BoxCollider(id,posArray[id].x, posArray[id].y, spriteArray[id].size.x,
                    spriteArray[id].size.y));
    createDebugBoxCollider(id,BoxColliderEnum::BOXCOLLIDER_PROYECTILE, Tyra::MODE_STRETCH);
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
    printf("reward big[%d] id: %d\n",i,entity->id[i]);
    // printf("pos x,y: %f,%f\n",j*width+(j)+x,k*height+k+y);
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