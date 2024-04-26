#include "entities/sun.hpp"
#include "components.hpp"

int sunsCreated = 0;

void createSun(Tyra::Vec2 position, sunCost cost) {
  sun.push_back(Sun());
  int indexpos = sun.size() - 1;
  sun[indexpos].id = Entities::newID();
  sun[indexpos].cost = cost;
  printf("sun id: %d\n", sun[indexpos].id);

  posArray[sun[indexpos].id] = position;
  spriteArray[sun[indexpos].id] = Sprite();

  loadSprite(&spriteArray[sun[indexpos].id], Tyra::MODE_STRETCH,
             posArray[sun[indexpos].id], Vec2(128 / 1.5f, 128 / 1.5f));

  // HitBox
  boxColliderArray[sun[indexpos].id] =
      BoxCollider(position.x + 31, position.y + 32, 32, 32);

  createDebugBoxCollider(sun[indexpos].id, Tyra::MODE_STRETCH);

  animationArray[sun[indexpos].id] = Animation(enumAnimation::sunAnim);
  animationDataArray[sunAnim].keys[0]->addLink(
      spriteArray[sun[indexpos].id].id);

  sunsCreated++;
}

// borrar
// void createSunSuavizado(Tyra::Vec2 position){
//   sun.push_back(Sun());
//   int indexpos = sun.size()-1;
//   sun[indexpos].id = Entities::newID();
//   printf("sun id: %d\n",sun[indexpos].id);

//   posArray[sun[indexpos].id] = position;
//   spriteArray[sun[indexpos].id] = Sprite();

//   loadSprite(&spriteArray[sun[indexpos].id], Tyra::MODE_STRETCH,
//              posArray[sun[indexpos].id], Vec2(128, 128));

//   animationArray[sun[indexpos].id] = Animation(enumAnimation::sunAnim2);
//   animationDataArray[sunAnim2].keys[0]->addLink(
//       spriteArray[sun[indexpos].id].id);
//   sunsCreated++;

// }