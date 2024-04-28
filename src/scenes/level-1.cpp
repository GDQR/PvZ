// #include "font/font.hpp"
#include "renderSprite/textures.hpp"
#include "renderSprite/animations.hpp"
#include "states.hpp"
#include "scenes.hpp"
#include "scenes/level-1.hpp"

#include "entities/entities.hpp"

#include "components.hpp"
#include "debugPVZ/debug.hpp"
#include "font/font.hpp"
#include <stdlib.h>
#include <time.h>
using namespace Tyra;

int background = Entities::newID();
int seedBank = Entities::newID();
int seeds = Entities::newID();
int seedShadow = Entities::newID();
int seedShadowTimer = Entities::newID();
int map[5][9];
// Sprite map[5][9];

int xMap = 9;
int yMap = 5;

AnimationManager animManager;
RendererSprites renderSprites;
RendererDebugSpritesManager renderDebugSpritesManager;
ZombiesManager zombiesManager;

class Cursor {
 public:
  int id = -1;
  Sprite sprite;
  Vec2 cursorTile;
};

class DeckCursor {
 public:
  int id = -1;
  int pos = 0;
  int cost;  // plantCost
};

Cursor cursor;
DeckCursor deckCursor;

int timerZombies = 0;
int maxZombies = 5;

ProjectileManager projectileManager;

int sunCounter = 0;
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
  // *posArray[plant.father] = Vec2(x,y);
  // spriteArray[plant.body[0]]->position += *posArray[plant.father];
  // spriteArray[plant.body[1]]->position += *posArray[plant.father];

  // *posArray[plant.father] = Vec2(0,1);
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
  debugSpriteBoxCollider[cursor.id].position =
      Vec2(boxColliderArray[cursor.id].x, boxColliderArray[cursor.id].y);
}

void Level1::init() {
  srand(time(NULL));
  animManager.texRepo = &engine->renderer.getTextureRepository();
  loadDebugTextures();
  // // load background
  createSprite(background, MODE_STRETCH, Vec2(-56, -1), Vec2(780, 524));
  createTexture(background, "Backgrounds/DAY Unsodded.png");
  // // printf("background id: %d\n",background);

  // // TODO: Fix size seedBank
  createSprite(seedBank,MODE_STRETCH,Vec2(63,10),Vec2(512/1.5f,128/1.5f));
  createTexture(seedBank,"UI/SeedBank.png");

  createSprite(seeds,MODE_REPEAT,Vec2(120,10),Vec2(50,70));
  createTexture(seeds,"UI/Seeds.png");
  spriteArray[seeds].offset.x = 100;

  createSprite(seedShadow,MODE_REPEAT,Vec2(120,10),Vec2(50,70));
  createTexture(seedShadow,"UI/Seeds.png");
  spriteArray[seedShadow].color = Color(0.0F,0.0F,0.0F,60.0F);
  // // seedShadow.flipVertical= true;
  // // seedShadow.offset.y = 70;

  createSprite(seedShadowTimer,MODE_REPEAT,Vec2(120,10),Vec2(50,70));
  createTexture(seedShadowTimer,"UI/Seeds.png");
  spriteArray[seedShadowTimer].color = Color(0.0F,0.0F,0.0F,60.0F);
  // seedShadowTimer.flipVertical= true;
  // seedShadowTimer.offset.y = 70;

  // loadTexture(&map[0][0],"asset_box.png"); // debug map

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      plantCreatedInMap[i][j] = false;
      mapCollider[i][j].x = 85 + (45 * j);
      mapCollider[i][j].y = 58 + (72 * i);
      mapCollider[i][j].width = 45;
      mapCollider[i][j].height = 72;
      map[i][j] = Entities::newID();
      // createSprite(map[i][j],SpriteMode::MODE_STRETCH,Vec2(mapCollider[i][j].x,
      // mapCollider[i][j].y),Vec2(mapCollider[i][j].width,
      // mapCollider[i][j].height)); createTexture(map[i][j],"UI/Seeds.png");
      // map[i][j].mode = SpriteMode::MODE_STRETCH;
      // map[i][j].position = Vec2(mapCollider[i][j].x, mapCollider[i][j].y);
      // map[i][j].size = Vec2(mapCollider[i][j].width,
      // mapCollider[i][j].height); debugBoxTexture->addLink(map[i][j].id);
    }
  }
  // map[0][1].color = Color(0, 255, 0, 128);

  printf("pase una vez 1\n");
  zombieCreateRow[2] = true;
  newCursor(&cursor.id,
            Vec2(mapCollider[0][0].x,
                 mapCollider[0][0].y +
                     30) /*Vec2(map[0][0].position.x, map[0][0].position.y)*/);
  newDeckCursor(&deckCursor.id, Vec2(0, 0));
  deckCursor.cost = 50;
  loadPeaShooterAnimation();
  loadZombieAnimation();
  loadProjectile();
  loadSunAnimation();
  // loadSunSuavizadoAnimation(); // borrar
  engine->font.loadFont(&myFont, "Fonts/roboto-Bold.ttf");
  // createSunSuavizado(Vec2(100,50)); // borrar
  // createPlant(5,9);
  // renderer->core.setFrameLimit(false);

  sunTimer = 60 * 6;
}

void Level1::update() {
  // plantMovement();
  if (cursor.id != -1 && debugMode == false) {
    cursorMovement();
    updateBoxCollider();
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxCollision(&boxColliderArray[cursor.id], &mapCollider[i][j]) ==
          true) {
        cursor.cursorTile = Vec2(i, j);
        //  printf("estoy en tile %d,%d\n",j,i);
        i = 5;
        j = 9;
      }
    }
  }

  if (engine->pad.getClicked().Cross && debugMode == false) {
    if (zombieCreateRow[(int)cursor.cursorTile.x] == true) {
      if (sunCounter >= deckCursor.cost && plantsCreated < maxPlants) {
        sunCounter -= deckCursor.cost;
        createPlant(cursor.cursorTile.x, cursor.cursorTile.y);
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
    for (std::vector<Sun>::iterator it = sun.begin(); it < sun.end(); it++) {
      if (posArray[it->id].y < 370) {
        posArray[it->id].y++;
        boxColliderArray[it->id].y++;
        debugSpriteBoxCollider[it->id].position.y = boxColliderArray[it->id].y;
      }
    }
  }

  if (stopAnimation == false) {
    // 6 segundos
    if (sunTimer > 0) {
      sunTimer--;
    } else {
      sunTimer = 60 * 6;
      // min:50 max:420
      float x = 50 + rand() % 420;
      createSun(Vec2(x, 10), sunCost::normalSun);
    }
  }

  for (std::vector<Sun>::iterator it = sun.begin(); it < sun.end(); it++) {
    if (boxCollision(&boxColliderArray[cursor.id], &boxColliderArray[it->id])) {
      printf("borrando soles\n");
      sunCounter += it->cost;
      engine->renderer.getTextureRepository()
          .getBySpriteId(spriteArray[it->id].id)
          ->removeLinkById(spriteArray[it->id].id);
      spriteArray.erase(it->id);
      boxColliderArray.erase(it->id);

      animationArray.erase(it->id);
      deleteDebugBoxCollider(it->id);
      Entities::deleteID(it->id);
      it = sun.erase(it);
      sunsCreated--;
    }
  }
  // printf("FPS: %d\n",engine->info.getFps()) ;
  // printf("ram: %f\n",engine->info.getAvailableRAM()) ;
  zombiesManager.collision();
  projectileManager.zombieCollision();

  // printf("animarray size: %d\n",animationArray.size());

  // shoot zombies
  std::vector<Zombie>::iterator it;

  for (int i = 0; i < 45; i++) {
    if (plant[i].type != NonePlant) {
      // printf("hay una planta en %d\n",i);

      for (it = zombie.begin(); it < zombie.end(); it++) {
        //  printf("vec plant %f,%f. vec zombi %f,%f,%f,%f\n",
        //  pointColliderArray[*plant[i].body[0]].x,
        //  pointColliderArray[*plant[i].body[0]].y,
        //  boxColliderArray[*zombie[j].body[0]].x,
        //  boxColliderArray[*zombie[j].body[0]].y,
        //  boxColliderArray[*zombie[j].body[0]].x +
        //  boxColliderArray[*zombie[j].body[0]].width,
        //  boxColliderArray[*zombie[j].body[0]].y +
        //  boxColliderArray[*zombie[j].body[0]].height);

        if (pointColliderArray[*plant[i].body[0]].x <
                boxColliderArray[*(it)->body[0]].x +
                    boxColliderArray[*(it)->body[0]].width &&
            pointColliderArray[*plant[i].body[0]].y >
                boxColliderArray[*(it)->body[0]].y &&
            pointColliderArray[*plant[i].body[0]].y <
                boxColliderArray[*(it)->body[0]].y +
                    boxColliderArray[*(it)->body[0]].height) {
          // printf("hay un zombi en frente\n");
          if (plant[i].attackTimer >= 0) {
            plant[i].attackTimer--;
          } else {
            // printf("disparar\n");
            newProjectile(pointColliderArray[*plant[i].body[0]]);
            plant[i].attackTimer = 60;
          }
          it = zombie.end();
        }
      }
    }
  }

  if (timerZombies > 0) {
    timerZombies--;
  } else {
    static int zombiescreados = 0;
    if (zombiescreados < 2) {
      int row = rand() % 5;
      while (zombieCreateRow[row] == false) {
        row = rand() % 5;
      }

      createZombie(Vec2(mapCollider[row][8].x, mapCollider[row][8].y));
      timerZombies = 60;
      zombiescreados++;
    }
  }

  renderer->beginFrame();

  renderSprites.updateChildPos();
  renderSprites.update();

  // for(int i=0;i<5;i++){
  //     for(int j=0;j<9;j++){
  //         renderer->renderer2D.render(&map[i][j]);
  //     }
  // }
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
      startDebugAnimationMode();
      menuDebugAnimation(engine->pad, engine->font);
      animManager.debug();
    } else {
      menuDebugMode(engine->pad);
      if(stopAnimation == true){
        animManager.debug();
      }
    }
  }

  renderer->endFrame();
}

void Level1::destroy() {}
