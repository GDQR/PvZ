#include "components.hpp"
#include "scenes.hpp"
#include "systems.hpp"


void SelectorScreen::init() {
  int background;
  createSprite(background, Tyra::MODE_STRETCH, Vec2(-56, -1),
               Vec2(780, 524));  // Vec2(467, 200*2.9f)
  // printf("posArray: %s\n",posArray[background].getPrint().c_str());
  createTexture(background, "SelectorScreen_BG_Center.jpg");
}

void SelectorScreen::update() {
  renderer->beginFrame();

  renderSprites.update();

  renderer->endFrame();
}