#include "entities/entities.hpp"
#include "systems.hpp"
#include "components.hpp"

int projectilesCreated = 0;

PlayerControl playerControl;
AnimationManager animManager;
ProjectileManager projectileManager;
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
  std::map<int, Animation>::iterator it;

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    it->second.update(it->first);
  }
}

void AnimationManager::debug() {
  std::map<int, Animation>::iterator it;

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    it->second.position(it->first);
  }
}

void AnimationManager::debugChangeFrame(const int entitieID, const int key) {

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
      texRepo->getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    texRepo->getByTextureId(animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame])->addLink(spriteArray[entitieID].id);
  } else if (animationDataArray[animationArray[entitieID].animID].texture.count(
                 animationArray[entitieID].currentFrame) == 1) {
    // Unlink Texture from the sprite entitie
    texRepo->getBySpriteId(rotationSprite[entitieID].sprite.id)
        ->removeLinkById(rotationSprite[entitieID].sprite.id);

    // Link new Texture to the sprite entitie
    texRepo->getByTextureId(animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame])->addLink(rotationSprite[entitieID].sprite.id);
  }

  if (animationDataArray[animationArray[entitieID].animID].x.count(
          animationArray[entitieID].currentFrame) == 1) {
    texPosArray[entitieID].x =
        animationDataArray[animationArray[entitieID].animID]
            .x[animationArray[entitieID].currentFrame];
  }

  if (animationDataArray[animationArray[entitieID].animID].y.count(
          animationArray[entitieID].currentFrame) == 1) {
    texPosArray[entitieID].y =
        animationDataArray[animationArray[entitieID].animID]
            .y[animationArray[entitieID].currentFrame];
  }

  if (animationDataArray[animationArray[entitieID].animID].alpha.count(
          animationArray[entitieID].currentFrame) == 1) {
    float alpha = animationDataArray[animationArray[entitieID].animID]
                      .alpha[animationArray[entitieID].currentFrame] *
                  128;
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].color.a = alpha;
    } else {
      rotationSprite[entitieID].sprite.color.a = alpha;
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].scaleX.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size.x = originalSize[entitieID].x * animationDataArray[animationArray[entitieID].animID]
              .scaleX[animationArray[entitieID].currentFrame];
    } else {
      rotationSprite[entitieID].sprite.size.x = originalSize[entitieID].x * animationDataArray[animationArray[entitieID].animID]
              .scaleX[animationArray[entitieID].currentFrame];
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].scaleY.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size.y = originalSize[entitieID].y * animationDataArray[animationArray[entitieID].animID]
              .scaleY[animationArray[entitieID].currentFrame];
    } else {
      rotationSprite[entitieID].sprite.size.y = originalSize[entitieID].y * animationDataArray[animationArray[entitieID].animID]
              .scaleY[animationArray[entitieID].currentFrame];
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].angleX.count(
          animationArray[entitieID].currentFrame) == 1) {
    rotationSprite[entitieID].angle.x = animationDataArray[animationArray[entitieID].animID]
                            .angleX[animationArray[entitieID].currentFrame];
  }

  if (animationDataArray[animationArray[entitieID].animID].angleY.count(
          animationArray[entitieID].currentFrame) == 1) {
    rotationSprite[entitieID].angle.y = animationDataArray[animationArray[entitieID].animID]
                            .angleY[animationArray[entitieID].currentFrame];
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

  for (it = dm_SpriteRotate.begin(); it != dm_SpriteRotate.end(); it++) {
    // printf("key: %d. sprite ID: %d\n", it->first, it->second.id);

    dm_SpriteRotate[it->first].position = rotationSprite[it->first].sprite.position;
    dm_SpriteRotate[it->first].scale = rotationSprite[it->first].sprite.scale;
    dm_SpriteRotate[it->first].size = rotationSprite[it->first].sprite.size;

    renderer->renderer2D.renderRotate(dm_SpriteRotate[it->first],
                                      rotationSprite[it->first].angle);
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
  //       rotationSprite[it->first].position;

  //   renderer->renderer2D.renderRotate(dm_SpriteRotatePivot[it->first],
  //                                     angles[it->first]);
  // }
}

void RendererSprites::updateChildPos() {
  std::map<int, FatherID>::iterator it;
  for (it = fatherIDArray.begin(); it != fatherIDArray.end(); it++) {
    it->second.update(it->first);
  }
}

void RendererSprites::updateTexture(){
  std::map<int, Vec2>::iterator it;
  for (it = texPosArray.begin(); it != texPosArray.end();
       it++) {
      finalPosArray[it->first] +=
      texPosArray.at(it->first) * scaleTexture.at(it->first);
  } 
}
void RendererSprites::update() {
  std::map<int, Sprite*>::iterator it;
  for (it = spritesNormalRender.begin(); it != spritesNormalRender.end();
       it++) {

    // finalPos += entitiePos

    finalPosArray[it->first] += posArray[it->first];

    // if (finalPosArray[it->first].x != it->second->position.x ||
    //     finalPosArray[it->first].y != it->second->position.y) {
      it->second->position = finalPosArray[it->first];
    // }

    renderer->renderer2D.render(it->second);
    finalPosArray[it->first] = Vec2(0.0f, 0.0f);
  }
}

void RendererSprites::updateRotate() {
  std::map<int, RotationSprite*>::iterator it;

  for (it = spritesRotateRender.begin(); it != spritesRotateRender.end();
       it++) {
    it->second->update(it->first);
  }
}

void ZombiesManager::update() {
  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); it++) {
    it->move();
    it->attackPlant();
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
          plantsCreated < maxPlants && cards[deckCursor[player].pos].seedTimer == 0) {
        sunCounter -= cards[deckCursor[player].pos].cost;
        cards[deckCursor[player].pos].seedTimer = 60 * 8;
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

void ProjectileManager::update() {
  std::vector<Proyectile>::iterator it;

  for (it = projectile.begin(); it < projectile.end(); it++) {
    posArray[it->id].x++;
    boxColliderArray[it->id].x = posArray[it->id].x;
    if (posArray[it->id].x >= 580) {
      // delete projectile
      printf("borrando proyectil\n");
      deleteSprite(it->id);
      boxColliderArray.erase(it->id);
      deletePosArray(it->id);
      deleteDebugBoxCollider(it->id);
      Entities::deleteID(it->id);
      it = projectile.erase(it);
      projectilesCreated--;
    }
  }
}

void ProjectileManager::zombieCollision() {
  std::vector<Proyectile>::iterator it;
  std::vector<Zombie>::iterator it2;
  for (it = projectile.begin(); it < projectile.end(); it++) {
    for (it2 = zombie.begin(); it2 < zombie.end(); ) {
      if (boxColliderArray[it->id].collision(&boxColliderArray[it2->id[0]]) == true) {

        // damage zombie
        it2->damage(it->id);
        if(it->type == enumProyectile::snow){
          speedArray[it2->id[0]] = 0.5f;
        }
        // printf("zombie id: %d\n",it2->id[0]);
        // delete zombie
        if(it2->erase() == true){
          it2 = zombie.erase(it2);
        }else{
          it2++;
        }

        // delete projectile

        Tyra::Texture* text =
            texRepo->getBySpriteId(spriteArray[it->id].id);
        TYRA_ASSERT(text,
                    "No se encontro la textura del proyectil with id: ", it->id);
        deleteSprite(it->id);
        boxColliderArray.erase(it->id);
        deleteDebugBoxCollider(it->id);
        Entities::deleteID(it->id);
        it = projectile.erase(it);

        // Break projectile loop if exist another zombie
        if (it == projectile.end()) {
          it2 = zombie.end();
        }

        projectilesCreated--;
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

void newProjectile(Vec2 position, bool normalPea) {
  if (projectilesCreated < 100) {
    Proyectile projectileData;
    projectileData.id = Entities::newID();
    if(normalPea == true){
      projectileData.type = enumProyectile::normal;
    }else{
      projectileData.type = enumProyectile::snow;
    }
    
    projectile.insert(projectile.begin() + projectilesCreated, projectileData);
    int* id = &projectile[projectilesCreated].id;

    position.y -= 15.0f;
    createSprite(*id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    if(normalPea == true) { 
      projectilePea->addLink(spriteArray[*id].id); 
    }else{
      projectileSnowPea->addLink(spriteArray[*id].id);
    }

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

void newFatherID(int* fatherID, int* childID) {
  fatherIDArray[*fatherID].id.push_back(*childID);
}

void deleteFatherID(int* fatherID, int* childID) {
  std::vector<int>::iterator it =
      find(fatherIDArray[*fatherID].id.begin(),
           fatherIDArray[*fatherID].id.end(), *childID);
  fatherIDArray[*fatherID].id.erase(it);
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