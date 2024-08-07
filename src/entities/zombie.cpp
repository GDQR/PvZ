#include "entities/entities.hpp"
#include "entities/zombie.hpp"
#include "components.hpp"
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
        animationArray[entityID].draw = (int) enumDraw::noDraw;
        setSprite(entityID, animationArray[entityID].draw);
        deleteAnimation(entityID);
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
    posArray[father].x -= speedArray[id[0]];

    boxColliderArray[id[0]].x = posArray[father].x + posArray[id[0]].x + 60;
    // printf("box: %f,%f\n",
    // boxColliderArray[*it->id[0]].x,boxColliderArray[*it->id[0]].y);
  }
  return 0;
}

void Zombie::attackPlant() {
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
            // printf("anim attack id: %d\n",m_animID["Zombie"][j]);
            animationDataArray[m_animID["Zombie"][j]].setAnimationState(
                id[j], normalZombieAttack);
          }
        }
      }

      if (attackTimer > 0) {
        attackTimer--;
      } else {
        attackTimer = 80;
        printf("comiendo planta\n");
        lifeArray[plant[i].father] -= damageArray[id[0]];
        if (lifeArray[plant[i].father] <= 0) {
          printf("borre planta id: %d\n", plant[i].father);
          plant[i].erase(i);
          attack = false;
          for (unsigned int j = 0; j < id.size(); j++) {
            if (animationArray.count(id[j]) == 1) {
              // printf("anim attack id: %d\n",id[j]);
              animationDataArray[m_animID["Zombie"][j]].setAnimationState(
                  id[j], normalZombieWalk);
            }
          }
          // animationArray[id[0]].animID = zombieWalk;
        }
      }
      break;
    }
  }
}

void Zombie::damage(const int entityID) {
  damaged = true;
  lifeArray[id[0]] -= damageArray[entityID];
  printf("dano zombie\n");
  for (unsigned int j = 0; j < id.size(); j++) {
    if (animationArray.count(id[j]) == 1) {
      // printf("anim attack id: %d\n",m_animID["Zombie"][j]);
      if (spriteArray.count(id[j]) == 1) {
        spriteArray[id[j]].color = Tyra::Color(255, 255, 255, 128);
      } else {
        rotationSprite[id[j]].sprite.color = Tyra::Color(255, 255, 255, 128);
      }
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
      } else {
        if (rotationSprite[id[j]].sprite.color.r > 128.0f &&
            rotationSprite[id[j]].sprite.color.g > 128.0f &&
            rotationSprite[id[j]].sprite.color.b > 128.0f) {
          rotationSprite[id[j]].sprite.color -= 5;
          rotationSprite[id[j]].sprite.color.a = 128;
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

    for (unsigned int i = 0; i < m_animID["Zombie"].size(); i++) {
      deletePosArray(id[i]);
      deleteFatherIDChild(&father, &id[i]);
      if (spriteArray.count(id[i]) == 1 || rotationSprite.count(id[i]) == 1){
        deleteSprite(id[i]);
      }
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
void createZombie(Vec2 pos) {
  zombie.push_back(Zombie());
  int id = zombie.size() - 1;
  zombie[id].newZombie(ZombieNormal);
  zombie[id].father = Entities::newID();
  posArray.insert(zombie[id].father, pos);

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
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             normalZombieWalk);
    // animationDataArray[animID].setAnimationState(entityID, normalZombieWalk);
    // animationArray[entityID].draw = true;
    zombie[id].animation(entityID, animID);
  }

  // Life
  lifeArray[zombie[id].id[0]] = 181;

  // damage
  damageArray[zombie[id].id[0]] = 100;

  // speed
  speedArray[zombie[id].id[0]] = 1;

  // HitBox
  boxColliderArray[zombie[id].id[0]] = BoxCollider(pos.x, pos.y + 10, 28, 50);
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].id[0], Tyra::MODE_STRETCH);
  zombiesCreated++;
  TYRA_LOG("Zombie Debug Created");
}
