#include "entities/entities.hpp"
#include "entities/zombie.hpp"
#include "components.hpp"
#include "systems.hpp"

int zombiesCreated = 0;

void Zombie::createSpace() {
  switch (type) {
    case Zombie_State_enum::normalZombie:
      break;

    default:
      break;
  }
}

void Zombie::newZombie(Zombie_State_enum newType) { type = newType; }

void Zombie::animation(const int entityID, const int animID) {
  switch (type) {
    case Zombie_State_enum::normalZombie:
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
        animationArray[entityID].draw = (int) enumDraw::noDraw;
        setSprite(entityID, animationArray[entityID].draw);
        deleteAnimation(entityID);
        animationIdStopRender.push_back(entityID);
        // printf("encontre anim_bucket o anim_cone\n");
      }
      break;
    case Zombie_State_enum::flagZombie:
      if (animationDataArray[animID].name == "anim_bucket" ||
          animationDataArray[animID].name == "anim_cone" ||
          animationDataArray[animID].name == "Zombie_whitewater2" ||
          animationDataArray[animID].name == "Zombie_outerarm_screendoor" ||
          animationDataArray[animID].name ==
              "Zombie_innerarm_screendoor_hand" ||
          animationDataArray[animID].name == "anim_screendoor" ||
          animationDataArray[animID].name == "Zombie_mustache" ||
          animationDataArray[animID].name == "Zombie_whitewater" ||
          animationDataArray[animID].name == "Zombie_duckytube" || // can use in water
          animationDataArray[animID].name == "anim_innerarm1" ||
          animationDataArray[animID].name == "anim_innerarm2" ||
          animationDataArray[animID].name == "anim_innerarm3") {
        animationArray[entityID].draw = (int) enumDraw::noDraw;
        setSprite(entityID, animationArray[entityID].draw);
        deleteAnimation(entityID);
        animationIdStopRender.push_back(entityID);
        // printf("encontre anim_bucket o anim_cone\n");
      }
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
    posArray[father].x -= speedArray[id[0]];

    boxColliderArray[id[0]].x = posArray[father].x + posArray[id[0]].x + 60;
    // printf("box: %f,%f\n",
    // boxColliderArray[*it->id[0]].x,boxColliderArray[*it->id[0]].y);
  }
  return 0;
}

int Zombie::attackPlant() {
  for (int i = 0; i < 45; i++) {
    if (plant[i].type == NonePlant) {
      continue;
    }
    if (boxColliderArray[plant[i].father].collision(&boxColliderArray[id[0]]) ==
        true) {
      if (attack == false) {
        attack = true;
        for (unsigned int j = 0; j < id.size(); j++) {
          if (animationArray.count(id[j]) == 1) {
            animationArray[id[j]].setAnimation(normalZombieAttack);
            // printf("anim attack id: %d\n",m_animID["Zombie"][j]);
            animationDataArray[m_animID[enumAnimName::ZombieAnimName][j]].setAnimationState(
                id[j], normalZombieAttack);
          }
        }
      }

      if (attackTimer > 0) {
        attackTimer--;
      } else {
        attackTimer = 80;
        if(lifeArray.count(plant[i].father) == 1){
          printf("comiendo planta\n");
          lifeArray[plant[i].father] -= damageArray[id[0]];
          if (lifeArray[plant[i].father] <= 0) {
            printf("borre planta id: %d\n", plant[i].father);
            plant[i].erase();
            attack = false;
            for (unsigned int j = 0; j < id.size(); j++) {
              if (animationArray.count(id[j]) == 1) {
                // printf("anim attack id: %d\n",id[j]);
                animationArray[id[j]].setAnimation(normalZombieWalk);
                animationDataArray[m_animID[enumAnimName::ZombieAnimName][j]].setAnimationState(
                    id[j], normalZombieWalk);
              }
            }
            // animationArray[id[0]].animID = zombieWalk;
          }
        }
      }
      return 0;
    }
  }
  
  if (attack == true) {
    attack = false;
    for (unsigned int j = 0; j < id.size(); j++) {
      if (animationArray.count(id[j]) == 1) {
        // printf("anim attack id: %d\n",id[j]);
        animationArray[id[j]].setAnimation(normalZombieWalk);
        animationDataArray[m_animID[enumAnimName::ZombieAnimName][j]].setAnimationState(
            id[j], normalZombieWalk);
      }
    }
  }

  return 1;
}

void Zombie::damage(const int entityID) {
  damaged = true;
  lifeArray[id[0]] -= damageArray[entityID];
  for (unsigned int j = 0; j < id.size(); j++) {
    if (animationArray.count(id[j]) == 1) {
      // printf("anim attack id: %d\n",m_animID["Zombie"][j]);  
      spriteArray[id[j]].color = Tyra::Color(255, 255, 255, 128);
    }
  }
}

// this maybe can be better
int Zombie::normalColor() {
  if (damaged == false) {
    return 1;
  }
  for (unsigned int j = 0; j < id.size(); j++) {
    if (animationArray.count(id[j]) == 1) {
      if (spriteArray.count(id[j]) == 1) {
        if (spriteArray[id[j]].color.r > 128.0f &&
            spriteArray[id[j]].color.g > 128.0f &&
            spriteArray[id[j]].color.b > 128.0f) {
          spriteArray[id[j]].color -= 5;
          spriteArray[id[j]].color.a = 128;
        } else {
          damaged = false;
        }
      }
    }
  }
  return 0;
}

bool Zombie::erase() {
  if (lifeArray[id[0]] <= 0) {
    deletePosArray(father);

    for (unsigned int i = 0; i < m_animID[enumAnimName::ZombieAnimName].size(); i++) {
      deletePosArray(id[i]);
      deleteFinalPosArray(id[i]);
      deleteFatherIDChild(&father, &id[i]);

      deleteSprite(id[i]);
      
      if (animationArray.count(id[i]) == 1){
        deleteAnimation(id[i]);
      }
      deleteTexPosArray(id[i]);
      Entities::deleteID(id[i]);
    }
    deleteFatherID(&father);
    Entities::deleteID(father);
    lifeArray.erase(id[0]);
    damageArray.erase(id[0]);
    boxColliderArray.erase(id[0]);
    deleteDebugBoxCollider(id[0]);
    zombiesCreated--;
    return true;
  }
  return false;
}

void createNormalZombie(const int id, Tyra::Vec2 pos){
  int entityID;
  int animID;
  printf("zombie anim size: %d\n", m_animID[enumAnimName::ZombieAnimName].size());
  for (unsigned int i = 0; i < m_animID[enumAnimName::ZombieAnimName].size(); i++) {
    zombie[id].id.push_back(Entities::newID());
    entityID = zombie[id].id[i];
    animID = m_animID[enumAnimName::ZombieAnimName][i];
    // printf("i: %d\n",i);
    // printf("Zombie ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&zombie[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             normalZombieWalk);
    // animationDataArray[animID].setAnimationState(entityID, normalZombieWalk);
    // animationArray[entityID].draw = true;
    zombie[id].animation(entityID, animID);
  }

  // Life
  lifeArray.insert(zombie[id].id[0], 200); //270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[zombie[id].id[0]] = 100;

  // speed
  speedArray[zombie[id].id[0]] = 1;

  // HitBox
  boxColliderArray[zombie[id].id[0]] = BoxCollider(pos.x, pos.y + 10, 28, 50);
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].id[0], Tyra::MODE_STRETCH);
}

void createFlagZombie(const int id, Tyra::Vec2 pos){
  int entityID;
  int animID;
  printf("zombie anim size: %d\n", m_animID[enumAnimName::ZombieAnimName].size());
  for (unsigned int i = 0; i < m_animID[enumAnimName::ZombieAnimName].size(); i++) {
    zombie[id].id.push_back(Entities::newID());
    entityID = zombie[id].id[i];
    animID = m_animID[enumAnimName::ZombieAnimName][i];
    // printf("i: %d\n",i);
    // printf("Zombie ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&zombie[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             normalZombieWalk);
    // animationDataArray[animID].setAnimationState(entityID, normalZombieWalk);
    // animationArray[entityID].draw = true;
    zombie[id].animation(entityID, animID);
  }

  // Life
  lifeArray.insert(zombie[id].id[0], 200); //270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[zombie[id].id[0]] = 100;

  // speed
  speedArray[zombie[id].id[0]] = 1;

  // HitBox
  boxColliderArray[zombie[id].id[0]] = BoxCollider(pos.x, pos.y + 10, 28, 50);
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].id[0], Tyra::MODE_STRETCH);
}

void createZombie(Tyra::Vec2 pos, const Zombie_State_enum type) {
  zombie.push_back(Zombie());
  int id = zombie.size() - 1;
  zombie[id].newZombie(type);
  zombie[id].father = Entities::newID();
  posArray.insert(zombie[id].father, pos);
  printf("zombie father id: %d\n",zombie[id].father);
  
  if(type == Zombie_State_enum::normalZombie){
    createNormalZombie(id, pos);
  }else if(type == Zombie_State_enum::flagZombie){
    createFlagZombie(id, pos);
  }

  zombiesCreated++;
  TYRA_LOG("Zombie Debug Created");
}
