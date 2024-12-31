#include "font/font.hpp"
#include "renderSprite/textures.hpp"
#include "states.hpp"
#include "scenes.hpp"
#include "scenes/level-1.hpp"

#include "entities/entities.hpp"

#include "systems.hpp"
#include "components.hpp"
#include "debugPVZ/debug.hpp"
#include "debugPVZ/menuDebugCommands.hpp"
#include <stdlib.h>
using namespace Tyra;

#include <iostream>

int background; 
int seedBank ;
int zombieDebug; 
int flagMeterTimer = 0;
int emptyFlagMeter;
int fullFlagMeter;

int map[5][9];
int xMap = 9;
int yMap = 5;

void Level1::init() {
  srand(time(NULL));
  newPlayer(&player);
  loadPlantCost();
  loadAnimString();
  loadPlantRechargeTime();
  loadAnimationStates();
  loadDebugTextures();
  background = Entities::newID();
  seedBank = Entities::newID();
  zombieDebug = Entities::newID();
  emptyFlagMeter = Entities::newID();
  fullFlagMeter = Entities::newID();
  // load background
  createSprite(background, MODE_STRETCH, Vec2(-56, -1), Vec2(780, 524));
  createTexture(background, "Backgrounds/DAY Unsodded.png");
  // TODO: Fix size seedBank
  createSprite(seedBank, MODE_STRETCH, Vec2(63, 10),
               Vec2(512 / 1.5f, 128 / 1.5f));
  createTexture(seedBank, "UI/SeedBank.png");
  
  // posicion es 255, 410 lo mejor para el flag
  createSprite(fullFlagMeter, MODE_REPEAT, Vec2(255, 410),
               Vec2(158,24));
  spriteArray[fullFlagMeter].scale = 1;
  spriteArray[fullFlagMeter].offset.y = 27;
  createTexture(fullFlagMeter, "Images/FlagMeter.png");
  
  createSprite(emptyFlagMeter, MODE_REPEAT, Vec2(255, 410),
               Vec2(158,24));
  spriteArray[emptyFlagMeter].scale = 1;
  createTexture(emptyFlagMeter, "Images/FlagMeter.png");


  // createSprite(emptyFlagMeter, MODE_STRETCH, Vec2(255, 410),
  //              Vec2(512 / 1.5f, 128 / 1.5f));
  // createTexture(emptyFlagMeter, "Images/FlagMeter.png");
  
  // createSprite(fullFlagMeter, MODE_STRETCH, Vec2(255, 410),
  //              Vec2(512 / 1.5f, 128 / 1.5f));
  // createTexture(fullFlagMeter, "Images/FlagMeter.png");

  bool isVersusMode = false;
  loadAnimation(AnimIndex::Peashooter);
  loadAnimation(AnimIndex::SunFlower);
  loadAnimation(AnimIndex::CherryBomb);
  loadAnimation(AnimIndex::LawnMower);
  loadAnimation(AnimIndex::Zombie);
  loadAnimation(AnimIndex::Sun);
  createCard(PeaShotter, Vec2(120, 10), isVersusMode);
  createCard(SunFlower, Vec2(180, 10), isVersusMode);
  createCard(CherryBomb, Vec2(240, 10), isVersusMode);
  // loadTexture(&map[0][0],"asset_box.png"); // debug map

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      plantCreatedInMap[i][j] = false;
      mapCollider[i][j].x = 85 + (45 * j);
      mapCollider[i][j].y = 58 + (72 * i);
      mapCollider[i][j].width = 45;
      mapCollider[i][j].height = 72;
      map[i][j] = Entities::newID();
    }
  }
  mapEnable[2] = true;
  // createPlant(cards[2].plant, 2,7);
  zombieCreateRow[2].maxZombiesInRow = 10;
  zombiescreated = 0;
  newCursor(&player, Vec2(mapCollider[0][0].x, mapCollider[0][0].y + 30));
  newDeckCursor(&player,
                Vec2(posArray[cards[deckCursor[player].pos].seed].x - 3, -10));  
  // createPlant(cards[deckCursor[player].pos].plant, 2,8);
  createZombie(Vec2(mapCollider[2][8].x, mapCollider[2][8].y), Zombie_State_enum::bucketHeadZombie);
  loadProjectile();
  // createPlant(cards[1].plant, 2,8);
  engine->font.loadFont(&myFont, 32, "Fonts/roboto-Bold.ttf");
  // renderer->core.setFrameLimit(false);
  // sunManager.create(Vec2(277, 77), sunCost::normalSun, false);
}

void Level1::update() {
  boxColliderManager.update();
  playerControl.update();

  if (player != -1 && debugMode == false) {
    cursor[player].move();
    boxColliderArray[cursor[player].id].move(cursor[player].id);
  }

  cardManager.update();

  if (stopAnimation == false) {
    zombiesManager.update();
    animManager.update();
  }
  if (debugMode == false) {
    sunManager.updateNaturalSun();
  }

  if (stopAnimation == false) {
    // sunManager.createByTime();
    // sunManager.erase(cursor.id);
  }


  // printf("FPS: %d\n",engine->info.getFps()) ;
  // printf("ram: %f\n",engine->info.getAvailableRAM());
  // printf("texture free space: %f\n",engine->renderer.core.gs.vram.getFreeSpaceInMB());

  // shoot zombies
  plantsManager.update();
  
  createZombieMain();

  rewardManager.update();

  if(spriteArray[emptyFlagMeter].size.x/*flagMeterTimer*/>0){
    printf("size flag: %f\n",spriteArray[emptyFlagMeter].size.x);
    spriteArray[emptyFlagMeter].size.x-- ;
  }

  renderer->beginFrame();

  // static u64 mytime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
  
  renderSprites.update();

  renderDebugSpritesManager.update();
  engine->font.drawText(&myFont, std::to_string(sunCounter).c_str(), 30, 30, 16,
                        Color(255, 255, 255, 128));

  if (debugMenu == true) {
    if (debugState == debugMain) {
      debugModeClass.drawMainMenu();
      if (stopAnimation == true) {
        animManager.debug();
      }
    }

    if (debugAnimation) {
      startDebugAnimationMode(engine->pad, engine->font);
      animManager.debug();
    } else if (debugState == SpriteDebug) {
      debugModeClass.drawSpriteModeMenu();
    }
  }

  renderer->endFrame();
}

void Level1::destroy() {}
