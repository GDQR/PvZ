#include "PVZ.hpp"
#include "manager.hpp"
#include "debugPVZ/menuDebugCommands.hpp"
#include <iostream>

// sparse array
ArrayKey<FrameCounter> frameCounterArray(enumComponents::FRAMECOUNTER);
std::unordered_map<int, std::vector<char*>> layerAnimNames;
ArrayKey<FatherID> fatherIDArray(enumComponents::fatherID);
ArrayKey<Tyra::Vec2> posArray(enumComponents::pos);
ArrayKey<Tyra::Vec2> texPosArray(enumComponents::texPos);
ArrayKey<Tyra::Vec2> finalPosArray(enumComponents::finalPos);
ArrayKey<Tyra::Sprite> spriteArray(enumComponents::sprite);
ArrayKey<int> spriteRenderIDArray(enumComponents::spriteRender);
// std::vector<int> spriteNormalIdStopRender;
// std::vector<int> animationIdStopRender;
ArrayKey<Tyra::Vec2> angleArray(enumComponents::angle);
std::unordered_map<int, Tyra::Vec2> originalSize;
std::unordered_map<int, Tyra::Vec2> scaleTexture;
std::unordered_map<int, Tyra::Vec2> pointColliderArray;
std::unordered_map<int, int> boxColliderArrayID;
std::unordered_map<int, std::vector<BoxCollider>> boxColliderArray;
std::vector<BoxCollider> boxColliderPlant;
std::vector<BoxCollider> boxColliderZombie;
std::vector<BoxCollider> boxColliderProyectile;
std::vector<BoxCollider> boxColliderExplosion;
std::vector<BoxCollider> boxColliderLawnmower;
std::vector<BoxCollider> boxColliderSun;
std::vector<BoxCollider> boxColliderPlayer;
std::vector<ResponseCollisionProjectile> responseCollisionZombieProjectile;
std::vector<ResponseCollisionZombiePlant> responseCollisionZombiePlant;
std::vector<ResponseCollisionZombiePlant> previousResponseCollisionZombiePlant;
std::vector<ResponseCollisionZombiePlant> stopResponseCollisionZombiePlant;
std::vector<ResponseCollisionZombiePlant> enterResponseCollisionZombiePlant;
std::vector<ResponseCollisionSunCursor> responseCollisionSunCursor;
std::unordered_map<int, TriggerBoxCollider> resultBoxCollider;
ArrayKey<PS2Timer> timerArray(enumComponents::timer);
std::unordered_map<int, float> speedArray;
std::unordered_map<int, int> damageArray;
ArrayKey<int> lifeArray(enumComponents::life);
std::map<int, Tyra::Vec2> pivot;
std::vector<Controller> controller;
std::vector<Zombie> zombie;
std::vector<Zombie> zombieAttackState;
std::vector<Zombie> zombieJumpState;
std::vector<Zombie> deadZombie;
std::vector<Zombie> charredZombie;
std::vector<Zombie> damagedZombie;
std::vector<Sun> sun;
std::vector<NaturalSun> naturalSun;
std::vector<Proyectile> projectile;
std::vector<Explosion> explosion;
std::vector<Card> cards;
std::vector<LawnMower> lawnMower;
std::vector<Cursor> cursor;
std::vector<DeckCursor> deckCursor;

BoxCollider::BoxCollider() {}
BoxCollider::BoxCollider(int id, float x, float y, float width, float height) {
  this->id = id;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}
BoxCollider::BoxCollider(float x, float y, float width, float height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

void BoxCollider::move(const int entityID, float offsetX, float offsetY) {
  x = offsetX + posArray[entityID].x;
  y = offsetY + posArray[entityID].y;
}

/*
 * @return True if collision exist
 */
bool BoxCollider::collision(const BoxCollider* box) {
  if (x + width >= box->x && box->x + box->width >= x && y + height >= box->y &&
      box->y + box->height >= y) {
    return true;
  }
  return false;
}

bool BoxCollider::pointCollision(const Tyra::Vec2* point) {
  if (point->x < x + width && point->y > y && point->y < y + height) {
    return true;
  }
  return false;
}

BoxCollider& searchBoxCollider(int type,int id){
  return boxColliderArray[type][boxColliderArrayID[id]];
}

void Card::update() {
  PS2Timer& timer = timerArray[seedShadowTimer];
  // printf("counter: %d\n", timer.counterMS);
  // printf("maxMS: %d\n", timer.maxMS);
  if (timer.counterMS <
      timer.maxMS) {
    timer.addMSinCounter();

    spriteArray[seedShadow].size = Vec2(50, 70);
    spriteArray[seedShadowTimer].size.y -= (70.0f * timer.getTimeInMS() / timer.maxMS);
  } else if (sunCounter >= cost) {
    spriteArray[seedShadow].size = Vec2(0, 0);
    spriteArray[seedShadowTimer].size = Vec2(0, 0);
  }
}

void Controller::update() {
  if (pad->getClicked().Cross) {
    // create plant
    // printf("press cross\n");
    plantsManager.create(cursorID);
  }
  if (pad->getClicked().DpadLeft) {
    deckCursor[cursorID].moveLeft(playerID);
  }
  if (pad->getClicked().DpadRight) {
    deckCursor[cursorID].moveRight(playerID);
  }

  if (debugMode == false) {
    Cursor& playerCursor = cursor[cursorID];
    playerCursor.move();
    for(size_t i=0; i < boxColliderPlayer.size();i++){
      if(boxColliderPlayer[i].id == playerCursor.id){
        boxColliderPlayer[i].move(playerCursor.id, 28 / 2,
                                               24 / 2);
      }
    }
  }

  if (pad->getClicked().R1 && debugMode == false) {
    debugMode = true;
    debugMenu = true;
    printf("\nDEBUG MODE ACTIVE\n");
  }

  if (debugMenu == true) {
    debugModeClass.mainMenu();
  }
}

void Cursor::move() {
  float x = 0.0F;
  float y = 0.0F;

  if (leftJoy->h <= 100) {
    x = -cursorSpeed;
  } else if (leftJoy->h >= 200) {
    x = cursorSpeed;
  }

  if (leftJoy->v <= 100) {
    y = -cursorSpeed;
  } else if (leftJoy->v >= 200) {
    y = cursorSpeed;
  }

  posArray[id] += Vec2(x, y);
  if (spriteArray[id].position.x != posArray[id].x ||
      spriteArray[id].position.y != posArray[id].y) {
    if (cursorTimer < 20) {
      cursorTimer++;

      if (cursorTimer == 10) {
        cursorSpeed = 1.5f;
      } else if (cursorTimer == 20) {
        cursorSpeed = 2.0f;
      }
    }

  } else {
    cursorTimer = 0;
    cursorSpeed = 1;
  }
}

void DeckCursor::moveLeft(int playerID) {
  std::vector<int>& actualAnim = cardsAnimations[pos].entity;
  for(size_t i=0;i<actualAnim.size();i++){
    deleteFatherIDChild(playerID,&actualAnim[i]);
    setSprite(actualAnim[i],noDraw,card_layer);
  }
  pos--;
  if (pos < 0) {
    pos = cards.size() - 1;
  }
  posArray[id].x = posArray[cards[pos].seed].x - 3;
  
  std::vector<int>& newAnim = cardsAnimations[pos].entity;
  for(size_t i=0;i<newAnim.size();i++){
    newFatherID(&playerID,&newAnim[i]);
    setSprite(newAnim[i],draw,card_layer);
  }
}

void DeckCursor::moveRight(int playerID) {
  std::vector<int>& actualAnim = cardsAnimations[pos].entity;
  for(size_t i=0;i<actualAnim.size();i++){
    deleteFatherIDChild(playerID,&actualAnim[i]);
    setSprite(actualAnim[i],noDraw,card_layer);
  }
  pos++;
  if (pos >= (int)cards.size()) {
    pos = 0;
  }
  posArray[id].x = posArray[cards[pos].seed].x - 3;

  std::vector<int>& newAnim = cardsAnimations[pos].entity;
  for(size_t i=0;i<newAnim.size();i++){
    newFatherID(&playerID,&newAnim[i]);
    setSprite(newAnim[i],draw,card_layer);
  }
}

void Explosion::erase() {
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  // boxColliderArray.erase(id);
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}

void FatherID::update(const int entityID) {
  Tyra::Vec2 fatherPos = posArray[entityID];
  for (unsigned int i = 0; i < id.size(); i++) {
    // finalPos += fatherPos
    // printf("childID: %d\n",id[i]);
    finalPosArray[id[i]] += fatherPos;
  }
  if(texPosArray.count(entityID) == 1){
    fatherPos = texPosArray[entityID];
    // printf("fatherID: %d texpos:%f,%f\n",entityID, pos.x,pos.y);
    for (unsigned int i = 0; i < id.size(); i++) {
      finalPosArray[id[i]] += fatherPos;
    }
  }
}

bool Proyectile::attack(){
  size_t searchIndex = responseCollisionZombieProjectile.size();
  size_t size = searchIndex;
  int zombieCollisionID;
  for(size_t i=0;i<size;i++){
    if(responseCollisionZombieProjectile[i].projectileID == id){
      searchIndex = i;
      zombieCollisionID = responseCollisionZombieProjectile[i].zombieID;
      break;
    }
  }

  if(searchIndex == size){
    return move(); 
  }

  size = zombie.size();
  for(size_t i=0; i < size; i++){
    if(zombie[i].boxColliderID == zombieCollisionID){
      if(type == pea){
        if(zombie[i].damage(id,Bullet) == true){
          zombie.erase(zombie.begin()+i);
        }
      }else if(type == snowPea){
        speedArray[zombie[i].father] = 0.5f;
        if(zombie[i].damage(id,SNOW_BULLET) == true){
          zombie.erase(zombie.begin()+i);
        }
      }
      break;
    }
  }
  return true;
}

bool Proyectile::move() {
  // boxColliderArray[id].x++;
  // boxColliderArray[BOXCOLLIDER_PROYECTILE][boxColliderArrayID[id]].x++;
  for(unsigned int i=0; i < boxColliderProyectile.size();i++){
    if(boxColliderProyectile[i].id == id){
      boxColliderProyectile[i].x++;
      break;
    }
  }
  posArray[id].x++;
  if (posArray[id].x >= 580) {
    // delete projectile
    printf("deleting projectile\n");
    return true;
  }
  return false;
}

void Proyectile::erase() {
  // if (type == enumProyectile::pea) {
  //   projectilePea->removeLinkById(spriteArray[id].id);
  // } else if (type == enumProyectile::snowPea) {
  //   projectileSnowPea->removeLinkById(spriteArray[id].id);
  // }

  printf("deleting projectile\n");
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  
  for(size_t i=0; i<boxColliderProyectile.size();i++){
    if(boxColliderProyectile[i].id == id){
      boxColliderProyectile.erase(boxColliderProyectile.begin()+i);
      break;
    }
  }
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}

static u32 globalTime;

void GetTime(){
  globalTime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
}

PS2Timer::PS2Timer() { resetCounter(); }
void PS2Timer::setLastTime() { lastTime = actualTime; }

u32 PS2Timer::getTimeInMS() {
  actualTime = globalTime;
  return actualTime - lastTime;
}

void PS2Timer::resetCounter() {
  lastTime = globalTime;
  actualTime = lastTime;
  counterMS = 0;
}

void PS2Timer::addMSinCounter() {
  setLastTime();
  counterMS += getTimeInMS();
}