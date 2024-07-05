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

void Animation::drawSprite(const int entitieID) {
  if (animationDataArray[animID].draw.count(currentFrame)) {
    draw = animationDataArray[animID].draw[currentFrame];
    if (spriteArray.count(entitieID) == 1) {
      if (draw == false) {
        spritesNormalRender.erase(entitieID);
        spriteNormalIdStopRender.push_back(entitieID);
      } else {
        spritesNormalRender[entitieID] = &spriteArray[entitieID];
      }
    } else {
      if (draw == false) {
        spritesRotateRender.erase(entitieID);
        spritesRotateIdStopRender.push_back(entitieID);
      } else {
        spritesRotateRender[entitieID] = &spritesRotate[entitieID];
      }
    }
  }

  if (spriteArray.count(entitieID) == 1 &&
      animationDataArray[animID].texture.count(currentFrame) == 1 &&
      draw == true) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spriteArray[entitieID].id) != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entitieID].id);
      texRepo->getBySpriteId(spriteArray[entitieID].id)
          ->removeLinkById(spriteArray[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animID].texture[currentFrame]->addLink(
        spriteArray[entitieID].id);
  } else if (animationDataArray[animID].texture.count(currentFrame) == 1 &&
             draw == true) {
    // Unlink Texture from the sprite entitie
    if (texRepo->getBySpriteId(spritesRotate[entitieID].id) != nullptr) {
      // printf("unlink sprite rotate id: %d\n", spritesRotate[entitieID].id);
      texRepo->getBySpriteId(spritesRotate[entitieID].id)
          ->removeLinkById(spritesRotate[entitieID].id);
    }

    // Link new Texture to the sprite entitie
    animationDataArray[animID].texture[currentFrame]->addLink(
        spritesRotate[entitieID].id);
  }
}

void Animation::position(const int entitieID) {
  // finalPos += animPos

  if (animationDataArray[animID].position.count(currentFrame)) {
    texPosArray[entitieID] = animationDataArray[animID].position[currentFrame];
  }
}

void Animation::angle(const int entitieID) {
  if (animationDataArray[animID].angle.count(currentFrame) == 1) {
    angles[entitieID] = animationDataArray[animID].angle[currentFrame];
  }
}
void Animation::alpha(const int entitieID) {
  if (animationDataArray[animID].alpha.count(currentFrame) == 1) {
    float alpha = animationDataArray[animID].alpha[currentFrame] * 128;
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].color.a = alpha;
    } else {
      spritesRotate[entitieID].color.a = alpha;
    }
  }
}

void Animation::scale(const int entitieID) {
  if (animationDataArray[animID].scale.count(currentFrame) == 1) {
    if (spriteArray.count(entitieID) == 1) {
      spriteArray[entitieID].size =
          originalSize[entitieID] *
          animationDataArray[animID].scale[currentFrame];
    } else {
      spritesRotate[entitieID].size =
          originalSize[entitieID] *
          animationDataArray[animID].scale[currentFrame];
    }
  }
}
