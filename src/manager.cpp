#include "manager.hpp"
#include "text.hpp"
#include "font/font.hpp"
#include "imageFiles.hpp"

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

void ProjectileManager::update(){
  std::vector<int> deleteID;
  size_t size = projectile.size();
  for(size_t i=0; i < size;i++){
    if(projectile[i].attack() == true){
      deleteID.push_back(projectile[i].id);
    }
  }

  while(deleteID.size() > 0){
    size = projectile.size();
    int sizeProyectile = deleteID.size()-1;
    for(size_t i=0; i < size;i++){
      if(deleteID[sizeProyectile] == projectile[i].id){
        printf("se borra el id: %d\n",projectile[i].id);
        projectile[i].erase();
        projectile[i] = projectile[size-1];
        projectile.erase(projectile.begin() + size-1);
        deleteID.erase(deleteID.begin()+sizeProyectile);
        projectilesCreated--;
        break;
      }
    }
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
      // if(frameOut.entityID == 200){
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
          if(spriteArray.count(frameArray[i].entityID) == 1){
            const int oldTextureID = spriteArray[frameArray[i].entityID].textureID;
            Tyra::Texture* oldTexture = texRepo->getByTextureId(oldTextureID);
            Tyra::Texture* newTexture = texRepo->getByTextureId(textureFrame[animProp[j].dataIndex]);
            if (oldTexture != newTexture) {
              // printf("link sprite\n");
            
              // Link new Texture to the sprite entitie
              spriteArray[frameArray[i].entityID].textureID = newTexture->id;
              originalSize[frameArray[i].entityID] =
                  Vec2(newTexture->getWidth(), newTexture->getHeight());
            }
          }
        }else if(animProp[j].type == ANIM_SCALE){
          if(spriteArray.count(frameArray[i].entityID) == 1){
            spriteArray[frameArray[i].entityID].size = 
              originalSize[frameArray[i].entityID] * 
              scaleTexture.at(frameArray[i].entityID) * 
              scaleFrame[animProp[j].dataIndex];
          }
        }else if(animProp[j].type == ANIM_ROTATION){
          // angleFrame[animProp[j].dataIndex].print();
          // if(frameArray[i].animIndex ==22){
          //   angleFrame[animProp[j].dataIndex].print();
          // }
          angleArray[frameArray[i].entityID] = angleFrame[animProp[j].dataIndex];
        } else if(animProp[j].type == ANIM_ALPHA){
          if(spriteArray.count(frameArray[i].entityID) == 1){
            spriteArray[frameArray[i].entityID].color.a = alphaFrame[animProp[j].dataIndex];
          }
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
  for (int &it : backgroundLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }

  // printf("card\n");
  for (int &it : cardLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }

  // printf("plantsLayer\n");
  for (int &it : plantsLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }

  for (int &it : projectileLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }
  
  for (int &it : zombieLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }

  for (int &it : sunLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }

  for (int &it : playerLayer) {
    Tyra::Sprite& spriteRender = spriteArray[it];
    spriteRender.position = finalPosArray[it];

    if (angleArray.count(it) == 1) {
      renderer2D->renderRotate(spriteRender, angleArray[it]);
    } else {
      renderer2D->render(spriteRender);
    }
  }
}

void RendererSprites::update() {
  resetFinalPos();
  updateChildPos();
  updateTexture();
  cameraManager.update();
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


void PlantsManager::create(int playerId) {
  if (debugMode == false) {
    Card& card = cards[deckCursor[playerId].pos];
    if (mapEnable[(int)cursor[playerId].tileX] == true) {
      PS2Timer& timer = timerArray[card.seedShadowTimer];
      if (sunCounter >= card.cost &&
          plantsCreated < maxPlants &&
          timer.counterMS >= timer.maxMS) {
        if(createPlant(card.plant,
                    cursor[playerId].tileX,
                    cursor[playerId].tileY,card.cost) == true){
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
      BigTexture textures2 = JpgImageScale::load(Tyra::FileUtils::fromCwd(AwardScreen_Back).c_str(),TextureScale::Tex128,TextureScale::Tex128);
      SetBigImage(&Entity::awardbackground, &textures2,Tyra::SpriteMode::MODE_STRETCH,0,0,81,95);

      while (textures2.data.size()!=0)
      {
        delete textures2.data[0];
        textures2.data.erase(textures2.data.begin()+0);
      }
      CreateTextData(NEW_PLANT,150,20,HouseofTerror16ID);
      
      int spr = Entities::newID();
      createSprite(spr,Tyra::SpriteMode::MODE_REPEAT,Vec2(160,350),Vec2(156,42), card_layer);
      loadTexture(spr,IMG_SeedChooser_Button);
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
  std::vector<BoxCollider>& vec = boxColliderArray[BOXCOLLIDER_MAP];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxColPlayer.collision(&vec[boxColliderArrayID[map[i][j]]]) ==
          true) {
        cursor[Entity::player.id].tileX = i;
        cursor[Entity::player.id].tileY = j;
        
        Tyra::Vec2 pos = Vec2(vec[boxColliderArrayID[map[i][j]]].x,vec[boxColliderArrayID[map[i][j]]].y);
        posArray[Entity::player.id] = pos;

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
  for(auto &it: finalPosArray.second){
    it -= cameraPos;
  }
}

bool CameraManager::intro(){
  if(state == cameraShowEnemies){
    if(cameraPos.x < 150){
      cameraPos.x +=5;
    }else{
      state = cameraDelay;
    }
  }else if(state == cameraDelay){
    if(cameraPos.x == 150){
      static PS2Timer cameraTimer;
      printf("camera timer: %d\n",cameraTimer.counterMS);
      if(cameraTimer.counterMS < 3000){
        cameraTimer.addMSinCounter();
      }else {
        state = cameraShowHouse;
      }
    }
  }else if(state == cameraShowHouse){
    if(cameraPos.x > 0){
      cameraPos.x -=5;
    }else{
      return true;
    }
  }
  return false;
}

void FontManager::update(){
  int size = textArray.size();
  for(int i=0; i < size; i++){
    // printf("texto: %s\n",textArray[i].text.c_str());
    // printf("fuente[%d]: %d, textureID: %d\n",i,textArray[i].fontID,fonts[textArray[i].fontID].textureID);
    drawText(&fonts[textArray[i].fontID], textArray[i].text,textArray[i].x,textArray[i].y);
  }
}