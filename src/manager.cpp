#include "manager.hpp"
#include "scenes.hpp"
#include "states.hpp"

static int actualState;
static States states;

void setScene(Game_States_enum newState){ actualState = newState;}

void initScene() {
  states.isActive[actualState] = true;
  switch (actualState) {
    case main:
      SelectorScreen::init();
      break;
    case level1:
      Level1::init();
      break;
    case level2:
      Level2::init();
      break;
    case level3:
      Level3::init();
      break;
    case level4:
      Level4::init();
      break;
    case level5:
      Level5::init();
      break;
    default:
      break;
  }
}

void updateScene() {
  switch (actualState) {
    case main:
      SelectorScreen::update();
      break;
    case level1:
      Level1::update();
      break;
    case level2:
      Level2::update();
      break;
    case level3:
      Level3::update();
      break;
    case level4:
      Level4::update();
      break;
    case level5:
      Level5::update();
      break;
    default:
      break;
  }
}

void Manager::init() {
  for (int i = 0; i < lastGameState; i++) {
    states.isActive.push_back(false);
  }

  setScene(Game_States_enum::level1);
}

void Manager::loop() {
  if (states.isActive[actualState] == false) {
    initScene();
  }
  
  updateScene();
}
