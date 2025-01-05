// File for all plants data
#include "entities/entities.hpp"
#include "entities/plants.hpp"
#include "components.hpp"
#include "systems.hpp"

int plantCost[enumMaxPlants];
int plantRechargeTime[enumMaxRecharge];
int plantsCreated = 0;

void loadPlantRechargeTime() {
  // values in milliseconds, is more easy for compare with the PS2Timer
  plantRechargeTime[fast] = 7500;       // 7.5 seconds
  plantRechargeTime[slow] = 30000;      // 30 seconds
  plantRechargeTime[verySlow] = 50000;  // 50 seconds
}

void createPeashotter(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::Peashooter].size());

  int entityID;
  int animID;

  int* father = &plant[id].father;
  for (unsigned int i = 0; i < m_animID[AnimIndex::Peashooter].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::Peashooter][i];
    // printf("plant ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             Tyra::Vec2(0.8f, 0.8f), 80, 104);
    // animationDataArray[animID].activeAnimation(entityID, 80, 104);
    // printf("draw: %d\n", animationArray[entityID].draw);
    // if (animationDataArray[animID].name == "anim_blink" ||
    //     animationDataArray[animID].name == "idle_shoot_blink") {
    //   // animationArray[entityID].draw = false;
    //   // setSprite(entityID, animationArray[entityID].draw);
    //   // deleteAnimation(entityID);
    //   // animationIdStopRender.push_back(entityID);
    //   printf("encontre anim_blink\n");
    // }
  }
  // printf("plant[%d].id[0]: %d\n",id,plant[id].id[0]);
  // printf("plant[%d].id[1]: %d\n",id,plant[id].id[1]);
  // printf("plant[%d].id[2]: %d\n",id,plant[id].id[2]);

  //  printf("father sprite pos: %f,%f\n",
  //        posArray[*plant[id].father].x,posArray[*plant[id].father].y);
  // printf("plant[%d].id[0] entitie:%d sprite pos: %f,%f\n", id,
  // *plant[id].body[0],
  //        posArray[*plant[id].body[0]].x,posArray[*plant[id].body[0]].y);
  // printf("plant[%d].id[1] entitie:%d sprite pos: %f,%f\n", id,
  // *plant[id].body[1],
  //        posArray[*plant[id].body[1]].x,posArray[*plant[id].body[1]].y);

  // texPosArray[*plant[id].body[0]] =
  // animationDataArray[peaShooterHead].position[0];
  // texPosArray[*plant[id].body[1]] =
  // animationDataArray[peaShooterBody].position[0];

  // Life

  lifeArray.insert(*father, 300);

  timerArray.insert(*father, PS2Timer());
  timerArray[*father].maxMS = 1500;

  // HitBox
  boxColliderArray[*father] = BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(*father, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[*father] = Tyra::Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(*father, Tyra::MODE_STRETCH);
}

void createSunflower(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::SunFlower].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::SunFlower].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::SunFlower][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(
        entityID, animID, Tyra::Vec2(0.8f, 0.8f), 5,
        animationDataArray[animID].maxFrame);
    // animationDataArray[animID].activeAnimation(entityID, 5,
    // animationDataArray[animID].maxFrame);
    // if (animationDataArray[animID].name == "anim_blink") {
    //   deleteAnimation(entityID);
    //   animationIdStopRender.push_back(entityID);
    //   animationArray[entityID].draw = (int)enumDraw::noDraw;
    //   // printf("encontre anim_blink\n");
    //   setSprite(entityID, animationArray[entityID].draw);
    // }
    // printf("draw: %d\n", animationArray[entityID].draw);
  }

  // Life

  lifeArray.insert(plant[id].father, 300);

  // time

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 7000;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void createCherryBomb(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::CherryBomb].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::CherryBomb].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::CherryBomb][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(
        entityID, animID, Tyra::Vec2(1, 1),
        enumAnimationState::explodeCherryBomb);
  }
  printf("lastframe: %d\n", animationArray[plant[id].id[0]].lastFrame);

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void createWallnut(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::Wallnut].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::Wallnut].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::Wallnut][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(1, 1),
                                             1, 17);
    // animationDataArray[animID].activeAnimation(entityID, 1, 17);
  }

  // Life

  lifeArray.insert(plant[id].father, 4000);

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void createPotatoMine(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::PotatoMine].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::PotatoMine].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::PotatoMine][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(1, 1),
                                             1, 1);
  }

  // Life

  lifeArray.insert(plant[id].father, 300);

  // time

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 15000;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void createSnowPea(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::SnowPea].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::SnowPea].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::SnowPea][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(1, 1),
                                             80, 104);
    // animationDataArray[animID].activeAnimation(entityID, 80, 104);
  }

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 1500;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);
}

void createChomper(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::Chomper].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::Chomper].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::Chomper][i];
    // printf("plant ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(1, 1),
                                             1, 25);
    // animationDataArray[animID].activeAnimation(entityID, 1, 25);
  }

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 0;

  damageArray[plant[id].father] = 1600;

  // lifeBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  // HitBox
  boxColliderArray[plant[id].id[0]] =
      BoxCollider(pos.x + 30, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
  createDebugBoxCollider(plant[id].id[0], Tyra::MODE_STRETCH);
}

void createRepeater(const int id, const Tyra::Vec2 pos) {
  printf("size: %d\n", m_animID[AnimIndex::Repeater].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID[AnimIndex::Repeater].size(); i++) {
    entityID = Entities::newID();
    plant[id].id.push_back(entityID);
    animID = m_animID[AnimIndex::Repeater][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(1, 1),
                                             80, 104);
    // animationDataArray[animID].activeAnimation(entityID, 80, 104);
  }

  // Life

  lifeArray.insert(plant[id].father, 300);

  timerArray.insert(plant[id].father, PS2Timer());
  timerArray[plant[id].father].maxMS = 1000;
  timerArray.insert(plant[id].id[0], PS2Timer());
  timerArray[plant[id].id[0]].maxMS = 0;

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void createPlant(Plant_State_enum typePlant, const int row, const int column) {
  if (plantCreatedInMap[row][column] == false) {
    plantCreatedInMap[row][column] = true;

    int plantPos = row * column + column;
    printf("new plant pos:%d\n", plantPos);

    plant[plantPos].newPlant(typePlant);
    plant[plantPos].row = row;
    plant[plantPos].column = column;
    plant[plantPos].father = Entities::newID();
    fatherIDArray.insert(plant[plantPos].father, FatherID());
    printf("plant father: %d\n", plant[plantPos].father);

    Tyra::Vec2 pos(mapCollider[row][column].x, mapCollider[row][column].y);
    posArray.insert(plant[plantPos].father, pos);

    switch (typePlant) {
      case PeaShotter:
        printf("peashooter\n");
        createPeashotter(plantPos, Vec2(mapCollider[row][column].x,
                                        mapCollider[row][column].y));
        break;
      case SunFlower:
        printf("sunflower\n");
        createSunflower(plantPos, Vec2(mapCollider[row][column].x,
                                       mapCollider[row][column].y));
        break;
      case CherryBomb:
        printf("cherryBomb");
        createCherryBomb(plantPos, Vec2(mapCollider[row][column].x,
                                        mapCollider[row][column].y));
        break;
      case Wallnut:
        printf("wallNut");
        createWallnut(plantPos, Vec2(mapCollider[row][column].x,
                                     mapCollider[row][column].y));
        break;
      case PotatoMine:
        printf("potatoMine");
        createPotatoMine(plantPos, Vec2(mapCollider[row][column].x,
                                        mapCollider[row][column].y));
        break;
      case SnowPea:
        printf("SnowPea");
        createSnowPea(plantPos, Vec2(mapCollider[row][column].x,
                                     mapCollider[row][column].y));
        break;
      case Chomper:
        printf("Chomper");
        createChomper(plantPos, Vec2(mapCollider[row][column].x,
                                     mapCollider[row][column].y));
        break;
      case Repeater:
        printf("Repeater");
        createRepeater(plantPos, Vec2(mapCollider[row][column].x,
                                      mapCollider[row][column].y));
        break;
      default:
        break;
    }
    plantsCreated++;
    // printf("estoy en tile %f,%f\n",cursorTile.x,cursorTile.y);
    // printf("plantas creadas: %d\n",plantsCreated);
  } else {
    printf("no se puede crear aqui, ya existe una planta\n");
  }
}

void Plant::newPlant(Plant_State_enum newType) { type = newType; }

int Plant::attack() {
  if (type == NonePlant) {
    return 1;
  }

  std::vector<Zombie>::iterator it;
  if (type == PeaShotter || type == SnowPea || type == Repeater) {
    for (it = zombie.begin(); it != zombie.end(); it++) {
      if (boxColliderArray[it->id[0]].pointCollision(
              &pointColliderArray[father])) {
        if (timerArray[father].counterMS < timerArray[father].maxMS) {
          timerArray[father].addMSinCounter();
        } else if (stopAnimation == false) {
          timerArray[father].resetCounter();
          if (type == PeaShotter) {
            newProjectile(pointColliderArray[father], 20, enumProyectile::pea);
          } else if (type == SnowPea) {
            newProjectile(pointColliderArray[father], 20,
                          enumProyectile::snowPea);
          } else if (type == Repeater) {
            newProjectile(pointColliderArray[father], 40, enumProyectile::pea);
            timerArray[id[0]].maxMS++;  // is used like a counter
            if (timerArray[id[0]].maxMS < 2) {
              timerArray[father].maxMS = 1000;
            } else {
              timerArray[father].maxMS = 1500;
              timerArray[id[0]].maxMS = 0;
            }
          }
        }
        break;
      }
    }
  } else if (type == Chomper) {
    for (it = zombie.begin(); it != zombie.end();) {
      if (timerArray[father].maxMS == 0 &&
          boxColliderArray[id[0]].collision(&boxColliderArray[it->id[0]]) ==
              true) {
        timerArray[father].maxMS = 42000;
        it->damage(father);
        it->erase();
        it = zombie.erase(it);
      } else {
        it++;
      }
    }
  }
  return 0;
}

void Plant::ability() {
  if (type == SunFlower) {
    if (timerArray[father].counterMS < timerArray[father].maxMS) {
      timerArray[father].addMSinCounter();
    } else {
      printf("sunflower create sun\n");
      timerArray[father].maxMS = 24000;
      timerArray[father].resetCounter();
      sunManager.create(spriteArray[id[0]].position, sunCost::normalSun, true);
    }
  } else if (type == CherryBomb) {
    if (animationArray[id[0]].currentFrame == animationArray[id[0]].lastFrame) {
      printf("explode\n");
      newExplosion(posArray[father], Vec2(256 / 1.6f, 256 / 1.6f), 1800,
                   enumProyectile::ExplosionPowie);
      erase();
    }
  } else if (type == Wallnut) {
    if (lifeArray[father] <= 2667) {
      printf("change animation\n");
    } else if (lifeArray[father] <= 1333) {
      printf("change animation\n");
    }
  } else if (type == PotatoMine) {
    printf("potato timer: %lld\n", timerArray[father].counterMS);
    if (timerArray[father].counterMS < timerArray[father].maxMS) {
      timerArray[father].addMSinCounter();
    } else {
      printf("activar estado de explosion\n");
      std::vector<Zombie>::iterator it = zombie.begin();
      for (; it < zombie.end(); it++) {
        if (boxColliderArray[father].collision(&boxColliderArray[it->id[0]]) ==
            true) {
          newExplosion(posArray[father], Vec2(64, 64), 1800,
                       enumProyectile::ExplosionSpudow);
          erase();  // TODO: arreglar la duracion de la palabra, esto hace que
                    // la palabra desaparezca de forma rapida
          break;
        }
      }
    }
  } else if (type == Chomper) {
    printf("maxMS: %lld\n", timerArray[father].maxMS);
    if (timerArray[father].counterMS < timerArray[father].maxMS) {
      printf("ms: %lld\n", timerArray[father].counterMS);
      timerArray[father].addMSinCounter();
    }
    if (timerArray[father].counterMS >= timerArray[father].maxMS) {
      timerArray[father].counterMS = 0;
      timerArray[father].maxMS = 0;
    }
  }
}

void Plant::erase() {
  printf("erase plant\n");
  plantCreatedInMap[row][column] = false;
  deletePosArray(father);
  std::vector<int>::iterator it = id.begin();
  while (it != id.end()) {
    deletePosArray(*it);
    deleteFinalPosArray(*it);
    deleteTexPosArray(*it);
    deleteFatherIDChild(&father, &*it);
    if (animationArray.count(*it)) {
      deleteAnimation(*it);
    }

    deleteSprite(*it);

    Entities::deleteID(*it);
    id.erase(it);
  }
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
  deleteFatherID(&father);

  if (type != CherryBomb) {
    lifeArray.erase(father);
  }

  deleteDebugBoxCollider(father);
  Entities::deleteID(father);
  type = NonePlant;
  plantsCreated--;
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
  plantCost[Threepeater] = 325;
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
    case Threepeater:
    case SplitPea:
    case Garlic:
    case Melonpult:
      if (isVersusMode == false) {
        return plantRechargeTime[fast];
      }
      return plantRechargeTime[verySlow];
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
    case Threepeater:
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