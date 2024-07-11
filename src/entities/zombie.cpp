#include "entities/zombie.hpp"
#include "renderSprite/animations.hpp"
#include "systems.hpp"

int zombiesCreated = 0;

void Zombie::createSpace() {
  switch (type) {
    case ZombieNormal:
      break;

    default:
      break;
  }
}

void Zombie::newZombie(Zombie_State_enum newType) { type = newType; }

void Zombie::animation(const int entityID, const int animID) {
  switch (type) {
    case ZombieNormal:
      if (animationDataArray[animID].name == "anim_bucket" ||
          animationDataArray[animID].name == "anim_cone" ||
          animationDataArray[animID].name == "anim_screendoor" ||
          animationDataArray[animID].name == "Zombie_duckytube" ||
          animationDataArray[animID].name == "Zombie_whitewater" ||
          animationDataArray[animID].name == "Zombie_whitewater2" ||
          animationDataArray[animID].name == "Zombie_outerarm_screendoor" ||
          animationDataArray[animID].name ==
              "Zombie_innerarm_screendoor_hand" ||
          animationDataArray[animID].name == "Zombie_mustache" ||
          animationDataArray[animID].name == "Zombie_innerarm_screendoor" ||
          animationDataArray[animID].name == "Zombie_flaghand") {
        animationArray[entityID].draw = false;
        setSprite(entityID, animID);
        animationArray.erase(entityID);
        animationIdStopRender.push_back(entityID);
        printf("encontre anim_bucket o anim_cone\n");
      }
      break;
    default:
      break;
  }
}

int Zombie::move() {
  if (debug == true) {
    return 1;
  }
  if (timer > 0) {
    timer--;
  } else if (attack == false) {
    timer = 12;
    posArray[father].x--;

    boxColliderArray[id[0]].x = posArray[father].x + posArray[id[0]].x + 60;
    // printf("box: %f,%f\n",
    // boxColliderArray[*it->id[0]].x,boxColliderArray[*it->id[0]].y);
  }
  return 0;
}

void Zombie::damage(const int entityID) {
  lifeArray[id[0]] -= damageArray[entityID];
}

bool Zombie::erase() {
  if (lifeArray[id[0]] <= 0) {
    posArray.erase(father);

    Entities::deleteID(father);

    for (unsigned int i = 0; i < m_animID["Zombie"].size(); i++) {
      posArray.erase(id[i]);
      deleteFatherID(&father, &id[i]);
      deleteSprite(id[i]);
      animationArray.erase(id[i]);
      texPosArray.erase(id[i]);
      Entities::deleteID(id[i]);
    }
    fatherIDArray.erase(father);
    lifeArray.erase(id[0]);
    damageArray.erase(id[0]);
    boxColliderArray.erase(id[0]);
    deleteDebugBoxCollider(id[0]);
    zombiesCreated--;
    return true;
  }
  return false;
}
void createZombie(Vec2 pos) {
  zombie.push_back(Zombie());
  int id = zombie.size() - 1;
  zombie[id].newZombie(ZombieNormal);
  zombie[id].father = Entities::newID();
  posArray[zombie[id].father] = pos;

  int entityID;
  int animID;
  printf("zombie anim size: %d\n", m_animID["Zombie"].size());
  for (unsigned int i = 0; i < m_animID["Zombie"].size(); i++) {
    zombie[id].id.push_back(Entities::newID());
    entityID = zombie[id].id[i];
    animID = m_animID["Zombie"][i];
    // printf("i: %d\n",i);
    // printf("Zombie ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&zombie[id].father, &entityID);
    loadAnimationSprite(entityID, animID);
    animationArray[entityID].firstFrame = 44;
    animationArray[entityID].lastFrame = 91;
    animationArray[entityID].currentFrame = 44;
    animationArray[entityID].draw = true;
    zombie[id].animation(entityID, animID);
  }

  // Life
  lifeArray[zombie[id].id[0]] = 181;

  // damage
  damageArray[zombie[id].id[0]] = 100;

  // HitBox
  boxColliderArray[zombie[id].id[0]] = BoxCollider(pos.x, pos.y + 10, 28, 50);
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].id[0], Tyra::MODE_STRETCH);
  zombiesCreated++;
  TYRA_LOG("Zombie Debug Created");
}
