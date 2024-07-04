#include "font/font.hpp"
#include "renderSprite/textures.hpp"
#include "renderSprite/animations.hpp"
#include "states.hpp"
#include "scenes.hpp"
#include "scenes/level-1.hpp"

#include "entities/entities.hpp"

#include "components.hpp"
#include "debugPVZ/debug.hpp"
#include "debugPVZ/menuDebugCommands.hpp"
#include "systems.hpp"
#include <stdlib.h>
#include <time.h>
using namespace Tyra;

int background = Entities::newID();
int seedBank = Entities::newID();
int zombieDebug = Entities::newID();

std::vector<Card> cards;

int map[5][9];
int xMap = 9;
int yMap = 5;

Cursor cursor;
DeckCursor deckCursor;

int timerZombies = 0;
int maxZombies = 5;

int sunTimer;

void plantMovement() {
  float x = 0.0F;
  float y = 0.0F;

  if (leftJoy->h <= 100) {
    x = -1;
  } else if (leftJoy->h >= 200) {
    x = 1;
  }

  if (leftJoy->v <= 100) {
    y = -1;
  } else if (leftJoy->v >= 200) {
    y = 1;
  }

  if (x != 0 || y != 0) {
    printf("me movi\n");
  }
}

int cursorTimer = 0;
float cursorSpeed = 1;

void cursorMovement() {
  float x = 0.0F;
  float y = 0.0F;

  if (leftJoy->h <= 100) {
    x = -cursorSpeed;
  } else if (leftJoy->h >= 200) {
    x = cursorSpeed;
  }

  if (leftJoy->v <= 100) {
    y = -cursorSpeed;
  } else if (leftJoy->v >= 200) {
    y = cursorSpeed;
  }

  posArray[cursor.id] += Vec2(x, y);
  if (spriteArray[cursor.id].position.x != posArray[cursor.id].x ||
      spriteArray[cursor.id].position.y != posArray[cursor.id].y) {
    if (cursorTimer < 20) {
      cursorTimer++;

      if (cursorTimer == 10) {
        cursorSpeed = 1.5f;
      } else if (cursorTimer == 20) {
        cursorSpeed = 2.0f;
      }
    }

  } else {
    cursorTimer = 0;
    cursorSpeed = 1;
  }
}

void updateBoxCollider() {
  boxColliderArray[cursor.id].x =
      boxColliderArray[cursor.id].offsetX + posArray[cursor.id].x;
  boxColliderArray[cursor.id].y =
      boxColliderArray[cursor.id].offsetY + posArray[cursor.id].y;
  dm_SpriteBoxCollider[cursor.id].position =
      Vec2(boxColliderArray[cursor.id].x, boxColliderArray[cursor.id].y);
}

void cursorDeckMovement() {
  if (engine->pad.getClicked().DpadLeft) {
    deckCursor.pos--;
    if (deckCursor.pos < 0) {
      deckCursor.pos = cards.size() - 1;
    }
    posArray[deckCursor.id].x = posArray[cards[deckCursor.pos].seed].x - 3;
  } else if (engine->pad.getClicked().DpadRight) {
    deckCursor.pos++;
    if (deckCursor.pos >= (int)cards.size()) {
      deckCursor.pos = 0;
    }
    posArray[deckCursor.id].x = posArray[cards[deckCursor.pos].seed].x - 3;
  }
}

void createCard(Plant_State_enum typePlant, Vec2 pos) {
  Card card;
  card.seed = Entities::newID();
  card.seedShadow = Entities::newID();
  card.seedShadowTimer = Entities::newID();
  card.seedTimer = Entities::newID();

  createSprite(card.seed, MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seed, "UI/Seeds.png");
  spriteArray[card.seed].offset.x = 100;
  texPosArray[card.seed] = Vec2(0.0f, 0.0f);
  scaleTexture[card.seed] = Vec2(1.0f, 1.0f);

  createSprite(card.seedShadow, MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seedShadow, "UI/Seeds.png");
  spriteArray[card.seedShadow].color = Color(0.0F, 0.0F, 0.0F, 60.0F);
  texPosArray[card.seedShadow] = Vec2(0.0f, 0.0f);
  scaleTexture[card.seedShadow] = Vec2(1.0f, 1.0f);

  createSprite(card.seedShadowTimer, MODE_REPEAT, pos, Vec2(0, 0));
  createTexture(card.seedShadowTimer, "UI/Seeds.png");
  spriteArray[card.seedShadowTimer].color = Color(0.0F, 0.0F, 0.0F, 60.0F);
  texPosArray[card.seedShadowTimer] = Vec2(0.0f, 0.0f);
  scaleTexture[card.seedShadowTimer] = Vec2(1.0f, 1.0f);

  card.seedTimer = 0;//60 * 8;

  card.plant = typePlant;

  card.cost = getPlantCost(typePlant);

  cards.push_back(card);
}

void Level1::init() {
  srand(time(NULL));
  loadDebugTextures();
  // load background
  createSprite(background, MODE_STRETCH, Vec2(-56, -1), Vec2(780, 524));
  createTexture(background, "Backgrounds/DAY Unsodded.png");
  texPosArray[background] = Vec2(0.0f, 0.0f);
  scaleTexture[background] = Vec2(1.0f, 1.0f);
  // TODO: Fix size seedBank
  createSprite(seedBank, MODE_STRETCH, Vec2(63, 10),
               Vec2(512 / 1.5f, 128 / 1.5f));
  createTexture(seedBank, "UI/SeedBank.png");
  texPosArray[seedBank] = Vec2(0.0f, 0.0f);
  scaleTexture[seedBank] = Vec2(1.0f, 1.0f);

  createCard(PeaShotter, Vec2(120, 10));
  createCard(SunFlower, Vec2(180, 10));

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

  printf("pase una vez 1\n");
  zombieCreateRow[2] = true;
  newCursor(&cursor.id, Vec2(mapCollider[0][0].x, mapCollider[0][0].y + 30));
  newDeckCursor(&deckCursor.id,
                Vec2(posArray[cards[deckCursor.pos].seed].x - 3, -10));

  loadPeaShooterAnimation();
  loadZombieAnimation();
  loadProjectile();
  loadSunAnimation();
  loadSunFlowerAnimation();
  engine->font.loadFont(&myFont, "Fonts/roboto-Bold.ttf");
  // createZombie(Vec2(mapCollider[2][8].x, mapCollider[2][8].y));
  // createPlant(5,9);
  // renderer->core.setFrameLimit(false);

  sunTimer = 60 * 6;
  // createSun(Vec2(277, 77), sunCost::normalSun, false);
}

void Level1::update() {
  // plantMovement();
  if (cursor.id != -1 && debugMode == false) {
    cursorMovement();
    updateBoxCollider();
    cursorDeckMovement();
  }

  for (unsigned int i = 0; i < cards.size(); i++) {
    if (cards[i].seedTimer > 0) {
      cards[i].seedTimer--;
      spriteArray[cards[i].seedShadow].size = Vec2(50, 70);
      spriteArray[cards[i].seedShadowTimer].size.y -=
          (70.0f / 8.0f / 60.0f);  // el size Y es 70
    } else if (sunCounter >= cards[i].cost) {
      spriteArray[cards[i].seedShadow].size = Vec2(0, 0);
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxCollision(&boxColliderArray[cursor.id], &mapCollider[i][j]) ==
          true) {
        cursor.cursorTile = Vec2(i, j);
        i = 5;
        j = 9;
      }
    }
  }

  // create plant

  if (engine->pad.getClicked().Cross && debugMode == false) {
    if (zombieCreateRow[(int)cursor.cursorTile.x] == true) {
      if (sunCounter >= cards[deckCursor.pos].cost &&
          plantsCreated < maxPlants && cards[deckCursor.pos].seedTimer == 0) {
        sunCounter -= cards[deckCursor.pos].cost;
        // cards[deckCursor.pos].seedTimer = 60 * 8;
        spriteArray[cards[deckCursor.pos].seedShadowTimer].size.y = 70;
        createPlant(cards[deckCursor.pos].plant, cursor.cursorTile.x,
                    cursor.cursorTile.y);
      } else {
        printf("max plants created\n");
      }
    }
  }

  if (stopAnimation == false) {
    projectileManager.update();
    zombiesManager.update();
    animManager.update();
  }
  if (debugMode == false) {
    moveNaturalSun();
  }

  if (stopAnimation == false) {
    // 6 seconds
    if (sunTimer > 0) {
      sunTimer--;
    } else {
      sunTimer = 60 * 6;
      // min:50 max:420
      float x = 50 + rand() % 420;
      createSun(Vec2(x, 10), sunCost::normalSun, false);
    }
  }

  deleteSun(cursor.id);

  // printf("FPS: %d\n",engine->info.getFps()) ;
  // printf("ram: %f\n",engine->info.getAvailableRAM());
  // zombiesManager.collision();
  // projectileManager.zombieCollision();
  // printf("texture free space: %f\n",engine->renderer.core.gs.vram.getFreeSpaceInMB());

  // shoot zombies
  std::vector<Zombie>::iterator it;

  // for (int i = 0; i < 45; i++) {
  //   if (plant[i].type == PeaShotter) {
  //     // printf("hay una planta en %d\n",i);

  //     for (it = zombie.begin(); it < zombie.end(); it++) {
  //       //  printf("vec plant %f,%f. vec zombi %f,%f,%f,%f\n",
  //       //  pointColliderArray[*plant[i].body[0]].x,
  //       //  pointColliderArray[*plant[i].body[0]].y,
  //       //  boxColliderArray[*zombie[j].body[0]].x,
  //       //  boxColliderArray[*zombie[j].body[0]].y,
  //       //  boxColliderArray[*zombie[j].body[0]].x +
  //       //  boxColliderArray[*zombie[j].body[0]].width,
  //       //  boxColliderArray[*zombie[j].body[0]].y +
  //       //  boxColliderArray[*zombie[j].body[0]].height);

  //       if (pointColliderArray[plant[i].father].x <
  //               boxColliderArray[*(it)->body[0]].x +
  //                   boxColliderArray[*(it)->body[0]].width &&
  //           pointColliderArray[plant[i].father].y >
  //               boxColliderArray[*(it)->body[0]].y &&
  //           pointColliderArray[plant[i].father].y <
  //               boxColliderArray[*(it)->body[0]].y +
  //                   boxColliderArray[*(it)->body[0]].height) {
  //         // printf("hay un zombi en frente\n");
  //         if (plant[i].attackTimer >= 0) {
  //           plant[i].attackTimer--;
  //         } else if (stopAnimation == false) {
  //           // printf("disparar\n");
  //           newProjectile(pointColliderArray[plant[i].father]);
  //           plant[i].attackTimer = 60;
  //         }
  //         it = zombie.end();
  //       }
  //     }
  //   } else if (plant[i].type == SunFlower) {
  //     if (plant[i].attackTimer > 0) {
  //       plant[i].attackTimer--;
  //     } else {
  //       printf("sunflower create sun\n");
  //       createSun(spriteArray[plant[i].id[0]].position, sunCost::normalSun,
  //                  true);
  //       plant[i].attackTimer = 60 * 6;
  //     }
  //   }
  // }

  if (timerZombies > 0) {
    timerZombies--;
  } else {
    static int zombiescreados = 0;
    if (zombiescreados < 1) {
      int row = rand() % 5;
      while (zombieCreateRow[row] == false) {
        row = rand() % 5;
      }

      // createDebugZombie(Vec2(mapCollider[row][8].x, mapCollider[row][8].y));
      timerZombies = 60;
      zombiescreados++;
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

  renderSprites.updateChildPos();
  renderSprites.update();
  renderSprites.updateRotate();

  renderDebugSpritesManager.update();
  engine->font.drawText(&myFont, std::to_string(sunCounter), 30, 30, 16,
                        Color(255, 255, 255, 128));

  if (engine->pad.getClicked().R1 && debugMode == false) {
    debugMode = true;
    debugMenu = true;
    printf("\nDEBUG MODE ACTIVE\n");
  }

  if (debugMenu == true) {
    if (debugAnimation) {
      startDebugAnimationMode(engine->pad, engine->font);
      animManager.debug();
    } else if (debugSprite) {
      startDebugSpriteMode(engine->pad, engine->font);
    } else {
      menuDebugMode(engine->pad);
      if (stopAnimation == true) {
        animManager.debug();
      }
    }
  }

  renderer->endFrame();
}

void Level1::destroy() {}
