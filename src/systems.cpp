#include "systems.hpp"
#include "components.hpp"

int projectilesCreated = 0;

AnimationManager animManager;
ProjectileManager projectileManager;
RendererSprites renderSprites;
RendererDebugSpritesManager renderDebugSpritesManager;
ZombiesManager zombiesManager;
PlantsManager plantsManager;

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

int AnimationManager::debugAnim(const int entitieID) {

  if (animationArray[entitieID].framesCounter < (60 / framesSpeed)) {
    animationArray[entitieID].framesCounter++;
    return 1;
  }

  animationArray[entitieID].currentFrame++;
  animationArray[entitieID].framesCounter = 0;

  if (animationArray[entitieID].currentFrame >=
      animationDataArray[animationArray[entitieID].animID].maxFrame) {
    animationArray[entitieID].currentFrame = 0;
  }

  if (spriteArray.count(entitieID) == 1 &&
      animationDataArray[animationArray[entitieID].animID].texture.count(
          animationArray[entitieID].currentFrame) == 1) {
    texRepo->getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);

    texRepo->getByTextureId(animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame])
        ->addLink(spriteArray[entitieID].id);
  } else if (animationDataArray[animationArray[entitieID].animID].texture.count(
                 animationArray[entitieID].currentFrame) == 1) {
    texRepo->getBySpriteId(rotationSprite[entitieID].sprite.id)
        ->removeLinkById(rotationSprite[entitieID].sprite.id);

    texRepo->getByTextureId(animationDataArray[animationArray[entitieID].animID]
        .texture[animationArray[entitieID].currentFrame])
        ->addLink(rotationSprite[entitieID].sprite.id);
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
      rotationSprite[entitieID].sprite.color.a = alpha;
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
    } else {
      rotationSprite[entitieID].sprite.size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    rotationSprite[entitieID].angle = animationDataArray[animationArray[entitieID].animID]
                            .angle[animationArray[entitieID].currentFrame];
  }

  return 0;
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
      rotationSprite[entitieID].sprite.color.a = alpha;
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
    } else {
      rotationSprite[entitieID].sprite.size = originalSize[entitieID] * animationDataArray[animationArray[entitieID].animID]
              .scale[animationArray[entitieID].currentFrame];
    }
  }

  if (animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    rotationSprite[entitieID].angle = animationDataArray[animationArray[entitieID].animID]
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

void RendererSprites::update() {
  std::map<int, Sprite*>::iterator it;
  for (it = spritesNormalRender.begin(); it != spritesNormalRender.end();
       it++) {

    // finalPos += entitiePos

    finalPosArray[it->first] +=
        texPosArray[it->first] * scaleTexture[it->first];

    finalPosArray[it->first] += posArray[it->first];

    if (finalPosArray[it->first].x != it->second->position.x ||
        finalPosArray[it->first].y != it->second->position.y) {
      it->second->position = finalPosArray[it->first];
    }

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
      animationArray[it->id[0]].animID = zombieWalk;
    }
    return 0;
  }

  for (it = zombie.begin(); it < zombie.end(); it++) {
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

        if (boxColliderArray[plant[i].id[0]].collision(&boxColliderArray[it->id[0]]) == true) {
          it->attack = true;
          animationArray[it->id[0]].animID = zombieNormalAttack;
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
              animationArray[it->id[0]].animID = zombieWalk;
            }
          }
        } else {
          it->attack = false;
          animationArray[it->id[0]].animID = zombieWalk;
        }
      }
    }
  }

  return 1;
}

void PlantsManager::create(){
  if (engine->pad.getClicked().Cross && debugMode == false) {
    if (zombieCreateRow[(int)cursor.cursorTile.x] == true) {
      if (sunCounter >= cards[deckCursor.pos].cost &&
          plantsCreated < maxPlants && cards[deckCursor.pos].seedTimer == 0) {
        sunCounter -= cards[deckCursor.pos].cost;
        cards[deckCursor.pos].seedTimer = 60 * 8;
        spriteArray[cards[deckCursor.pos].seedShadowTimer].size.y = 70;
        createPlant(cards[deckCursor.pos].plant, cursor.cursorTile.x,
                    cursor.cursorTile.y);
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
  std::vector<int>::iterator it;

  for (it = projectile.begin(); it < projectile.end(); it++) {
    posArray[*it].x++;
    boxColliderArray[*it].x = posArray[*it].x;
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
  for (it = projectile.begin(); it < projectile.end(); it++) {
    for (it2 = zombie.begin(); it2 < zombie.end(); ) {
      if (boxColliderArray[*it].collision(&boxColliderArray[it2->id[0]]) == true) {

        // damage zombie
        it2->damage(*it);
        // printf("zombie id: %d\n",it2->id[0]);
        // delete zombie
        if(it2->erase() == true){
          it2 = zombie.erase(it2);
        }else{
          it2++;
        }

        // delete projectile

        Tyra::Texture* text =
            texRepo->getBySpriteId(spriteArray[*it].id);
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
      }else{
        it2++;
      }
    }
  }
}

void newProjectile(Vec2 position) {
  if (projectilesCreated < 100) {
    projectile.insert(projectile.begin() + projectilesCreated,
                      Entities::newID());
    int* id = &projectile[projectilesCreated];

    position.y -= 15.0f;
    createSprite(*id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
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

void newFatherID(int* fatherID, int* childID) {
  fatherIDArray[*fatherID].id.push_back(*childID);
}

void deleteFatherID(int* fatherID, int* childID) {
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