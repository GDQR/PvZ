#include "components.hpp"

void LawnMower::move(){
    if(canMove == true && posArray[id[0]].x < 550){
        posArray[id[0]].x+=2;
        for(BoxCollider& box: boxColliderLawnmower){
          if(box.id == id[0]){
            box.x+=2;
            break;
          }
        }
    }
}