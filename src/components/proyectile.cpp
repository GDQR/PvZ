#include "components.hpp"
#include "systems.hpp"

bool Proyectile::move() {
  // boxColliderArray[id].x++;
  // boxColliderArray[BOXCOLLIDER_PROYECTILE][boxColliderArrayID[id]].x++;
  for(unsigned int i=0; i < boxColliderProyectile.size();i++){
    if(boxColliderProyectile[i].id == id){
      boxColliderProyectile[i].x++;
      break;
    }
  }
  posArray[id].x++;
  if (posArray[id].x >= 580) {
    // delete projectile
    printf("deleting projectile\n");
    return true;
  }
  return false;
}

void Proyectile::erase() {
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  
  for(unsigned int i=0; i<boxColliderProyectile.size();i++){
    if(boxColliderProyectile[i].id == id){
      boxColliderProyectile.erase(boxColliderProyectile.begin()+i);
      break;
    }
  } 
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}
