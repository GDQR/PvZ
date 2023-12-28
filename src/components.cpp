#include "components.hpp"
#include <iostream>

// sparse array
std::map<int, Animation> animationArray;
std::map<int, Time> animationTime;
std::unordered_map<int, AnimationData> animationDataArray;
std::vector<MultipleID*> componentMultipleID(100, nullptr);
std::map<int, Tyra::Vec2> vec2Array;
std::map<int, Tyra::Sprite> spriteArray;
std::vector<Tyra::Texture*> textureArray(100, nullptr);
std::map<int, Tyra::Vec2> pointColliderArray;
std::map<int, BoxCollider> boxColliderArray;
std::map<int, int> damageArray;
std::map<int, int> lifeArray;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
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
  // printf("nuevo sprite id: %d. pos: %d\n",spriteArray[id].id,id);
  loadSprite(&spriteArray[id], mode, position, size);
}

void createTexture(int id, std::string fileImage) {
  textureArray[id] = loadTexture(fileImage);
  TYRA_ASSERT(!(spriteArray.find(id) == spriteArray.end()), "Entitie id: ", id,
              "Is NULL, use <<CreateSprite>> function");
  textureArray[id]->addLink(spriteArray[id].id);
}

void deleteSprite(const int id) { spriteArray.erase(id); }

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

MultipleID::MultipleID(const int fatherID) { id.push_back(fatherID); }

Animation::Animation() {}

Animation::Animation(enumAnimation anim) { animID = anim; }

void AnimationManager::update() {
  // printf("entro\n");
  std::map<int, Animation>::iterator it;
  auto& textureRepository = renderer->getTextureRepository();

  for (it = animationArray.begin(); it != animationArray.end(); it++) {
    if (animationArray[it->first].time <
        animationTime[animationArray[it->first].animID]
            .seconds[animationArray[it->first].key]) {
      animationArray[it->first].time++;
      continue;
    }

    textureRepository.getBySpriteId(spriteArray[it->first].id)
        ->removeLinkById(spriteArray[it->first].id);

    animationArray[it->first].key++;
    animationArray[it->first].time = 0;

    if (animationArray[it->first].key >=
        animationDataArray[animationArray[it->first].animID].keys.size()) {
      animationArray[it->first].key = 0;
    }

    // textureArray[it->first] =
    // animationDataArray[animationArray[it->first].animID].keys[animationArray[it->first].key];

    // textureArray[it->first]->addLink(spriteArray[it->first].id);
    animationDataArray[animationArray[it->first].animID]
        .keys[animationArray[it->first].key]
        ->addLink(spriteArray[it->first].id);
  }
}

void AnimationManager::debug() {}

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

void RendererSprites::update() {
  std::map<int, Sprite>::iterator it;
  // printf("size: %d\n",spriteArray.size());
  for (it = spriteArray.begin(); it != spriteArray.end(); it++) {
    // printf("key: %d. sprite ID: %d\n",it->first,it->second.id);
    renderer->renderer2D.render(it->second);
  }
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
      spriteArray[*it->body[0]].position.x--;

      boxColliderArray[*it->body[0]].x =
          spriteArray[*it->body[0]].position.x + 60;
      debugSpriteBoxCollider[*it->body[0]].position.x =
          boxColliderArray[*it->body[0]].x;
    }
  }
}

int ZombiesManager::collision() {
  std::vector<Zombie>::iterator it;

  if(plantsCreated == 0){
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
              printf("borre planta id: %d\n",*plant[i].body[0]);
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
    spriteArray[*it].position.x++;
    // printf("position: %f,%f\n", spriteArray[*it].position.x,spriteArray[*it].position.y);
    boxColliderArray[*it].x = spriteArray[*it].position.x;
    debugSpriteBoxCollider[*it].position.x = boxColliderArray[*it].x;
    if(spriteArray[*it].position.x >= 580){
      // delete projectile
      printf("borrando proyectil\n");
      textureRepository.getBySpriteId(spriteArray[*it].id)->removeLinkById(spriteArray[*it].id);
      spriteArray.erase(*it);
      boxColliderArray.erase(*it);
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
        printf("zombie id: %d\n",*it2->body[0]);
        //delete zombie
        if(lifeArray[*it2->body[0]] <= 0){
          vec2Array.erase(*it2->father);
          textureRepository.getBySpriteId(spriteArray[*it2->body[0]].id)->removeLinkById(spriteArray[*it2->body[0]].id);
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
        
        printf("borrando proyectil\n");
        printf("it: %d\n",*it);
        printf("it end: %d\n\n",*projectile.end());
        Tyra::Texture* text = textureRepository.getBySpriteId(spriteArray[*it].id);
        TYRA_ASSERT(text,"No se encontro la textura del proyectil with id: ",*it);

        text->removeLinkById(spriteArray[*it].id);
        spriteArray.erase(*it);
        boxColliderArray.erase(*it);
        deleteDebugBoxCollider(*it);
        Entities::deleteID(*it);
        it = projectile.erase(it);

        // Break projectile loop if exist another zombie
        if(it == projectile.end()){
          it2 = zombie.end();
        }
        
        projectilesCreated--;
      }
    }
  }

}

void newCursor(int* cursor, Tyra::Vec2 pos) {
  *cursor = Entities::newID();
  printf("cursor id: %d\n",*cursor);
  createSprite(*cursor, Tyra::MODE_STRETCH,
               pos, Vec2(56, 48));
  createTexture(*cursor, "cursor6.png");
  // vec2Array[cursor] = new Vec2(0,0);
  vec2Array[*cursor] = Vec2(0, 0);
  boxColliderArray[*cursor] = BoxCollider(
      pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  createDebugBoxCollider(*cursor, Tyra::MODE_STRETCH);
}

void newProjectile(Vec2 position) {
  if (projectilesCreated < 100) {
    projectile.insert(projectile.begin() + projectilesCreated,
                      Entities::newID());
    int* id = &projectile[projectilesCreated];
    printf("projectile ID: %d\n", *id);

    createSprite(*id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    // Sprite* spriteProjectile = &spriteArray[*id];
    projectilePea->addLink(spriteArray[*id].id);

    // damage
    damageArray[*id] = 20;
    // hitbox
    boxColliderArray[*id] =
        BoxCollider(spriteArray[*id].position.x, spriteArray[*id].position.y,
                    spriteArray[*id].size.x, spriteArray[*id].size.y);
    createDebugBoxCollider(*id, Tyra::MODE_STRETCH);
    projectilesCreated++;
  }
}