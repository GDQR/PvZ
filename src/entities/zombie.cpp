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

int Zombie::move() {
  if (debug == true) {
    return 1;
  }
  if (timer > 0) {
    timer--;
  } else if (attack == false) {
    timer = 12;
    posArray[father].x--;

    boxColliderArray[id[0]].x =
        posArray[father].x + posArray[id[0]].x + 60;
    // printf("box: %f,%f\n",
    // boxColliderArray[*it->id[0]].x,boxColliderArray[*it->id[0]].y);
  }
  return 0;
}

void createZombie(Vec2 pos) {
  zombie.push_back(Zombie());
  int id = zombie.size() - 1;
  zombie[id].newZombie(ZombieNormal);
  zombie[id].father = Entities::newID();
  posArray[zombie[id].father] = pos;

  int entityID;
  int animID;
  printf("zombie anim size: %d\n",m_animID["Zombie"].size());
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
  }

  // HitBox
  boxColliderArray[zombie[id].id[0]] = BoxCollider(pos.x, pos.y + 10, 28, 50);
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].id[0], Tyra::MODE_STRETCH);  
  zombiesCreated++;
  TYRA_LOG("Zombie Debug Created");
  //   zombie.push_back(Zombie());
  //   Zombie* zom = &(zombie[zombie.size() - 1]);
  //   zom->newZombie(ZombieNormal);
  //   zom->id[0] = Entities::newID();
  //   zom->id[1] = Entities::newID();
  //   printf("zombie 0 ID: %d\n", zom->id[0]);
  //   printf("zombie 1 ID: %d\n", zom->id[1]);
  //   printf("zom pos: %f,%f\n", pos.x, pos.y);
  //   posArray[*zom->father] =
  //       Vec2(pos.x , pos.y - 20);  // Vec2(pos.x,pos.y-10);

  //   newFatherID(zom->father, zom->body[0]);
  //   //   newFatherID(zom->father,zom->body[1]);

  //   createSpriteRotate(*zom->body[0], Tyra::MODE_STRETCH, Vec2(0, 0),
  //                      Vec2(50, 50),
  //                      Vec2(0, 0));  // 80, 139 = 128,256

  //   TYRA_LOG("zombie sprite ID:
  //   %d\n",rotationSprite[*zom->body[0]].sprite.id);

  //   animationArray[*zom->body[0]] = Animation(enumAnimation::zombieWalk);
  //   animationDataArray[zombieWalk].texture[0]->addLink(
  //       rotationSprite[*zom->body[0]].sprite.id);

  //   // Life

  //   lifeArray[*zom->body[0]] = 181;

  //   // damage

  //   damageArray[*zom->body[0]] = 100;

  //   // HitBox
  //   boxColliderArray[*zom->body[0]] = BoxCollider(pos.x, pos.y + 10, 28, 50);
  //   //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  //   createDebugBoxCollider(*zom->body[0], Tyra::MODE_STRETCH);

  //   zombiesCreated++;
  //   TYRA_LOG("Zombie Created");
  // }

  // void createDebugZombie(Vec2 pos) {
  //   //   zombie.insert(zombie.begin() + zombiesCreated, Zombie());
  //   zombie.push_back(Zombie());
  //   Zombie* zom = &(zombie[zombie.size() - 1]);
  //   zom->newZombie(ZombieNormal);
  //   zom->debug = true;
  //   zom->id[0] = Entities::newID();
  //   zom->id[1] = Entities::newID();
  //   printf("zombie 0 ID: %d\n", zom->id[0]);
  //   printf("zombie 1 ID: %d\n", zom->id[1]);
  //   printf("zom pos: %f,%f\n", pos.x, pos.y);
  //   posArray[*zom->father] =
  //       Vec2(pos.x + 10, pos.y - 20);  // Vec2(pos.x,pos.y-10);

  //   newFatherID(zom->father, zom->body[0]);
  //   //   newFatherID(zom->father,zom->body[1]);

  //   createSprite(*zom->body[0], Tyra::MODE_STRETCH, Vec2(0, 0),
  //                Vec2(128, 256));  // 80, 139 = 128,256

  //   animationArray[*zom->body[0]] = Animation(enumAnimation::deb_zombieWalk);
  //   animationDataArray[deb_zombieWalk].texture[0]->addLink(
  //       spriteArray[*zom->body[0]].id);

  //   // Life

  //   lifeArray[*zom->body[0]] = 181;

  //   // damage

  //   damageArray[*zom->body[0]] = 100;

  //   // HitBox
  //   boxColliderArray[*zom->body[0]] = BoxCollider(pos.x + 60, pos.y + 10, 28,
  //   50);
  //   //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  //   createDebugBoxCollider(*zom->body[0], Tyra::MODE_STRETCH);

  //   zombiesCreated++;
  //   TYRA_LOG("Zombie Debug Created");
}
