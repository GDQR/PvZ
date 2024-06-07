#pragma once
#include <tyra>

enum sunCost { BigSun = 50, normalSun = 25, smallerSun = 15 };
extern int sunsCreated;
class Sun {
 public:
  int id;
  int cost;
};

void createSun(Tyra::Vec2 position, sunCost cost, bool createdByPlant);