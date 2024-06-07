#include "entities/sun.hpp"
#include "components.hpp"

int sunsCreated = 0;
int sunCounter = 100;

void createSun(Tyra::Vec2 position, sunCost cost, bool createdByPlant) {
  sun.push_back(Sun());
  int indexpos = sun.size() - 1;
  sun[indexpos].id = Entities::newID();
  sun[indexpos].cost = cost;
  // printf("sun id: %d\n", sun[indexpos].id);

  createSprite(sun[indexpos].id, Tyra::MODE_STRETCH, position,
               Vec2(128 / 1.5f, 128 / 1.5f));

  // HitBox
  boxColliderArray[sun[indexpos].id] =
      BoxCollider(position.x + 31, position.y + 32, 32, 32);

  createDebugBoxCollider(sun[indexpos].id, Tyra::MODE_STRETCH);

  animationArray[sun[indexpos].id] = Animation(enumAnimation::sunAnim);
  animationDataArray[sunAnim].keys[0]->addLink(
      spriteArray[sun[indexpos].id].id);
  if (createdByPlant == false) {
    naturalSunIds.push_back(sun[indexpos].id);
  }
  sunsCreated++;
}

void deleteSun(const int cursorID) {
  for (std::vector<Sun>::iterator it = sun.begin(); it != sun.end();) {
    if (boxCollision(&boxColliderArray[cursorID], &boxColliderArray[it->id])) {
      printf("Deleting sun\n");
      sunCounter += it->cost;
      deleteSprite(it->id);
      boxColliderArray.erase(it->id);

      animationArray.erase(it->id);
      deleteDebugBoxCollider(it->id);
      Entities::deleteID(it->id);

      // delete natural sun if exists
      std::vector<int>::iterator it2 =
          find(naturalSunIds.begin(), naturalSunIds.end(), it->id);
      if (it2 != naturalSunIds.end()) {
        it2 = naturalSunIds.erase(it2);
      }

      it = sun.erase(it);
      sunsCreated--;
    } else {
      it++;
    }
  }
}

void moveNaturalSun() {
  for (std::vector<int>::iterator it = naturalSunIds.begin();
       it != naturalSunIds.end(); it++) {
    if (posArray[(*it)].y < 370) {
      posArray[(*it)].y++;
      boxColliderArray[(*it)].y++;
      debugSpriteBoxCollider[(*it)].position.y = boxColliderArray[(*it)].y;
    }
  }
}