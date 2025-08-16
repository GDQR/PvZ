#include "PVZ.hpp"

std::vector<ZombieAnimation> zombieAnims;
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

const char* anim_bucket = "anim_bucket";
const char* anim_cone = "anim_cone";
const char* anim_hair = "anim_hair";
const char* anim_screendoor = "anim_screendoor";
const char* Zombie_duckytube = "Zombie_duckytube";
const char* anim_innerarm1 = "anim_innerarm1";
const char* anim_innerarm2 = "anim_innerarm2";
const char* anim_innerarm3 = "anim_innerarm3";
const char* Zombie_whitewater = "Zombie_whitewater";
const char* Zombie_whitewater2 = "Zombie_whitewater2";
const char* Zombie_outerarm_screendoor = "Zombie_outerarm_screendoor";
const char* Zombie_innerarm_screendoor_hand = "Zombie_innerarm_screendoor_hand";
const char* Zombie_mustache = "Zombie_mustache";
const char* anim_tongue = "anim_tongue";
const char* Zombie_innerarm_screendoor = "Zombie_innerarm_screendoor";
const char* Zombie_flaghand = "Zombie_flaghand";
void SetZombieAnimation(const int entityID, const int animID, const Zombie_State_enum type) {
  switch (type) {
    case Zombie_State_enum::normalZombie:
      if ((strcmp(animationDataArray[animID].name, anim_bucket)==0) ||
      (strcmp(animationDataArray[animID].name, anim_cone)==0) ||
      (strcmp(animationDataArray[animID].name, anim_screendoor)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_duckytube)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_whitewater)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_whitewater2)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_outerarm_screendoor)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor_hand)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_mustache)==0) ||
      (strcmp(animationDataArray[animID].name, anim_tongue)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor)==0) ||
      (strcmp(animationDataArray[animID].name, Zombie_flaghand)==0)) {
        setSprite(entityID, (int)enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      break;
    case Zombie_State_enum::flagZombie:
      if ((strcmp(animationDataArray[animID].name, anim_bucket)==0) ||
        (strcmp(animationDataArray[animID].name, anim_cone)==0) ||
        (strcmp(animationDataArray[animID].name, Zombie_whitewater2)==0) ||
        (strcmp(animationDataArray[animID].name, Zombie_outerarm_screendoor)==0) ||
        (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor_hand)==0) ||
        (strcmp(animationDataArray[animID].name, anim_screendoor)==0) ||
        (strcmp(animationDataArray[animID].name, Zombie_mustache)==0) ||
        (strcmp(animationDataArray[animID].name, anim_tongue)==0) ||
        (strcmp(animationDataArray[animID].name, Zombie_whitewater)==0) ||
        (strcmp(animationDataArray[animID].name, Zombie_duckytube)==0) || // can use in water
        (strcmp(animationDataArray[animID].name, anim_innerarm1)==0) ||
        (strcmp(animationDataArray[animID].name, anim_innerarm2)==0) ||
        (strcmp(animationDataArray[animID].name, anim_innerarm3)==0)) {
        setSprite(entityID, (int)enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      break;
    case Zombie_State_enum::coneheadZombie:
      if ((strcmp(animationDataArray[animID].name, anim_bucket)==0) ||
          (strcmp(animationDataArray[animID].name, anim_hair)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_outerarm_screendoor)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor_hand)==0)||
          (strcmp(animationDataArray[animID].name, anim_screendoor)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_mustache)==0) ||
          (strcmp(animationDataArray[animID].name, anim_tongue)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_whitewater)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_duckytube)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_flaghand)==0)) {
        setSprite(entityID, (int)enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      break;
    case Zombie_State_enum::bucketHeadZombie:
      if ((strcmp(animationDataArray[animID].name, anim_cone)==0) ||
          (strcmp(animationDataArray[animID].name, anim_hair)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_outerarm_screendoor)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor_hand)==0) ||
          (strcmp(animationDataArray[animID].name, anim_screendoor)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_mustache)==0) ||
          (strcmp(animationDataArray[animID].name, anim_tongue)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_whitewater)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_duckytube)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_innerarm_screendoor)==0) ||
          (strcmp(animationDataArray[animID].name, Zombie_flaghand)==0)) {
        setSprite(entityID, (int)enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      break;
    default:
      break;
  }
}

int Zombie::move() {
  // printf("timer: %llu\n",timerArray[father].counterMS);
  // printf("maxMS: %llu\n",timerArray[father].maxMS);
  // lifeArray[father] = 0;
  // erase();
  if(attack == true){
   return 1; 
  }

  PS2Timer& timer = timerArray[father];
  // sizeof(ArrayKey<int,PS2Timer>)
  if (timer.counterMS < timer.maxMS) {
    timer.addMSinCounter();
  } else if (attack == false) {
    timer.resetCounter();
    posArray[father].x -= speedArray[father];
    // boxColliderArray[BOXCOLLIDER_ZOMBIE][boxColliderArrayID[boxColliderID]].x = posArray[father].x;
    for(BoxCollider& box: boxColliderZombie){
      if(box.id == boxColliderID){
        box.x = posArray[father].x;
        break;
      }
    }
    // boxColliderArray[boxColliderID].x = posArray[father].x;
    // printf("box: %f,%f\n",
    // boxColliderArray[*it->id[0]].x,boxColliderArray[*it->id[0]].y);
  }
  return 0;
}

int Zombie::attackPlant() {
  int searchIndex = responseCollisionZombiePlant.size();
  int size = searchIndex;
  for(int i=0;i<size;i++){
    if(responseCollisionZombiePlant[i].zombieID == boxColliderID){
      searchIndex = i;
      break;
    }
  }

  if(size == searchIndex){
    if(attack==true){
      for(unsigned int k=0 ; k < zombieAnims.size(); k++){
        if(zombieAnims[k].id == father){
          attack = false;
          ChangeAnimationEntity(zombieAnims[k].entity,AnimIndex::Zombie,enumAnimationState::normalZombieWalk, zombie_layer);
        }
      }
    }
    return 0;
  }

  for(unsigned int k=0 ; k < zombieAnims.size(); k++){
    // printf("seaching\n");
    if(zombieAnims[k].id == father){
      // printf("encontre\n");
      if(attack == false){
        attack = true;
        ChangeAnimationEntity(zombieAnims[k].entity,AnimIndex::Zombie,enumAnimationState::normalZombieAttack, zombie_layer);
      }else {
        for(size_t m=0;m<frameCounterArray.size();m++){
          if(frameCounterArray[m].entityID == zombieAnims[k].entity[0]){
            if(frameCounterArray[m].framesCounter == 0 && (frameCounterArray[m].currentFrame == 144 || frameCounterArray[m].currentFrame == 164)){
              // printf("currentFrame: %d\n",frameCounterArray[m].currentFrame);
              for(size_t j=0;j<45;j++){
                if(plant[j].father == responseCollisionZombiePlant[searchIndex].plantID){
                  plant[j].damage(father);
                  break;
                }
              }
              // lifeArray[] -= damageArray[father];
              // printf("plant life: %d\n",lifeArray[responseCollisionZombiePlant[searchIndex].plantID]);
            }
            break;
          }
        }
      }
      break;
    }
  }

  return 1;
}

void Zombie::damage(const int entityID) {
  damaged = true;
  lifeArray[father] -= damageArray[entityID];
  printf("lifeArray: %d\n",lifeArray[father]);
  // damagedZombie.push_back()
  size_t size = zombieAnims.size();
  unsigned int indexAnim = size;
  for(size_t i=0; i < size; i++){
    if (zombieAnims[i].id == father) {
      indexAnim = i;
      break;
    }
  }

  if(indexAnim == size) { return; }

  std::vector<int>& animEntity = zombieAnims[indexAnim].entity;
  size = animEntity.size();
  for(size_t i=0; i < size; i++){
    if (spriteRenderIDArray.count(animEntity[i]) == 1) {
      // printf("anim attack id: %d\n",m_animID["Zombie"][j]);
      spriteArray[animEntity[i]].color = Tyra::Color(255, 255, 255, 128);
    }
  }
  // unsigned int size = id.size();
  // for (unsigned int j = 0; j < size; j++) {
  //   if (animationArray.count(id[j]) == 1) {
  //     // printf("anim attack id: %d\n",m_animID["Zombie"][j]);
  //     spriteArray[id[j]].color = Tyra::Color(255, 255, 255, 128);
  //   }
  // }
}

bool Zombie::explosionState() {
  // for(int i=0; i<zombieAnims.size();i++){
  //   if(zombieAnims[i].id == father){
  //     if(animationArray[zombieAnims[i].entity[0]].currentFrame == animationArray[zombieAnims[i].entity[0]].lastFrame){
  //       // delete zombie
  //       return erase();
  //     }
  //   }
  // }
  // if (animationArray[id[0]].currentFrame == animationArray[id[0]].lastFrame) {
  //   // printf("zombie id: %d\n",it2->id[0]);
  //   // delete zombie
  //   return erase();
  // }
  return false;
}

// this maybe can be better
int Zombie::normalColor() {
  if (damaged == false) {
    return 1;
  }
  size_t size = zombieAnims.size();
  unsigned int indexAnim = size;
  for(size_t i=0; i < size; i++){
    if (zombieAnims[i].id == father) {
      indexAnim = i;
      break;
    }
  }

  if(indexAnim == size) { return 1; }

  std::vector<int>& ids = zombieAnims[indexAnim].entity;
  size = ids.size();
  for(size_t i=0; i < size; i++){
    if (spriteRenderIDArray.count(ids[i]) == 1) {
      // printf("anim attack id: %d\n",m_animID["Zombie"][j]);
      Tyra::Sprite& animSprite = spriteArray[ids[i]];
      animSprite.color.r -= 5;
      animSprite.color.g -= 5;
      animSprite.color.b -= 5;
      if(animSprite.color.r < 128.0f){
        animSprite.color.r = 128.0f;
        animSprite.color.g = 128.0f;
        animSprite.color.b = 128.0f;
        damaged = false;
      }
    }
  }
  return 0;
}

int zombiesDefeated = 0;
bool Zombie::erase() {
  // printf("zombie id:%d life: %d\n",father, lifeArray[father]);
  if (lifeArray[father] <= 0) {
    printf("delete zombie\n");
    zombiesDefeated++;
    createReward(posArray[father]);
    deletePosArray(father);

    // unsigned int animSize = m_animID[AnimIndex::Zombie].size();
 
    lifeArray.erase(father);
    damageArray.erase(father);
    speedArray.erase(father);
    
    // boxColliderArray.erase(boxColliderID);
    for(unsigned int i=0; i<boxColliderZombie.size();i++){
      if(boxColliderZombie[i].id == boxColliderID){
        boxColliderZombie.erase(boxColliderZombie.begin()+i);
        break;
      }
    }

    deleteDebugBoxCollider(boxColliderID);
    for(unsigned int i=0 ; i < zombieAnims.size(); i++){
      if(zombieAnims[i].id == father){
        // printf("zombie father ID: %d\n",zombieAnims[i].id);
        ZombieAnimation& zomAnim = zombieAnims[i];
        int animSize = zombieAnims[i].entity.size()-1;
        while (animSize >= 0)
        {
          // printf("borrando zombie anim ID: %d\n",zombieAnims[i].entity[animSize]);
          deletePosArray(zomAnim.entity[animSize]);
          deleteFinalPosArray(zomAnim.entity[animSize]);
          deleteFatherIDChild(father, &zomAnim.entity[animSize]);
          deleteSprite(zomAnim.entity[animSize]);
          deleteTexPosArray(zomAnim.entity[animSize]);
          for(unsigned int j=0; j< frameCounterArray.size();j++){
            if(frameCounterArray[j].entityID == zomAnim.entity[animSize]){
              frameCounterArray.erase(frameCounterArray.begin() + j);
              break;
            }
          }
          Entities::deleteID(zomAnim.entity[animSize]);
          animSize--;
        }
        zombieAnims.erase(zombieAnims.begin() + i);
        break;
      }
    }

    // for (unsigned int i = 0; i < animSize; i++) {
    //   deletePosArray(id[i]);
    //   deleteFinalPosArray(id[i]);
    //   deleteFatherIDChild(&father, &id[i]);

    //   deleteSprite(id[i]);

    //   if (animationArray.count(id[i]) == 1) {
    //     deleteAnimation(id[i]);
    //   }
    //   deleteTexPosArray(id[i]);
    //   Entities::deleteID(id[i]);
    // }
    deleteFatherID(father);
    Entities::deleteID(father);
    Entities::deleteID(boxColliderID);
    type = Zombie_State_enum::NoneZombie;
    zombiesCreated--;
    return true;
  }
  return false;
}

void createNormalZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n", m_animID[AnimIndex::Zombie].size());
  SetAnimationToEntity(anim.entity,zombie[id].father,AnimIndex::Zombie, Tyra::Vec2(1, 1), normalZombieWalk, enumSpriteLayer::zombie_layer);
  std::vector<int>& animData = m_animID[AnimIndex::Zombie];
  int size = animData.size();
  Zombie_State_enum type = zombie[id].type;
  for(int i=0;i< size;i++){
    SetZombieAnimation(anim.entity[i], animData[i], type);
  }
  zombieAnims.push_back(anim);

  // Life
  lifeArray.insert(zombie[id].father, 200);  // 270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[zombie[id].father] = 50;

  // speed
  speedArray[zombie[id].father] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 10, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createFlagZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n", m_animID[AnimIndex::Zombie].size());
  SetAnimationToEntity(anim.entity,zombie[id].father,AnimIndex::Zombie, Tyra::Vec2(1, 1), normalZombieWalk, enumSpriteLayer::zombie_layer);
  std::vector<int>& animData = m_animID[AnimIndex::Zombie];
  int size = animData.size();
  Zombie_State_enum type = zombie[id].type;

  for(int i=0;i< size;i++){
    SetZombieAnimation(anim.entity[i], animData[i], type);
  }

  zombieAnims.push_back(anim);

  // Life
  lifeArray.insert(zombie[id].father, 200);  // 270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[zombie[id].father] = 50;

  // speed
  speedArray[zombie[id].father] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 10, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createConeheadZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n", m_animID[AnimIndex::Zombie].size());
  SetAnimationToEntity(anim.entity,zombie[id].father,AnimIndex::Zombie, Tyra::Vec2(1, 1), normalZombieWalk, enumSpriteLayer::zombie_layer);
  std::vector<int>& animData = m_animID[AnimIndex::Zombie];
  int size = animData.size();
  Zombie_State_enum type = zombie[id].type;
  for(int i=0;i< size;i++){
    SetZombieAnimation(anim.entity[i], animData[i], type);
  }

  zombieAnims.push_back(anim);

  // Life
  lifeArray.insert(fatherID, 200);  // 270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[fatherID] = 50;

  // speed
  speedArray[fatherID] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 20, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createPoleVaulterZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n",
  //        m_animID[AnimIndex::Zombie_PoleVaulter].size());
  SetAnimationToEntity(anim.entity,zombie[id].father,AnimIndex::Zombie_PoleVaulter, Tyra::Vec2(1, 1), 14,50, enumSpriteLayer::zombie_layer);

  zombieAnims.push_back(anim);

  // Life
  lifeArray.insert(zombie[id].father, 200);  // 270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[zombie[id].father] = 100;

  // speed
  speedArray[zombie[id].father] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 10, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createBucketheadZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  ZombieAnimation anim;
  anim.id = fatherID;
  SetAnimationToEntity(anim.entity,zombie[id].father,AnimIndex::Zombie, Tyra::Vec2(1, 1), normalZombieWalk, enumSpriteLayer::zombie_layer);
  std::vector<int>& animData = m_animID[AnimIndex::Zombie];
  int size = animData.size();
  Zombie_State_enum type = zombie[id].type;
  
  for(int i=0;i< size;i++){
    SetZombieAnimation(anim.entity[i], animData[i], type);
  }

  zombieAnims.push_back(anim);

  // Life
  lifeArray.insert(zombie[id].father, 200);  // 270 for flagZombie
  // TODO: change apparence when has 100 of life

  // damage
  damageArray[zombie[id].father] = 100;

  // speed
  speedArray[zombie[id].father] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 10, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createZombie(Tyra::Vec2 pos, const Zombie_State_enum type) {
  zombie.push_back(Zombie());
  int id = zombie.size() - 1;
  zombie[id].newZombie(type);
  zombie[id].father = Entities::newID();
  zombie[id].boxColliderID = Entities::newID();
  // zombieAnimationIDs.anim.push_back(new std::vector<int>);
  PS2Timer timer;
  timer.maxMS = 150;
  // PS2Timer attackTimer;
  // attackTimer.maxMS = 150;
  timerArray.insert(zombie[id].father ,timer);
  posArray.insert(zombie[id].father, pos);

  fatherIDArray.insert(zombie[id].father, FatherID());
  printf("zombie father id: %d\n", zombie[id].father);

  if (type == Zombie_State_enum::normalZombie) {
    createNormalZombie(id, zombie[id].father, pos);
  } else if (type == Zombie_State_enum::flagZombie) {
    createFlagZombie(id, zombie[id].father, pos);
  } else if (type == Zombie_State_enum::coneheadZombie) {
    createConeheadZombie(id, zombie[id].father, pos);
  } else if (type == Zombie_State_enum::poleVaulterZombie) {
    createPoleVaulterZombie(id, zombie[id].father, pos);
  } else if (type == Zombie_State_enum::bucketHeadZombie) {
    createBucketheadZombie(id, zombie[id].father, pos);
  }

  zombiesCreated++;
  TYRA_LOG("Zombie Debug Created");
}

int waves = 1;
int zombiesLeftForWave = 2;

int timerZombies = 30*60;//1*60=60=1 sec //2310;
int maxZombies;  // this is used for when you win the level
// para terminar un nivel se usa el tiempo, hay un tiempo determinado por eso la
// barra sigue moviendose procedimiento crea zombie espera se termina el tiempo
// y crea otro zombie espera el tiempo es igual al tiempo que transcurre una
// oleada se crean varios zombies al crear varios zombies se puede hacer un
// limite para que no esten todos en una fila

//nivel 1
//en el segundo 0 se crea 1 zombie
//en 1/4 se crea 1 zombie
//la mitad se crea 1 zombie
//al final se crea 2 zombie
struct ZombieWave{
  int time;
  int maxZombies;
};
ZombieWave timeZombie;
void createZombieMain() {
  timeZombie.maxZombies = 1;
  timeZombie.time = 450;//2310;
  // 100% --- 158  --- 1800
  // 25%  --- 39.5 --- 450
  // 154 es el size maximo del fullflagmeter
  // 100% --- 154
  //  25% --- 38.5
  // digamos que el tiempo maximo son 30 segundos
  // 100% --- 30000 
  //  25% --- 7500
  // printf("timerZombies: %d\n",timerZombies);
  if (timerZombies < timeZombie.time) {
    timerZombies++;
    if(timerZombies%12==0){
      posArray[Entity::zombieFlagMeter].x--;
      spriteArray[Entity::fullFlagMeter].size.x++;
    }
  } else {
    // printf("creando zombie\n");
    if (zombiescreated < maxZombies) {
      int row = rand() % 5;
      while (zombieCreateRow[row].zombiesInRow ==
             zombieCreateRow[row].maxZombiesInRow) {
        row = rand() % 5;
      }
      // TODO: hacer que se elimine esto cuando se elimine un zombie o tal vez
      // no
      zombieCreateRow[row].zombiesInRow++;

      BoxCollider& boxcollider = boxColliderArray[BOXCOLLIDER_MAP][boxColliderArrayID[map[row][8]]];
      createZombie(Vec2(boxcollider.x, boxcollider.y),
            Zombie_State_enum::normalZombie);

      // createZombie(Vec2(mapCollider[row][8].x, mapCollider[row][8].y),
      //              Zombie_State_enum::coneheadZombie);
      timerZombies = 0;
      if (maxZombies - zombiescreated != zombiesLeftForWave) {
        // time = 60
      } else {
        // timerZombies = 30;
      }
      zombiescreated++;
    }
  }
}