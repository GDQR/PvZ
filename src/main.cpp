#include "font/font.hpp"
#include "manager.hpp"
#include "components.hpp"

int main() {
  Tyra::Engine e;
  engine = &e;
  renderer = &e.renderer;
  leftJoy = &e.pad.getLeftJoyPad();
  texRepo = &engine->renderer.getTextureRepository();
  loadFonts();
  Manager game(engine);
  e.run(&game);
  SleepThread();
  return 0;
}
