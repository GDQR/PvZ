#include "entities/sun.hpp"
#include "components.hpp"
#include "entities/entities.hpp"
#include "font/font.hpp"
#include "systems.hpp"


int sunsCreated = 0;
int sunCounter = 1000;
int sunTimer = 60 * 6;
SunManager sunManager;

void SunManager::create(Tyra::Vec2 position, sunCost cost,
                        bool createdByPlant) {  
  Sun newSun;           
  newSun.cost = cost;
  newSun.father = Entities::newID();
  posArray.insert(newSun.father, position);

  fatherIDArray.insert(newSun.father, FatherID());

  if (createdByPlant == false) {
    NaturalSun newNaturalSun;
    newNaturalSun.father = newSun.father;
    naturalSun.push_back(newNaturalSun);
  }
  
  SetAnimationToEntity(newSun.id,newSun.father,AnimIndex::Sun,Tyra::Vec2(0.5f, 0.5f), 1, 12);

  // HitBox
  createBoxCollider(newSun.father,BoxColliderEnum::BOXCOLLIDER_SUN,BoxCollider(newSun.father, position.x-16,
                  position.y-16, 32, 32));
  createDebugBoxCollider(newSun.father, BoxColliderEnum::BOXCOLLIDER_SUN, Tyra::MODE_STRETCH);

  sunsCreated++;
  sun.push_back(newSun);
}

void SunManager::update(){
  if (debugMode == false) {
    updateNaturalSun();
  }

  if (stopAnimation == false) {
    createByTime();
    erase(cursor[0].id);
  }
}

void Sun::erase(const int cursorID) {
    printf("Deleting sun\n");
    sunCounter += cost;
    textArray[sunCounterText].text = std::to_string(sunCounter);

    for(size_t i=0; i<boxColliderSun.size();i++){
      if(boxColliderSun[i].id == father){
        boxColliderSun.erase(boxColliderSun.begin() + i);
      }
    }
    
    int size;
    while (id.size() > 0) {
      size = id.size()-1;
      // deleteDebugSprite(id[i]);
      // deleteDebugSpritePivot(id[i]);
      deleteSprite(id[size]);
      deleteAnimation(id[size]);
      deleteTexPosArray(id[size]);
      deleteFatherIDChild(&father, &id[size]);
      for(size_t j=0; j<frameCounterArray.size();j++){
        if(frameCounterArray[j].entityID == id[size]){
          frameCounterArray.erase(frameCounterArray.begin() + j);
        }
      }
      Entities::deleteID(id[size]);
      id.erase(id.begin()+size);
    }

    // delete natural sun if exists
    for (unsigned int i = 0; i < naturalSun.size(); i++) {
      if (naturalSun[i].father == father) {
        naturalSun.erase(naturalSun.begin() + i);
        break;
      }
    }

    deletePosArray(father);
    deleteFatherID(&father);
    Entities::deleteID(father);
    sunsCreated--;
}

void NaturalSun::move() {
  Tyra::Vec2& pos = posArray[father];
  if (pos.y < 370) {
    pos.y++;
    for(size_t i=0;i<boxColliderSun.size();i++){
      if(boxColliderSun[i].id == father){
        boxColliderSun[i].y++;
        break;
      }
    }
  }
}

void SunManager::createByTime() {
  if (sunTimer > 0) {
    sunTimer--;
  } else {
    sunTimer = 60 * 6;  // 6 seconds
    // min:50 max:420
    float x = 50 + rand() % 420;
    create(Vec2(x, 10), sunCost::normalSun, false);
  }
}

void SunManager::erase(const int cursorID) {
  size_t size = responseCollisionSunCursor.size();
  size_t sunSize;
  for(size_t i=0; i < size; i++){
    sunSize = sun.size();
    for(size_t j=0;j< sunSize;j++){
      if(sun[j].father == responseCollisionSunCursor[i].sunID){
        sun[j].erase(responseCollisionSunCursor[i].cursorID);
        break;
      }
    }
  }
}
void SunManager::updateNaturalSun() {
  for (NaturalSun& sun: naturalSun){
    sun.move();
  }
}