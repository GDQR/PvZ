#include "components.hpp"
#include "font/font.hpp"
#include "manager.hpp"

int main() {
  Tyra::Engine e;
  engine = &e;
  renderer = &e.renderer;
  leftJoy = &e.pad.getLeftJoyPad();
  texRepo = &engine->renderer.getTextureRepository();
  // loadFonts();
  Manager game;
  game.init();
  while (true) {
    e.pad.update();
    game.loop();
    e.info.update();
  }

  // SleepThread();
  return 0;
}
