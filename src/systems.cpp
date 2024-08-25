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
        spriteNormalIdStopRender.push_back(entitieID);
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
  std::map<int, FatherID>::iterator it;
  for (it = fatherIDArray.begin(); it != fatherIDArray.end(); it++) {
    it->second.update(it->first);
  }
}

void RendererSprites::updateTexture(){
  int i=0;
  for (auto it : texPosArray.first) {
    finalPosArray[it] += texPosArray.second[i];
    i++;
  } 
}
void RendererSprites::update() {
  // for (unsigned int i = 0; i < finalPosArray.first.size(); i++){
  //   spriteArray[finalPosArray.first[i]].position = finalPosArray.second[i];
  // }
  for (auto it : spriteRenderIDArray.first) {
    // spriteArray[it].color.a = frameDataArray[it].alpha;
    spriteArray[it].position = finalPosArray[it];
    // spriteArray[it].size = Tyra::Vec2(frameDataArray[it].scaleX,frameDataArray[it].scaleY);
  //   if (animationDataArray[animID].texture.count(currentFrame) == 1) {
  //   // Unlink Texture from the sprite entitie
  //   if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
  //     // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
  //     texRepo->getBySpriteId(spriteArray[entityID].id)
  //         ->removeLinkById(spriteArray[entityID].id);
  //   }

  //   // Link new Texture to the sprite entitie
  //   texRepo->getByTextureId(animationDataArray[animID].texture[currentFrame])
  //       ->addLink(spriteArray[entityID].id);
  //   originalSize[entityID] = Vec2(
  //       texRepo
  //           ->getByTextureId(animationDataArray[animID].texture[currentFrame])
  //           ->getWidth(),
  //       texRepo
  //           ->getByTextureId(animationDataArray[animID].texture[currentFrame])
  //           ->getHeight());
  // }
  // if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
  //   spriteArray[entityID].color.a =
  //       animationDataArray[animID].alpha[currentFrame] * 128;
  // }
  // if (animationDataArray[animID].scaleX.count(currentFrame) == 1) {
  //   spriteArray[entityID].size.x =
  //       originalSize[entityID].x *
  //       animationDataArray[animID].scaleX[currentFrame];
  // }
  // if (animationDataArray[animID].scaleY.count(currentFrame) == 1) {
  //   spriteArray[entityID].size.y =
  //       originalSize[entityID].y *
  //       animationDataArray[animID].scaleY[currentFrame];
  // }

    if(angleArray.count(it) == 1){
      renderer->renderer2D.renderRotate(spriteArray[it],angleArray[it]);
    }else{
      renderer->renderer2D.render(spriteArray[it]);
    }
  }
  // std::map<int, Sprite*>::iterator it;
  // for (it = spritesNormalRender.begin(); it != spritesNormalRender.end();
  //      it++) {
  //   // if (finalPosArray[it->first].x != it->second->position.x ||
  //   //     finalPosArray[it->first].y != it->second->position.y) {
  //     it->second->position = finalPosArray.read(it->first);
  //   // }

  //   renderer->renderer2D.render(it->second);
  // }
}

void ZombiesManager::update() {
  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); it++) {
    it->move();
    it->attackPlant();
    it->normalColor();
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
    if (zombieCreateRow[(int)cursor[player].cursorTile.x] == true) {
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
  while (it != projectile.end()) {
    for (it2 = zombie.begin(); it2 != zombie.end();) {
      if (boxColliderArray[it->id].collision(&boxColliderArray[it2->id[0]]) == false){
        it2++;
      }else{
        it2->damage(it->id);
        if(it->type == enumProyectile::snowPea){
          speedArray[it2->id[0]] = 0.5f;
        }
        // printf("zombie id: %d\n",it2->id[0]);
        // delete zombie
        if (it2->erase() == true) {
          zombie.erase(it2);
        }
        // delete projectile
        it->erase();
        it = projectile.erase(it);
        it2 = zombie.begin();
        projectilesCreated--;
        if(it == projectile.end()){
          return 1;
        }
      }
    }

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
  for (it = explosion.begin(); it < explosion.end(); it++) {
    for (it2 = zombie.begin(); it2 < zombie.end(); ) {
      if (boxColliderArray[it->id].collision(&boxColliderArray[it2->id[0]]) == true) {

        // damage zombie
        it2->damage(it->id);

        // printf("zombie id: %d\n",it2->id[0]);
        // delete zombie
        if(it2->erase() == true){
          it2 = zombie.erase(it2);
        }else{
          it2++;
        }

        // delete explosion
        it->erase();
        it = explosion.erase(it);

        // Break projectile loop if exist another zombie
        if (it == explosion.end()) {
          it2 = zombie.end();
        }

        explosionsCreated--;
      }else{
        it2++;
      }
    }
  }
}

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

// TODO: Fix this for potato mine
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

void deleteFatherIDChild(int* fatherID, int* childID) {
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
  int entityID;
  int animID;
  for(unsigned int i=0; i < m_animID[enumAnimName::LawnMowerAnimName].size(); i++){
    entityID = Entities::newID();
    entity.id.push_back(entityID);
    animID = m_animID[enumAnimName::LawnMowerAnimName][i];
    // printf("plant ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&entity.id[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 1, 1);
  }

  // HitBox
  boxColliderArray[entity.id[0]] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(entity.id[0], Tyra::MODE_STRETCH);
  lawnMower.push_back(entity);
}