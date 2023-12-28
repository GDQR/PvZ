#include "font/font.hpp"
#include "manager.hpp"

Tyra::Engine* engine;
Tyra::Renderer* renderer;
const Tyra::PadJoy* leftJoy;

int main() {
  Tyra::Engine e;
  engine = &e;
  renderer = &e.renderer;
  leftJoy = &e.pad.getLeftJoyPad();
  loadFonts();
  Manager game(engine);
  e.run(&game);
  SleepThread();
  return 0;
}
