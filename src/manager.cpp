#include "manager.hpp"
#include "text.hpp"
#include "font/font.hpp"
#include "particles.hpp"
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
ParticleManager particleManager;

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
        if(projectile[i].type == enumProyectile::pea || projectile[i].type == enumProyectile::snowPea){
          CreateParticle(posArray[projectile[i].id], enumPARTICLETYPE::PEASPLAT);
        }
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
  
  for(FrameCounter& frame: frameCounterArray.dataType){
    if(frame.update() == 0){
      // printf("Entity id: %d, animID: %d, layer:%d, frame: %d\n",frame.entityID,frame.animIndex,frame.layerIndex,frame.currentFrame);
      frameOut.entityID = frame.entityID;
      frameOut.animIndex = frame.animIndex;
      frameOut.layerIndex = frame.layerIndex;
      frameOut.frame = frame.currentFrame;
      frameArray.push_back(frameOut);
      // if(frameOut.entityID == 286){
      //   printf("ingresar Entity id: %d, animID: %d, frame: %d\n",frame.entityID,frame.animIndex,frame.currentFrame);
      // }
    }
  }

  if(frameArray.size() > 0){
    for(unsigned int i=0;i<frameArray.size();i++){
      // if(frameArray[i].entityID==295){
      //   printf("entity:%d, animID: %d, frame: %d\n",frameArray[i].entityID,frameArray[i].animIndex,frameArray[i].frame);
      // }
      // printf("entity:%d, animID: %d, frame: %d\n",frameArray[i].entityID,frameArray[i].animIndex,frameArray[i].frame);
      std::vector<FrameProperty>& animProp = animComponent[frameArray[i].animIndex].GetFrameProperties(frameArray[i].layerIndex,frameArray[i].frame);
      for(unsigned int j=0; j< animProp.size();j++){
        // if(frameArray[i].entityID ==286){
        //   printf("type: %d, data: %d\n",animProp[j].type,animProp[j].dataIndex);
        // }
        // printf("type: %d, data: %d\n",animProp[j].type,animProp[j].dataIndex);
        if(animProp[j].type == ANIM_POSITION){
          // if(frameArray[i].entityID ==286){
          //   // printf("entity:%d, animID: %d, frame: %d\n",frameArray[i].entityID,frameArray[i].animIndex,frameArray[i].frame);
          // }
          texPosArray[frameArray[i].entityID] = positionFrame[animProp[j].dataIndex] * scaleTexture[frameArray[i].entityID];
        }else if(animProp[j].type == ANIM_TEXTURE){
          
          // if(spriteArray.count(frameArray[i].entityID) == true){
            const int oldTextureID = spriteArray[frameArray[i].entityID].textureID;
            Tyra::Texture* oldTexture = texRepo->getByTextureId(oldTextureID);
            Tyra::Texture* newTexture = texRepo->getByTextureId(textureFrame[animProp[j].dataIndex]);

            if (oldTexture != newTexture) {
              // printf("link sprite\n");
            
              // Link new Texture to the sprite entitie
              spriteArray[frameArray[i].entityID].textureID = newTexture->id;
              originalSize[frameArray[i].entityID] =
                  Vec2(newTexture->getWidth(), newTexture->getHeight());

              // this is a hack to get the scaleFrame
              for(int k=frameArray[i].frame; k>0;k--){
                AnimationFrameData& fd = animComponent[frameArray[i].animIndex].GetFrameProperties(frameArray[i].layerIndex,k);
                for(size_t m = 0; m < fd.size();m++){
                  if(fd[m].type == ANIM_SCALE){
                    spriteArray[frameArray[i].entityID].size = 
                      originalSize[frameArray[i].entityID] * 
                      scaleTexture.at(frameArray[i].entityID) * 
                      scaleFrame[fd[m].dataIndex];
                      k = 0;
                      m = 0;
                    break;
                  }
                }
              }
            }
            
        }else if(animProp[j].type == ANIM_SCALE){
          if(spriteArray.count(frameArray[i].entityID) == true){
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
          if(spriteArray.count(frameArray[i].entityID) == true){
            spriteArray[frameArray[i].entityID].color.a = alphaFrame[animProp[j].dataIndex];
          }
        } else if (animProp[j].type == ANIM_DRAW){
          setSprite(frameArray[i].entityID, drawFrame[animProp[j].dataIndex],layerID[frameArray[i].entityID]);
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
  std::vector<unsigned int>& keys = finalPosArray.getDenseData();
  for (unsigned int i = 0; i < finalPosArray.dataType.size(); i++) {
    finalPosArray.dataType[i] = posArray[keys[i]];
  }
}

void RendererSprites::updateChildPos() {
  std::vector<unsigned int>& keys = fatherIDArray.getDenseData();
  for (unsigned int i = 0; i < keys.size(); i++) {
    fatherIDArray.dataType[i].update(keys[i]);
  }
}

void RendererSprites::updateTexture() {
  int i = 0;
  std::vector<unsigned int>& keys = texPosArray.getDenseData();
  for (auto it : keys) {
    finalPosArray[it] += texPosArray.dataType[i];
    i++;
  }
}
void RendererSprites::updateRender() {
  // printf("background\n");
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

  // printf("zombie layer\n");
  for (int &it : zombieLayer) {
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

  // printf("Sun layer\n");
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
  // printf("render 1\n");
  resetFinalPos();
  // printf("render 2\n");
  updateChildPos();
  // printf("render 3\n");
  updateTexture();
  // printf("render 4\n");
  cameraManager.update();
  // printf("render 5\n");
  updateRender();
}

void ZombiesManager::update() {
  for(int i = zombie.size()-1; i>=0; i--){
    Zombie& it = zombie[i];
    if(it.type != NoneZombie){
      it.move();
      it.normalColor();
      if(it.animAttackPlant() == true){
        zombie.erase(zombie.begin()+i);
      }
    }
  }

  for(int i = zombieAttackState.size()-1; i >= 0; i--){
    Zombie& it = zombieAttackState[i];
    it.normalColor();
    if(it.animWalk() == true){
      zombieAttackState.erase(zombieAttackState.begin()+i);
    }
  }

  for(int i = deadZombie.size()-1; i>=0; i--){
    Zombie& it = deadZombie[i];
    it.normalColor();
    if(it.erase() == true){
      deadZombie.erase(deadZombie.begin()+i);
    } 
  }

  for(int i = charredZombie.size()-1; i>=0; i--){
    Zombie& it = charredZombie[i];
    it.normalColor();
    if(it.explosionState() == true){
      charredZombie.erase(charredZombie.begin()+i);
    }
  }
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
      if(boxColliderPlayer[i].id == cursor[Entity::player.cursorID].id){
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
  Cursor& cursorPlayer = cursor[Entity::player.cursorID];
  for(size_t i=0;i<boxColliderPlayer.size();i++){
    if(boxColliderPlayer[i].id == cursorPlayer.id){
      boxColPlayer = boxColliderPlayer[i];
      break;
    }
  }

  std::vector<BoxCollider>& vec = boxColliderArray[BOXCOLLIDER_MAP];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxColPlayer.collision(&vec[boxColliderArrayID[map[i][j]]]) ==
          true) {
        cursorPlayer.tileX = i;
        cursorPlayer.tileY = j;
        
        Tyra::Vec2 pos = Vec2(vec[boxColliderArrayID[map[i][j]]].x,vec[boxColliderArrayID[map[i][j]]].y);
        posArray[Entity::player.id] = pos;

        i = 5;
        j = 9;
      }
    }
  }
  // printf("cursor i:%d j:%d\n",cursor[Entity::player.id].tileX,cursor[Entity::player.id].tileY);
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
        if(zombie[i].damage(explosionEraseID[sizeProyectile], EXPLOSION) == true){
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
        // if(zombie[i].erase() == true){
        //   zombie.erase(zombie.begin()+i);
        // }
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

bool CollisionEnterPlant(int boxCollider){
  // printf("buscando zombie\n");
  for(size_t i=0; i < enterResponseCollisionZombiePlant.size();i++){
    if(enterResponseCollisionZombiePlant[i].plantID == boxCollider ||
    enterResponseCollisionZombiePlant[i].zombieID == boxCollider){
  printf("encontrado\n");
      return true;
    }
  }
  // printf("no paso\n");
  return false;
}

bool CollisionStopPlant(int boxCollider){
  for(size_t i=0; i < stopResponseCollisionZombiePlant.size();i++){
    if(stopResponseCollisionZombiePlant[i].plantID == boxCollider ||
    stopResponseCollisionZombiePlant[i].zombieID == boxCollider){
      printf("stop encontrado\n");
      return true;
    }
  }
  // printf("no paso\n");
  return false;
}

void BoxCollisionManager::plantZombieCollision(){
  previousResponseCollisionZombiePlant = responseCollisionZombiePlant;
  // check for collisions that make contact

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
  }

  // Event when collision stopped
  stopResponseCollisionZombiePlant.clear();

  bool found = false;
  for(ResponseCollisionZombiePlant& col1: previousResponseCollisionZombiePlant){
    found = false;
    for(size_t j=0; j < responseCollisionZombiePlant.size(); j++){
      if(col1.plantID == responseCollisionZombiePlant[j].plantID &&
      col1.zombieID == responseCollisionZombiePlant[j].zombieID){
        found = true;
        break;
      }
    }
    if(found == false){
      // printf("ingreso stop plantID:%d zombieID: %d, size: %d\n",col1.plantID,col1.zombieID,stopResponseCollisionZombiePlant.size());
      stopResponseCollisionZombiePlant.push_back(col1);
    }
  }

  // Event when collision enter
  enterResponseCollisionZombiePlant.clear();

  for(ResponseCollisionZombiePlant& col1: responseCollisionZombiePlant){
    found = false;
    for(size_t j=0; j < previousResponseCollisionZombiePlant.size(); j++){
      if(col1.plantID == previousResponseCollisionZombiePlant[j].plantID &&
      col1.zombieID == previousResponseCollisionZombiePlant[j].zombieID){
        found = true;
        break;
      }
    }
    if(found == false){
      // printf("ingreso enter plantID:%d zombieID: %d, size: %d\n",col1.plantID,col1.zombieID,enterResponseCollisionZombiePlant.size());
      enterResponseCollisionZombiePlant.push_back(col1);
    }
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
  for(auto &it: finalPosArray.dataType){
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