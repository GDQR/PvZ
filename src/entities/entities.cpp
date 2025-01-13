#include <entities/entities.hpp>
#include <stdio.h>

Tyra::Vec2 cameraPos(0.0f, 0.0f);
bool rewardExist = false;
Reward reward;

unsigned int Entities::counter = 1;
std::vector<unsigned int> Entities::aliveEntities;
std::vector<unsigned int> Entities::deadEntities;

unsigned int Entities::newID() {
  // printf("deadEntities.size(): %d\n",deadEntities.size());
  if (deadEntities.size() == 0) {
    return counter++;
  }
  unsigned int oldID = deadEntities.front();
  deadEntities.erase(deadEntities.begin());
  return oldID;
}

void Entities::deleteID(unsigned int& id) {
  int newID = id;
  deadEntities.push_back(newID);
  id = 0;
}

void Entities::deleteID(int& id) {
  int newID = id;
  deadEntities.push_back(newID);
  id = 0;
}
