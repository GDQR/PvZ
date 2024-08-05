#include "debugPVZ/menuDebugCommands.hpp"
#include "entities/entities.hpp"
#include "components.hpp"
#include <iostream>

Tyra::Engine* engine;
Tyra::Renderer* renderer;
const Tyra::PadJoy* leftJoy;
Tyra::TextureRepository* texRepo;

// sparse array
std::unordered_map<std::string, std::vector<int>> m_animID;
std::map<int, Animation> animationArray;
std::unordered_map<int, AnimationData> animationDataArray;
std::map<int, FatherID> fatherIDArray;
ArrayKey<int, Tyra::Vec2> posArray(enumComponents::pos);
ArrayKey<int, Tyra::Vec2> texPosArray(enumComponents::texPos);
ArrayKey<int, Tyra::Vec2> finalPosArray(enumComponents::finalPos);
ArrayKey<int, Tyra::Sprite> spriteArray(enumComponents::sprite);
ArrayKey<int, int> spriteRenderIDArray(enumComponents::spriteRender);
std::vector<int> spriteNormalIdStopRender;
std::vector<int> animationIdStopRender;
std::unordered_map<int, Tyra::Vec2> angleArray;
std::map<int, Tyra::Vec2> originalSize;
std::map<int, Tyra::Vec2> scaleTexture;
std::map<int, Tyra::Vec2> pointColliderArray;
std::map<int, BoxCollider> boxColliderArray;
std::map<int, PS2Timer> timerArray;
std::map<int, float> speedArray;
std::map<int, int> damageArray;
std::map<int, int> lifeArray;
std::map<int, Tyra::Vec2> pivot;
std::map<int, Controller> controller;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
std::vector<Sun> sun;
std::vector<NaturalSun> naturalSun;
std::vector<Proyectile> projectile;
std::vector<Card> cards;
int player;
std::map<int, Cursor> cursor;
std::map<int, DeckCursor> deckCursor;

bool zombieCreateRow[5];
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
  angleArray[id] = angle;
  createSprite(id, mode, position, size);
}

void deleteSprite(const int entityID) {
  if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
    engine->renderer.getTextureRepository()
        .getBySpriteId(spriteArray[entityID].id)
        ->removeLinkById(spriteArray[entityID].id);
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
bool BoxCollider::collision(BoxCollider* box) {
  if (x + width >= box->x && box->x + box->width >= x && y + height >= box->y &&
      box->y + box->height >= y) {
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

Animation::Animation() {}

Animation::Animation(const int anim) { animID = anim; }

void Animation::update(const int entityID) {
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > lastFrame) {
      currentFrame = firstFrame;
    }

    if (spriteArray.count(entityID) == 1) {
      activeDrawNormalSprites(entityID);
      if (draw == (int)enumDraw::draw) {
        updateSprites(entityID);
        if (angleArray.count(entityID) == 1) {
          updateAngle(entityID);
        }
      }
    }
  }
  position(entityID);
  framesCounter++;
}

void Animation::position(const int entityID) {
  // finalPos += animPos

  if (animationDataArray[animID].x.count(currentFrame)) {
    texPosArray[entityID].x = animationDataArray[animID].x[currentFrame];
  }
  if (animationDataArray[animID].y.count(currentFrame)) {
    texPosArray[entityID].y = animationDataArray[animID].y[currentFrame];
  }
}

void Animation::activeDrawNormalSprites(const int entityID) {
  if (animationDataArray[animID].draw.count(currentFrame)) {
    draw = animationDataArray[animID].draw[currentFrame];
    if (draw == (int)enumDraw::noDraw) {
      spriteRenderIDArray.erase(entityID);
      spriteNormalIdStopRender.push_back(entityID);
    } else {
      spriteRenderIDArray[entityID] = entityID;
    }
  }
}

void Animation::updateSprites(const int entityID) {
  // if (animationDataArray[animID].texture.count(currentFrame) == 1) {
  //   frameDataArray[entityID].texture = animationDataArray[animID].texture[currentFrame];
  // }

  // if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
  //   frameDataArray[entityID].alpha = animationDataArray[animID].alpha[currentFrame] * 128;
  // }

  // if (animationDataArray[animID].scaleX.count(currentFrame) == 1) {
  //   frameDataArray[entityID].scaleX = originalSize[entityID].x * animationDataArray[animID].scaleX[currentFrame];
  // }
  // if (animationDataArray[animID].scaleY.count(currentFrame) == 1) {
  //   frameDataArray[entityID].scaleY = originalSize[entityID].y * animationDataArray[animID].scaleY[currentFrame];
  // }

  // spriteArray[entityID].color.a = frameDataArray[entityID].alpha;
  // spriteArray[entityID].position = finalPosArray.second[Entities::componentIndex[entityID][0]];
  // spriteArray[entityID].size = Tyra::Vec2(frameDataArray[entityID].scaleX,frameDataArray[entityID].scaleY);
  if (animationDataArray[animID].texture.count(currentFrame) == 1) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
      texRepo->getBySpriteId(spriteArray[entityID].id)
          ->removeLinkById(spriteArray[entityID].id);
    }

    // Link new Texture to the sprite entitie
    texRepo->getByTextureId(animationDataArray[animID].texture[currentFrame])
        ->addLink(spriteArray[entityID].id);
    originalSize[entityID] = Vec2(
        texRepo
            ->getByTextureId(animationDataArray[animID].texture[currentFrame])
            ->getWidth(),
        texRepo
            ->getByTextureId(animationDataArray[animID].texture[currentFrame])
            ->getHeight());
  }
  if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
    spriteArray[entityID].color.a =
        animationDataArray[animID].alpha[currentFrame] * 128;
  }
  if (animationDataArray[animID].scaleX.count(currentFrame) == 1) {
    spriteArray[entityID].size.x =
        originalSize[entityID].x *
        animationDataArray[animID].scaleX[currentFrame];
  }
  if (animationDataArray[animID].scaleY.count(currentFrame) == 1) {
    spriteArray[entityID].size.y =
        originalSize[entityID].y *
        animationDataArray[animID].scaleY[currentFrame];
  }
}

void Animation::updateAngle(const int entityID) {
  if (animationDataArray[animID].angleX.count(currentFrame) == 1) {
    angleArray[entityID].x = animationDataArray[animID].angleX[currentFrame];
  }

  if (animationDataArray[animID].angleY.count(currentFrame) == 1) {
    angleArray[entityID].y = animationDataArray[animID].angleY[currentFrame];
  }
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

  if (animationDataArray[animID].x.count(currentFrame) == 1) {
    texPosArray[entitieID].x = animationDataArray[animID].x[currentFrame];
  }

  if (animationDataArray[animID].y.count(currentFrame) == 1) {
    texPosArray[entitieID].y = animationDataArray[animID].y[currentFrame];
  }

  if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
    float alpha = animationDataArray[animID].alpha[currentFrame] * 128;
    spriteArray[entitieID].color.a = alpha;
  }

  if (animationDataArray[animID].scaleX.count(currentFrame) == 1) {
    spriteArray[entitieID].size.x =
        originalSize[entitieID].x *
        animationDataArray[animID].scaleX[currentFrame];
  }

  if (animationDataArray[animID].scaleY.count(currentFrame) == 1) {
    spriteArray[entitieID].size.y =
        originalSize[entitieID].y *
        animationDataArray[animID].scaleY[currentFrame];
  }

  if (animationDataArray[animID].angleX.count(currentFrame) == 1) {
    angleArray[entitieID].x = animationDataArray[animID].angleX[currentFrame];
  }
  if (animationDataArray[animID].angleY.count(currentFrame) == 1) {
    angleArray[entitieID].y = animationDataArray[animID].angleY[currentFrame];
  }

  return 0;
}

void FatherID::update(const int entityID) {
  for (unsigned int i = 0; i < id.size(); i++) {
    // finalPos += fatherPos
    finalPosArray[id[i]].x += posArray[entityID].x;
    finalPosArray[id[i]].y += posArray[entityID].y;
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

void createCard(Plant_State_enum typePlant, Vec2 pos, bool isVersusMode) {
  Card card;
  card.seed = Entities::newID();
  card.seedShadow = Entities::newID();
  card.seedShadowTimer = Entities::newID();

  createSprite(card.seed, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seed, "UI/Seeds.png");
  spriteArray[card.seed].offset.x = 100;

  createSprite(card.seedShadow, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seedShadow, "UI/Seeds.png");
  spriteArray[card.seedShadow].color = Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);

  createSprite(card.seedShadowTimer, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seedShadowTimer, "UI/Seeds.png");
  spriteArray[card.seedShadowTimer].color =
      Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);

  timerArray[card.seedShadowTimer].maxMS = 0;
      // getPlantRechargeTime(typePlant, isVersusMode);
  if (startWithoutWait(typePlant, isVersusMode) == true) {
    timerArray[card.seedShadowTimer].counterMS =
        timerArray[card.seedShadowTimer].maxMS;
  }

  card.plant = typePlant;

  card.cost = getPlantCost(typePlant);

  cards.push_back(card);
}