#include "components.hpp"
#include "font/font.hpp"
#include "manager.hpp"
#include "systems.hpp"

int main() {
  Tyra::Engine e;
  engine = &e;
  renderer = &e.renderer;
  renderer2D = &e.renderer.renderer2D;
  pad = &e.pad;
  leftJoy = &e.pad.getLeftJoyPad();
  texRepo = &engine->renderer.getTextureRepository();
  // loadFonts();
  Manager game;
  game.init();
  while (true) {
    GetTime();
    e.pad.update();
    game.loop();
    e.info.update();
  }

  // SleepThread();
  return 0;
}
