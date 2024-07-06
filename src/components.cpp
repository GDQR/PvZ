#include "components.hpp"
#include <iostream>

Tyra::Engine* engine;
Tyra::Renderer* renderer;
const Tyra::PadJoy* leftJoy;
Tyra::TextureRepository* texRepo;

// sparse array
std::map<std::string, std::vector<int>> m_animID;
std::map<int, Animation> animationArray;
std::unordered_map<int, AnimationData> animationDataArray;
std::map<int, FatherID> fatherIDArray;
std::map<int, Tyra::Vec2> posArray;
std::map<int, Tyra::Vec2> texPosArray;
std::map<int, Tyra::Vec2> finalPosArray;
std::map<int, Tyra::Sprite> spriteArray;
std::map<int, Tyra::Sprite*> spritesNormalRender;
std::vector<int> spriteNormalIdStopRender;
std::vector<int> animationIdStopRender;
std::map<int, RotationSprite> rotationSprite;
std::map<int, RotationSprite*> spritesRotateRender;
std::vector<int> spritesRotateIdStopRender;
std::map<int, Tyra::Vec2> originalSize;
std::map<int, Tyra::Vec2> scaleTexture;
std::map<int, Tyra::Vec2> pointColliderArray;
std::map<int, BoxCollider> boxColliderArray;
std::map<int, int> damageArray;
std::map<int, int> lifeArray;
std::map<int, Tyra::Vec2> pivot;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
std::vector<Sun> sun;
std::vector<NaturalSun> naturalSun;
std::vector<int> projectile;
std::vector<Card> cards;

bool zombieCreateRow[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

std::map<int, Tyra::Sprite> dm_SpritePointCollider;
std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpriteNormal;
std::map<int, Tyra::Sprite> dm_SpriteRotate;
std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;
std::map<int, Tyra::Sprite> dm_SpriteRotatePivot;

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size) {
  spriteArray[id] = Sprite();
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  loadSprite(&spriteArray[id], mode, Vec2(0.0f, 0.0f), size);
  spritesNormalRender[id] = &spriteArray[id];
}

void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle) {
  rotationSprite[id].sprite = Sprite();
  rotationSprite[id].angle = angle;
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  loadSprite(&rotationSprite[id].sprite, mode, Vec2(0.0f, 0.0f), size);
  spritesRotateRender[id] = &rotationSprite[id];
}

void deleteSprite(const int entitieID) {
  if (spriteArray.count(entitieID) == 1) {
    engine->renderer.getTextureRepository()
        .getBySpriteId(spriteArray[entitieID].id)
        ->removeLinkById(spriteArray[entitieID].id);
    spriteArray.erase(entitieID);
    if (spritesNormalRender.count(entitieID)) {
      spritesNormalRender.erase(entitieID);
    }
  } else {
    engine->renderer.getTextureRepository()
        .getBySpriteId(rotationSprite[entitieID].sprite.id)
        ->removeLinkById(rotationSprite[entitieID].sprite.id);
    rotationSprite.erase(entitieID);
    if (spritesRotateRender.count(entitieID)) {
      spritesRotateRender.erase(entitieID);
    }
  }
}

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

void BoxCollider::move(const int entityID) {
  x = offsetX + posArray[entityID].x;
  y = offsetY + posArray[entityID].y;
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

void DeckCursor::move() {
  if (engine->pad.getClicked().DpadLeft) {
    pos--;
    if (pos < 0) {
      pos = cards.size() - 1;
    }
    posArray[id].x = posArray[cards[pos].seed].x - 3;
  } else if (engine->pad.getClicked().DpadRight) {
    pos++;
    if (pos >= (int)cards.size()) {
      pos = 0;
    }
    posArray[id].x = posArray[cards[pos].seed].x - 3;
  }
}

void Card::update() {
  if (seedTimer > 0) {
    seedTimer--;
    spriteArray[seedShadow].size = Vec2(50, 70);
    spriteArray[seedShadowTimer].size.y -=
        (70.0f / 8.0f / 60.0f);  // el size Y es 70
  } else if (sunCounter >= cost) {
    spriteArray[seedShadow].size = Vec2(0, 0);
  }
}

Animation::Animation() {}

Animation::Animation(enumAnimation anim) { animID = anim; }

void Animation::update(const int entityID) {
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame >= animationDataArray[animID].maxFrame) {
      currentFrame = 0;
    }

    if (spriteArray.count(entityID) == 1) {
      activeDrawNormalSprites(entityID);
      if (draw == true) {
        updateNormalSprites(entityID);
      }
    } else {
      activeDrawRotationSprites(entityID);
      if (draw == true) {
        updateRotationSprites(entityID);
      }
    }
  }
  position(entityID);
  framesCounter++;
}

void Animation::position(const int entityID) {
  // finalPos += animPos

  if (animationDataArray[animID].position.count(currentFrame)) {
    texPosArray[entityID] = animationDataArray[animID].position[currentFrame];
  }
}

void Animation::activeDrawNormalSprites(const int entityID) {
  if (animationDataArray[animID].draw.count(currentFrame)) {
    draw = animationDataArray[animID].draw[currentFrame];
    if (draw == false) {
      spritesNormalRender.erase(entityID);
      spriteNormalIdStopRender.push_back(entityID);
    } else {
      spritesNormalRender[entityID] = &spriteArray[entityID];
    }
  }
}

void Animation::updateNormalSprites(const int entityID) {
  if (animationDataArray[animID].texture.count(currentFrame) == 1) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
      texRepo->getBySpriteId(spriteArray[entityID].id)
          ->removeLinkById(spriteArray[entityID].id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animID].texture[currentFrame]->addLink(
        spriteArray[entityID].id);
  }
  if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
    spriteArray[entityID].color.a =
        animationDataArray[animID].alpha[currentFrame] * 128;
  }
  if (animationDataArray[animID].scale.count(currentFrame) == 1) {
    spriteArray[entityID].size =
        originalSize[entityID] * animationDataArray[animID].scale[currentFrame];
  }
}

void Animation::updateRotationSprites(const int entityID) {
  if (animationDataArray[animID].texture[currentFrame] != nullptr) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(rotationSprite[entityID].sprite.id) != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
      texRepo->getBySpriteId(rotationSprite[entityID].sprite.id)
          ->removeLinkById(rotationSprite[entityID].sprite.id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animID].texture[currentFrame]->addLink(
        rotationSprite[entityID].sprite.id);
  }

  if (animationDataArray[animID].scale.count(currentFrame) == 1) {
    rotationSprite[entityID].sprite.size =
        originalSize[entityID] * animationDataArray[animID].scale[currentFrame];
  }

  if (animationDataArray[animID].angle.count(currentFrame) == 1) {
    rotationSprite[entityID].angle =
        animationDataArray[animID].angle[currentFrame];
  }
  if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
    rotationSprite[entityID].sprite.color.a =
        animationDataArray[animID].alpha[currentFrame] * 128;
  }
}

void Animation::activeDrawRotationSprites(const int entityID) {
  if (animationDataArray[animID].draw.count(currentFrame)) {
    draw = animationDataArray[animID].draw[currentFrame];
    if (draw == false) {
      spritesRotateRender.erase(entityID);
      spritesRotateIdStopRender.push_back(entityID);
    } else {
      spritesRotateRender[entityID] = &rotationSprite[entityID];
    }
  }
}

void FatherID::update(const int entityID) {
  for (unsigned int i = 0; i < id.size(); i++) {
    // finalPos += fatherPos
    finalPosArray[id[i]].x += posArray[entityID].x;
    finalPosArray[id[i]].y += posArray[entityID].y;
  }
}

void RotationSprite::update(const int entityID) {
  // finalPos += texPosArray
  // finalPos += entitiePos

  finalPosArray[entityID] += texPosArray[entityID] * scaleTexture[entityID];

  finalPosArray[entityID] += posArray[entityID];

  if (finalPosArray[entityID].x != sprite.position.x ||
      finalPosArray[entityID].y != sprite.position.y) {
    sprite.position = finalPosArray[entityID];
  }

  renderer->renderer2D.renderRotate(sprite, angle);
  finalPosArray[entityID] = Vec2(0.0f, 0.0f);
}
