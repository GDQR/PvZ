// File for all plants data
#include "entities/plants.hpp"
#include "renderSprite/animations.hpp"
#include "systems.hpp"

int plantsCreated = 0;

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

void createPeashotter(int id, int row, int column, Tyra::Vec2 pos) {
  plant[id].newPlant(PeaShotter);

  plant[id].row = row;
  plant[id].column = column;

  plant[id].father = Entities::newID();

  posArray[plant[id].father] = pos;  // Vec2(row, column);

  printf("size: %d\n", m_animID["PeaShooterSingle"].size());

  int entityID;
  int animID;
  // int spriteID;

  for (unsigned int i = 0; i < 12/*m_animID["PeaShooterSingle"].size()*/; i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["PeaShooterSingle"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    loadAnimationSprite(entityID, animID);
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

  posArray.erase(plant[pos].father);
  posArray.erase(plant[pos].id[0]);
  posArray.erase(plant[pos].id[1]);

  deleteFatherID(&plant[pos].father, &plant[pos].id[0]);
  deleteFatherID(&plant[pos].father, &plant[pos].id[1]);

  animationArray.erase(plant[pos].id[0]);

  deleteSprite(plant[pos].id[0]);
  deleteSprite(plant[pos].id[1]);

  lifeArray.erase(plant[pos].id[0]);

  deleteDebugBoxCollider(plant[pos].id[0]);
  deleteDebugPoint(plant[pos].id[0]);
  Entities::deleteID(plant[pos].father);
  Entities::deleteID(plant[pos].id[0]);
  Entities::deleteID(plant[pos].id[1]);
  plantsCreated--;
}

void createSunflower(const int id, int row, int col, Tyra::Vec2 pos) {
  // plant[id].newPlant(SunFlower);

  // plant[id].row = row;
  // plant[id].column = col;

  // plant[id].id[0] = Entities::newID();
  // plant[id].id[1] = Entities::newID();
  // plant[id].id[2] = Entities::newID();

  // newFatherID(&plant[id].father, &plant[id].id[0]);
  // newFatherID(&plant[id].father, &plant[id].id[1]);

  // posArray[plant[id].father] = pos;  // Vec2(row, column);

  // createSprite(plant[id].id[0], Tyra::MODE_STRETCH, Vec2(0, 5),
  //              Vec2(128 / 1.6f, 64 / 1.6f));
  // // createSprite(*plant[id].body[1], Tyra::MODE_STRETCH, Vec2(0, 5),
  // //              Vec2(128 / 1.6f, 128 / 1.6f));

  // // printf("plant[%d].id[0] sprite id: %d\n", id,
  // //        spriteArray[*plant[id].body[0]].id);
  // // printf("plant[%d].id[1] sprite id:
  // // %d\n",id,spriteArray[*plant[id].body[1]].id); printf("plant[%d].id[2]:
  // // %d\n",id,plant[id].id[2]);

  // animationArray[plant[id].id[0]] = Animation(SunFlowerHead);

  // animationDataArray[SunFlowerHead].texture[0]->addLink(
  //     spriteArray[plant[id].id[0]].id);
  // // animationDataArray[peaShooterBody].texture[0]->addLink(
  // //     spriteArray[*plant[id].body[1]].id);

  // // Life

  // lifeArray[plant[id].id[0]] = 300;

  // // time

  // plant[id].attackTimer = 30;

  // // HitBox
  // boxColliderArray[plant[id].id[0]] =
  //     BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  // createDebugBoxCollider(plant[id].id[0], Tyra::MODE_STRETCH);
}

void deleteSunflower(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  posArray.erase(plant[pos].father);
  posArray.erase(plant[pos].id[0]);
  posArray.erase(plant[pos].id[1]);

  deleteFatherID(&plant[pos].father, &plant[pos].id[0]);
  deleteFatherID(&plant[pos].father, &plant[pos].id[1]);

  animationArray.erase(plant[pos].id[0]);

  deleteSprite(plant[pos].id[0]);
  // deleteSprite(*plant[pos].body[1]);

  lifeArray.erase(plant[pos].id[0]);

  deleteDebugBoxCollider(plant[pos].id[0]);
  Entities::deleteID(plant[pos].father);
  Entities::deleteID(plant[pos].id[0]);
  Entities::deleteID(plant[pos].id[1]);
  plantsCreated--;
}

void createPlant(Plant_State_enum typePlant, const int row, const int column) {
  if (plantCreatedInMap[row][column] == false) {
    plantCreatedInMap[row][column] = true;
    plantsCreated++;

    switch (typePlant) {
      case PeaShotter:
        printf("peashooter\n");
        createPeashotter(
            plantsCreated, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;
      case SunFlower:
        printf("sunflower\n");
        createSunflower(
            plantsCreated, row, column,
            Vec2(mapCollider[row][column].x, mapCollider[row][column].y));
        break;

      default:
        break;
    }

    // printf("estoy en tile %f,%f\n",cursorTile.x,cursorTile.y);
    // printf("plantas creadas: %d\n",plantsCreated);
  } else {
    printf("no se puede crear aqui, ya existe una planta\n");
  }
}

int getPlantCost(Plant_State_enum typePlant) {
  switch (typePlant) {
    case PeaShotter:
      printf("peashooter\n");
      return 100;
    case SunFlower:
      printf("sunflower\n");
      return 50;
    default:
      break;
  }
  return 0;
}