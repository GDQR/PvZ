// File for all plants data
#include "entities/plants.hpp"
#include "components.hpp"

int plantsCreated = 0;

void Plant::createSpace() {
  switch (type) {
    case PeaShotter:
      id.reserve(3);
      body.reserve(2);
      father = &id[0];
      body[0] = &id[1];
      body[1] = &id[2];
      // body[2] = &id[3];
      break;
    case SunFlower:
      id.reserve(3);
      body.reserve(2);
      father = &id[0];
      body[0] = &id[1];
      body[1] = &id[2];
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

  plant[id].id[0] = Entities::newID();
  plant[id].id[1] = Entities::newID();
  plant[id].id[2] = Entities::newID();

  // printf("plant[%d].id[0]: %d\n",id,plant[id].id[0]);
  // printf("plant[%d].id[1]: %d\n",id,plant[id].id[1]);
  // printf("plant[%d].id[2]: %d\n",id,plant[id].id[2]);

  newFatherID(plant[id].father, plant[id].body[0]);
  newFatherID(plant[id].father, plant[id].body[1]);

  posArray[*plant[id].father] = pos;  // Vec2(row, column);

  createSprite(*plant[id].body[0], Tyra::MODE_STRETCH, Vec2(0, 5),
               Vec2(128 / 1.6f, 128 / 1.6f));
  createSprite(*plant[id].body[1], Tyra::MODE_STRETCH, Vec2(0, 5),
               Vec2(128 / 1.6f, 128 / 1.6f));

  animationArray[*plant[id].body[0]] = Animation(peaShooterHead);

  animationDataArray[peaShooterHead].texture[0]->addLink(
      spriteArray[*plant[id].body[0]].id);
  animationDataArray[peaShooterBody].texture[0]->addLink(
      spriteArray[*plant[id].body[1]].id);

  // Life

  lifeArray[*plant[id].body[0]] = 300;

  // HitBox
  boxColliderArray[*plant[id].body[0]] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(*plant[id].body[0], Tyra::MODE_STRETCH);

  // proyectile
  pointColliderArray[*plant[id].body[0]] = Vec2(pos.x + 40, pos.y + 25);
  createDebugPoint(*plant[id].body[0], Tyra::MODE_STRETCH);
}

void deletePeashotter(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  posArray.erase(*plant[pos].father);
  posArray.erase(*plant[pos].body[0]);
  posArray.erase(*plant[pos].body[1]);

  deleteFatherID(plant[pos].father, plant[pos].body[0]);
  deleteFatherID(plant[pos].father, plant[pos].body[1]);

  animationArray.erase(*plant[pos].body[0]);

  deleteSprite(*plant[pos].body[0]);
  deleteSprite(*plant[pos].body[1]);

  lifeArray.erase(*plant[pos].body[0]);

  deleteDebugBoxCollider(*plant[pos].body[0]);
  deleteDebugPoint(*plant[pos].body[0]);
  Entities::deleteID(*plant[pos].father);
  Entities::deleteID(*plant[pos].body[0]);
  Entities::deleteID(*plant[pos].body[1]);
  plantsCreated--;
}

void createSunflower(const int id, int row, int col, Tyra::Vec2 pos) {
  plant[id].newPlant(SunFlower);

  plant[id].row = row;
  plant[id].column = col;

  plant[id].id[0] = Entities::newID();
  plant[id].id[1] = Entities::newID();
  plant[id].id[2] = Entities::newID();

  newFatherID(plant[id].father, plant[id].body[0]);
  newFatherID(plant[id].father, plant[id].body[1]);

  posArray[*plant[id].father] = pos;  // Vec2(row, column);

  createSprite(*plant[id].body[0], Tyra::MODE_STRETCH, Vec2(0, 5),
               Vec2(128 / 1.6f, 64 / 1.6f));
  // createSprite(*plant[id].body[1], Tyra::MODE_STRETCH, Vec2(0, 5),
  //              Vec2(128 / 1.6f, 128 / 1.6f));

  printf("plant[%d].id[0] sprite id: %d\n", id,
         spriteArray[*plant[id].body[0]].id);
  // printf("plant[%d].id[1] sprite id:
  // %d\n",id,spriteArray[*plant[id].body[1]].id); printf("plant[%d].id[2]:
  // %d\n",id,plant[id].id[2]);

  animationArray[*plant[id].body[0]] = Animation(SunFlowerHead);

  animationDataArray[SunFlowerHead].texture[0]->addLink(
      spriteArray[*plant[id].body[0]].id);
  // animationDataArray[peaShooterBody].texture[0]->addLink(
  //     spriteArray[*plant[id].body[1]].id);

  // Life

  lifeArray[*plant[id].body[0]] = 300;

  // time

  plant[id].attackTimer = 30;

  // HitBox
  boxColliderArray[*plant[id].body[0]] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(*plant[id].body[0], Tyra::MODE_STRETCH);
}

void deleteSunflower(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  posArray.erase(*plant[pos].father);
  posArray.erase(*plant[pos].body[0]);
  posArray.erase(*plant[pos].body[1]);

  deleteFatherID(plant[pos].father, plant[pos].body[0]);
  deleteFatherID(plant[pos].father, plant[pos].body[1]);

  animationArray.erase(*plant[pos].body[0]);

  deleteSprite(*plant[pos].body[0]);
  // deleteSprite(*plant[pos].body[1]);

  lifeArray.erase(*plant[pos].body[0]);

  deleteDebugBoxCollider(*plant[pos].body[0]);
  Entities::deleteID(*plant[pos].father);
  Entities::deleteID(*plant[pos].body[0]);
  Entities::deleteID(*plant[pos].body[1]);
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