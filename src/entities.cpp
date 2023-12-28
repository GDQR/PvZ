#include <entities.hpp>

unsigned int Entities::counter = 0;
std::vector<unsigned int> Entities::aliveEntities;
std::vector<unsigned int> Entities::deadEntities;

unsigned int Entities::newID(){
    if(deadEntities.size() == 0){
        return counter++;
    }
    unsigned int oldID = deadEntities.back();
    deadEntities.pop_back();
    return oldID;
    
}

void Entities::deleteID(const unsigned int id){
    deadEntities.push_back(id);
}
