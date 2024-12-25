#include <entities/entities.hpp>
#include <stdio.h>

bool rewardExist = false;
int reward;

unsigned int Entities::counter = 0;
std::vector<unsigned int> Entities::aliveEntities;
std::vector<unsigned int> Entities::deadEntities;
std::vector<std::unordered_map<unsigned int, unsigned int>>
    Entities::componentIndex;

unsigned int Entities::newID() {
  // printf("deadEntities.size(): %d\n",deadEntities.size());
  if (deadEntities.size() == 0) {
    componentIndex.push_back(std::unordered_map<unsigned int, unsigned int>());
    return counter++;
  }
  unsigned int oldID = deadEntities.front();
  deadEntities.erase(deadEntities.begin());
  return oldID;
}

void Entities::deleteID(const unsigned int id) { deadEntities.push_back(id); }
void Entities::addComponent(const unsigned int id,
                            const unsigned int componentID,
                            const unsigned int componentIDIndex) {
  // printf("componentINdex size: %d\n",componentIndex.size());
  componentIndex[id][componentID] = componentIDIndex;
}

void Entities::removeComponent(const unsigned int id,
                               const unsigned int componentID) {
  // printf("componente borrado: %d id: %d\n",componentID,id);
  // printf("size: %d\n",size);
  componentIndex[id].erase(componentID);
  // for(unsigned int i=id+1;i<componentIndex.size();i++){
  //   if(componentIndex[i].count(componentID)){
  //     componentIndex[i][componentID]--;
  //   }
  // }

  // for(int i=id-1;i>=0;i--){ // el int puede que de problemas
  //   if(componentIndex[i].count(componentID) ){
  //     if(componentIndex[i][componentID]>=size){
  //       componentIndex[i][componentID]--;
  //       size--;
  //     }
  //   }
  // }
}

void Entities::clearComponent(const unsigned int componentID) {
  for(unsigned int i=0;i<componentIndex.size();i++){
    if(componentIndex[i].count(componentID)){
      componentIndex[i].erase(componentID);
    }
  }
}