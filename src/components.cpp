#include "debugPVZ/menuDebugCommands.hpp"
#include "entities/entities.hpp"
#include "components.hpp"
#include <iostream>

Tyra::Engine* engine;
Tyra::Renderer* renderer;
const Tyra::PadJoy* leftJoy;
Tyra::TextureRepository* texRepo;

// sparse array
std::unordered_map<int, std::vector<int>> m_animID;
ArrayKey<int, Animation> animationArray(enumComponents::animation);
std::unordered_map<int, AnimationData> animationDataArray;
ArrayKey<int, FatherID> fatherIDArray(enumComponents::fatherID);
ArrayKey<int, Tyra::Vec2> posArray(enumComponents::pos);
ArrayKey<int, Tyra::Vec2> texPosArray(enumComponents::texPos);
ArrayKey<int, Tyra::Vec2> finalPosArray(enumComponents::finalPos);
ArrayKey<int, Tyra::Sprite> spriteArray(enumComponents::sprite);
ArrayKey<int, int> spriteRenderIDArray(enumComponents::spriteRender);
// std::vector<int> spriteNormalIdStopRender;
// std::vector<int> animationIdStopRender;
ArrayKey<int, Tyra::Vec2> angleArray(enumComponents::angle);
std::unordered_map<int, Tyra::Vec2> originalSize;
std::unordered_map<int, Tyra::Vec2> scaleTexture;
std::unordered_map<int, Tyra::Vec2> pointColliderArray;
std::unordered_map<int, BoxCollider> boxColliderArray;
ArrayKey<int, PS2Timer> timerArray(enumComponents::timer);
std::unordered_map<int, float> speedArray;
std::unordered_map<int, int> damageArray;
ArrayKey<int, int> lifeArray(enumComponents::life);
std::map<int, Tyra::Vec2> pivot;
std::map<int, Controller> controller;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
std::vector<Sun> sun;
std::vector<NaturalSun> naturalSun;
std::vector<Proyectile> projectile;
std::vector<Explosion> explosion;
std::vector<Card> cards;
std::vector<LawnMower> lawnMower;
int player;
std::map<int, Cursor> cursor;
std::map<int, DeckCursor> deckCursor;

int zombiescreated;
ZombieRow zombieCreateRow[5];
bool mapEnable[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

std::map<int, Tyra::Sprite> dm_SpritePointCollider;
std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpriteNormal;
std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;

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

void Controller::update(const int entityID) {
  if (engine->pad.getClicked().Cross) {
    // create plant
    plantsManager.create();
  }
  if (engine->pad.getClicked().DpadLeft) {
    deckCursor[entityID].moveLeft();
  }
  if (engine->pad.getClicked().DpadRight) {
    deckCursor[entityID].moveRight();
  }
  if (engine->pad.getClicked().R1 && debugMode == false) {
    debugMode = true;
    debugMenu = true;
    printf("\nDEBUG MODE ACTIVE\n");
  }

  if (debugMenu == true) {
    debugModeClass.mainMenu();
  }
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

void BoxCollider::move(const int entityID) {
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

void DeckCursor::moveLeft() {
  pos--;
  if (pos < 0) {
    pos = cards.size() - 1;
  }
  posArray[id].x = posArray[cards[pos].seed].x - 3;
}

void DeckCursor::moveRight() {
  pos++;
  if (pos >= (int)cards.size()) {
    pos = 0;
  }
  posArray[id].x = posArray[cards[pos].seed].x - 3;
}

void Card::update() {
  if (timerArray[seedShadowTimer].counterMS <
      timerArray[seedShadowTimer].maxMS) {
    timerArray[seedShadowTimer].addMSinCounter();

    spriteArray[seedShadow].size = Vec2(50, 70);
    spriteArray[seedShadowTimer].size.x = 50;
    spriteArray[seedShadowTimer].size.y -=
        (70.0f * timerArray[seedShadowTimer].getTimeInMS() /
         timerArray[seedShadowTimer].maxMS);
  } else if (sunCounter >= cost) {
    spriteArray[seedShadow].size = Vec2(0, 0);
    spriteArray[seedShadowTimer].size = Vec2(0, 0);
  }
}

bool Proyectile::move() {
  boxColliderArray[id].x++;
  posArray[id].x++;
  if (posArray[id].x >= 580) {
    // delete projectile
    printf("deleting projectile\n");
    erase();
    return true;
  }
  return false;
}

void Proyectile::erase() {
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  boxColliderArray.erase(id);
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}

void Explosion::erase() {
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  boxColliderArray.erase(id);
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}

Animation::Animation() {}

Animation::Animation(const int anim) { animID = anim; }

void Animation::update(const int entityID) {
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > lastFrame) {
      currentFrame = firstFrame;
    }

    activeDrawNormalSprites(entityID);
    if (draw == (int)enumDraw::draw) {
      updateSprites(entityID);
      if (angleArray.count(entityID) == 1) {
        updateAngle(entityID);
      }
    }
  }

  framesCounter++;
}

void Animation::position(const int entityID) {
  // finalPos += animPos
  if (animationDataArray[animID].position.count(currentFrame)) {
    texPosArray[entityID] = animationDataArray[animID].position[currentFrame];
  }
}

void Animation::activeDrawNormalSprites(const int entityID) {
  int index = animationDataArray[animID].draw.getIndex(currentFrame);
  if (index != -1) {
    draw = animationDataArray[animID].draw.second[index];
    if (draw == (int)enumDraw::noDraw) {
      spriteRenderIDArray.erase(entityID);
      // spriteNormalIdStopRender.push_back(entityID);
    } else if (spriteRenderIDArray.count(entityID) == 0) {
      spriteRenderIDArray.insert(entityID, 0);
    }
  }
}

void Animation::updateSprites(const int entityID) {
  int myindex = animationDataArray[animID].texture.getIndex(currentFrame);
  if (myindex != -1) {
    Tyra::Texture* texture = texRepo->getBySpriteId(spriteArray[entityID].id);
    // Unlink Texture from the sprite entitie
    if (texture != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
      texture->removeLinkById(spriteArray[entityID].id);
    }

    // Link new Texture to the sprite entitie
    texture = texRepo->getByTextureId(animationDataArray[animID].texture.second[myindex]);
        texture->addLink(spriteArray[entityID].id);
    originalSize[entityID] = Vec2(
        texture->getWidth(),
        texture->getHeight());
  }
  myindex = animationDataArray[animID].position.getIndex(currentFrame);
  // printf("currentFrame: %d\n",currentFrame);
  // printf("index: %d\n",myindex);
  if (myindex != -1) {
    texPosArray[entityID] = animationDataArray[animID].position.second[myindex] * scaleTexture.at(entityID);
  }

  myindex = animationDataArray[animID].alpha.getIndex(currentFrame);
  if (myindex != -1) {
    spriteArray[entityID].color.a =
        animationDataArray[animID].alpha.second[myindex];
  }

  myindex = animationDataArray[animID].scale.getIndex(currentFrame);
  if (myindex != -1) {
    spriteArray[entityID].size =
        originalSize[entityID] *
        animationDataArray[animID].scale.second[myindex] * scaleTexture.at(entityID);
  }
}

void Animation::updateAngle(const int entityID) {
  int myindex = animationDataArray[animID].angle.getIndex(currentFrame);
  if (myindex != -1) {
    angleArray[entityID] = animationDataArray[animID].angle.second[myindex];
  }
}

void Animation::setAnimation(enumAnimationState animationState){
  currentFrame = animationStateVector[animationState].firstFrame;
  lastFrame = animationStateVector[animationState].lastFrame;
  firstFrame = currentFrame;
}
int Animation::debugAnim(const int entitieID) {
  if (framesCounter < (60 / framesSpeed)) {
    framesCounter++;
    return 1;
  }

  currentFrame++;
  framesCounter = 0;

  if (currentFrame > lastFrame) {
    currentFrame = firstFrame;
  }

  if (spriteArray.count(entitieID) == 1 &&
      animationDataArray[animID].texture.count(currentFrame) == 1) {
    texRepo->getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);

    texRepo->getByTextureId(animationDataArray[animID].texture[currentFrame])
        ->addLink(spriteArray[entitieID].id);
  }
  int myindex = animationDataArray[animID].position.getIndex(currentFrame);
  if (myindex != 1) {
    texPosArray[entitieID] = animationDataArray[animID].position.second[currentFrame];
  }

  if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
    spriteArray[entitieID].color.a = animationDataArray[animID].alpha[currentFrame];
  }
  myindex = animationDataArray[animID].scale.getIndex(currentFrame);
  if (myindex != -1) {
    spriteArray[entitieID].size = originalSize[entitieID] *
    animationDataArray[animID].scale.second[myindex];
  }

  if (animationDataArray[animID].angle.count(currentFrame) == 1) {
    angleArray[entitieID] = animationDataArray[animID].angle[currentFrame];
  }

  return 0;
}

void FatherID::update(const int entityID) {
  for (unsigned int i = 0; i < id.size(); i++) {
    // finalPos += fatherPos
    finalPosArray[id[i]] += posArray[entityID];
  }
}

PS2Timer::PS2Timer() { resetCounter(); }
void PS2Timer::setLastTime() { lastTime = actualTime; }

u64 PS2Timer::getTimeInMS() {
  actualTime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
  return actualTime - lastTime;
}

void PS2Timer::resetCounter() {
  lastTime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
  actualTime = lastTime;
  counterMS = 0;
}

void PS2Timer::addMSinCounter() {
  setLastTime();
  counterMS += getTimeInMS();
}