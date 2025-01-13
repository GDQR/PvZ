#include "scenes.hpp"

void Scene::init() {
  states.isActive[state] = true;
  switch (state) {
    case main:
      SelectorScreen::init();
      break;
    case level1:
      Level1::init();
      break;
    case level2:
      Level2::init();
      break;
    default:
      break;
  }
}

void Scene::update() {
  switch (state) {
    case main:
      SelectorScreen::update();
      break;
    case level1:
      Level1::update();
      break;
    case level2:
      Level2::update();
      break;
    default:
      break;
  }
}
