#include "components.hpp"

void Card::update() {
  PS2Timer& timer = timerArray[seedShadowTimer];
  // printf("counter: %d\n", timer.counterMS);
  // printf("maxMS: %d\n", timer.maxMS);
  if (timer.counterMS <
      timer.maxMS) {
    timer.addMSinCounter();

    spriteArray[seedShadow].size = Vec2(50, 70);
    spriteArray[seedShadowTimer].size.y -= (70.0f * timer.getTimeInMS() / timer.maxMS);
  } else if (sunCounter >= cost) {
    spriteArray[seedShadow].size = Vec2(0, 0);
    spriteArray[seedShadowTimer].size = Vec2(0, 0);
  }
}