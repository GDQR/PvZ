// File for all plants data
#include "entities/plants.hpp"
#include "renderSprite/animations.hpp"
#include "components.hpp"
#include "systems.hpp"

int plantsCreated = 0;

void deletePeashotter(const int pos);
void deleteSunflower(const int pos);

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

int Plant::attack(){
  if(type == NonePlant){
    return 1;
  }

  std::vector<Zombie>::iterator it;

  for (it = zombie.begin(); it < zombie.end(); it++) {
    if(type == PeaShotter){
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
          pointColliderArray[father].y >
              boxColliderArray[it->id[0]].y &&
          pointColliderArray[father].y <
              boxColliderArray[it->id[0]].y +
                  boxColliderArray[it->id[0]].height) {
        // printf("hay un zombi en frente\n");
        if (attackTimer >= 0) {
          attackTimer--;
        } else if (stopAnimation == false) {
          // printf("disparar\n");
          newProjectile(pointColliderArray[father]);
          attackTimer = 60;
        }
        it = zombie.end();
      }
    } 
  }
  return 0;
}

void Plant::ability(){
  if (type == SunFlower) {
    if (attackTimer > 0) {
      attackTimer--;
    } else {
      printf("sunflower create sun\n");
      sunManager.create(spriteArray[id[0]].position, sunCost::normalSun,
                 true);
      attackTimer = 60 * 6;
    }
  }
}

void Plant::erase(const int entityID){
  if (type == PeaShotter) {
    deletePeashotter(entityID);
  } else if (type == SunFlower) {
    deleteSunflower(entityID);
  }
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

  for (unsigned int i = 0; i < m_animID["PeaShooterSingle"].size(); i++) {
    plant[id].id.push_back(Entities::newID());
    entityID = plant[id].id[i];
    animID = m_animID["PeaShooterSingle"][i];
    printf("plant ID: %d\n", entityID);
    printf("animID: %d\n", animID);
    newFatherID(&plant[id].father, &entityID);
    loadAnimationSprite(entityID, animID);
    animationArray[entityID].firstFrame = 79;
    animationArray[entityID].lastFrame = 104;
    animationArray[entityID].currentFrame = 79;
    animationArray[entityID].draw = true;
    if (animationDataArray[animID].name == "anim_blink" ||
          animationDataArray[animID].name == "idle_shoot_blink") {
        deleteAnimation(entityID);
        animationIdStopRender.push_back(entityID);
        animationArray[entityID].draw = false;
        printf("encontre anim_blink\n");
      setSprite(entityID, animID);
    }
    printf("draw: %d\n", animationArray[entityID].draw);
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

  for (unsigned int i = 0; i < m_animID["PeaShooterSingle"].size(); i++) {
    posArray.erase(plant[pos].id[i]);
    deleteFatherID(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  lifeArray.erase(plant[pos].father);

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

  posArray[plant[id].father] = pos;  // Vec2(row, column);

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
    loadAnimationSprite(entityID, animID);
    animationArray[entityID].firstFrame = 4;
    animationArray[entityID].lastFrame = animationDataArray[animID].maxFrame;
    animationArray[entityID].currentFrame = 4;
    // animationArray[entityID].draw = true;
    if (animationDataArray[animID].name == "anim_blink") {
      deleteAnimation(entityID);
      animationIdStopRender.push_back(entityID);
      animationArray[entityID].draw = false;
      // printf("encontre anim_blink\n");
      setSprite(entityID, animID);
    }
    // printf("draw: %d\n", animationArray[entityID].draw);
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // time

  plant[id].attackTimer = 30;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
}

void deleteSunflower(const int pos) {
  plant[pos].type = NonePlant;

  plantCreatedInMap[plant[pos].row][plant[pos].column] = false;

  posArray.erase(plant[pos].father);

  for (unsigned int i = 0; i < m_animID["SunFlower"].size(); i++) {
    posArray.erase(plant[pos].id[i]);
    deleteFatherID(&plant[pos].father, &plant[pos].id[i]);
    deleteAnimation(plant[pos].id[i]);
    deleteSprite(plant[pos].id[i]);
    Entities::deleteID(plant[pos].id[i]);
  }

  lifeArray.erase(plant[pos].father);

  deleteDebugBoxCollider(plant[pos].father);
  Entities::deleteID(plant[pos].father);
  plantsCreated--;
}

void createCherryBomb(const int id, int row, int col, Tyra::Vec2 pos){
  plant[id].newPlant(CherryBomb);

  plant[id].row = row;
  plant[id].column = col;

  plant[id].father = Entities::newID();

  posArray[plant[id].father] = pos;

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
    loadAnimationSprite(entityID, animID);
    animationArray[entityID].firstFrame = 0;
    animationArray[entityID].lastFrame = 13;
    animationArray[entityID].currentFrame = 0;
  }

  // Life

  lifeArray[plant[id].father] = 300;

  // time

  plant[id].attackTimer = 30;

  // HitBox
  boxColliderArray[plant[id].father] =
      BoxCollider(pos.x + 10, pos.y + 20, 28, 38);
  createDebugBoxCollider(plant[id].father, Tyra::MODE_STRETCH);
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
      case CherryBomb:
        printf("cherryBomb");
        createCherryBomb(
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