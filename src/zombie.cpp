#include "zombie.hpp"
#include "components.hpp"

int zombiesCreated = 0;

void Zombie::createSpace(){
    switch (type)
    {
    case ZombieNormal:
        id.reserve(3);
        body.reserve(2);
        father = &id[0];
        body[0] = &id[1];
        body[1] = &id[2];
        // body[2] = &id[3];
        break;
    
    default:
        break;
    }
}

void Zombie::newZombie(Zombie_State_enum newType){
    type = newType;
    createSpace();
}

void createZombie(Vec2 pos) {

//   zombie.insert(zombie.begin() + zombiesCreated, Zombie());
  zombie.push_back(Zombie());
  Zombie* zom = &(zombie[zombie.size()-1]);  
  zom->newZombie(ZombieNormal);
  zom->id[0] = Entities::newID();
  zom->id[1] = Entities::newID();
  
  vec2Array[*zom->father] = Vec2(pos.x+10,pos.y-20);//Vec2(pos.x,pos.y-10);
  spriteArray[*zom->body[0]] = Sprite();

  loadSprite(&spriteArray[*zom->body[0]], Tyra::MODE_STRETCH,
             vec2Array[*zom->father], Vec2(255 / 1.6f, 255 / 1.5f));

  animationArray[*zom->body[0]] = Animation(enumAnimation::zombieWalk);
  animationDataArray[zombieWalk].keys[0]->addLink(
      spriteArray[*zom->body[0]].id);

  // Life

  lifeArray[*zom->body[0]] = 181;

  // damage

  damageArray[*zom->body[0]] = 100;

  // HitBox
  boxColliderArray[*zom->body[0]] = BoxCollider(pos.x + 60, pos.y + 10, 28, 50);
    //   BoxCollider(pos.x + 100, pos.y + 20, 28, 50);
  createDebugBoxCollider(*zom->body[0], Tyra::MODE_STRETCH);

  zombiesCreated++;
  TYRA_LOG("Zombie Created");
}
