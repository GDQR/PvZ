#include "components.hpp"

void FatherID::update(const int entityID) {
  for (unsigned int i = 0; i < id.size(); i++) {
    // finalPos += fatherPos
    finalPosArray[id[i]] += posArray[entityID];
  }
}
