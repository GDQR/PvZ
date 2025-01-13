#include "entities/sun.hpp"
#include "components.hpp"
#include "entities/entities.hpp"
#include "systems.hpp"


int sunsCreated = 0;
int sunCounter = 1000;
int sunTimer = 60 * 6;
SunManager sunManager;

void SunManager::create(Tyra::Vec2 position, sunCost cost,
                        bool createdByPlant) {
  sun.push_back(Sun());
  int indexpos = sun.size() - 1;
  sun[indexpos].cost = cost;
  sun[indexpos].father = Entities::newID();
  posArray.insert(sun[indexpos].father, position);

  fatherIDArray.insert(sun[indexpos].father, FatherID());

  int entityID;
  int animID;

  if (createdByPlant == false) {
    int naturalSunID = naturalSun.size();
    naturalSun.push_back(NaturalSun());
    naturalSun[naturalSunID].father = sun[indexpos].father;
  }

  for (unsigned int i = 0; i < m_animID[AnimIndex::Sun].size(); i++) {
    sun[indexpos].id.push_back(Entities::newID());

    entityID = sun[indexpos].id[i];
    animID = m_animID[AnimIndex::Sun][i];

    newFatherID(&sun[indexpos].father, &sun[indexpos].id[i]);
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             Tyra::Vec2(0.5f, 0.5f), 1, 1);

    animationArray[entityID].lastFrame = animationDataArray[animID].maxFrame;
  }

  createDebugSprite(sun[indexpos].id[0], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[1], Tyra::MODE_STRETCH);
  createDebugSprite(sun[indexpos].id[2], Tyra::MODE_STRETCH);

  createDebugSpritePivot(sun[indexpos].id[0], Tyra::MODE_STRETCH);
  createDebugSpritePivot(sun[indexpos].id[1], Tyra::MODE_STRETCH);
  createDebugSpritePivot(sun[indexpos].id[2], Tyra::MODE_STRETCH);

  // printf("sun hitbox id: %d\n", sun[indexpos].id[0]);
  // HitBox
  boxColliderArray[sun[indexpos].father] =
      BoxCollider(position.x + texPosArray[entityID].x,
                  position.y + texPosArray[entityID].y, 32, 32);
  createDebugBoxCollider(sun[indexpos].father, Tyra::MODE_STRETCH);

  sunsCreated++;
}

bool Sun::erase(const int cursorID) {
  if (boxColliderArray[cursorID].collision(&boxColliderArray[father])) {
    printf("Deleting sun\n");
    sunCounter += cost;

    boxColliderArray.erase(father);
    deleteDebugBoxCollider(father);

    for (unsigned int i = 0; i < m_animID[AnimIndex::Sun].size(); i++) {
      deleteDebugSprite(id[i]);
      deleteDebugSpritePivot(id[i]);
      deleteSprite(id[i]);
      deleteAnimation(id[i]);
      deleteTexPosArray(id[i]);
      deleteFatherIDChild(&father, &id[i]);
      Entities::deleteID(id[i]);
    }

    // delete natural sun if exists
    for (unsigned int i = 0; i < naturalSun.size(); i++) {
      if (naturalSun[i].father == father) {
        naturalSun.erase(naturalSun.begin() + i);
        break;
      }
    }

    deleteFatherID(&father);
    Entities::deleteID(father);
    sunsCreated--;
    return true;
  }
  return false;
}

void NaturalSun::move() {
  if (posArray[father].y < 370) {
    posArray[father].y++;
    boxColliderArray[father].y++;
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