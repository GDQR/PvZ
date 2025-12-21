#include "PVZ.hpp"
#include "imageFiles.hpp"

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

void Zombie::newZombie(Zombie_State_enum newType) { 
  type = newType;
  color.set(10,10,10,0);
}

int anim_bucket;
int anim_cone;
int anim_hair;
int anim_screendoor;
int Zombie_duckytube;
int anim_innerarm1;
int anim_innerarm2;
int anim_innerarm3;
int Zombie_whitewater;
int Zombie_whitewater2;
int Zombie_outerarm_screendoor;
int Zombie_innerarm_screendoor_hand;
int Zombie_mustache;
int anim_tongue;
int Zombie_innerarm_screendoor;
int Zombie_flaghand;

void SetAnimationNamesID(EnumAnimationIndex animation){
  if(animation == EnumAnimationIndex::ANIM_Zombie){
    anim_bucket = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_bucket");
    anim_cone = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_cone");
    anim_hair = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_hair");
    anim_screendoor = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_screendoor");
    Zombie_duckytube = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_duckytube");;
    anim_innerarm1 = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_innerarm1");;
    anim_innerarm2 = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_innerarm2");;
    anim_innerarm3 = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_innerarm3");;
    Zombie_whitewater = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_whitewater");;
    Zombie_whitewater2 = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_whitewater2");;
    Zombie_outerarm_screendoor = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_outerarm_screendoor");;
    Zombie_innerarm_screendoor_hand = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_innerarm_screendoor_hand");;
    Zombie_mustache = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_mustache");;
    anim_tongue = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_tongue");;
    Zombie_innerarm_screendoor = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_innerarm_screendoor");;
    Zombie_flaghand = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_flaghand");;
  }
}

void Zombie::setNormalZombieAnimation(){
  if(lifeArray[father] <= 80){
    for(ZombieAnimation& anim: zombieAnims){
      if(anim.id == father){
        int layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_head1");
        setSprite(anim.entity[layerID],noDraw,enumSpriteLayer::zombie_layer);
        layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_head2");
        setSprite(anim.entity[layerID],noDraw,enumSpriteLayer::zombie_layer);
        layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_tongue");
        setSprite(anim.entity[layerID],noDraw,enumSpriteLayer::zombie_layer);
        layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_hair");
        setSprite(anim.entity[layerID],noDraw,enumSpriteLayer::zombie_layer);
        break;
      }
    } 
  } else if(lifeArray[father] <= 170){
    for(ZombieAnimation& anim: zombieAnims){
      if(anim.id == father){
        int layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_outerarm_lower");
        setSprite(anim.entity[layerID],noDraw,enumSpriteLayer::zombie_layer);
        layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_outerarm_hand");
        setSprite(anim.entity[layerID],noDraw,enumSpriteLayer::zombie_layer);
        layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("Zombie_outerarm_upper");
        createTexture(anim.entity[layerID],"REANIM/Zombie_outerarm_upper2.PNG");
        break;
      }
    }    
  }
}

void Zombie::setConeheadAnimation(int entityID){
  if(lifeArray[father] <= 270){
    setSprite(entityID,noDraw,enumSpriteLayer::zombie_layer);
    for(ZombieAnimation& anim: zombieAnims){
      if(anim.id == father){
        int layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_hair");
        setSprite(anim.entity[layerID],draw,enumSpriteLayer::zombie_layer);
        break;
      }
    }
    type = normalZombie;
  }else if (lifeArray[father] <= 380) {
    createTexture(entityID,IMG_Zombie_cone3);
  }else if (lifeArray[father] <= 510) {
    createTexture(entityID,IMG_Zombie_cone2);
  }
}

void Zombie::setBucketheadAnimation(int entityID){
  if(lifeArray[father] <= 270){
    setSprite(entityID,noDraw,enumSpriteLayer::zombie_layer);
    for(ZombieAnimation& anim: zombieAnims){
      if(anim.id == father){
        int layerID = animComponent[EnumAnimationIndex::ANIM_Zombie].GetAnimationNameID("anim_hair");
        setSprite(anim.entity[layerID],draw,enumSpriteLayer::zombie_layer);
        break;
      }
    }
    type = normalZombie;
  }else if (lifeArray[father] <= 380) {
    createTexture(entityID,IMG_Zombie_bucket3);
  }else if (lifeArray[father] <= 510) {
    createTexture(entityID,IMG_Zombie_bucket2);
  }
}

void Zombie::SetZombieAnimation(const int entityID, const int nameID, const Zombie_State_enum type) {
  switch (type) {
    case Zombie_State_enum::normalZombie:
        if(nameID == anim_bucket
          || nameID == anim_cone
          || nameID == anim_screendoor
          || nameID == Zombie_duckytube
          || nameID == Zombie_whitewater
          || nameID == Zombie_whitewater2
          || nameID == Zombie_outerarm_screendoor
          || nameID == Zombie_innerarm_screendoor_hand
          || nameID == Zombie_mustache || nameID == anim_tongue
          || nameID == Zombie_innerarm_screendoor
          || nameID == Zombie_flaghand){
          setSprite(entityID, enumDraw::noDraw, enumSpriteLayer::zombie_layer);
        }
        setNormalZombieAnimation();
      break;
    case Zombie_State_enum::flagZombie:
      if(nameID == anim_bucket 
        || nameID == anim_cone 
        || nameID == anim_screendoor
        || nameID == Zombie_duckytube /* can use in water*/ 
        || nameID == anim_innerarm1
        || nameID == anim_innerarm2 
        || nameID == anim_innerarm3
        || nameID == Zombie_whitewater 
        || nameID == Zombie_whitewater2
        || nameID == Zombie_outerarm_screendoor 
        || nameID == Zombie_innerarm_screendoor_hand
        || nameID == Zombie_mustache 
        || nameID == anim_tongue){
        setSprite(entityID, enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      break;
    case Zombie_State_enum::coneheadZombie:
      if(nameID == anim_bucket 
        || nameID == anim_hair
        || nameID == Zombie_outerarm_screendoor
        || nameID == Zombie_innerarm_screendoor_hand
        || nameID == anim_screendoor
        || nameID == Zombie_mustache
        || nameID == anim_tongue
        || nameID == Zombie_whitewater
        || nameID == Zombie_duckytube
        || nameID == Zombie_innerarm_screendoor
        || nameID == Zombie_flaghand){
        setSprite(entityID, enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      if(nameID == anim_cone){
        setConeheadAnimation(entityID);
      }
      break;
    case Zombie_State_enum::bucketHeadZombie:
      if(nameID == anim_cone
        || nameID == anim_hair
        || nameID == Zombie_outerarm_screendoor
        || nameID == Zombie_innerarm_screendoor_hand
        || nameID == anim_screendoor
        || nameID == Zombie_mustache
        || nameID == anim_tongue
        || nameID == Zombie_whitewater
        || nameID == Zombie_duckytube
        || nameID == Zombie_innerarm_screendoor
        || nameID == Zombie_flaghand){
        setSprite(entityID, enumDraw::noDraw, enumSpriteLayer::zombie_layer);
      }
      if(nameID == anim_bucket){
        setBucketheadAnimation(entityID);
      }
      break;
    default:
      break;
  }
}

int Zombie::move() {
  // printf("timer: %llu\n",timerArray[father].counterMS);
  // printf("maxMS: %llu\n",timerArray[father].maxMS);

  PS2Timer& timer = timerArray[father];
  // sizeof(ArrayKey<int,PS2Timer>)
  if (timer.counterMS < timer.maxMS) {
    timer.addMSinCounter();
  } else {
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

void finishJump(const int entityID){
  int zombieID = 0;
  int zombieAnimIndex = 0;
  for(unsigned int k=0; k < zombieAnims.size(); k++){
    if(zombieAnims[k].entity[0] == entityID){
      animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(zombieAnims[k].entity, "anim_walk", 0, zombie_layer, true);
      zombieID = zombieAnims[k].id;
      zombieAnimIndex = k;
      break;
    }
  }

  for(size_t i=0; i< zombieJumpState.size();i++){
    if(zombieJumpState[i].father == zombieID){
      for(size_t j=0; j< animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetLayerSize();j++){
        zombieJumpState[i].SetZombieAnimation(zombieAnims[zombieAnimIndex].entity[j], animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetNameID(j),poleVaulterZombie);
      }

      int layer = animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetAnimationNameID("Zombie_polevaulter_innerleg_toe");
      printf("pos 1: %f\n",posArray[zombieJumpState[i].father].x);
      printf("pos 2: %f\n",spriteArray[zombieAnims[zombieAnimIndex].entity[layer]].position.x);
      posArray[zombieJumpState[i].father].x = spriteArray[zombieAnims[zombieAnimIndex].entity[layer]].position.x;
      for(BoxCollider& box: boxColliderZombie){
        if(box.id == zombieJumpState[i].boxColliderID){
          box.x = posArray[zombieJumpState[i].father].x;
          break;
        }
      }

      zombie.push_back(zombieJumpState[i]);

      zombieJumpState.erase(zombieJumpState.begin()+ i);

      break;
    }
  }
}

void attackPlant(const int entityID){
  int size = zombieAnims.size();
  int father = 0;
  for(int i=0; i < size; i++){
    if(zombieAnims[i].entity[0] == entityID){
      father = zombieAnims[i].id;
      break;
    }
  }
  int boxColliderID = 0;
  size = zombieAttackState.size();
  for(int i=0; i < size; i++){
    if(zombieAttackState[i].father == father){
      boxColliderID = zombieAttackState[i].boxColliderID;
      break;
    }
  }

  int searchIndex = responseCollisionZombiePlant.size();
  size = searchIndex;
  for(int i=0;i<size;i++){
    if(responseCollisionZombiePlant[i].zombieID == boxColliderID){
      searchIndex = i;
      break;
    }
  }

  for(size_t j=0;j<45;j++){
    if(plant[j].father == responseCollisionZombiePlant[searchIndex].plantID){
      plant[j].damage(father);
      break;
    }
  }
}

bool Zombie::animWalk(){
  bool col = CollisionStopPlant(boxColliderID);

  if(col == false){
    return false;
  }

  // No plant detected
  for(unsigned int k=0 ; k < zombieAnims.size(); k++){
    if(zombieAnims[k].id == father){
      if(type == Zombie_State_enum::normalZombie || type == Zombie_State_enum::coneheadZombie || type == Zombie_State_enum::bucketHeadZombie){
        animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(zombieAnims[k].entity, "anim_walk", 0, zombie_layer, true);
        for(size_t i = 0; i < zombieAnims[k].entity.size();i++){
          SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
        }
      }else if(type == Zombie_State_enum::poleVaulterZombie){
        animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(zombieAnims[k].entity, "anim_walk", 0, zombie_layer, true);
        for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();i++){
          SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
        }
      }  
    }
  }

  zombie.push_back(*this);

  return true;
}

bool Zombie::animAttackPlant() {
  size_t searchIndex = responseCollisionZombiePlant.size();
  bool col = CollisionEnterPlant(boxColliderID);

  if(col == false){
    return false;
  }

  for(size_t j=0;j<45;j++){
    if(plant[j].father == responseCollisionZombiePlant[searchIndex].plantID){
      if(plant[j].type == WallnutBowling || plant[j].type == WallnutBowlingExplosion){
        return false;
      }
    }
  }

  // Plants that should be attacked

  for(unsigned int k=0 ; k < zombieAnims.size(); k++){
    // printf("seaching\n");
    if(zombieAnims[k].id == father){
      // printf("encontre\n");
      if(type == Zombie_State_enum::normalZombie || type == Zombie_State_enum::coneheadZombie || type == Zombie_State_enum::bucketHeadZombie){
        animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(zombieAnims[k].entity, "anim_eat", 0, zombie_layer, true);
        for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();i++){
          SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
        }
      }else if(type == Zombie_State_enum::poleVaulterZombie){
        // for(int j=0; j < frameCounterArray.size(); j++){
        //   if()
        // }
        // en el frame 75 se cancela la animacion si hay una colision grande
        // no es comido por el chomper al saltar pero hace la animacion de comer
        unsigned int layer = animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetAnimationNameID("anim_run");
        std::vector<AnimationTime> animTime = animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetTimeLapseFromLayer(layer);
        FrameCounter frameCounter = frameCounterArray[zombieAnims[k].entity[0]];
        bool isRunning = false;
        for(size_t k=0; k<animTime.size();k++){
          if(frameCounter.firstFrame == animTime[k].start
            && frameCounter.lastFrame == animTime[k].end){
            printf("esta corre\n");
            isRunning = true;
            break;
          }
        }

        if(isRunning == true){
          animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(zombieAnims[k].entity, "anim_jump", 0, zombie_layer, false);
          for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetLayerSize();i++){
            SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetNameID(i),type);
          }
          
          zombieJumpState.push_back(*this);
          return true;
        }

        animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(zombieAnims[k].entity, "anim_eat", 0, zombie_layer, true);
        for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetLayerSize();i++){
          SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetNameID(i),type);
        }
      }
      break;
    }
  }

  zombieAttackState.push_back(*this);

  return true;

  // // No plant detected
  // if(size == searchIndex){
  //   if(attack==true){
  //     for(unsigned int k=0 ; k < zombieAnims.size(); k++){
  //       if(zombieAnims[k].id == father){
  //         attack = false;
  //         if(type == Zombie_State_enum::normalZombie || type == Zombie_State_enum::coneheadZombie || type == Zombie_State_enum::bucketHeadZombie){
  //           animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(zombieAnims[k].entity, "anim_walk", 0, zombie_layer, true);
  //           for(size_t i = 0; i < zombieAnims[k].entity.size();i++){
  //             SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
  //           }
  //         }else if(type == Zombie_State_enum::poleVaulterZombie){
  //           animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(zombieAnims[k].entity, "anim_walk", 0, zombie_layer, true);
  //           for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();i++){
  //             SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
  //           }
  //         }  
  //       }
  //     }
  //   }
  //   return 0;
  // }

  // // Plants that should not be attacked

  // for(size_t j=0;j<45;j++){
  //   if(plant[j].father == responseCollisionZombiePlant[searchIndex].plantID){
  //     if(plant[j].type == WallnutBowling || plant[j].type == WallnutBowlingExplosion){
  //       return 0;
  //     }
  //   }
  // }

  // // Plants that should be attacked

  // for(unsigned int k=0 ; k < zombieAnims.size(); k++){
  //   // printf("seaching\n");
  //   if(zombieAnims[k].id == father){
  //     // printf("encontre\n");
  //     if(attack == false){
  //       attack = true;
  //       if(type == Zombie_State_enum::normalZombie || type == Zombie_State_enum::coneheadZombie || type == Zombie_State_enum::bucketHeadZombie){
  //         animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(zombieAnims[k].entity, "anim_eat", 0, zombie_layer, true);
  //         for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();i++){
  //           SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
  //         }
  //       }else if(type == Zombie_State_enum::poleVaulterZombie){
  //         animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(zombieAnims[k].entity, "anim_eat", 0, zombie_layer, true);
  //         for(size_t i=0; i< animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();i++){
  //           SetZombieAnimation(zombieAnims[k].entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i),type);
  //         }
  //       }
  //     }
  //     break;
  //   }
  // }

  // return 1;
}

bool Zombie::damage(const int entityID, DamageType damageType) {
  damaged = true;
  int& life = lifeArray[father];
  life -= damageArray[entityID];
  printf("lifeArray: %d\n",lifeArray[father]);

  size_t size = zombieAnims.size();
  unsigned int indexAnim = size;
  for(size_t i=0; i < size; i++){
    if (zombieAnims[i].id == father) {
      indexAnim = i;
      break;
    }
  }

  if(indexAnim == size) { return false; }

  //con el salvavidas de pato en la piscina al explotar no muestran nada, solo se destruye
  switch (type){
  case normalZombie:
    if (life <= 0) {     
      if(damageType == Bullet){
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            printf("cambie anim zombie\n");
            animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(anim.entity,"anim_death2", 0, enumSpriteLayer::zombie_layer, false);
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }

            deleteDebugBoxCollider(boxColliderID);
            deadZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }  
        }
      }else if(damageType == EXPLOSION){
        printf("damage explosion zmbie\n");
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            for(unsigned int i=0 ; i < zombieAnims.size(); i++){
              if(zombieAnims[i].id == father){
                // printf("zombie father ID: %d\n",zombieAnims[i].id);
                ZombieAnimation& zomAnim = zombieAnims[i];
                int animSize = zombieAnims[i].entity.size()-1;
                while (animSize >= 0)
                {
                  // printf("deleting zombie anim ID: %d\n",zombieAnims[i].entity[animSize]);
                  deletePosArray(zomAnim.entity[animSize]);
                  deleteFinalPosArray(zomAnim.entity[animSize]);
                  deleteFatherIDChild(father, &zomAnim.entity[animSize]);
                  deleteSprite(zomAnim.entity[animSize]);
                  deleteTexPosArray(zomAnim.entity[animSize]);
                  deleteFrameCounter(zomAnim.entity[animSize]);
                  Entities::deleteID(zomAnim.entity[animSize]);
                  animSize--;
                }
                zombieAnims[i].entity.clear();
                zombieAnims.erase(zombieAnims.begin() + i);
                break;
              }
            }
            
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }
            
            createNormalCharredZombie(father,posArray[father]);


            charredZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }
        }
      }
    }else{
      setNormalZombieAnimation();
    }
    break;
  case coneheadZombie:
    if (life <= 0) {     
      if(damageType == Bullet){
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            printf("cambie anim zombie\n");
            animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(anim.entity,"anim_death2", 0, enumSpriteLayer::zombie_layer, false);
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }

            deleteDebugBoxCollider(boxColliderID);
            deadZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }  
        }
      }else if(damageType == EXPLOSION){
        printf("damage explosion zmbie\n");
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            for(unsigned int i=0 ; i < zombieAnims.size(); i++){
              if(zombieAnims[i].id == father){
                // printf("zombie father ID: %d\n",zombieAnims[i].id);
                ZombieAnimation& zomAnim = zombieAnims[i];
                int animSize = zombieAnims[i].entity.size()-1;
                while (animSize >= 0)
                {
                  // printf("deleting zombie anim ID: %d\n",zombieAnims[i].entity[animSize]);
                  deletePosArray(zomAnim.entity[animSize]);
                  deleteFinalPosArray(zomAnim.entity[animSize]);
                  deleteFatherIDChild(father, &zomAnim.entity[animSize]);
                  deleteSprite(zomAnim.entity[animSize]);
                  deleteTexPosArray(zomAnim.entity[animSize]);
                  deleteFrameCounter(zomAnim.entity[animSize]);
                  Entities::deleteID(zomAnim.entity[animSize]);
                  animSize--;
                }
                zombieAnims[i].entity.clear();
                zombieAnims.erase(zombieAnims.begin() + i);
                break;
              }
            }
            
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }
            
            createNormalCharredZombie(father,posArray[father]);


            charredZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }
        }
      }
    }else{
      for(ZombieAnimation& anim: zombieAnims){
        if(anim.id == father){
          setConeheadAnimation(anim.entity[anim_cone]);   
        }
      }
    }
    break;
  case bucketHeadZombie:
  if (life <= 0) {     
      if(damageType == Bullet){
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            animComponent[EnumAnimationIndex::ANIM_Zombie].ChangeAnimationEntity(anim.entity,"anim_death2", 0, enumSpriteLayer::zombie_layer, false);
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }

            deleteDebugBoxCollider(boxColliderID);
            deadZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }  
        }
      }else if(damageType == EXPLOSION){
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            for(unsigned int i=0 ; i < zombieAnims.size(); i++){
              if(zombieAnims[i].id == father){
                // printf("zombie father ID: %d\n",zombieAnims[i].id);
                ZombieAnimation& zomAnim = zombieAnims[i];
                int animSize = zombieAnims[i].entity.size()-1;
                while (animSize >= 0)
                {
                  // printf("deleting zombie anim ID: %d\n",zombieAnims[i].entity[animSize]);
                  deletePosArray(zomAnim.entity[animSize]);
                  deleteFinalPosArray(zomAnim.entity[animSize]);
                  deleteFatherIDChild(father, &zomAnim.entity[animSize]);
                  deleteSprite(zomAnim.entity[animSize]);
                  deleteTexPosArray(zomAnim.entity[animSize]);
                  deleteFrameCounter(zomAnim.entity[animSize]);
                  Entities::deleteID(zomAnim.entity[animSize]);
                  animSize--;
                }
                zombieAnims[i].entity.clear();
                zombieAnims.erase(zombieAnims.begin() + i);
                break;
              }
            }
            
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }
            
            createNormalCharredZombie(father,posArray[father]);

            charredZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }
        }
      }
    }else{
      for(ZombieAnimation& anim: zombieAnims){
        if(anim.id == father){
          setBucketheadAnimation(anim.entity[anim_bucket]);
        }
      }
    }
    break;
  case poleVaulterZombie:
  if (life <= 0) {     
      if(damageType == Bullet){
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].ChangeAnimationEntity(anim.entity,"anim_death", 0, enumSpriteLayer::zombie_layer, false);
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }

            deleteDebugBoxCollider(boxColliderID);
            deadZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }  
        }
      }else if(damageType == EXPLOSION){
        for(ZombieAnimation& anim: zombieAnims){
          if(anim.id == father){
            for(unsigned int i=0 ; i < zombieAnims.size(); i++){
              if(zombieAnims[i].id == father){
                // printf("zombie father ID: %d\n",zombieAnims[i].id);
                ZombieAnimation& zomAnim = zombieAnims[i];
                int animSize = zombieAnims[i].entity.size()-1;
                while (animSize >= 0)
                {
                  // printf("deleting zombie anim ID: %d\n",zombieAnims[i].entity[animSize]);
                  deletePosArray(zomAnim.entity[animSize]);
                  deleteFinalPosArray(zomAnim.entity[animSize]);
                  deleteFatherIDChild(father, &zomAnim.entity[animSize]);
                  deleteSprite(zomAnim.entity[animSize]);
                  deleteTexPosArray(zomAnim.entity[animSize]);
                  deleteFrameCounter(zomAnim.entity[animSize]);
                  Entities::deleteID(zomAnim.entity[animSize]);
                  animSize--;
                }
                zombieAnims[i].entity.clear();
                zombieAnims.erase(zombieAnims.begin() + i);
                break;
              }
            }
            
            // delete boxcollider
            for(unsigned int i=0; i<boxColliderZombie.size();i++){
              if(boxColliderZombie[i].id == boxColliderID){
                boxColliderZombie.erase(boxColliderZombie.begin()+i);
                break;
              }
            }
            
            createNormalCharredZombie(father,posArray[father]);

            charredZombie.push_back(*this);
            type = NoneZombie;
            return true;
            break;
          }
        }
      }
    }
    break;
  default:
    break;
  }

  std::vector<int>& animEntity = zombieAnims[indexAnim].entity;
  size = animEntity.size();
  if(damageType == Bullet){
    color.set(10,10,10,0);
  }else if(damageType == SNOW_BULLET){
    // TODO: include timer to stop slow movement 
    color.set(10,10,0,0);
  }
  for(size_t i=0; i < size; i++){
    if(spriteArray.count(animEntity[i]) == 1){
      spriteArray[animEntity[i]].color = Tyra::Color(255, 255, 255, 128);
    }
  }

  return false;
}

bool Zombie::explosionState() {
  for(size_t i=0; i<zombieAnims.size();i++){
    if(zombieAnims[i].id == father){
      if(frameCounterArray[zombieAnims[i].entity[0]].IsLastframe() == true){
        deleteData();
        return true;
      }
    }
  }

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
    if (spriteArray.count(ids[i]) == 1) {
      Tyra::Sprite& animSprite = spriteArray[ids[i]];
      animSprite.color.r -= color.r;
      animSprite.color.g -= color.g;
      animSprite.color.b -= color.b;
      if(animSprite.color.r <= 128.0f){
        damaged = false;
      }
    }
  }
  return 0;
}

int zombiesDefeated = 0;
//TODO: the last zombie the body is erased without animation
bool Zombie::erase() {
  // printf("zombie id:%d life: %d\n",father, lifeArray[father]);

  bool deleteZombie = false;
  printf("delete zombie\n");
  for(ZombieAnimation& anim: zombieAnims){
    if(anim.id == father){
      // unsigned int frameIndex = frameCounterArray.dataType.size();
      
      // for(size_t i=0;i<frameCounterArray.dataType.size();i++){
      //   if(frameCounterArray[i].entityID == anim.entity[0]){
      //     frameIndex = i;
      //     break;
      //   }
      // }

      FrameCounter& fc = frameCounterArray[anim.entity[0]];
      bool fadeZombie = false;
      if(fc.IsLastframe() == true){
        fadeZombie = true;
        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 5;
        printf("fade\n");
      }

      if(fadeZombie == true){
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
          if (spriteArray.count(ids[i]) == 1) {
            Tyra::Sprite& animSprite = spriteArray[ids[i]];
            if(animSprite.color.a > 0.0f){
              animSprite.color.a -= color.a;
              if(animSprite.color.a < 0){
                animSprite.color.a = 0;
              }
            }else{
              deleteZombie = true;
            }
          }
        }
        if(deleteZombie == true){
          printf("erase\n");
        }
      }
      break;
    }
  }
  if (deleteZombie == true) {
    deleteData();
    return true;
  }
  return false;
}

void Zombie::deleteData(){
  printf("delete zombie\n");
    zombiesDefeated++;
    createReward(posArray[father]);
    deletePosArray(father);

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
          // printf("deleting zombie anim ID: %d\n",zombieAnims[i].entity[animSize]);
          deletePosArray(zomAnim.entity[animSize]);
          deleteFinalPosArray(zomAnim.entity[animSize]);
          deleteFatherIDChild(father, &zomAnim.entity[animSize]);
          deleteSprite(zomAnim.entity[animSize]);
          deleteTexPosArray(zomAnim.entity[animSize]);
          deleteFrameCounter(zomAnim.entity[animSize]);
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
}

void createNormalCharredZombie(int& fatherID, Tyra::Vec2 pos){
  printf("CharredZombie\n");
  ZombieAnimation anim;
  anim.id = fatherID;
  animComponent[EnumAnimationIndex::ANIM_Zombie_charred].SetAnimationToEntity(anim.entity,fatherID, Tyra::Vec2(1, 1), "Zombie_hair", 0, true, enumSpriteLayer::zombie_layer);
  zombieAnims.push_back(anim);  
}

void createNormalZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  printf("zmobie normal id: %d\n",fatherID);
  // Life
  lifeArray.insert(zombie[id].father, 270);

  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n", animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize());
  animComponent[EnumAnimationIndex::ANIM_Zombie].SetAnimationToEntity(anim.entity,zombie[id].father, Tyra::Vec2(1, 1), "anim_walk", 0, true, enumSpriteLayer::zombie_layer);

  int size = animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();
  Zombie_State_enum type = zombie[id].type;
  for(int i=0;i< size;i++){
    zombie[id].SetZombieAnimation(anim.entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i) /*animClipLayers[EnumAnimationIndex::ANIM_Zombie][i].nameID*/, type);
  }
  zombieAnims.push_back(anim);

  // damage
  damageArray[zombie[id].father] = 36;

  // speed
  speedArray[zombie[id].father] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 10, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createFlagZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  // Life
  lifeArray.insert(zombie[id].father, 270);

  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n", animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize());
  animComponent[EnumAnimationIndex::ANIM_Zombie].SetAnimationToEntity(anim.entity,zombie[id].father, Tyra::Vec2(1, 1), "anim_walk", 0, true, enumSpriteLayer::zombie_layer);
  int size = animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();
  Zombie_State_enum type = zombie[id].type;

  for(int i=0;i< size;i++){
    zombie[id].SetZombieAnimation(anim.entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i), type);
  }

  zombieAnims.push_back(anim);

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
  // Life
  lifeArray.insert(fatherID, 640);  // 370 for cone 270 for flagZombie

  ZombieAnimation anim;
  anim.id = fatherID;
  // printf("zombie anim size: %d\n", animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize());
  animComponent[EnumAnimationIndex::ANIM_Zombie].SetAnimationToEntity(anim.entity,zombie[id].father, Tyra::Vec2(1, 1), "anim_walk", 0, true, enumSpriteLayer::zombie_layer);
  int size = animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();
  Zombie_State_enum type = zombie[id].type;
  printf("aca\n");
  for(int i=0;i< size;i++){
    zombie[id].SetZombieAnimation(anim.entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i), type);
  }
printf("aca2\n");
  zombieAnims.push_back(anim);

  // TODO: change apparence when has 100 of life

  // damage
  damageArray[fatherID] = 36;

  // speed
  speedArray[fatherID] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 20, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createPoleVaulterZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  // Life
  lifeArray.insert(fatherID, 600);
  
  ZombieAnimation anim;
  anim.id = fatherID;
  printf("zombie anim size: %d\n", animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].GetLayerSize());
  animComponent[EnumAnimationIndex::ANIM_Zombie_PoleVaulter].SetAnimationToEntity(anim.entity,zombie[id].father, Tyra::Vec2(1, 1), "anim_run",0, true, enumSpriteLayer::zombie_layer);

  zombieAnims.push_back(anim);

  // damage
  damageArray[fatherID] = 36;

  // speed
  speedArray[fatherID] = 1;

  // HitBox
  createBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, BoxCollider(zombie[id].boxColliderID, pos.x, pos.y + 10, 28, 50));
  //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(zombie[id].boxColliderID, BoxColliderEnum::BOXCOLLIDER_ZOMBIE, Tyra::MODE_STRETCH);
}

void createBucketheadZombie(const int id, const int fatherID, Tyra::Vec2 pos) {
  // Life
  lifeArray.insert(zombie[id].father, 640);

  ZombieAnimation anim;
  anim.id = fatherID;
  animComponent[EnumAnimationIndex::ANIM_Zombie].SetAnimationToEntity(anim.entity,zombie[id].father, Tyra::Vec2(1, 1), "anim_walk", 0, true, enumSpriteLayer::zombie_layer);
  int size = animComponent[EnumAnimationIndex::ANIM_Zombie].GetLayerSize();
  Zombie_State_enum type = zombie[id].type;
  
  for(int i=0;i< size;i++){
    zombie[id].SetZombieAnimation(anim.entity[i], animComponent[EnumAnimationIndex::ANIM_Zombie].GetNameID(i), type);
  }

  zombieAnims.push_back(anim);

  // damage
  damageArray[zombie[id].father] = 36;

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
            Zombie_State_enum::bucketHeadZombie);

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