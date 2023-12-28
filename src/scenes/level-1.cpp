#include "renderSprite/textures.hpp"
#include "renderSprite/animations.hpp"
#include "states.hpp"
#include "scenes.hpp"
#include "scenes/level-1.hpp"

#include "components.hpp"
#include "debug.hpp"
#include <stdlib.h>
#include <time.h>

using namespace Tyra;

Sprite background;
Sprite Cursor;
Sprite map[5][9];


int xMap = 9;
int yMap = 5;

AnimationManager animManager;
RendererSprites renderSprites;
RendererDebugSpritesManager renderDebugSpritesManager;
ZombiesManager zombiesManager;

int cursor = -1;
Vec2 cursorTile;

int timerZombies = 0;
int maxZombies = 5;

ProjectileManager projectileManager;

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
  // *vec2Array[plant.father] = Vec2(x,y);
  // spriteArray[plant.body[0]]->position += *vec2Array[plant.father];
  // spriteArray[plant.body[1]]->position += *vec2Array[plant.father];

  // *vec2Array[plant.father] = Vec2(0,1);
}

void cursorMovement() {
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

  vec2Array[cursor] = Vec2(x, y);
  spriteArray[cursor].position += vec2Array[cursor];
  vec2Array[cursor] = Vec2(0, 1);
}

void updateBoxCollider() {
  boxColliderArray[cursor].x =
      boxColliderArray[cursor].offsetX + spriteArray[cursor].position.x;
  boxColliderArray[cursor].y =
      boxColliderArray[cursor].offsetY + spriteArray[cursor].position.y;
  debugSpriteBoxCollider[cursor].position =
      Vec2(boxColliderArray[cursor].x, boxColliderArray[cursor].y);
}

void Level1::init() {
  srand(time(NULL));
  animManager.texRepo = &engine->renderer.getTextureRepository();
  loadDebugTextures();
  // load background
  loadSprite(&background, Vec2(780, 524));
  loadTexture(&background, "Backgrounds/DAY Unsodded.png");
  background.position = Vec2(-56, -1);

  // loadTexture(&map[0][0],"asset_box.png"); // debug map

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      plantCreatedInMap[i][j] = false;
      mapCollider[i][j].x = 85 + (45 * j);
      mapCollider[i][j].y = 58 + (72 * i);
      mapCollider[i][j].width = 45;
      mapCollider[i][j].height = 72;
      map[i][j].mode = SpriteMode::MODE_STRETCH;
      map[i][j].position = Vec2(mapCollider[i][j].x, mapCollider[i][j].y);
      map[i][j].size = Vec2(mapCollider[i][j].width, mapCollider[i][j].height);
      debugBoxTexture->addLink(map[i][j].id);
    }
  }
  map[0][1].color = Color(0, 255, 0, 128);

  printf("pase una vez 1\n");
  zombieCreateRow[2] = true;
  newCursor(&cursor, Vec2(map[0][0].position.x, map[0][0].position.y));
  loadPeaShooterAnimation();
  loadZombieAnimation();
  loadProjectile();
  // renderer->core.setFrameLimit(false);
}

void Level1::update() {
  // if(engine->pad.getClicked().R1){
  //     debugMode = !debugMode;
  //     if(debugMode == true){
  //         printf("\nDEBUG MODE ACTIVE\n");
  //         debugMenu();
  //     }else{
  //         printf("\nDEBUG MODE DEACTIVE\n");
  //     }
  // }

  // if(debugMode == true){
  //     if(engine->pad.getPressed().DpadUp){
  //         if(debugOption == 0){ debugOption = debugModesSize-1; }
  //         else{
  //             debugOption--;
  //         }
  //         debugMenu();
  //     }else if(engine->pad.getPressed().DpadDown){

  //         if(debugOption == debugModesSize-1){ debugOption = 0; }
  //         else{
  //             debugOption++;
  //         }
  //         debugMenu();
  //     }

  //     if(engine->pad.getPressed().Cross){
  //         activeDebugMode();
  //     }else if(engine->pad.getPressed().Circle){
  //         deactiveDebugMode();
  //     }
  // }

  // plantMovement();
  if (cursor != -1) {
    cursorMovement();
    updateBoxCollider();
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (boxCollision(&boxColliderArray[cursor], &mapCollider[i][j]) == true) {
        cursorTile = Vec2(i, j);
        //  printf("estoy en tile %d,%d\n",j,i);
        i = 5;
        j = 9;
      }
    }
  }

  if (engine->pad.getClicked().Cross && debugMode == false) {
    if(zombieCreateRow[(int)cursorTile.x] == true){
      if (plantsCreated < maxPlants) {
        createPlant(cursorTile.x, cursorTile.y);
      } else {
        printf("max plants created\n");
      }
    }
  }

  projectileManager.update();
  zombiesManager.update();

  if (stopAnimation == false) {
    animManager.update();
  }
  // printf("FPS: %d\n",engine->info.getFps()) ;
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
                boxColliderArray[*(it)->body[0]].x + boxColliderArray[*(it)->body[0]].width &&
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

  if(timerZombies>0){
    timerZombies--;
  }else{
    static int zombiescreados = 0;
    if(zombiescreados<2){
      int row = rand() % 5;
      while(zombieCreateRow[row] == false){
        row = rand() % 5;
      }
      
      createZombie(Vec2(mapCollider[row][8].x,mapCollider[row][8].y));
      timerZombies=60;
      zombiescreados++;
    }
    
  }

  renderer->beginFrame();
  renderer->renderer2D.render(&background);

  renderSprites.update();

  // for(int i=0;i<5;i++){
  //     for(int j=0;j<9;j++){
  //         renderer->renderer2D.render(&map[i][j]);
  //     }
  // }
  renderDebugSpritesManager.update();
  renderer->endFrame();
}

void Level1::destroy() {}
