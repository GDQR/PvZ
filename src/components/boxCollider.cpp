#include "components.hpp"

BoxCollider::BoxCollider() {}
BoxCollider::BoxCollider(float x, float y, float width, float height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

void BoxCollider::move(const int entityID, float offsetX, float offsetY) {
  x = offsetX + posArray[entityID].x;
  y = offsetY + posArray[entityID].y;
}

/*
 * @return True if collision exist
 */
bool BoxCollider::collision(const BoxCollider* box) {
  if (x + width >= box->x && box->x + box->width >= x && y + height >= box->y &&
      box->y + box->height >= y) {
    return true;
  }
  return false;
}

bool BoxCollider::pointCollision(const Tyra::Vec2* point) {
  if (point->x < x + width && point->y > y && point->y < y + height) {
    return true;
  }
  return false;
}