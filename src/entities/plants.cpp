// File for all plants data
#include "PVZ.hpp"
#include "font/font.hpp"

std::vector<int> plantCollisionID;
std::vector<PlantAnimation> plantAnims;
int plantCost[enumMaxPlants];
int plantRechargeTime[enumMaxRecharge];
int plantsCreated = 0;

void loadPlantRechargeTime() {
  // values in milliseconds, is more easy for compare with the PS2Timer
  plantRechargeTime[fast] = 7500;       // 7.5 seconds
  plantRechargeTime[slow] = 30000;      // 30 seconds
  plantRechargeTime[verySlow] = 50000;  // 50 seconds
}

void createPeashotter(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father, Tyra::Vec2(0.8f, 0.8f), "anim_idle", 0, true, enumSpriteLayer::plants);

  plantAnims.push_back(anim);
  
  int anim_stem = anim.entity[animComponent[animationIndex].GetAnimationNameID("anim_stem")];

  anim.entity.clear();
  fatherIDArray.insert(anim_stem, FatherID());
  posArray[anim_stem] = posArray[father];

  animComponent[animationIndex].SetAnimationToEntity(anim.entity,anim_stem, Tyra::Vec2(0.8f, 0.8f), "anim_head_idle", 0, true, enumSpriteLayer::plants);
  
  for (size_t i = 0; i < anim.entity.size(); i++) {
    posArray[anim.entity[i]] -= texPosArray[anim_stem]; 
  }

  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(father, 300);

  timerArray.insert(father, PS2Timer());
  timerArray[father].maxMS = 1500;

  // HitBox
  createBoxCollider(father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[father] = Tyra::Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(father, Tyra::MODE_STRETCH);
}

void createSunflower(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());
  
  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;

  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father, Tyra::Vec2(0.8f, 0.8f), 5, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);
  
  // Life

  lifeArray.insert(plant[id].father, 300);

  // time

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 7000;

  // HitBox
  createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createCherryBomb(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;

  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), 1, 14, true, enumSpriteLayer::plants);

  plantAnims.push_back(anim);
  
  lifeArray.insert(father, 1000);

  // HitBox
  createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createWallnut(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), 1, 17, true, enumSpriteLayer::plants);

  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(plant[id].father, 4000);

  // HitBox
  createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createWallnutBowling(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), "_ground", 0, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(father, 4000);

  damageArray[father] = 700;

  speedArray[father] = 0;

  // HitBox
  createBoxCollider(father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createPotatoMine(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), 1, 1, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(plant[id].father, 300);

  // time

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 15000;

  // HitBox
  createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createSnowPea(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), 80, 104, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 1500;

  // HitBox
   createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);
}

void createChomper(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), 1, 25, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 0;

  damageArray[plant[id].father] = 1600;

  // lifeBox
  createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  // HitBox
  // createBoxCollider(plant[id].id[0], BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(pos.x + 30, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
  // createDebugBoxCollider(plant[id].id[0], BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createRepeater(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), 80, 104, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 1000;
  // timerArray.insert(plant[id].id[0], PS2Timer());
  // timerArray[plant[id].id[0]].maxMS = 0;

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);

  // HitBox
   createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father,pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createPuffShroom(const int id, const Tyra::Vec2 pos, EnumAnimationIndex animationIndex) {
  printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father,Tyra::Vec2(0.8f, 0.8f), "anim_idle", 0, true, enumSpriteLayer::plants);
  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 1000;
  // timerArray.insert(plant[id].id[0], PS2Timer());
  // timerArray[plant[id].id[0]].maxMS = 0;

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);

  // HitBox
   createBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father,pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(plant[id].father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);
}

void createPlantData(const int id, const Tyra::Vec2 pos, const int life, const int damage, const int speed, const int timeMaxMS, EnumAnimationIndex animationIndex, const char* layerAnimation){
printf("size: %d\n", animComponent[animationIndex].GetLayerSize());

  int& father = plant[id].father;
  PlantAnimation anim;
  anim.id = father;
  
  animComponent[animationIndex].SetAnimationToEntity(anim.entity,father, Tyra::Vec2(0.8f, 0.8f), layerAnimation, 0, true, enumSpriteLayer::plants);

  plantAnims.push_back(anim);
  
  // esto es solo para peashotter
  // int anim_stem = anim.entity[animComponent[animationIndex].GetAnimationNameID("anim_stem")];

  // anim.entity.clear();
  // fatherIDArray.insert(anim_stem, FatherID());
  // posArray[anim_stem] = posArray[father];

  // animComponent[animationIndex].SetAnimationToEntity(anim.entity,anim_stem, Tyra::Vec2(0.8f, 0.8f), "anim_head_idle", 0, true, enumSpriteLayer::plants);
  
  // for (size_t i = 0; i < anim.entity.size(); i++) {
  //   posArray[anim.entity[i]] -= texPosArray[anim_stem]; 
  // }

  plantAnims.push_back(anim);

  // Life

  lifeArray.insert(father, life);

  // time
  timerArray.insert(father, PS2Timer());
  timerArray[father].maxMS = timeMaxMS;
  
  // Damage
  damageArray[father] = damage;

  // Speed
  speedArray[father] = speed;

  // HitBox
  createBoxCollider(father, BoxColliderEnum::BOXCOLLIDER_PLANT, BoxCollider(father, pos.x + 10, pos.y + 20, 28, 38));
  createDebugBoxCollider(father, BoxColliderEnum::BOXCOLLIDER_PLANT, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[father] = Tyra::Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(father, Tyra::MODE_STRETCH);
}

bool createPlant(Plant_State_enum typePlant, const int row, const int column, int cost) {
  if (plantCreatedInMap[row][column] == false) {
    plantCreatedInMap[row][column] = true;

    
    sunCounter -= cost;
    textArray[sunCounterText].text = std::to_string(sunCounter);

    int plantPos = row * column + column;
    printf("new plant pos:%d\n", plantPos);

    plant[plantPos].newPlant(typePlant);
    plant[plantPos].row = row;
    plant[plantPos].column = column;
    plant[plantPos].father = Entities::newID();
    fatherIDArray.insert(plant[plantPos].father, FatherID());
    printf("plant father: %d\n", plant[plantPos].father);

    // Tyra::Vec2 pos(mapCollider[row][column].x, mapCollider[row][column].y);
    BoxCollider& boxPos = boxColliderArray[BOXCOLLIDER_MAP][boxColliderArrayID[map[row][column]]];
    Tyra::Vec2 pos(boxPos.x,boxPos.y);
    posArray.insert(plant[plantPos].father, pos);
    printf("typePlant: %d\n",typePlant);
    switch (typePlant) {
      case PeaShotter:
        printf("peashooter\n");
        createPeashotter(plantPos, pos, EnumAnimationIndex::ANIM_PeaShotter);
        break;
      case SunFlower:
        printf("sunflower\n");
        createSunflower(plantPos, pos, EnumAnimationIndex::ANIM_SunFlower);
        break;
      case CherryBomb:
        printf("cherryBomb");
        createCherryBomb(plantPos, pos, EnumAnimationIndex::ANIM_CherryBomb);
        break;
      case Wallnut:
        printf("wallNut");
        createWallnut(plantPos, pos, EnumAnimationIndex::ANIM_Wallnut);
        break;
      case PotatoMine:
        printf("potatoMine");
        createPotatoMine(plantPos, pos, EnumAnimationIndex::ANIM_PotatoMine);
        break;
      case SnowPea:
        printf("SnowPea");
        createSnowPea(plantPos, pos, EnumAnimationIndex::ANIM_SnowPea);
        break;
      case Chomper:
        printf("Chomper");
        createChomper(plantPos, pos, EnumAnimationIndex::ANIM_Chomper);
        break;
      case Repeater:
        printf("Repeater");
        createRepeater(plantPos, pos, EnumAnimationIndex::ANIM_Repeater);
        break;
      case PuffShroom:
        if(Entity::backgroundType == DAY){
          createPlantData(plantPos, pos, 300, 0, 0, 1000, EnumAnimationIndex::ANIM_PuffShroom, "anim_sleep");
        }else if(Entity::backgroundType == NIGHT){
          createPlantData(plantPos, pos, 300, 0, 0, 0, EnumAnimationIndex::ANIM_PuffShroom, "anim_idle");
        }
        break;
      case SunShroom:
        if(Entity::backgroundType == DAY){
          createPlantData(plantPos, pos, 300, 0, 0, 1000, EnumAnimationIndex::ANIM_SunShroom, "anim_sleep");
        }else if(Entity::backgroundType == NIGHT){
          createPlantData(plantPos, pos, 300, 0, 0, 0, EnumAnimationIndex::ANIM_SunShroom, "anim_idle");
        }
        break;
      case FumeShroom:
        if(Entity::backgroundType == DAY){
          createPlantData(plantPos, pos, 300, 0, 0, 1000, EnumAnimationIndex::ANIM_FumeShroom, "anim_sleep");
        }else if(Entity::backgroundType == NIGHT){
          createPlantData(plantPos, pos, 300, 0, 0, 0, EnumAnimationIndex::ANIM_FumeShroom, "anim_idle");
        }
        break;
      case GraveBuster:
        if(Entity::backgroundType == NIGHT){
          createPlantData(plantPos, pos, 300, 0, 0, 0, EnumAnimationIndex::ANIM_FumeShroom, "anim_idle");
        }
        break;
      case WallnutBowling:
        createWallnutBowling(plantPos,pos, EnumAnimationIndex::ANIM_Wallnut);
        break;
      default:
        TYRA_TRAP("ERROR CAN'T CREATE PLANT");
        break;
    }
    plantsCreated++;
    // printf("estoy en tile %f,%f\n",cursorTile.x,cursorTile.y);
    // printf("plantas creadas: %d\n",plantsCreated);
    return true;
  } 

  printf("no se puede crear aqui, ya existe una planta\n");
  
  return false;
}

void Plant::newPlant(Plant_State_enum newType) { type = newType; }

void Plant::setWallnutAnimation(){
  //TODO: the system animation reset to the first image
  if (lifeArray[father] <= 1333) {
      printf("change animation\n");
      for(size_t i=0; i<plantAnims.size();i++){
        if(plantAnims[i].id == father){
          int layerID = animComponent[ANIM_Wallnut].GetAnimationNameID("anim_face");
          spriteArray[plantAnims[i].entity[layerID]].textureID = TEX_Wallnut_cracked2->id;
          originalSize[plantAnims[i].entity[layerID]] =
                  Vec2(TEX_Wallnut_cracked2->getWidth(), TEX_Wallnut_cracked2->getHeight());  
        }
      }
    } else if (lifeArray[father] <= 2667) {
      printf("change animation\n");
      for(size_t i=0; i<plantAnims.size();i++){
        if(plantAnims[i].id == father){
          int layerID = animComponent[ANIM_Wallnut].GetAnimationNameID("anim_face");
          spriteArray[plantAnims[i].entity[layerID]].textureID = TEX_Wallnut_cracked1->id;
          originalSize[plantAnims[i].entity[layerID]] =
                  Vec2(TEX_Wallnut_cracked1->getWidth(), TEX_Wallnut_cracked1->getHeight());  
        }
      }
    }
}

void attackZombie(int entityID) {
  int father = 0;
  for(size_t i=0; i< plantAnims.size();i++){
    if(plantAnims[i].entity[0] == entityID){
      animComponent[EnumAnimationIndex::ANIM_Chomper].ChangeAnimationEntity(plantAnims[i].entity,"anim_chew",0,enumSpriteLayer::plants,true);
      father = plantAnims[i].id;
    }
  }

  BoxCollider plantBox;
  for(unsigned int i=0; i<boxColliderPlant.size();i++){
    if(boxColliderPlant[i].id == father){
      plantBox = boxColliderPlant[i];
      break;
    }
  }

  int id= 0;
  std::vector<BoxCollider>& zombieBox = boxColliderZombie;
  for (BoxCollider& zomBox: zombieBox) {
    if (zomBox.collision(&plantBox) == true){
        id = zomBox.id;
    }
  }

  if(id == 0){
    TYRA_TRAP("NO ENCONTRO EL ZOMBIE\n");
  }

  for(size_t i=0;i<zombie.size();i++){
    if(id == zombie[i].boxColliderID){
      zombie[i].deleteData();
      return;
    }
  }

  for(size_t i=0;i<zombieAttackState.size();i++){
    if(id == zombieAttackState[i].boxColliderID){
      zombieAttackState[i].deleteData();
      return;
    }
  }
}

int Plant::attack() {
  if (type == NonePlant) {
    return 1;
  }
  
  std::vector<BoxCollider>& zombieBox = boxColliderZombie;
  if (type == PeaShotter || type == SnowPea || type == Repeater
    || type == PuffShroom || type == FumeShroom) {
    for (BoxCollider& zomBox: zombieBox) {
      if (zomBox.pointCollision(
              &pointColliderArray[father])) {
        PS2Timer& plantTimer = timerArray[father];
        if (plantTimer.counterMS < plantTimer.maxMS) {
          plantTimer.addMSinCounter();
          break;
        }

        if (stopAnimation == false) {
          plantTimer.resetCounter();
          switch (type){
            case PeaShotter:
              newProjectile(pointColliderArray[father], 20, enumProyectile::pea);
              break;
            case SnowPea:
              newProjectile(pointColliderArray[father], 20,
                            enumProyectile::snowPea);
              break;
            case Repeater:
              newProjectile(pointColliderArray[father], 40, enumProyectile::pea);
              break;
            case PuffShroom:
            case FumeShroom: {
              size_t size = plantAnims.size();
              for(size_t i=0;i<size;i++){
                if(plantAnims[i].id == father){
                  int layer;
                  if(type == PuffShroom){
                    layer = animComponent[EnumAnimationIndex::ANIM_PuffShroom].GetAnimationNameID("anim_sleep");
                  }else if(type == FumeShroom){
                    layer = animComponent[EnumAnimationIndex::ANIM_FumeShroom].GetAnimationNameID("anim_sleep");
                  }

                  bool plantSleep = false;
                  std::vector<AnimationTime> animTime;
                  if(type == PuffShroom){
                    animTime = animComponent[EnumAnimationIndex::ANIM_PuffShroom].GetTimeLapseFromLayer(layer);
                  }else if(type == FumeShroom){
                    animTime = animComponent[EnumAnimationIndex::ANIM_FumeShroom].GetTimeLapseFromLayer(layer);
                  }
                  FrameCounter frameCounter = frameCounterArray[plantAnims[i].entity[0]];

                  for(size_t k=0; k<animTime.size();k++){
                    if(frameCounter.firstFrame == animTime[k].start
                      && frameCounter.lastFrame == animTime[k].end){
                      plantSleep = true;
                      break;
                    }
                  }

                  if(plantSleep == false){
                    newProjectile(pointColliderArray[father], 40, enumProyectile::PuffShroom_PUF);
                  }   
                  break;
                } 
              }
              break;
            }
            default:
              break;
          }
        }
        break;
      }
    }
  } else if (type == SunFlower || type == SunShroom) {
    PS2Timer& sunTimer = timerArray[father];
    if (sunTimer.counterMS < sunTimer.maxMS) {
      sunTimer.addMSinCounter();
    } else {
      sunTimer.maxMS = 24000;
      sunTimer.resetCounter();
      size_t size = plantAnims.size();
      for(size_t i=0;i<size;i++){
        if(plantAnims[i].id == father){
          if(type == SunFlower){
            printf("plant create sun\n");
            sunManager.create(spriteArray[plantAnims[i].entity[0]].position, sunCost::normalSun, true);
          }else if(type == SunShroom){
            int layer = animComponent[EnumAnimationIndex::ANIM_SunShroom].GetAnimationNameID("anim_sleep");
   
            bool plantSleep = false;
            std::vector<AnimationTime> animTime = animComponent[EnumAnimationIndex::ANIM_SunShroom].GetTimeLapseFromLayer(layer);
            FrameCounter frameCounter = frameCounterArray[plantAnims[i].entity[0]];
            for(size_t k=0; k<animTime.size();k++){
              if(frameCounter.firstFrame == animTime[k].start
                && frameCounter.lastFrame == animTime[k].end){
                // printf("plant sleep\n");
                plantSleep = true;
                break;
              }
            }

            if(plantSleep == false){
              sunManager.create(spriteArray[plantAnims[i].entity[5]].position, sunCost::smallerSun, true);
            }
          }
          break;
        }
      }
    }
  } else if (type == CherryBomb) {
    size_t size = plantAnims.size();
    unsigned int frameIndex = size;
    for(size_t i=0;i<size;i++){
      if(plantAnims[i].id == father){
        frameIndex = i;
        break;
      }
    }
    if(frameIndex == size){ return 1;}
   
    if (frameCounterArray[plantAnims[frameIndex].entity[0]].IsLastframe() == true) {
      printf("explode\n");
      newExplosion(posArray[father], Vec2(256 / 1.6f, 256 / 1.6f), 1800,
                   enumProyectile::ExplosionPowie);
      lifeArray[father] = 0;
      // erase();
    }
  } else if (type == WallnutBowling){
    posArray[father].x++;
    for(size_t i=0; i < stopResponseCollisionZombiePlant.size();i++){
      if(stopResponseCollisionZombiePlant[i].plantID == father){
        collision = false;
      }
    }

    if(collision == false){
      for(size_t i=0; i < responseCollisionZombiePlant.size();i++){
        if(responseCollisionZombiePlant[i].plantID == father){
          for(size_t j=0; j < zombie.size();j++){
            if(zombie[j].boxColliderID == responseCollisionZombiePlant[i].zombieID && collision == false){
              if(speedArray[father] == 0){
                speedArray[father] = 2; // TODO: esto empieza con abajo o arriba y se usa el mismo estado para todos
              }if(speedArray[father] == 1){
                speedArray[father] = 2;
              }else if(speedArray[father] == 2){
                speedArray[father] = 1;
              }
              if(zombie[j].damage(father, Bowling) == true){
                zombie.erase(zombie.begin()+j);
              }
              // if(zombie[j].erase() == true){
              //   zombie.erase(zombie.begin()+j);
              // }
              collision = true;
              break;
            }
          }
          break;
        }
      }
    }
    if(speedArray[father] == 1){
      posArray[father].y++;
    }else if(speedArray[father] == 2){
      posArray[father].y--;
    }
    
    for(unsigned int i=0; i<boxColliderPlant.size();i++){
      if(boxColliderPlant[i].id == father){
        boxColliderPlant[i].x = posArray[father].x;
        boxColliderPlant[i].y = posArray[father].y;
        break;
      }
    }
  } else if (type == PotatoMine) {
    PS2Timer& potatoTimer = timerArray[father];
    printf("potato timer: %d\n", potatoTimer.counterMS);
    if (potatoTimer.counterMS < potatoTimer.maxMS) {
      potatoTimer.addMSinCounter();
    } else {
      printf("activar estado de explosion\n");
      BoxCollider plantBox = boxColliderArray[BOXCOLLIDER_PLANT][boxColliderArrayID[father]];
      for (BoxCollider& zomBox: zombieBox) {
        if (zomBox.collision(&plantBox) == true) {
          newExplosion(posArray[father], Vec2(64, 64), 1800,
                       enumProyectile::ExplosionSpudow);
          erase();  // TODO: arreglar la duracion de la palabra, esto hace que
                    // la palabra desaparezca de forma rapida
          break;
        }
      }
    }
  } else if (type == Chomper) {
    PS2Timer& chomperTimer = timerArray[father];
    // printf("maxMS: %d\n", chomperTimer.maxMS);
    if (chomperTimer.counterMS < chomperTimer.maxMS) {
      // printf("ms: %d\n", chomperTimer.counterMS);
      chomperTimer.addMSinCounter();
    }
    if (chomperTimer.counterMS >= chomperTimer.maxMS) {
      chomperTimer.counterMS = 0;
      chomperTimer.maxMS = 0;
    }
    // printf("dead zombies: %d\n",deadZombie.size());
    BoxCollider plantBox;
    for(unsigned int i=0; i<boxColliderPlant.size();i++){
      if(boxColliderPlant[i].id == father){
        plantBox = boxColliderPlant[i];
        break;
      }
    }
    for (BoxCollider& zomBox: zombieBox) {
      if (chomperTimer.maxMS == 0 &&
          zomBox.collision(&plantBox) ==
              true) {
        for(size_t i=0; i< plantAnims.size();i++){
          if(plantAnims[i].id == father){
            animComponent[EnumAnimationIndex::ANIM_Chomper].ChangeAnimationEntity(plantAnims[i].entity,"anim_bite",0,enumSpriteLayer::plants,true);
            break;
          }
        }
        chomperTimer.maxMS = 42000;
      }
    }
  }
  return 0;
}

void Plant::damage(const int entityID){
  damaged = true;
  lifeArray[father] -= damageArray[entityID];
  printf("plant life: %d\n",lifeArray[father]);
  size_t size = plantAnims.size();
  std::vector<unsigned int> indexes;
  for(size_t i=0; i < size; i++){
    if (plantAnims[i].id == father) {
      indexes.push_back(i);
    }
  }

  if(indexes.size() == 0) { return; }

  if(type == Wallnut){
    setWallnutAnimation();
  }

  for(unsigned int indexAnim : indexes){
    std::vector<int>& animEntity = plantAnims[indexAnim].entity;
    size = animEntity.size();
    for(size_t i=0; i < size; i++){
      if (spriteArray.count(animEntity[i]) == 1) {;
        spriteArray[animEntity[i]].color = Tyra::Color(255, 255, 255, 128);
      }
    }
  }
}

int Plant::normalColor(){
  if (damaged == false) {
    return 1;
  }

  size_t size = plantAnims.size();
  std::vector<unsigned int> indexes;

  for(size_t i=0; i < size; i++){
    if (plantAnims[i].id == father) {
      indexes.push_back(i);
    }
  }

  if(indexes.size() == 0) { return 1; }

  for(unsigned int indexAnim : indexes){
    std::vector<int>& ids = plantAnims[indexAnim].entity;
    size = ids.size();
    for(size_t i=0; i < size; i++){
      if (spriteArray.count(ids[i]) == 1) {
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
  }
  return 0;
}

void Plant::erase() {
  if(lifeArray.count(father) == 0){
    return;
  }
  
  if(lifeArray[father] <= 0 && type != NonePlant){
    printf("erase plant\n");
    printf("type: %d\n",type);
    plantCreatedInMap[row][column] = false;
    for(unsigned int i=0; i<boxColliderPlant.size();i++){
      if(boxColliderPlant[i].id == father){
        boxColliderPlant.erase(boxColliderPlant.begin()+i);
        break;
      }
    }
    deletePosArray(father);
    size_t animIndex;
    for(size_t i=0;i < plantAnims.size();i++){
      if(plantAnims[i].id == father){
        animIndex = i;
        break;
      }
    }
    
    std::vector<int>::iterator it = plantAnims[animIndex].entity.begin();
    while (it != plantAnims[animIndex].entity.end()) {
      deletePosArray(*it);
      deleteFinalPosArray(*it);
      deleteTexPosArray(*it);
      deleteFatherID(*it);
      deleteFatherIDChild(father, &*it);
      deleteFrameCounter(*it);

      deleteSprite(*it);
      Entities::deleteID(*it);
      it++;
    }
    // TODO: delete all plantAnims from 1 Plant
    plantAnims[animIndex].entity.clear();
    plantAnims.erase(plantAnims.begin() + animIndex);

    if (type == PeaShotter) {
      timerArray.erase(father);
      deleteDebugPoint(father);
    } else if (type == SunFlower) {
      timerArray.erase(father);
    } else if (type == SnowPea) {
      deleteDebugPoint(father);
    } else if (type == Repeater) {
      deleteDebugPoint(father);
    }
    deleteFatherID(father);

    if (type != CherryBomb) {
      lifeArray.erase(father);
    }

    deleteDebugBoxCollider(father);
    Entities::deleteID(father);
    type = NonePlant;
    plantsCreated--;
  }
}

void loadPlantCost() {
  plantCost[PeaShotter] = 100;
  plantCost[SunFlower] = 50;
  plantCost[CherryBomb] = 150;
  plantCost[Wallnut] = 50;
  plantCost[PotatoMine] = 25;
  plantCost[SnowPea] = 175;
  plantCost[Chomper] = 150;
  plantCost[Repeater] = 200;
  plantCost[PuffShroom] = 0;
  plantCost[SunShroom] = 25;
  plantCost[FumeShroom] = 75;
  plantCost[GraveBuster] = 75;
  plantCost[HypnoShroom] = 75;
  plantCost[ScaredyShroom] = 25;
  plantCost[IceShroom] = 75;
  plantCost[DoomShroom] = 125;
  plantCost[LilyPad] = 25;
  plantCost[Squash] = 50;
  plantCost[ThreePeater] = 325;
  plantCost[Tanglekelp] = 25;
  plantCost[Jalapeno] = 125;
  plantCost[Spikeweed] = 100;
  plantCost[Torchwood] = 175;
  plantCost[Tallnut] = 125;
  plantCost[SeaShroom] = 0;
  plantCost[Plantern] = 25;
  plantCost[Cactus] = 125;
  plantCost[Blover] = 100;
  plantCost[SplitPea] = 125;
  plantCost[Starfruit] = 125;
  plantCost[Pumpkin] = 125;
  plantCost[Magnetshroom] = 100;
  plantCost[Cabbagepult] = 100;
  plantCost[FlowerPot] = 25;
  plantCost[Kernelpult] = 100;
  plantCost[CoffeeBean] = 75;
  plantCost[Garlic] = 50;
  plantCost[UmbrellaLeaf] = 100;
  plantCost[Marigold] = 50;
  plantCost[Melonpult] = 300;
  plantCost[GatlingPea] = 250;
  plantCost[TwinSunflower] = 150;
  plantCost[GloomShroom] = 150;
  plantCost[Cattail] = 225;
  plantCost[WinterMelon] = 200;
  plantCost[GoldMagnet] = 50;
  plantCost[Spikerock] = 125;
  plantCost[CobCannon] = 500;
  plantCost[Imitator] = 0;  // this needs to copy the cost of another plant
}

int getPlantCost(Plant_State_enum typePlant) { return plantCost[typePlant]; }

int getPlantRechargeTime(Plant_State_enum typePlant, bool isVersusMode) {
  switch (typePlant) {
    case PeaShotter:
    case SunFlower:
    case SnowPea:
    case Chomper:
    case Repeater:
    case PuffShroom:
    case SunShroom:
    case FumeShroom:
    case ScaredyShroom:
    case LilyPad:
    case Spikeweed:
    case Torchwood:
    case Cactus:
    case Blover:
    case Starfruit:
    case Magnetshroom:
    case Cabbagepult:
    case FlowerPot:
    case Kernelpult:
    case CoffeeBean:
    case UmbrellaLeaf:
      return plantRechargeTime[fast];
    case Wallnut:
    case PotatoMine:
    case HypnoShroom:
    case Squash:
    case Tanglekelp:
    case Tallnut:
    case SeaShroom:
    case Plantern:
    case Pumpkin:
    case Marigold:
      return plantRechargeTime[slow];
    case CherryBomb:
    case IceShroom:
    case DoomShroom:
    case Jalapeno:
    case GatlingPea:
    case TwinSunflower:
    case GloomShroom:
    case Cattail:
    case WinterMelon:
    case GoldMagnet:
    case Spikerock:
    case CobCannon:
      return plantRechargeTime[verySlow];
    case GraveBuster:
    case ThreePeater:
    case SplitPea:
    case Garlic:
    case Melonpult:
      if (isVersusMode == false) {
        return plantRechargeTime[fast];
      }
      return plantRechargeTime[verySlow];
    case WallnutBowling:
    case WallnutBowlingExplosion:
      return 0;
    default:
      TYRA_ASSERT(!(true == true), "ERROR: PLANT RECHARGE TIME DON'T FOUNDED");
      break;
  }
  return 1;
}

bool startWithoutWait(Plant_State_enum typePlant, bool isVersusMode) {
  // Imitator is the same for the plant as it imitates.
  switch (typePlant) {
    case PeaShotter:
    case SunFlower:
    case PuffShroom:
    case SunShroom:
    case FumeShroom:
    case ScaredyShroom:
    case LilyPad:
    case Blover:
    case Magnetshroom:
    case Cabbagepult:
    case FlowerPot:
      return true;
    case PotatoMine:
    case Wallnut:
    case Tallnut:
      // start fast in versus mode
      // slow in other mode
      return isVersusMode;
    case SnowPea:
    case Chomper:
    case Repeater:
    case GraveBuster:
    case ThreePeater:
    case Spikeweed:
    case Torchwood:
    case Cactus:
    case Starfruit:
    case Kernelpult:
    case CoffeeBean:
    case Garlic:
    case UmbrellaLeaf:
    case Melonpult:
      // start slow in versus mode
      // fast in other mode
      if (isVersusMode == true) {
        return false;
      }
      return true;
    default:
      break;
  }
  return false;
}