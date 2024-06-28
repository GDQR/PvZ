#pragma once
#include <tyra>

enum sunCost { BigSun = 50, normalSun = 25, smallerSun = 15 };
extern int sunsCreated;
extern int sunCounter;
class Sun {
 public:
  int father;
  std::vector<int> id;
  int cost;
};

class NaturalSun{
  public:
  int father;
};

// void createSun(Tyra::Vec2 position, sunCost cost, bool createdByPlant);
void createSun(Tyra::Vec2 position, sunCost cost, bool createdByPlant);
void deleteSun(const int cursorID);

void moveNaturalSun();