#include "debug/debug.hpp"
#include "file/file_utils.hpp"
#include "font/font.hpp"
#include "fontFiles.hpp"
#include "scenes.hpp"
#include "imageTools.hpp"
#include "manager.hpp"
#include <stdio.h>
#include <string.h>
#include <string>
#include <tyra>

void Level5::init() {
  loadPlantCost();
    loadAnimString();
  loadPlantRechargeTime();
    // loadAnimation(AnimIndex::Sun);
    // printf("pase 1\n");
    // sunManager.create(Vec2(20,20),sunCost::normalSun,true);
    // printf("pase 2\n");
    
    loadAnimation(AnimIndex::PeaShotter);
    loadAnimation(AnimIndex::SunFlower);
    // createCard(Chomper, Vec2(120, 10), false);
    // createCard(PeaShotter, Vec2(180, 10), false);
    // createCard(SunFlower, Vec2(240, 10), false);
  
    for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      plantCreatedInMap[i][j] = false;
      // mapCollider[i][j].x = 20 + (52 * j);
      // mapCollider[i][j].y = 58 + (75 * i);
      // mapCollider[i][j].width = 52;
      // mapCollider[i][j].height = 75;
      map[i][j] = Entities::newID();
      createBoxCollider(map[i][j],BoxColliderEnum::BOXCOLLIDER_MAP,
        BoxCollider(20 + (52 * j),
        58 + (75 * i),
        52,
        75));
      // boxColliderArray[map[i][j]] = mapCollider[i][j];
      // createDebugBoxCollider(map[i][j],SpriteMode::MODE_STRETCH);
    }
  }
  mapEnable[2] = true;
  Entity::player.init(Vec2(mapCollider[0][0].x, mapCollider[0][0].y + 30),Tyra::Vec2(posArray[cards[0].seed].x - 3, -10));
}

void Level5::update() {
//   animManager.update();
  boxColliderManager.update();
  playerControl.update();
  cardManager.update();
  frameManager.update();

  renderer->beginFrame();

  renderSprites.update();

  renderer->endFrame();
}