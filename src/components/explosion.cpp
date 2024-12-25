#include "components.hpp"
#include "systems.hpp"

void Explosion::erase() {
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  boxColliderArray.erase(id);
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}