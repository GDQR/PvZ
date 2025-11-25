#pragma once
#include "states.hpp"
#include <tyra>

class SelectorScreen {
 public:
  static void init();
  static void update();
  static void Levels();
  static void BG();        // Background
  static void BGLeft();    // Background Left
  static void BGCenter();  // Background Center
  static void BGRight();   // Background Right
  static void OptionHighlight(int option, int previousOption);
};

class Level1 {
 private:
  static void initAnimation();
  static bool loopAnimation();
  static void initGameplay();
 public:
  static void init();
  static void update();
};

class Level2 {
 public:
  static void init();
  static void initAnimation();
  static void loopAnimation();
  static void update();
};

class Level3 {
 public:
  static void init();
  static void update();
};

class Level4 {
 public:
  static void init();
  static void update();
};


class Level5 {
 public:
  static void init();
  static void update();
};