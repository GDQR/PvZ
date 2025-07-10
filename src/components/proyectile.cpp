#include "components.hpp"
#include "systems.hpp"

void ProjectileManager::update(){
  std::vector<int> deleteID;
  size_t size = projectile.size();
  for(size_t i=0; i < size;i++){
    if(projectile[i].attack() == true){
      deleteID.push_back(projectile[i].id);
    }
  }

  while(deleteID.size() > 0){
    size = projectile.size();
    int sizeProyectile = deleteID.size()-1;
    for(size_t i=0; i < size;i++){
      if(deleteID[sizeProyectile] == projectile[i].id){
        printf("se borra el id: %d\n",projectile[i].id);
        projectile[i].erase();
        projectile[i] = projectile[size-1];
        projectile.erase(projectile.begin() + size-1);
        deleteID.erase(deleteID.begin()+sizeProyectile);
        projectilesCreated--;
        break;
      }
    }
  }
}

bool Proyectile::attack(){
  size_t searchIndex = responseCollisionZombieProjectile.size();
  size_t size = searchIndex;
  int zombieCollisionID;
  for(size_t i=0;i<size;i++){
    if(responseCollisionZombieProjectile[i].projectileID == id){
      searchIndex = i;
      zombieCollisionID = responseCollisionZombieProjectile[i].zombieID;
      break;
    }
  }

  if(searchIndex == size){
    return move(); 
  }

  size = zombie.size();
  for(size_t i=0; i < size; i++){
    if(zombie[i].boxColliderID == zombieCollisionID){
      zombie[i].damage(id);
      if(zombie[i].erase() == true){
        zombie.erase(zombie.begin()+i);
      }else if (type == enumProyectile::snowPea) {
        speedArray[zombie[i].father] = 0.5f;
      }
      break;
    }
  }
  return true;
}

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
  if (type == enumProyectile::pea) {
    projectilePea->removeLinkById(spriteArray[id].id);
  } else if (type == enumProyectile::snowPea) {
    projectileSnowPea->removeLinkById(spriteArray[id].id);
  }

  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  
  for(size_t i=0; i<boxColliderProyectile.size();i++){
    if(boxColliderProyectile[i].id == id){
      boxColliderProyectile.erase(boxColliderProyectile.begin()+i);
      break;
    }
  }
  deleteDebugBoxCollider(id);
  Entities::deleteID(id);
}
