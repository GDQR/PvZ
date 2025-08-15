// #include "systems.hpp"
#include "PVZ.hpp"
#include "imageFiles.hpp"
#include "font/font.hpp"
#include "text.hpp"
// #include "entities.hpp"

int projectilesCreated = 0;
int explosionsCreated = 0;


// int ZombiesManager::collision() {
//   std::vector<Zombie>::iterator it;

//   if (plantsCreated == 0) {
//     for (it = zombie.begin(); it < zombie.end(); it++) {
//       if (it->debug == true) {
//         continue;
//       }
//       it->attack = false;
//       animationArray[it->id[0]].animID = zombieWalk;
//     }
//     return 0;
//   }

//   for (it = zombie.begin(); it < zombie.end(); it++) {
//     if (it->debug == true) {
//       continue;
//     }
//     for (int i = 0; i < 45; i++) {
//       if (plant[i].type != NonePlant) {
//         //  printf("vec plant %f,%f. vec zombi %f,%f,%f,%f\n",
//         //  pointColliderArray[*plant[i].body[0]].x,
//         //  pointColliderArray[*plant[i].body[0]].y,
//         //  boxColliderArray[*zombie[j].body[0]].x,
//         //  boxColliderArray[*zombie[j].body[0]].y,
//         //  boxColliderArray[*zombie[j].body[0]].x +
//         //  boxColliderArray[*zombie[j].body[0]].width,
//         //  boxColliderArray[*zombie[j].body[0]].y +
//         //  boxColliderArray[*zombie[j].body[0]].height);

//         if
//         (boxColliderArray[plant[i].id[0]].collision(&boxColliderArray[it->id[0]])
//         == true) {
//           it->attack = true;
//           animationArray[it->id[0]].animID = zombieNormalAttack;
//           if (it->attackTimer > 0) {
//             it->attackTimer--;
//           } else {
//             it->attackTimer = 80;
//             printf("comiendo planta\n");
//             lifeArray[plant[i].id[0]] -= damageArray[it->id[0]];

//             if (lifeArray[plant[i].id[0]] <= 0) {
//               printf("borre planta id: %d\n", plant[i].id[0]);
//               if (plant[i].type == PeaShotter) {
//                 deletePeashotter(i);
//               } else if (plant[i].type == SunFlower) {
//                 deleteSunflower(i);
//               }

//               it->attack = false;
//               animationArray[it->id[0]].animID = zombieWalk;
//             }
//           }
//         } else {
//           it->attack = false;
//           animationArray[it->id[0]].animID = zombieWalk;
//         }
//       }
//     }
//   }

//   return 1;
// }

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                  Tyra::Vec2 size) {
  spriteArray.insert(id, Sprite());
  posArray.insert(id, position);
  finalPosArray.insert(id, Vec2(0, 0));
  loadSprite(&spriteArray[id], mode, Vec2(0.0f, 0.0f), size);
  // spriteRenderIDArray.insert(id, 0);
  setSprite(id,(int)enumDraw::draw);
}

void createSpriteRotate(int id, Tyra::SpriteMode mode, Tyra::Vec2 position,
                        Tyra::Vec2 size, const Tyra::Vec2 angle) {
  angleArray.insert(id, angle);
  createSprite(id, mode, position, size);
}
void createBoxCollider(int id, BoxColliderEnum type, BoxCollider collider){
  if(type == BOXCOLLIDER_PROYECTILE){
    boxColliderProyectile.push_back(collider) ;
  } else if(type == BOXCOLLIDER_ZOMBIE){
    boxColliderZombie.push_back(collider);
  } else if(type == BOXCOLLIDER_EXPLOSION){
    boxColliderExplosion.push_back(collider);
  } else if(type == BOXCOLLIDER_LAWNMOWER){
    boxColliderLawnmower.push_back(collider);
  } else if(type == BOXCOLLIDER_PLANT){
    boxColliderPlant.push_back(collider);
  } else if(type == BOXCOLLIDER_SUN){
    boxColliderSun.push_back(collider);
  } else if(type == BOXCOLLIDER_PLAYER){
    boxColliderPlayer.push_back(collider);
  } else{
    // boxColliderArray[id] = collider;
    boxColliderArrayID[id] = boxColliderArray[type].size();
    // boxColliderArrayTypeID[type][id] = boxColliderArray[type].size();
    boxColliderArray[type].push_back(collider);
  }
}

void deleteSprite(const int entityID) {
  spriteArray.erase(entityID);

  spriteRenderIDArray.erase(entityID);
  
  if(angleArray.count(entityID) == 1){
    angleArray.erase(entityID);
  }
}

void deletePosArray(const int entityID) { posArray.erase(entityID); }
void deleteFinalPosArray(const int entityID) { finalPosArray.erase(entityID); }

void deleteTexPosArray(const int entityID) { texPosArray.erase(entityID); }

void newPlayer(int* player) {
  // static int countPlayer = 0;
  // *player = Entities::newID();
  // controller[*player].index = countPlayer;
  // countPlayer++;
}

void newProjectile(Vec2 position, const int damage,
                   const enumProyectile projectileType) {
  if (projectilesCreated < 100) {
    Proyectile projectileData;
    projectileData.id = Entities::newID();
    projectileData.type = projectileType;

    projectile.push_back(projectileData);
    int& id = projectile[projectile.size()-1].id; //projectile[projectilesCreated].id;

    position.y -= 15.0f;
    createSprite(id, Tyra::MODE_STRETCH, position, Vec2(31 / 1.6f, 31 / 1.6f));
    if (projectileType == enumProyectile::pea) {
      spriteArray[id].textureID = projectilePea->id;
    } else if (projectileType == enumProyectile::snowPea) {
      spriteArray[id].textureID = projectileSnowPea->id;
    }

    // damage
    damageArray[id] = damage;
    // hitbox
    createBoxCollider(id,BoxColliderEnum::BOXCOLLIDER_PROYECTILE,BoxCollider(id,posArray[id].x, posArray[id].y, spriteArray[id].size.x,
                    spriteArray[id].size.y));
    createDebugBoxCollider(id,BoxColliderEnum::BOXCOLLIDER_PROYECTILE, Tyra::MODE_STRETCH);
    projectilesCreated++;
  }
}

void newExplosion(Vec2 position, Vec2 size, const int damage,
                  const enumProyectile projectileType) {
  if (explosionsCreated < 100) {
    Explosion explosionData;
    explosionData.id = Entities::newID();
    explosionData.type = projectileType;

    explosion.insert(explosion.begin() + explosionsCreated, explosionData);
    int* id = &explosion[explosionsCreated].id;
    // TODO: Fix position for sprite
    createSprite(*id, Tyra::MODE_STRETCH, position - size / 2 / 2,
                 Vec2(256 / 1.6f, 256 / 1.6f));
    printf("sprite explosion id: %d\n",spriteArray[*id].id);
    if (projectileType == enumProyectile::ExplosionPowie) {
      spriteArray[*id].textureID = projectileExplosionPowie->id;
    } else if (projectileType == enumProyectile::ExplosionSpudow) {
      spriteArray[*id].textureID = projectileExplosionSpudow->id;
    }
    position -= size / 2 / 2;

    // damage
    damageArray[*id] = damage;
    // hitbox
    createBoxCollider(*id,BoxColliderEnum::BOXCOLLIDER_EXPLOSION, BoxCollider(*id, position.x, position.y, size.x, size.y));
    // createDebugBoxCollider(*id,BoxColliderEnum::BOXCOLLIDER_EXPLOSION, Tyra::MODE_STRETCH);
    explosionsCreated++;
  }
}

void newFatherID(int* fatherID, int* childID) {
  fatherIDArray[*fatherID].id.push_back(*childID);
}

void deleteFatherIDChild(const int fatherID, const int* childID) {
  std::vector<int>::iterator it =
      find(fatherIDArray[fatherID].id.begin(),
           fatherIDArray[fatherID].id.end(), *childID);
  fatherIDArray[fatherID].id.erase(it);
}

void deleteFatherID(const int entityID) { fatherIDArray.erase(entityID); }

void createLawnMower(const Tyra::Vec2 pos) {
  LawnMower entity;
  entity.id.push_back(Entities::newID());
  posArray.insert(entity.id[0], pos);
  fatherIDArray.insert(entity.id[0], FatherID());
  int entityID;
  int animID;
  for (unsigned int i = 0; i < m_animID[AnimIndex::LawnMower].size(); i++) {
    entityID = Entities::newID();
    entity.id.push_back(entityID);
    animID = m_animID[AnimIndex::LawnMower][i];
    // printf("plant ID: %d\n", entityID);
    // printf("animID: %d\n", animID);
    newFatherID(&entity.id[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID,
                                             Tyra::Vec2(0.7f, 0.7f), 1, 1);
  }

  // HitBox
  createBoxCollider(entity.id[0],BOXCOLLIDER_LAWNMOWER, BoxCollider(entity.id[0],pos.x + 10, pos.y + 20, 45, 38));
  createDebugBoxCollider(entity.id[0],BoxColliderEnum::BOXCOLLIDER_LAWNMOWER, Tyra::MODE_STRETCH);
  lawnMower.push_back(entity);
}

void SetBigImage(BigSpriteJPG* entity, BigTexture* textures, Tyra::SpriteMode mode,float x,float y, float width, float height){
  int j=0;
  int k=0;

  for(unsigned int i=0;i<textures->data.size();i++){
    entity->id.push_back(Entities::newID());
    printf("reward big[%d] id: %d\n",i,entity->id[i]);
    // printf("pos x,y: %f,%f\n",j*width+(j)+x,k*height+k+y);
    createSprite(entity->id[i], mode, Vec2(j*width+(j)+x, k*height+k+y),
               Vec2(width, height));
               //award
    // createSprite(backgroundIDs.id[i], Tyra::MODE_STRETCH, Vec2(j*81+(j), k*94+k),
    //            Vec2(81, 94));
    Tyra::Texture* texture = new Tyra::Texture(textures->data[i]);
    spriteArray[entity->id[i]].textureID = texture->id;
    texRepo->add(texture);

    j++;
    if(j==textures->width){
        k++;
        j=0;
    }
  }
}

// void SetBigImage(BackgroundEntity* entity, Tyra::TextureBuilderData* texture, Tyra::SpriteMode mode,float x,float y, float width, float height){
//   int j=0;
//   int k=0;

//   int widthTexture = texture->width;
//   int heightTexture = texture->g;

//   for(unsigned int i=0;i<textures.size();i++){
//     entity->id.push_back(Entities::newID());
    
//     createSprite(entity->id[i], mode, Vec2(j*width+(j)+x, k*height+k+y),
//                Vec2(width, height));
//                //award
//     // createSprite(backgroundIDs.id[i], Tyra::MODE_STRETCH, Vec2(j*81+(j), k*94+k),
//     //            Vec2(81, 94));
//     Tyra::Texture* texture = new Tyra::Texture(textures[i]);
//     texture->addLink(spriteArray[entity->id[i]].id);
//     texRepo->add(texture);

//     j++;
//     if(j==textures->width){
//         k++;
//         j=0;
//     }
//   }
// }