#include "entities/sun.hpp"
#include "systems.hpp"

int sunsCreated = 0;
int sunCounter = 1000;
int sunTimer = 60 * 6;
SunManager sunManager;

void SunManager::create(Tyra::Vec2 position, sunCost cost, bool createdByPlant) {
  sun.push_back(Sun());
  int indexpos = sun.size() - 1;
  sun[indexpos].cost = cost;
  sun[indexpos].father = Entities::newID();
  posArray[sun[indexpos].father] = position;

  int entitieID;
  bool hasAngle = false;
  bool hasAlpha = false;

  if (createdByPlant == false) {
    int naturalSunID = naturalSun.size();
    naturalSun.push_back(NaturalSun());
    naturalSun[naturalSunID].father = sun[indexpos].father;
  }

  for (unsigned int i = 0; i < m_animID["Sun"].size(); i++) {
    sun[indexpos].id.push_back(Entities::newID());

    entitieID = sun[indexpos].id[i];

    newFatherID(&sun[indexpos].father, &sun[indexpos].id[i]);

    for (unsigned int j = 0;
         j < animationDataArray[m_animID["Sun"][i]].maxFrame; j++) {
      if (animationDataArray[m_animID["Sun"][i]].alpha.count(j) == true) {
        hasAlpha = true;
      }
      if (animationDataArray[m_animID["Sun"][i]].angle.count(j) == true) {
        hasAngle = true;
      }
      if (hasAngle == true && hasAlpha == true) {
        break;
      }
    }

    texPosArray[entitieID] = animationDataArray[m_animID["Sun"][i]].position[0];

    if (hasAngle == true) {
      if (animationDataArray[m_animID["Sun"][i]].angle.count(0) == 0) {
        animationDataArray[m_animID["Sun"][i]].angle[0] = Vec2(0.0f, 0.0f);
      }
      createSpriteRotate(entitieID, Tyra::MODE_STRETCH, Vec2(0.0f, 0.0f),
                         Vec2(0, 0),
                         animationDataArray[m_animID["Sun"][i]].angle[0]);

      animationArray[entitieID] = Animation((enumAnimation)m_animID["Sun"][i]);
      animationDataArray[m_animID["Sun"][i]].texture[0]->addLink(
          spritesRotate[entitieID].id);

      originalSize[entitieID] =
          Vec2(animationDataArray[m_animID["Sun"][i]].texture[0]->getWidth(),
               animationDataArray[m_animID["Sun"][i]].texture[0]->getHeight());

      if (animationDataArray[m_animID["Sun"][i]].scale.count(0) == 0) {
        animationDataArray[m_animID["Sun"][i]].scale[0] = Vec2(1.0f, 1.0f);
      }

      spritesRotate[entitieID].size =
          originalSize[entitieID] *
          animationDataArray[animationArray[entitieID].animID].scale[0];

      if (hasAlpha == true) {
        if (animationDataArray[m_animID["Sun"][i]].alpha.count(0) == 0) {
          animationDataArray[m_animID["Sun"][i]].alpha[0] = 1.0f;
        }
        float alpha = animationDataArray[m_animID["Sun"][i]].alpha[0] * 128;
        spritesRotate[entitieID].color.a = alpha;
      }
    } else {
      createSprite(entitieID, Tyra::MODE_STRETCH, Vec2(0.0f, 0.0f), Vec2(0, 0));

      animationArray[entitieID] = Animation((enumAnimation)m_animID["Sun"][i]);
      animationDataArray[m_animID["Sun"][i]].texture[0]->addLink(
          spriteArray[entitieID].id);

      originalSize[entitieID] =
          Vec2(animationDataArray[m_animID["Sun"][i]].texture[0]->getWidth(),
               animationDataArray[m_animID["Sun"][i]].texture[0]->getHeight());

      if (animationDataArray[m_animID["Sun"][i]].scale.count(0) == 0) {
        animationDataArray[m_animID["Sun"][i]].scale[0] = Vec2(1.0f, 1.0f);
      }

      spriteArray[entitieID].size =
          originalSize[entitieID] *
          animationDataArray[animationArray[entitieID].animID].scale[0];

      if (hasAlpha == true) {
        float alpha = animationDataArray[m_animID["Sun"][i]].alpha[0] * 128;
        spriteArray[entitieID].color.a = alpha;
      }
    }

    hasAlpha = false;
    hasAngle = false;
  }

  // spritesRotate[sun[indexpos].id[0]].size = Vec2(128.0f/2, 128.0f/2);
  // spritesRotate[sun[indexpos].id[1]].size = Vec2(128.0f/2, 128.0f/2);
  // spriteArray[sun[indexpos].id[2]].size = Vec2(64.0f/2, 64.0f/2);

  scaleTexture[sun[indexpos].id[0]] =
      Vec2(originalSize[sun[indexpos].id[0]].x /
               animationDataArray[m_animID["Sun"][0]].texture[0]->getWidth(),
           originalSize[sun[indexpos].id[0]].y /
               animationDataArray[m_animID["Sun"][0]].texture[0]->getHeight());
  scaleTexture[sun[indexpos].id[1]] =
      Vec2(originalSize[sun[indexpos].id[1]].x /
               animationDataArray[m_animID["Sun"][1]].texture[0]->getWidth(),
           originalSize[sun[indexpos].id[1]].y /
               animationDataArray[m_animID["Sun"][1]].texture[0]->getHeight());
  scaleTexture[sun[indexpos].id[2]] =
      Vec2(originalSize[sun[indexpos].id[2]].x /
               animationDataArray[m_animID["Sun"][2]].texture[0]->getWidth(),
           originalSize[sun[indexpos].id[2]].y /
               animationDataArray[m_animID["Sun"][2]].texture[0]->getHeight());

  // printf("sun sizeX: %f, sizeY: %f\n", spriteArray[sun[indexpos].id[2]].size.x*0.8f,spriteArray[sun[indexpos].id[2]].size.y*0.8f);
  // printf("scaleTexture: %s\n", scaleTexture[sun[indexpos].id[2]].getPrint().c_str());
  createDebugSprite(sun[indexpos].id[0], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[1], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[2], Tyra::MODE_STRETCH);

  createDebugSpritePivot(sun[indexpos].id[0], Tyra::MODE_STRETCH);
  createDebugSpritePivot(sun[indexpos].id[1], Tyra::MODE_STRETCH);
  createDebugSpritePivot(sun[indexpos].id[2], Tyra::MODE_STRETCH);

  // printf("sun hitbox id: %d\n", sun[indexpos].id[0]);
  // HitBox
  boxColliderArray[sun[indexpos].father] =
      BoxCollider(position.x + texPosArray[entitieID].x,
                  position.y + texPosArray[entitieID].y, 32, 32);
  createDebugBoxCollider(sun[indexpos].father, Tyra::MODE_STRETCH);

  sunsCreated++;
}

bool Sun::erase(const int cursorID) {
  if (boxCollision(&boxColliderArray[cursorID], &boxColliderArray[father])) {
    printf("Deleting sun\n");
    sunCounter += cost;

    boxColliderArray.erase(father);
    deleteDebugBoxCollider(father);

    fatherIDArray.erase(father);

    for (unsigned int i = 0; i < m_animID["Sun"].size(); i++) {
      deleteDebugSprite(id[i]);
      deleteDebugSpritePivot(id[i]);
      deleteSprite(id[i]);
      animationArray.erase(id[i]);
      texPosArray.erase(id[i]);
      Entities::deleteID(id[i]);
    }

    // delete natural sun if exists
    for (unsigned int i = 0; i < naturalSun.size(); i++) {
      if (naturalSun[i].father == father) {
        naturalSun.erase(naturalSun.begin() + i);
        break;
      }
    }
    sunsCreated--;
    return true;
  }
  return false;
}

void NaturalSun::move() {
  if (posArray[father].y < 370) {
    posArray[father].y++;
    boxColliderArray[father].y++;
    dm_SpriteBoxCollider[father].position.y = boxColliderArray[father].y;
  }
}

void SunManager::createByTime() {
  if (sunTimer > 0) {
    sunTimer--;
  } else {
    sunTimer = 60 * 6;  // 6 seconds
    // min:50 max:420
    float x = 50 + rand() % 420;
    create(Vec2(x, 10), sunCost::normalSun, false);
  }
}
void SunManager::erase(const int cursorID) {
  for (std::vector<Sun>::iterator it = sun.begin(); it != sun.end();) {
    if (it->erase(cursorID) == true) {
      it = sun.erase(it);
    } else {
      it++;
    }
  }
}
void SunManager::updateNaturalSun() {
  for (std::vector<NaturalSun>::iterator it = naturalSun.begin();
       it != naturalSun.end(); it++) {
    it->move();
  }
}