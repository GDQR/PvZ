// File for all plants data
#include "plants.hpp"

void Plant::createSpace(){
    switch (type)
    {
    case PeaShotter:
        id.reserve(3);
        body.reserve(2);
        father = &id[0];
        body[0] = &id[1];
        body[1] = &id[2];
        break;
    
    default:
        break;
    }
}

void Plant::newPlant(Plant_State_enum newType){
    type = newType;
    createSpace();
}
// class PeaShooter{

// };