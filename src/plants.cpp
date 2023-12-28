// File for all plants data
#include "main.hpp"
#include "plants.hpp"
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

  // printf("plant[%d].id[0]: %d\n",pos,plant[pos].id[0]);
  // printf("plant[%d].id[1]: %d\n",pos,plant[pos].id[1]);
  // printf("plant[%d].id[2]: %d\n",pos,plant[pos].id[2]);

  vec2Array[*plant[id].father] = pos;  // Vec2(row, column);

  createSprite(*plant[id].body[0], Tyra::MODE_STRETCH, Vec2(pos.x, pos.y + 5),
               Vec2(128 / 1.6f, 128 / 1.6f));
  createSprite(*plant[id].body[1], Tyra::MODE_STRETCH, Vec2(pos.x, pos.y + 5),
               Vec2(128 / 1.6f, 128 / 1.6f));

  animationArray[*plant[id].body[0]] = Animation(peaShooterHead);

  animationDataArray[peaShooterHead].keys[0]->addLink(
      spriteArray[*plant[id].body[0]].id);
  animationDataArray[peaShooterBody].keys[0]->addLink(
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

  vec2Array.erase(*plant[pos].father);

  engine->renderer.getTextureRepository()
      .getBySpriteId(spriteArray[*plant[pos].body[0]].id)
      ->removeLinkById(spriteArray[*plant[pos].body[0]].id);

  engine->renderer.getTextureRepository()
      .getBySpriteId(spriteArray[*plant[pos].body[1]].id)
      ->removeLinkById(spriteArray[*plant[pos].body[1]].id);

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

void createPlant(const int row, const int column) {
  if (plantCreatedInMap[row][column] == false) {
    plantCreatedInMap[row][column] = true;
    createPeashotter(plantsCreated,row,column, Vec2(mapCollider[row][column].x,
                                         mapCollider[row][column].y));
    plantsCreated++;
    // printf("estoy en tile %f,%f\n",cursorTile.x,cursorTile.y);
    // printf("plantas creadas: %d\n",plantsCreated);
  } else {
    printf("no se puede crear aqui, ya existe una planta\n");
  }
}