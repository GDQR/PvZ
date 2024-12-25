#include "components.hpp"

void Card::update() {
  if (timerArray[seedShadowTimer].counterMS <
      timerArray[seedShadowTimer].maxMS) {
    timerArray[seedShadowTimer].addMSinCounter();

    spriteArray[seedShadow].size = Vec2(50, 70);
    spriteArray[seedShadowTimer].size.x = 50;
    spriteArray[seedShadowTimer].size.y -=
        (70.0f * timerArray[seedShadowTimer].getTimeInMS() /
         timerArray[seedShadowTimer].maxMS);
  } else if (sunCounter >= cost) {
    spriteArray[seedShadow].size = Vec2(0, 0);
    spriteArray[seedShadowTimer].size = Vec2(0, 0);
  }
}