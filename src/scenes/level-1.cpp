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

int map[5][9];
int xMap = 9;
int yMap = 5;

int timerZombies = 0;
int maxZombies = 5;

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
  // load background
  createSprite(background, MODE_STRETCH, Vec2(-56, -1), Vec2(780, 524));
  createTexture(background, "Backgrounds/DAY Unsodded.png");
  // TODO: Fix size seedBank
  createSprite(seedBank, MODE_STRETCH, Vec2(63, 10),
               Vec2(512 / 1.5f, 128 / 1.5f));
  createTexture(seedBank, "UI/SeedBank.png");

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
  // createPlant(cards[2].plant, 2,7);
  zombieCreateRow[2] = true;
  zombiescreated = 0;
  newCursor(&player, Vec2(mapCollider[0][0].x, mapCollider[0][0].y + 30));
  newDeckCursor(&player,
                Vec2(posArray[cards[deckCursor[player].pos].seed].x - 3, -10));  
  // createPlant(cards[deckCursor[player].pos].plant, 2,8);
  createZombie(Vec2(mapCollider[2][8].x, mapCollider[2][8].y), Zombie_State_enum::bucketHeadZombie);
  loadProjectile();
  engine->font.loadFont(&myFont, "Fonts/roboto-Bold.ttf");
  // renderer->core.setFrameLimit(false);
  // sunManager.create(Vec2(277, 77), sunCost::normalSun, false);
}

void Level1::update() {
  // plantMovement();
  playerControl.update();

  if (player != -1 && debugMode == false) {
    cursor[player].move();
    boxColliderArray[cursor[player].id].move(cursor[player].id);
  }

  for (unsigned int i = 0; i < cards.size(); i++) {
    cards[i].update();
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxColliderArray[cursor[player].id].collision(&mapCollider[i][j]) ==
          true) {
        cursor[player].cursorTile = Vec2(i, j);
        i = 5;
        j = 9;
      }
    }
  }


  if (stopAnimation == false) {
    projectileManager.update();
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
  projectileManager.zombieCollision();
  explosionManager.zombieCollision();
  // printf("texture free space: %f\n",engine->renderer.core.gs.vram.getFreeSpaceInMB());

  // shoot zombies
  plantsManager.update();

  if (timerZombies > 0) {
    timerZombies--;
  } else {
    if (zombiescreated < 1) {
      int row = rand() % 5;
      while (zombieCreateRow[row] == false) {
        row = rand() % 5;
      }

      // createDebugZombie(Vec2(mapCollider[row][8].x, mapCollider[row][8].y));
      timerZombies = 60;
      zombiescreated++;
    }
  }

  renderer->beginFrame();

  // atest_t atest;
  // atest.enable = 0;
  // atest.method = ATEST_METHOD_GREATER;
  // atest.compval = 128;
  // atest.keep = ATEST_KEEP_ALL;

  // dtest_t dtest;
  // dtest.enable =0;
  // dtest.pass = 0;

  // renderer->core.renderer2D.pixelTest(&atest,&dtest,ZTEST_METHOD_GREATER);

  // static u64 mytime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
  
  renderSprites.resetFinalPos();
  renderSprites.updateChildPos();
  renderSprites.updateTexture();
  renderSprites.update();

  renderDebugSpritesManager.update();
  engine->font.drawText(&myFont, std::to_string(sunCounter), 30, 30, 16,
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
