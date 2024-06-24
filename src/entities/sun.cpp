#include "entities/sun.hpp"
#include "components.hpp"

int sunsCreated = 0;
int sunCounter = 100;

// void createSun(Tyra::Vec2 position, sunCost cost, bool createdByPlant) {
// TYRA_LOG("SUN CREATED");
// sun.push_back(Sun());
// int indexpos = sun.size() - 1;
// sun[indexpos].id = Entities::newID();
// sun[indexpos].cost = cost;
// // printf("sun id: %d\n", sun[indexpos].id);

// createSprite(sun[indexpos].id, Tyra::MODE_STRETCH, position,
//              Vec2(128 / 1.5f, 128 / 1.5f));

// // HitBox
// boxColliderArray[sun[indexpos].id] =
//     BoxCollider(position.x + 31, position.y + 32, 32, 32);

// createDebugBoxCollider(sun[indexpos].id, Tyra::MODE_STRETCH);

// animationArray[sun[indexpos].id] = Animation(enumAnimation::sunAnim);
// animationDataArray[sunAnim].texture[0]->addLink(
//     spriteArray[sun[indexpos].id].id);
// if (createdByPlant == false) {
//   naturalSunIds.push_back(sun[indexpos].id);
// }
// sunsCreated++;
// }

void createSun2(Tyra::Vec2 position, sunCost cost, bool createdByPlant) {
  TYRA_LOG("SUN CREATED");
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
  // printf("position: %f,%f\n", position.x, position.y);

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

    // printf("sun id: %d\n", entitieID);
    texPosArray[entitieID] = animationDataArray[m_animID["Sun"][i]].position[0];

    if (hasAngle == true) {
      if (animationDataArray[m_animID["Sun"][i]].angle.count(0) == 0) {
        animationDataArray[m_animID["Sun"][i]].angle[0] = 0.0f;
      }
      createSpriteRotate(entitieID, Tyra::MODE_STRETCH, Vec2(0.0f, 0.0f),
                         Vec2(128 / 1.5f, 128 / 1.5f),
                         animationDataArray[m_animID["Sun"][i]].angle[0]);

      animationArray[entitieID] = Animation((enumAnimation)m_animID["Sun"][i]);
      animationDataArray[m_animID["Sun"][i]].texture[0]->addLink(
          spritesRotate[entitieID].id);

      if (animationDataArray[m_animID["Sun"][i]].scale.count(0) == 0) {
          animationDataArray[m_animID["Sun"][i]].scale[0] = 1.0f;
      }

      spritesRotate[entitieID].scale = animationDataArray[m_animID["Sun"][i]].scale[0];

      if (hasAlpha == true) {
        if (animationDataArray[m_animID["Sun"][i]].alpha.count(0) == 0) {
          animationDataArray[m_animID["Sun"][i]].alpha[0] = 1.0f;
        }
        float alpha = animationDataArray[m_animID["Sun"][i]].alpha[0] * 128;
        spritesRotate[entitieID].color.a = alpha;
      }
    } else {
      createSprite(entitieID, Tyra::MODE_STRETCH, Vec2(0.0f, 0.0f),
                   Vec2(128 / 1.5f, 128 / 1.5f));

      animationArray[entitieID] = Animation((enumAnimation)m_animID["Sun"][i]);
      animationDataArray[m_animID["Sun"][i]].texture[0]->addLink(
          spriteArray[entitieID].id);
      
      if (animationDataArray[m_animID["Sun"][i]].scale.count(0) == 0) {
          animationDataArray[m_animID["Sun"][i]].scale[0] = 1.0f;
      }

      spriteArray[entitieID].scale = animationDataArray[m_animID["Sun"][i]].scale[0];

      if (hasAlpha == true) {
        float alpha = animationDataArray[m_animID["Sun"][i]].alpha[0] * 128;
        spriteArray[entitieID].color.a = alpha;
      }
    }

    hasAlpha = false;
    hasAngle = false;
  }

  originalSize[sun[indexpos].id[0]] = Vec2(117.0f, 116.0f);
  originalSize[sun[indexpos].id[1]] = Vec2(77.0f, 79.0f);
  originalSize[sun[indexpos].id[2]] = Vec2(36.0f, 36.0f);

  spritesRotate[sun[indexpos].id[0]].size = Vec2(117.0f, 116.0f);
  spritesRotate[sun[indexpos].id[1]].size = Vec2(77.0f, 79.0f);
  spriteArray[sun[indexpos].id[2]].size = Vec2(36.0f, 36.0f);

  createDebugSprite(sun[indexpos].id[0], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[1], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[2], Tyra::MODE_STRETCH);

  // printf("sun hitbox id: %d\n", sun[indexpos].id[0]);
  // HitBox
  boxColliderArray[sun[indexpos].father] =
      BoxCollider(position.x + 31, position.y + 32, 32, 32);

  createDebugBoxCollider(sun[indexpos].father, Tyra::MODE_STRETCH);

  sunsCreated++;
}

void deleteSun(const int cursorID) {
  for (std::vector<Sun>::iterator it = sun.begin(); it != sun.end();) {
    if (boxCollision(&boxColliderArray[cursorID],
                     &boxColliderArray[it->father])) {
      printf("Deleting sun\n");
      sunCounter += it->cost;

      boxColliderArray.erase(it->father);
      deleteDebugBoxCollider(it->father);

      fatherIDArray.erase(it->father);

      for (unsigned int i = 0; i < m_animID["Sun"].size(); i++) {
        deleteDebugSprite(it->id[i]);
        deleteSprite(it->id[i]);
        animationArray.erase(it->id[i]);
        texPosArray.erase(it->id[i]);
        Entities::deleteID(it->id[i]);
      }

      // delete natural sun if exists
      for (unsigned int i = 0; i < naturalSun.size(); i++) {
        if (naturalSun[i].father == it->father) {
          naturalSun.erase(naturalSun.begin() + i);
          break;
        }
      }

      it = sun.erase(it);
      sunsCreated--;
    } else {
      it++;
    }
  }
}

void moveNaturalSun() {
  // printf("naturalSun size: %d\n", naturalSun.size());
  for (std::vector<NaturalSun>::iterator it = naturalSun.begin();
       it != naturalSun.end(); it++) {
    // printf("naturalSun id: %d\n", (it)->father);
    if (posArray[(it)->father].y < 370) {
      posArray[(it)->father].y++;
      boxColliderArray[(it)->father].y++;
      dm_SpriteBoxCollider[(it)->father].position.y =
          boxColliderArray[(it)->father].y;
    }
  }
}