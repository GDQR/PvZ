#include "components.hpp"
#include "debug/debug.hpp"
#include "file/file_utils.hpp"
#include "font/font.hpp"
#include "fontFiles.hpp"
#include "scenes.hpp"
#include "imageTools.hpp"
#include "systems.hpp"
#include <stdio.h>
#include <string.h>
#include <string>
#include <tyra>

void Level5::init() {
    loadAnimString();
    // loadAnimation(AnimIndex::Sun);
    // printf("pase 1\n");
    // sunManager.create(Vec2(20,20),sunCost::normalSun,true);
    // printf("pase 2\n");
    
    loadAnimation(AnimIndex::SunFlower);
    loadAnimation(AnimIndex::Chomper);
    // createCard(Chomper, Vec2(120, 10), false);
    createCard(SunFlower, Vec2(0, 0), false);
}

void Level5::update() {
//   animManager.update();
  frameManager.update();

  renderer->beginFrame();

  renderSprites.update();

  renderer->endFrame();
}