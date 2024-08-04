// File for all plants data
#include "entities/entities.hpp"
#include "entities/plants.hpp"
#include "components.hpp"
#include "systems.hpp"

std::string plantsAnim[enumMaxPlants];
int plantCost[enumMaxPlants];
int plantRechargeTime[enumMaxRecharge];
int plantsCreated = 0;

void loadPlantRechargeTime() {
  // values in milliseconds, is more easy for compare with the PS2Timer
  plantRechargeTime[fast] = 7500;       // 7.5 seconds
  plantRechargeTime[slow] = 30000;      // 30 seconds
  plantRechargeTime[verySlow] = 50000;  // 50 seconds
}

void createPeashotter(int id, int row, int column, Tyra::Vec2 pos) {
  plant[id].newPlant(PeaShotter);

  plant[id].row = row;
  plant[id].column = column;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);  // Vec2(row, column);

  printf("size: %d\n", m_animID["PeaShooterSingle"].size());

  int entityID;
  int animID;
  // int spriteID;

  for (unsigned int i = 0; i < m_animID["PeaShooterSingle"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["PeaShooterSingle"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 80,104);
    // animationDataArray[animID].activeAnimation(entityID, 80, 104);
    // printf("draw: %d\n", animationArray[entityID].draw);
    if (animationDataArray[animID].name == "anim_blink" ||
        animationDataArray[animID].name == "idle_shoot_blink") {
      // animationArray[entityID].draw = false;
      // setSprite(entityID, animationArray[entityID].draw);
      // deleteAnimation(entityID);
      // animationIdStopRender.push_back(entityID);
      printf("encontre anim_blink\n");
    }
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

  lifeArray[plant[id].father] = 300;

  timerArray[plant[id].father].maxMS = 1500;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);
}

void deletePeashotter(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  std::vector<int>::iterator it = plant[pos].id.begin();
  while (it != plant[pos].id.end()) {
    deletePosArray(*it);
    deleteFinalPosArray(*it);
    deleteTexPosArray(*it);
    deleteFatherIDChild(&plant[pos].father, &*it);
    if(animationArray.count(*it)){
      deleteAnimation(*it);
    }

    deleteSprite(*it);   
    
    Entities::deleteID(*it);
    plant[pos].id.erase(it);
  }

  deleteFatherID(&plant[pos].father);

  lifeArray.erase(plant[pos].father);

  timerArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  deleteDebugPoint(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createSunflower(const int id, int row, int col, Tyra::Vec2 pos) {
  plant[id].newPlant(SunFlower);

  plant[id].row = row;
  plant[id].column = col;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);  // Vec2(row, column);

  printf("size: %d\n", m_animID["SunFlower"].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID["SunFlower"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["SunFlower"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 5, animationDataArray[animID].maxFrame);
    // animationDataArray[animID].activeAnimation(entityID, 5, animationDataArray[animID].maxFrame);
    if (animationDataArray[animID].name == "anim_blink") {
      deleteAnimation(entityID);
      animationIdStopRender.push_back(entityID);
      animationArray[entityID].draw = (int) enumDraw::noDraw;
      // printf("encontre anim_blink\n");
      setSprite(entityID, animationArray[entityID].draw);
    }
    // printf("draw: %d\n", animationArray[entityID].draw);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // time

  timerArray[plant[id].father].maxMS = 7000;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteSunflower(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["SunFlower"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  deleteFatherID(&plant[pos].father);

  lifeArray.erase(plant[pos].father);

  timerArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createCherryBomb(const int id, int row, int col, Tyra::Vec2 pos) {
  plant[id].newPlant(CherryBomb);

  plant[id].row = row;
  plant[id].column = col;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);

  printf("size: %d\n", m_animID["CherryBomb"].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID["CherryBomb"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["CherryBomb"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 1, 13);
    // animationDataArray[animID].activeAnimation(entityID, 1, 13);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteCherryBomb(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["CherryBomb"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  deleteFatherID(&plant[pos].father);

  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createWallnut(const int id, int row, int col, Tyra::Vec2 pos) {
  plant[id].newPlant(Wallnut);

  plant[id].row = row;
  plant[id].column = col;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);

  printf("size: %d\n", m_animID["Wallnut"].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID["Wallnut"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["Wallnut"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 1, 17);
    // animationDataArray[animID].activeAnimation(entityID, 1, 17);
  }

  // Life

  lifeArray[plant[id].father] = 4000;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteWallNut(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["Wallnut"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  deleteFatherID(&plant[pos].father);

  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createPotatoMine(const int id, int row, int col, Tyra::Vec2 pos) {
  plant[id].newPlant(PotatoMine);

  plant[id].row = row;
  plant[id].column = col;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);

  printf("size: %d\n", m_animID["PotatoMine"].size());

  int entityID;
  int animID;

  for (unsigned int i = 0; i < m_animID["PotatoMine"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["PotatoMine"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 1, 2);
    // animationDataArray[animID].activeAnimation(entityID, 1, 2);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // time

  plant[id].attackTimer = 30;  // TODO: change this

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deletePotatoMine(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["PotatoMine"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  deleteFatherID(&plant[pos].father);
  
  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createSnowPea(int id, int row, int column, Tyra::Vec2 pos) {
  plant[id].newPlant(SnowPea);

  plant[id].row = row;
  plant[id].column = column;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);  // Vec2(row, column);

  printf("size: %d\n", m_animID["SnowPea"].size());

  int entityID;
  int animID;
  // int spriteID;

  for (unsigned int i = 0; i < m_animID["SnowPea"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["SnowPea"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 80, 104);
    // animationDataArray[animID].activeAnimation(entityID, 80, 104);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  timerArray[plant[id].father].maxMS = 1500;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteSnowPea(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["SnowPea"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }
  
  deleteFatherID(&plant[pos].father);

  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  deleteDebugPoint(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createChomper(int id, int row, int column, Tyra::Vec2 pos) {
  plant[id].newPlant(Chomper);

  plant[id].row = row;
  plant[id].column = column;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos);  // Vec2(row, column);

  printf("size: %d\n", m_animID["Chomper"].size());

  int entityID;
  int animID;
  // int spriteID;

  for (unsigned int i = 0; i < m_animID["Chomper"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["Chomper"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 1, 25);
    // animationDataArray[animID].activeAnimation(entityID, 1, 25);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteChomper(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["Chomper"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  deleteFatherID(&plant[pos].father);
  
  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createRepeater(int id, int row, int column, Tyra::Vec2 pos) {
  plant[id].newPlant(Repeater);

  plant[id].row = row;
  plant[id].column = column;

  plant[id].father = Entities::newID();

  posArray.insert(plant[id].father, pos); // Vec2(row, column);

  printf("size: %d\n", m_animID["PeaShooter"].size());

  int entityID;
  int animID;
  // int spriteID;

  for (unsigned int i = 0; i < m_animID["PeaShooter"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["PeaShooter"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, 80, 104);
    // animationDataArray[animID].activeAnimation(entityID, 80, 104);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // proyectile
  pointColliderArray[plant[id].father] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(plant[id].father, Tyra::MODE_STRETCH);

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteRepeater(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  deletePosArray(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["Repeater"].size(); i++) {
    deletePosArray(plant[pos].id[i]);
    deleteTexPosArray(plant[pos].id[i]);
    deleteFatherIDChild(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  deleteFatherID(&plant[pos].father);
  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  deleteDebugPoint(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createPlant(Plant_State_enum typePlant, const int row, const int column) {
  if (plantCreatedInMap[row][column] == false) {
    plantCreatedInMap[row][column] = true;

    int plantPos = row * column + column;
    switch (typePlant) {
      case PeaShotter:
        printf("peashooter\n");
        createPeashotter(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case SunFlower:
        printf("sunflower\n");
        createSunflower(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case CherryBomb:
        printf("cherryBomb");
        createCherryBomb(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case Wallnut:
        printf("wallNut");
        createWallnut(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case PotatoMine:
        printf("potatoMine");
        createPotatoMine(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case SnowPea:
        printf("SnowPea");
        createSnowPea(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case Chomper:
        printf("Chomper");
        createChomper(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
      case Repeater:
        printf("Repeater");
        createRepeater(
            plantPos, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
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

void Plant::createSpace() {
  switch (type) {
    case PeaShotter:
      break;
    case SunFlower:
      id.reserve(3);
    default:
      break;
  }
}

void Plant::newPlant(Plant_State_enum newType) {
  type = newType;
  createSpace();
}

int Plant::attack() {
  if (type == NonePlant) {
    return 1;
  }

  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); it++) {
    if (type == PeaShotter || type == SnowPea || type == Repeater) {
      //  printf("vec plant %f,%f. vec zombi %f,%f,%f,%f\n",
      //  pointColliderArray[*plant[i].body[0]].x,
      //  pointColliderArray[*plant[i].body[0]].y,
      //  boxColliderArray[*zombie[j].body[0]].x,
      //  boxColliderArray[*zombie[j].body[0]].y,
      //  boxColliderArray[*zombie[j].body[0]].x +
      //  boxColliderArray[*zombie[j].body[0]].width,
      //  boxColliderArray[*zombie[j].body[0]].y +
      //  boxColliderArray[*zombie[j].body[0]].height)
      if (pointColliderArray[father].x <
              boxColliderArray[it->id[0]].x +
                  boxColliderArray[it->id[0]].width &&
          pointColliderArray[father].y > boxColliderArray[it->id[0]].y &&
          pointColliderArray[father].y <
              boxColliderArray[it->id[0]].y +
                  boxColliderArray[it->id[0]].height) {
        // printf("hay un zombi en frente\n");
        if (timerArray[father].counterMS < timerArray[father].maxMS) {
          timerArray[father].addMSinCounter();
        } else if (stopAnimation == false) {
          timerArray[father].resetCounter();
          if (type == PeaShotter) {
            newProjectile(pointColliderArray[father], 20, true);
          } else if (type == SnowPea) {
            newProjectile(pointColliderArray[father], 20, false);
          } else if (type == Repeater) {
            newProjectile(pointColliderArray[father], 40, true);
            attackTimer++;  // is used like a counter
            if (attackTimer < 2) {
              timerArray[father].maxMS = 1000;
            } else {
              timerArray[father].maxMS = 1500;
              attackTimer = 0;
            }
          }
        }
        it = zombie.end();
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
    }
  } else if (type == Wallnut) {
    if (lifeArray[father] <= 2667) {
      printf("change animation\n");
    } else if (lifeArray[father] <= 1333) {
      printf("change animation\n");
    }
  }
}

void Plant::erase(const int entityID) {
  if (type == PeaShotter) {
    deletePeashotter(entityID);
  } else if (type == SunFlower) {
    deleteSunflower(entityID);
  } else if (type == CherryBomb) {
    deleteCherryBomb(entityID);
  } else if (type == Wallnut) {
    deleteWallNut(entityID);
  } else if (type == SnowPea) {
    deleteSnowPea(entityID);
  } else if (type == Chomper) {
    deleteChomper(entityID);
  } else if (type == Repeater) {
    deleteRepeater(entityID);
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

void loadPlantAnimString() {
  plantsAnim[PeaShotter] = "PeaShooterSingle";
  plantsAnim[SunFlower] = "SunFlower";
  plantsAnim[CherryBomb] = "CherryBomb";
  plantsAnim[Wallnut] = "Wallnut";
  plantsAnim[PotatoMine] = "PotatoMine";
  plantsAnim[SnowPea] = "SnowPea";
  plantsAnim[Chomper] = "Chomper";
  plantsAnim[Repeater] = "PeaShooter";
  plantsAnim[PuffShroom] = "PuffShroom";
  plantsAnim[SunShroom] = "SunShroom";
  plantsAnim[FumeShroom] = "FumeShroom";
  plantsAnim[GraveBuster] = "Gravebuster";
  plantsAnim[HypnoShroom] = "HypnoShroom";
  plantsAnim[ScaredyShroom] = "ScaredyShroom";
  plantsAnim[IceShroom] = "IceShroom";
  plantsAnim[DoomShroom] = "DoomShroom";
  plantsAnim[LilyPad] = "LilyPad";
  plantsAnim[Squash] = "Squash";
  plantsAnim[Threepeater] = "ThreePeater";
  plantsAnim[Tanglekelp] = "Tanglekelp";
  plantsAnim[Jalapeno] = "Jalapeno";
  plantsAnim[Spikeweed] = "Caltrop";
  plantsAnim[Torchwood] = "Torchwood";
  plantsAnim[Tallnut] = "Tallnut";
  plantsAnim[SeaShroom] = "SeaShroom";
  plantsAnim[Plantern] = "Plantern";
  plantsAnim[Cactus] = "Cactus";
  plantsAnim[Blover] = "Blover";
  plantsAnim[SplitPea] = "SplitPea";
  plantsAnim[Starfruit] = "Starfruit";
  plantsAnim[Pumpkin] = "Pumpkin";
  plantsAnim[Magnetshroom] = "Magnetshroom";
  plantsAnim[Cabbagepult] = "Cabbagepult";
  plantsAnim[FlowerPot] = "Pot";
  plantsAnim[Kernelpult] = "Cornpult";
  plantsAnim[CoffeeBean] = "Coffeebean";
  plantsAnim[Garlic] = "Garlic";
  plantsAnim[UmbrellaLeaf] = "Umbrellaleaf";
  plantsAnim[Marigold] = "Marigold";
  plantsAnim[Melonpult] = "Melonpult";
  plantsAnim[GatlingPea] = "GatlingPea";
  plantsAnim[TwinSunflower] = "TwinSunflower";
  plantsAnim[GloomShroom] = "GloomShroom";
  plantsAnim[Cattail] = "Cattail";
  plantsAnim[WinterMelon] = "WinterMelon";
  plantsAnim[GoldMagnet] = "GoldMagnet";
  plantsAnim[Spikerock] = "SpikeRock";
  plantsAnim[CobCannon] = "CobCannon";
  plantsAnim[Imitator] = "Imitater";
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