#include "components.hpp"
#include "systems.hpp"

bool Proyectile::move() {
  boxColliderArray[id].x++;
  posArray[id].x++;
  if (posArray[id].x >= 580) {
    // delete projectile
    printf("deleting projectile\n");
    erase();
    return true;
  }
  return false;
}

void Proyectile::erase() {
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  boxColliderArray.erase(id);
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}
