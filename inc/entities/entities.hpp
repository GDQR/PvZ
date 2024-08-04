#pragma once

#include <vector>
#include <unordered_map>

enum enumComponents {
  pos,
  finalPos,
  texPos,
  spriteRender
};

class Entities {
 public:
  static unsigned int counter;
  static std::vector<unsigned int> aliveEntities;
  static std::vector<unsigned int> deadEntities;
  static std::vector<std::unordered_map<unsigned int, unsigned int>>
      componentIndex;

  static unsigned int newID();
  static void deleteID(const unsigned int id);
  static void addComponent(const unsigned int id,
                           const unsigned int componentID,
                           const unsigned int componentIDIndex);
  static void removeComponent(const unsigned int id,
                              const unsigned int componentID, unsigned int size);
  static void clearComponent(const unsigned int componentID);
  static unsigned int getComponent(const unsigned int id,
                              const unsigned int componentID);
};