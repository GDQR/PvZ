#pragma once
#include <tyra>

enum sunCost { BigSun = 50, normalSun = 25, smallerSun = 15 };
extern int sunsCreated;
class Sun {
 public:
  int id;
  int cost;
};
// solo se necesita 1
extern void createSun(Tyra::Vec2 position, sunCost cost);
// extern void createSunSuavizado(Tyra::Vec2 position); //borrar