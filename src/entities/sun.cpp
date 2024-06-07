#include "entities/sun.hpp"
#include "components.hpp"

int sunsCreated = 0;

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