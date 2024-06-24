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
  int entitieID;
  int naturalSunID = -1;
  bool hasAngle = false;
  bool hasAlpha = false;

  if (createdByPlant == false) {
    naturalSunID = naturalSun.size();
    naturalSun.push_back(NaturalSun());
  }

  for (unsigned int i = 0; i < m_animID["Sun"].size(); i++) {
    sun[indexpos].id.push_back(Entities::newID());

    entitieID = sun[indexpos].id[i];

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
      if(animationDataArray[m_animID["Sun"][i]].angle.count(0) == 0){
        animationDataArray[m_animID["Sun"][i]].angle[0] = 0.0f;
      }
      createSpriteRotate(entitieID, Tyra::MODE_STRETCH, position,
                         Vec2(128 / 1.5f, 128 / 1.5f),
                         animationDataArray[m_animID["Sun"][i]].angle[0]);
      
      animationArray[entitieID] = Animation((enumAnimation)m_animID["Sun"][i]);
      animationDataArray[m_animID["Sun"][i]].texture[0]->addLink(
          spritesRotate[entitieID].id);
      
      if (hasAlpha == true) {
        if(animationDataArray[m_animID["Sun"][i]].alpha.count(0) == 0){
          animationDataArray[m_animID["Sun"][i]].alpha[0] = 1.0f;
        }
        float alpha = animationDataArray[m_animID["Sun"][i]].alpha[0] * 128;
        spritesRotate[entitieID].color.a = alpha;
      }
    } else {
      createSprite(entitieID, Tyra::MODE_STRETCH, position,
                   Vec2(128 / 1.5f, 128 / 1.5f));

      animationArray[entitieID] = Animation((enumAnimation)m_animID["Sun"][i]);
      animationDataArray[m_animID["Sun"][i]].texture[0]->addLink(
          spriteArray[entitieID].id);

      if (hasAlpha == true) {
        float alpha = animationDataArray[m_animID["Sun"][i]].alpha[0] * 128;
        spriteArray[entitieID].color.a = alpha;
      }
    }

    if (naturalSunID != -1) {
      naturalSun[naturalSunID].id.push_back(entitieID);
    }

    hasAlpha = false;
    hasAngle = false;
  }

  originalSize[sun[indexpos].id[0]] = Vec2(117.0f, 116.0f);
  originalSize[sun[indexpos].id[1]] = Vec2(77.0f, 79.0f);
  originalSize[sun[indexpos].id[2]] = Vec2(36.0f, 36.0f);

  spritesRotate[sun[indexpos].id[0]].size = Vec2(117.0f , 116.0f);
  spritesRotate[sun[indexpos].id[1]].size = Vec2(77.0f, 79.0f);
  spriteArray[sun[indexpos].id[2]].size = Vec2(36.0f, 36.0f);

  createDebugSprite(sun[indexpos].id[0], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[1], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[2], Tyra::MODE_STRETCH);

  // printf("sun hitbox id: %d\n", sun[indexpos].id[0]);
  // HitBox
  boxColliderArray[sun[indexpos].id[0]] =
      BoxCollider(position.x + 31, position.y + 32, 32, 32);

  createDebugBoxCollider(sun[indexpos].id[0], Tyra::MODE_STRETCH);

  sunsCreated++;
}

void deleteSun(const int cursorID) {
  for (std::vector<Sun>::iterator it = sun.begin(); it != sun.end();) {
    if (boxCollision(&boxColliderArray[cursorID],
                     &boxColliderArray[it->id[0]])) {
      printf("Deleting sun\n");
      sunCounter += it->cost;

      boxColliderArray.erase(it->id[0]);
      deleteDebugBoxCollider(it->id[0]);

      for (unsigned int i = 0; i < m_animID["Sun"].size(); i++) {
        deleteDebugSprite(it->id[i]);
        deleteSprite(it->id[i]);
        animationArray.erase(it->id[i]);
        texPosArray.erase(it->id[i]);
        Entities::deleteID(it->id[i]);
      }

      // delete natural sun if exists
      for (unsigned int i = 0; i < naturalSun.size(); i++) {
        if (naturalSun[i].id[0] == it->id[0]) {
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
    // printf("naturalSun id: %d\n", (it)->id[0]);
    for (unsigned int i = 0; i < m_animID["Sun"].size(); i++) {
      if (posArray[(it)->id[i]].y < 370) {
        posArray[(it)->id[i]].y++;
        boxColliderArray[(it)->id[i]].y++;
      }
    }

    dm_SpriteBoxCollider[(it)->id[0]].position.y =
        boxColliderArray[(it)->id[0]].y;
  }
}