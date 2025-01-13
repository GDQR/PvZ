#include "manager.hpp"
#include "scenes.hpp"
#include "states.hpp"

int actualState;
States states;
Scene scene;

void Manager::init() {
  for (int i = 0; i < lastGameState; i++) {
    states.isActive.push_back(false);
  }

  actualState = main;
  scene.setScene((Game_States_enum)actualState);
}

void Manager::loop() {
  if (states.isActive[actualState] == false) {
    scene.init();
  }

  scene.update();
}
