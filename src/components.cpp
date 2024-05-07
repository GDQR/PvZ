#include "components.hpp"
#include <iostream>

// sparse array
std::map<int, Animation> animationArray;
std::map<int, Time> animationTime;
std::unordered_map<int, AnimationData> animationDataArray;
std::map<int, FatherID> fatherIDArray;
std::map<int, Tyra::Vec2> posArray;
std::map<int, Tyra::Vec2> finalPosArray;
std::map<int, Tyra::Sprite> spriteArray;
std::map<int, Tyra::Sprite> spritesRotate;
std::map<int, float> angles;
std::map<int, Tyra::Vec2> pointColliderArray;
std::map<int, BoxCollider> boxColliderArray;
std::map<int, int> damageArray;
std::map<int, int> lifeArray;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
std::vector<Sun> sun;
std::vector<int> projectile;
int projectilesCreated = 0;

bool zombieCreateRow[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

std::map<int, Tyra::Sprite> debugSpritePointCollider;
std::map<int, Tyra::Sprite> debugSpriteBoxCollider;

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size) {
  spriteArray[id] = Sprite();
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  // printf("nuevo sprite id: %d. pos: %d\n",spriteArray[id].id,id);
  loadSprite(&spriteArray[id], mode, Vec2(0.0f, 0.0f), size);
}

void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size, const float angle) {
  spritesRotate[id] = Sprite();             
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  // printf("nuevo sprite id: %d. pos: %d\n",spritesRotate[id].id,id);
  angles[id] = angle;
  loadSprite(&spritesRotate[id], mode, Vec2(0.0f, 0.0f), size);
}

void deleteSprite(const int id) { spriteArray.erase(id); }

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
  auto& textureRepository = renderer->getTextureRepository();

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    if (animationArray[it->first].time <
        animationTime[animationArray[it->first].animID]
            .seconds[animationArray[it->first].key]) {
      animationArray[it->first].time++;

      position(it->first);
      continue;
    }

    // Unlink Texture from the sprite entitie
    textureRepository.getBySpriteId(spriteArray[it->first].id)
        ->removeLinkById(spriteArray[it->first].id);

    animationArray[it->first].key++;
    animationArray[it->first].time = 0;

    if (animationArray[it->first].key >=
        animationDataArray[animationArray[it->first].animID].keys.size()) {
      animationArray[it->first].key = 0;
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animationArray[it->first].animID]
        .keys[animationArray[it->first].key]
        ->addLink(spriteArray[it->first].id);

    position(it->first);
  }
}

void AnimationManager::position(const int entitieID) {
  // finalPos += animPos
  finalPosArray[entitieID] =
      *animationDataArray[animationArray[entitieID].animID]
           .position[animationArray[entitieID].key];
}

void AnimationManager::debug() {
  std::map<int, Animation>::iterator it;

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    position(it->first);
  }
}

int AnimationManager::debugAnim(const int entitieID) {
  auto& textureRepository = renderer->getTextureRepository();

  if (animationArray[entitieID].time <
      animationTime[animationArray[entitieID].animID]
          .seconds[animationArray[entitieID].key]) {
    animationArray[entitieID].time++;
    return 1;
  }

  textureRepository.getBySpriteId(spriteArray[entitieID].id)
      ->removeLinkById(spriteArray[entitieID].id);

  animationArray[entitieID].key++;
  animationArray[entitieID].time = 0;

  if (animationArray[entitieID].key >=
      animationDataArray[animationArray[entitieID].animID].keys.size()) {
    animationArray[entitieID].key = 0;
  }

  animationDataArray[animationArray[entitieID].animID]
      .keys[animationArray[entitieID].key]
      ->addLink(spriteArray[entitieID].id);
  return 0;
}

void AnimationManager::debugChangeFrame(const int entitieID, const int key) {
  auto& textureRepository = renderer->getTextureRepository();

  // Unlink Texture from the sprite entitie
  textureRepository.getBySpriteId(spriteArray[entitieID].id)
      ->removeLinkById(spriteArray[entitieID].id);

  // Link new Texture to the sprite entitie
  animationDataArray[animationArray[entitieID].animID]
      .keys[animationArray[entitieID].key]
      ->addLink(spriteArray[entitieID].id);
}

void RendererDebugSpritesManager::update() {
  std::map<int, Sprite>::iterator it;
  // auto& textureRepository = renderer->getTextureRepository();

  for (it = debugSpriteBoxCollider.begin(); it != debugSpriteBoxCollider.end();
       it++) {
    renderer->renderer2D.render(debugSpriteBoxCollider[it->first]);
  }

  for (it = debugSpritePointCollider.begin();
       it != debugSpritePointCollider.end(); it++) {
    renderer->renderer2D.render(debugSpritePointCollider[it->first]);
  }
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
  std::map<int, Sprite>::iterator it;
  // printf("size: %d\n", spriteArray.size());
  for (it = spriteArray.begin(); it != spriteArray.end(); it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);

    // finalPos += entitiePos

    finalPosArray[it->first].x += posArray[it->first].x;
    finalPosArray[it->first].y += posArray[it->first].y;

    if (finalPosArray[it->first].x != it->second.position.x ||
        finalPosArray[it->first].y != it->second.position.y) {
      it->second.position.x = finalPosArray[it->first].x;
      it->second.position.y = finalPosArray[it->first].y;
      // printf("key: %d. sprite pos:
      // %f,%f\n",it->first,it->second.position.x,it->second.position.y);
    }

    renderer->renderer2D.render(it->second);
    finalPosArray[it->first] = Vec2(0.0f, 0.0f);
  }
  // printf("Render Finish\n");
}

void RendererSprites::updateRotate() {
  std::map<int, Sprite>::iterator it;
  // static float angle = 0;
  
  for (it = spritesRotate.begin(); it != spritesRotate.end(); it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);

    // finalPos += entitiePos
    
    finalPosArray[it->first].x += posArray[it->first].x;
    finalPosArray[it->first].y += posArray[it->first].y;

    if (finalPosArray[it->first].x != it->second.position.x ||
        finalPosArray[it->first].y != it->second.position.y) {
      it->second.position.x = finalPosArray[it->first].x;
      it->second.position.y = finalPosArray[it->first].y;
      // printf("key: %d. sprite pos:
      // %f,%f\n",it->first,it->second.position.x,it->second.position.y);
    }

    renderer->renderer2D.renderRotate(it->second,angles[it->first]);
    finalPosArray[it->first] = Vec2(0.0f, 0.0f);
  }
  // angle++;
  // if(angle>360){
  //   angle =0;
  // }
  // printf("Render Finish\n");
}

void ZombiesManager::update() {
  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); it++) {
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
      debugSpriteBoxCollider[*it->body[0]].position.x =
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
      it->attack = false;
      animationArray[*it->body[0]].animID = zombieWalk;
    }
    return 0;
  }

  for (it = zombie.begin(); it < zombie.end(); it++) {
    // printf("hay una planta en %d\n",i);

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

        if (boxCollision(&boxColliderArray[*plant[i].body[0]],
                         &boxColliderArray[*(it)->body[0]]) == true) {
          it->attack = true;
          animationArray[*it->body[0]].animID = zombieNormalAttack;
          if (it->attackTimer > 0) {
            it->attackTimer--;
          } else {
            it->attackTimer = 80;
            printf("comiendo planta\n");
            lifeArray[*plant[i].body[0]] -= damageArray[*it->body[0]];

            if (lifeArray[*plant[i].body[0]] <= 0) {
              printf("borre planta id: %d\n", *plant[i].body[0]);
              deletePeashotter(i);
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
  auto& textureRepository = renderer->getTextureRepository();

  for (it = projectile.begin(); it < projectile.end(); it++) {
    // printf("projectile id: %d\n", *it);
    posArray[*it].x++;
    // printf("proyectile pos: %f,%f\n", posArray[*it].x, posArray[*it].y);
    // printf("position: %f,%f\n",
    // spriteArray[*it].position.x,spriteArray[*it].position.y);
    boxColliderArray[*it].x = posArray[*it].x;
    debugSpriteBoxCollider[*it].position.x = boxColliderArray[*it].x;
    if (posArray[*it].x >= 580) {
      // delete projectile
      printf("borrando proyectil\n");
      textureRepository.getBySpriteId(spriteArray[*it].id)
          ->removeLinkById(spriteArray[*it].id);
      spriteArray.erase(*it);
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

          deleteFatherID(it2->father,it2->body[0]);
          // deleteFatherID(*it2->father,*it2->body[1]);
          textureRepository.getBySpriteId(spriteArray[*it2->body[0]].id)
              ->removeLinkById(spriteArray[*it2->body[0]].id);
          spriteArray.erase(*it2->body[0]);
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

        text->removeLinkById(spriteArray[*it].id);
        spriteArray.erase(*it);
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
  createDebugBoxCollider(*cursor, Tyra::MODE_STRETCH);
}

void newDeckCursor(int* cursor, Tyra::Vec2 pos) {
  *cursor = Entities::newID();
  printf("deck cursor id: %d\n", *cursor);
  createSprite(*cursor, Tyra::MODE_STRETCH, pos, Vec2(56, 48));
  createTexture(*cursor, "cursor6.png");
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