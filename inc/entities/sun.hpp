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
  bool erase(const int cursorID);
};

class NaturalSun {
 public:
  int father;
  void move();
};

class SunManager {
 public:
  void create(Tyra::Vec2 position, sunCost cost, bool createdByPlant);
  void createByTime();
  void erase(const int cursorID);
  void updateNaturalSun();
};

extern SunManager sunManager;
