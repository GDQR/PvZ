#include "components.hpp"

void Cursor::move() {
  float x = 0.0F;
  float y = 0.0F;

  if (leftJoy->h <= 100) {
    x = -cursorSpeed;
  } else if (leftJoy->h >= 200) {
    x = cursorSpeed;
  }

  if (leftJoy->v <= 100) {
    y = -cursorSpeed;
  } else if (leftJoy->v >= 200) {
    y = cursorSpeed;
  }

  posArray[id] += Vec2(x, y);
  if (spriteArray[id].position.x != posArray[id].x ||
      spriteArray[id].position.y != posArray[id].y) {
    if (cursorTimer < 20) {
      cursorTimer++;

      if (cursorTimer == 10) {
        cursorSpeed = 1.5f;
      } else if (cursorTimer == 20) {
        cursorSpeed = 2.0f;
      }
    }

  } else {
    cursorTimer = 0;
    cursorSpeed = 1;
  }
}
