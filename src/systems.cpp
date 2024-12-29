#include "entities/entities.hpp"
#include "systems.hpp"
#include "components.hpp"

int projectilesCreated = 0;
int explosionsCreated = 0;

PlayerControl playerControl;
AnimationManager animManager;
ProjectileManager projectileManager;
ExplosionManager explosionManager;
RendererSprites renderSprites;
RendererDebugSpritesManager renderDebugSpritesManager;
ZombiesManager zombiesManager;
PlantsManager plantsManager;
RewardManager rewardManager;

void PlayerControl::update(){
  std::map<int, Controller>::iterator it;

  for(it = controller.begin(); it != controller.end(); it++){
    it->second.update(it->first);
  }
}
void AnimationManager::update() {
  int i=0;
  for (auto it : animationArray.first) {
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

  if (animationDataArray[animationArray[entitieID].animID].draw.count(animationArray[entitieID].currentFrame)) {
    animationArray[entitieID].draw =
        animationDataArray[animationArray[entitieID].animID].draw[animationArray[entitieID].currentFrame];
    if (animationArray[entitieID].draw == (int) enumDraw::noDraw) {
      if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
        texRepo->getBySpriteId(spriteArray[entitieID].id)
            ->removeLinkById(spriteArray[entitieID].id);
        spriteRenderIDArray.erase(entitieID);
        // spriteNormalIdStopRender.push_back(entitieID);
      }

    } else {
      spriteRenderIDArray[entitieID] = entitieID;
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].texture.count(
          animationArray[entitieID].currentFrame) == 1) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
      texRepo->getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    texRepo->getByTextureId(animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame])->addLink(spriteArray[entitieID].id);
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
                      .alpha[animationArray[entitieID].currentFrame];
    spriteArray[entitieID].color.a = alpha;
  }

  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    spriteArray[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
            .scale[animationArray[entitieID].currentFrame];
  }

  if (animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    angleArray[entitieID] = animationDataArray[animationArray[entitieID].animID]
                            .angle[animationArray[entitieID].currentFrame];
  }
}

void RendererDebugSpritesManager::update() {
  std::map<int, Sprite>::iterator it;
  // auto& textureRepository = renderer->getTextureRepository();

  // printf("debug size: %d\n",debugSpriteBoxCollider.size());
  for (it = dm_SpriteBoxCollider.begin(); it != dm_SpriteBoxCollider.end();
       it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    dm_SpriteBoxCollider[it->first].position = Vec2(boxColliderArray[it->first].x,boxColliderArray[it->first].y);  
    renderer->renderer2D.render(dm_SpriteBoxCollider[it->first]);
  }

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
  
  // TODO: delete this
  // for (it = dm_SpriteRotate.begin(); it != dm_SpriteRotate.end(); it++) {
  //   // printf("key: %d. sprite ID: %d\n", it->first, it->second.id);

  //   dm_SpriteRotate[it->first].position = rotationSprite[it->first].sprite.position;
  //   dm_SpriteRotate[it->first].scale = rotationSprite[it->first].sprite.scale;
  //   dm_SpriteRotate[it->first].size = rotationSprite[it->first].sprite.size;

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

void RendererSprites::resetFinalPos(){
  // std::map<int, Vec2>::iterator it;
  for (unsigned int i = 0; i < finalPosArray.second.size(); i++) {
    finalPosArray.second[i] = posArray[finalPosArray.first[i]];
  }
}

void RendererSprites::updateChildPos() {
  for (unsigned int i=0; i < fatherIDArray.first.size(); i++) {
    fatherIDArray.second[i].update(fatherIDArray.first[i]);
  }
}

void RendererSprites::updateTexture(){
  int i=0;
  for (auto it : texPosArray.first) {
    finalPosArray[it] += texPosArray.second[i];
    i++;
  } 
}
void RendererSprites::updateRender() {
  for (auto it : spriteRenderIDArray.first) {
    spriteArray[it].position = finalPosArray[it];
    if(angleArray.count(it) == 1){
      renderer->renderer2D.renderRotate(spriteArray[it],angleArray[it]);
    }else{
      renderer->renderer2D.render(spriteArray[it]);
    }
  }
}

void RendererSprites::update() {
  resetFinalPos();
  updateChildPos();
  updateTexture();
  updateRender();
}

void ZombiesManager::update() {
  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); ) {
    if(it->explosion == false){
      it->move();
      it->attackPlant();
      it->normalColor();
      it++;
    }else{
      if(it->explosionState() == true){
        it = zombie.erase(it);
      }else{
        it++;
      }
    }
  }
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

//         if (boxColliderArray[plant[i].id[0]].collision(&boxColliderArray[it->id[0]]) == true) {
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

void PlantsManager::create(){
  if (debugMode == false) {
    if (mapEnable[(int)cursor[player].cursorTile.x] == true) {
      if (sunCounter >= cards[deckCursor[player].pos].cost &&
          plantsCreated < maxPlants && timerArray[cards[deckCursor[player].pos].seedShadowTimer].counterMS >= timerArray[cards[deckCursor[player].pos].seedShadowTimer].maxMS) {
        sunCounter -= cards[deckCursor[player].pos].cost;
        timerArray[cards[deckCursor[player].pos].seedShadowTimer].resetCounter();
        spriteArray[cards[deckCursor[player].pos].seedShadowTimer].size.y = 70;
        createPlant(cards[deckCursor[player].pos].plant, cursor[player].cursorTile.x,
                    cursor[player].cursorTile.y);
      } else {
        printf("can't create plants now\n");
      }
    }
  }
}

void PlantsManager::update() {
  for(int i = 0; i < 45; i++){
    plant[i].attack();
    plant[i].ability();
  }
}

int ProjectileManager::update() {
  std::vector<Proyectile>::iterator it = projectile.begin();
  std::vector<Zombie>::iterator it2;

  std::vector<int> eraseProjectileID;
  // printf("1 proj end: %d\n",projectile.end());
  auto size = projectile.end();
  auto zombieSize = zombie.end();
  while (it != size) {
    for (it2 = zombie.begin(); it2 != zombieSize; it2++) {
      if (boxColliderArray[it->id].collision(&boxColliderArray[it2->id[0]]) == true){
        eraseProjectileID.push_back(it->id);
        it2->damage(it->id);
        // printf("zombie id: %d\n",it2->id[0]);
        // delete zombie
        if (it2->erase() == true) {
          zombie.erase(it2);
          zombieSize = zombie.end();
        }else if(it->type == enumProyectile::snowPea){
          speedArray[it2->id[0]] = 0.5f;
        }
        break;
      }
    }
    it++;
  }
  unsigned int eraseSize = eraseProjectileID.size();
  for(unsigned i=0;i < eraseSize; i++){
    for(it = projectile.begin(); it != projectile.end(); it++){
      if(eraseProjectileID[i] == it->id){
        // delete projectile
        it->erase();
        it = projectile.erase(it);
        projectilesCreated--;
        break;
      }
    }
  }
  it = projectile.begin();
  while(it != projectile.end()){
    if (it->move() == false){
      it++;
    }else{
      // delete projectile
      printf("deleting projectile\n");
      it = projectile.erase(it);
      projectilesCreated--;
    }
  }
  return 0;
}

void ExplosionManager::zombieCollision() {
  std::vector<Explosion>::iterator it;
  std::vector<Zombie>::iterator it2;
  bool explode;
  for (it = explosion.begin(); it < explosion.end();) {
    explode = false;
    for (it2 = zombie.begin(); it2 < zombie.end(); ) {
      if (boxColliderArray[it->id].collision(&boxColliderArray[it2->id[0]]) == true) {
        // damage zombie
        lifeArray[it2->id[0]] -= damageArray[it->id];

        if(lifeArray[it2->id[0]] <= 0 && it2->explosion == false ){
          printf("explosion state\n");
          it2->explosion = true;
          it2->damaged = false;
          it2->attack = false;
          for (unsigned int j = 0; j < it2->id.size(); j++) {
            if (animationArray.count(it2->id[j]) == 1) {
              // printf("id: %d\n",it2->id[j]);
              animationArray[it2->id[j]].draw = -1;
              if (texRepo->getBySpriteId(spriteArray[it2->id[j]].id) != nullptr) {
                // printf("unlink sprite id: %d\n", spriteArray[it2->id[j]].id);
                texRepo->getBySpriteId(spriteArray[it2->id[j]].id)
                    ->removeLinkById(spriteArray[it2->id[j]].id);
              }
              setSprite(it2->id[j], -1);
            }
          }
          int animID;
          for (unsigned int j = 0; j < m_animID[AnimIndex::Zombie_charred].size(); j++) {
            if (animationArray.count(it2->id[j]) == 1) {
              if(angleArray.count(it2->id[j]) == 1){
                angleArray[it2->id[j]] = Vec2(0.0f, 0.0f);
              }
              animID = m_animID[AnimIndex::Zombie_charred][j];
              animationArray[it2->id[j]].animID = animID;
              animationArray[it2->id[j]].framesCounter = 0;
              animationArray[it2->id[j]].setAnimation(normalZombieCharred);
              animationDataArray[animID]
              .setAnimationState(it2->id[j], normalZombieCharred);
            }
          }
        }

        // delete explosion
        // if(it->type == enumProyectile::ExplosionSpudow){
        //   it->erase();
        //   it = explosion.erase(it);
        //   explosionsCreated--;
        // }else{
          explode = true;
        // }

        // Break projectile loop if doesn't exist another projectile
        // if (it == explosion.end()) {
        //   it2 = zombie.end();
        // }else{
        //   it2++;
        // }
        it2++;

      }else{
        it2++;
      }
    }
    if(explode == true){
      it->erase();
      it = explosion.erase(it);
      explosionsCreated--;
    }else{
      it++;
    }
  }
}

void RewardManager::update(){
  if(rewardExist == true){
    if(boxColliderArray[cursor[player].id].collision(&boxColliderArray[reward.father])){
      eraseReward();
    }
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

void deleteSprite(const int entityID) {
  Tyra::Texture* textureID = texRepo->getBySpriteId(spriteArray[entityID].id);
  if (textureID != nullptr) {
    textureID->removeLinkById(spriteArray[entityID].id);
  }
  
  if(spriteArray.count(entityID) == 1){
    spriteArray.erase(entityID);
  }

  if(spriteRenderIDArray.count(entityID) == 1){
    spriteRenderIDArray.erase(entityID);
  }
  if (angleArray.count(entityID) == 1) {
    angleArray.erase(entityID);
  }
}
void deleteAnimation(const int entityID) { animationArray.erase(entityID); }

void deletePosArray(const int entityID) {
  posArray.erase(entityID);
}
void deleteFinalPosArray(const int entityID){
  finalPosArray.erase(entityID);
}

void deleteTexPosArray(const int entityID) { texPosArray.erase(entityID); }


void newPlayer(int* player){
  static int countPlayer = 0;
  *player = Entities::newID();
  controller[*player].index = countPlayer;
  countPlayer++;
}

void newProjectile(Vec2 position, const int damage, const enumProyectile projectileType) {
  if (projectilesCreated < 100) {
    Proyectile projectileData;
    projectileData.id = Entities::newID();
    projectileData.type = projectileType;
    
    projectile.insert(projectile.begin() + projectilesCreated, projectileData);
    int* id = &projectile[projectilesCreated].id;

    position.y -= 15.0f;
    createSprite(*id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    if(projectileType == enumProyectile::pea) { 
      projectilePea->addLink(spriteArray[*id].id); 
    }else if(projectileType == enumProyectile::snowPea) {
      projectileSnowPea->addLink(spriteArray[*id].id);
    }

    // damage
    damageArray[*id] = damage;
    // hitbox
    boxColliderArray[*id] =
        BoxCollider(posArray[*id].x, posArray[*id].y, spriteArray[*id].size.x,
                    spriteArray[*id].size.y);
    createDebugBoxCollider(*id, Tyra::MODE_STRETCH);
    projectilesCreated++;
  }
}

void newExplosion(Vec2 position, Vec2 size, const int damage, const enumProyectile projectileType){
  if (explosionsCreated < 100) {
    Explosion explosionData;
    explosionData.id = Entities::newID();
    explosionData.type = projectileType;
    
    explosion.insert(explosion.begin() + explosionsCreated, explosionData);
    int* id = &explosion[explosionsCreated].id;
    // TODO: Fix position for sprite
    createSprite(*id, Tyra::MODE_STRETCH, position-size/2/2, Vec2(256 / 1.6f, 256 / 1.6f));
    if (projectileType == enumProyectile::ExplosionPowie) {
      projectileExplosionPowie->addLink(spriteArray[*id].id);
    }else if (projectileType == enumProyectile::ExplosionSpudow){
      projectileExplosionSpudow->addLink(spriteArray[*id].id);
    }
    position -= size/2/2;

    // damage
    damageArray[*id] = damage;
    // hitbox
    boxColliderArray[*id] =
        BoxCollider(position.x, position.y, size.x, size.y);
    createDebugBoxCollider(*id, Tyra::MODE_STRETCH);
    explosionsCreated++;
  }
}

void newFatherID(int* fatherID, int* childID) {
  fatherIDArray[*fatherID].id.push_back(*childID);
}

void deleteFatherIDChild(const int* fatherID,const int* childID) {
  std::vector<int>::iterator it =
      find(fatherIDArray[*fatherID].id.begin(),
           fatherIDArray[*fatherID].id.end(), *childID);
  fatherIDArray[*fatherID].id.erase(it);
}

void deleteFatherID(const int* entityID){
  fatherIDArray.erase(*entityID);
}

void newCursor(int* player, Tyra::Vec2 pos) {
  // *cursor = Entities::newID();
  cursor[*player].id = Entities::newID();
  printf("cursor id: %d\n", cursor[*player].id);
  createSprite(cursor[*player].id, Tyra::MODE_STRETCH, pos, Vec2(56, 48));
  createTexture(cursor[*player].id, "cursor6.png");
  boxColliderArray[cursor[*player].id] = BoxCollider(pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  createDebugBoxCollider(cursor[*player].id, Tyra::MODE_STRETCH);
}

void newDeckCursor(int* player, Tyra::Vec2 pos) {
  // *cursor = Entities::newID();
  deckCursor[*player].id = Entities::newID();
  printf("deck cursor id: %d\n", deckCursor[*player].id);
  createSprite(deckCursor[*player].id, Tyra::MODE_STRETCH, pos, Vec2(56, 48));
  createTexture(deckCursor[*player].id, "cursor6.png");
  // boxColliderArray[deckCursor[*player].id] = BoxCollider(
  //     pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  // createDebugBoxCollider(deckCursor[*player].id, Tyra::MODE_STRETCH);
}

void createLawnMower(const Tyra::Vec2 pos) {
  LawnMower entity;
  entity.id.push_back(Entities::newID());
  posArray.insert(entity.id[0], pos);
  fatherIDArray.insert(entity.id[0], FatherID());
  int entityID;
  int animID;
  for(unsigned int i=0; i < m_animID[AnimIndex::LawnMower].size(); i++){
    entityID = Entities::newID();
    entity.id.push_back(entityID);
    animID = m_animID[AnimIndex::LawnMower][i];
    // printf("plant ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&entity.id[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.7f, 0.7f), 1, 1);
  }

  // HitBox
  boxColliderArray[entity.id[0]] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(entity.id[0], Tyra::MODE_STRETCH);
  lawnMower.push_back(entity);
}
