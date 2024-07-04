#include "components.hpp"
#include <iostream>

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
std::map<int, Tyra::Sprite> spritesRotate;
std::map<int, Tyra::Sprite*> spritesRotateRender;
std::vector<int> spritesRotateIdStopRender;
std::map<int, Tyra::Vec2> angles;
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

bool zombieCreateRow[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

std::map<int, Tyra::Sprite> dm_SpritePointCollider;
std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpriteNormal;
std::map<int, Tyra::Sprite> dm_SpriteRotate;
std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;
std::map<int, Tyra::Sprite> dm_SpriteRotatePivot;

Animation::Animation() {}

Animation::Animation(enumAnimation anim) { animID = anim; }

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
  spritesRotate[id] = Sprite();
  posArray[id] = position;
  finalPosArray[id] = Vec2(0, 0);
  angles[id] = angle;
  loadSprite(&spritesRotate[id], mode, Vec2(0.0f, 0.0f), size);
  spritesRotateRender[id] = &spritesRotate[id];
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
        .getBySpriteId(spritesRotate[entitieID].id)
        ->removeLinkById(spritesRotate[entitieID].id);
    spritesRotate.erase(entitieID);
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
