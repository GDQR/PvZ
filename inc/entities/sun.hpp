#pragma once
#include <tyra>

enum sunCost { BigSun = 50, normalSun = 25, smallerSun = 15 };
extern int sunsCreated;
extern int sunCounter;
class Sun {
 public:
  std::vector<int> id;
  int cost;
};

class NaturalSun{
  public:
  std::vector<int> id;
};

// void createSun(Tyra::Vec2 position, sunCost cost, bool createdByPlant);
void createSun2(Tyra::Vec2 position, sunCost cost, bool createdByPlant);
void deleteSun(const int cursorID);

void moveNaturalSun();