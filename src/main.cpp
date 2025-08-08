// #include "systems.hpp"
#include "PVZ.hpp"
#include "text.hpp"
#include "scenes.hpp"

static int actualState;
static States states;

void setScene(Game_States_enum newState){ actualState = newState;}

void initScene() {
  states.isActive[actualState] = true;
  switch (actualState) {
    case sceneSelectorScreen:
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
    case sceneSelectorScreen:
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

void GameLoop(){
  if (states.isActive[actualState] == false) {
    initScene();
  }
  updateScene();
}

int main() {
  Tyra::Engine e;
  engine = &e;
  renderer = &e.renderer;
  renderer2D = &e.renderer.renderer2D;
  pad = &e.pad;
  leftJoy = &e.pad.getLeftJoyPad();
  texRepo = &engine->renderer.getTextureRepository();
  ReadTextFile();
  // loadFonts();
  states.isActive.reserve(lastGameState);
  
  for (int i = 0; i < lastGameState; i++) {
    states.isActive[i] = false;
  }

  setScene(Game_States_enum::level1);

  while (true) {
    GetTime();
    e.pad.update();
    GameLoop();
    e.info.update();
  }

  // SleepThread();
  return 0;
}
