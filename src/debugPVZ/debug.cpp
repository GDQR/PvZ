#include "font/font.hpp"
#include "debugPVZ/debug.hpp"
#include "debugPVZ/menuDebugAnimation.hpp"
#include "debugPVZ/menuDebugSprite.hpp"
#include "components.hpp"
#include <iostream>
#include <iterator>

unsigned int debugState = debugMain;
unsigned int debugOption = 0;
bool debugMode = false;
bool debugMenu = false;
bool debugAnimation = false;
bool stopAnimation = false;
bool debugSprite = false;
float debugAlphaColor;
int debugEntityId;
float d_texPosXNull;
float* d_texPosX = &d_texPosXNull;
float d_texPosYNull;
float* d_texPosY = &d_texPosYNull;
Vec2 d_texPosNull;
float* d_scale = NULL;
float d_angleXNull;
float* d_angleX = &d_angleXNull;
float d_angleYNull;
float* d_angleY = &d_angleYNull;
int d_framesCounter;
bool d_saveFramesCounter = true;
bool d_hasScale = false;
std::string d_name;

std::map<int, Tyra::Sprite*> debugSpritesType;  // Normal or rotated sprites
std::vector<int> debugStopRenderRotateSprites;
std::vector<int> debugStopRenderNormalSprites;

Tyra::Texture* debugBoxTexture;
Tyra::Texture* debugFillBoxTexture;
Tyra::Texture* debugPointTexture;

DebugMode debugModeClass;

void activeDebugMode() {
  debugState = debugOption;
  switch (debugOption) {
    case AnimationDebug:
      debugAnimation = true;
      stopAnimation = true;
      break;
    case SpriteDebug:
      debugSprite = true;
      stopAnimation = true;
      break;
    case testDebug:
      break;
    default:
      break;
  }
}

void deactiveDebugMode() {
  switch (debugOption) {
    case AnimationDebug:
      debugAnimation = false;
      stopAnimation = false;
      break;
    case SpriteDebug:
      debugSprite = false;
      stopAnimation = false;
      break;
    case testDebug:
      break;
    default:
      break;
  }
}

void DebugMode::mainMenu(){
  crossOption = true;
  if(debugState == debugMain){
    if (padTimer <= 0) {  
      if (engine->pad.getPressed().DpadUp || leftJoy->v <= 100) {
        padTimer = 10;
        if (debugOption == 0) {
          debugOption = debugModesSize - 1;
        } else {
          debugOption--;
        }
      } else if (engine->pad.getPressed().DpadDown || leftJoy->v >= 200) {
        padTimer = 10;
        if (debugOption == debugModesSize - 1) {
          debugOption = 0;
        } else {
          debugOption++;
        }
      }
    }else{
      padTimer--;
    }

    if (menuCrossClickedOption()) {
      activeDebugMode();
      // debugMenu = false;
    } else if (engine->pad.getClicked().Circle) {
      deactiveDebugMode();
      debugMode = false;
      debugMenu = false;
      if (debugSpritesType.empty() == false) {
        debugSpritesType.clear();
      }
      printf("\nDEBUG MODE DEACTIVE\n");
    }
  }
  if (debugState == AnimationDebug) {
    startDebugAnimationMode(engine->pad, engine->font);
    // animManager.debug();
  } else if (debugState == SpriteDebug) {
    spriteModeMenu();
  } 
}

void DebugMode::drawMainMenu() {
  Tyra::Color colorMenu;
  int textPos = 100;
  for (unsigned int i = 0; i < debugModesSize; i++) {
    if (debugOption != i) {
      colorMenu = black;
    } else {
      colorMenu = orange;
    }

    switch (i) {
      case AnimationDebug:
        engine->font.drawText(&myFont, "Animation Debug", 30, textPos, 16,
                              colorMenu);
        break;
      case SpriteDebug:
        engine->font.drawText(&myFont, "Sprite Debug", 30, textPos, 16,
                              colorMenu);
        break;
      case testDebug:
        engine->font.drawText(&myFont, "Test Debug", 30, textPos, 16,
                              colorMenu);
        break;
      default:
        break;
    }
    textPos += 20;
  }

  engine->font.drawText(&myFont, "PRESS X FOR ACTIVE", 30, 400, 16, black);
  engine->font.drawText(&myFont, "PRESS O FOR DESACTIVE", 30, 420, 16, black);
}

void DebugMode::spriteModeMenu(){
  debugSpriteMode.init();
  debugSpriteMode.menu();
}
int DebugMode::drawSpriteModeMenu(){
  if (spriteArray.size() == 0) {
    // ERROR MENU
    engine->font.drawText(&myFont, "Sprites not found", 30, 80, 16, black);
    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 320, 16, black);
    return 1;
  }
  debugSpriteMode.drawMenu();
  return 0;
}

int startDebugAnimationMode(Tyra::Pad& pad, Tyra::Font& font) {
  // if (animationArray.size() == 0) {
  //   // ERROR MENU
  //   if (engine->pad.getClicked().Circle) {
  //     debugAnimation = false;
  //   }
  //   engine->font.drawText(&myFont, "Animations not found", 30, 80, 16, black);
  //   engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 320, 16, black);
  //   return 1;
  // }

  // if (startAnimationDebug == true) {
  //   printf("start debug animation\n");
  //   startAnimationDebug = false;
  //   std::map<int, Animation>::iterator it;
  //   it = animationArray.begin();
  //   printf("base id: %d\n", it->first);
  //   debugEntityId = it->first;
  // }

  menuDebugAnimation(pad, font, debugEntityId);
  return 0;
}

void loadDebugTextures() {
  debugBoxTexture = loadTexture("asset_box.png");
  debugFillBoxTexture = loadTexture("debug_fillBox.png");
  debugPointTexture = loadTexture("debugPoint.png");
}

void createDebugSprite(const int id, Tyra::SpriteMode mode) {
  if (spriteArray.count(id)) {
    dm_SpriteNormal[id] = Sprite();
    loadSprite(&dm_SpriteNormal[id], mode, spriteArray[id].position,
               spriteArray[id].size);
    debugBoxTexture->addLink(dm_SpriteNormal[id].id);
  }
}

void createDebugSpritePivot(const int id, Tyra::SpriteMode mode) {
  if (spriteArray.count(id)) {
    dm_SpriteNormalPivot[id] = Sprite();
    loadSprite(&dm_SpriteNormalPivot[id], mode, spriteArray[id].position,
               spriteArray[id].size);
    debugPointTexture->addLink(dm_SpriteNormalPivot[id].id);
    dm_SpriteNormalPivot[id].color = Tyra::Color(255.0f, 0.0f, 0.0f, 128.0f);
  }
}

void createDebugBoxCollider(const int id, Tyra::SpriteMode mode) {
  // printf("id debug box: %d\n", id);
  dm_SpriteBoxCollider[id] = Sprite();
  loadSprite(&dm_SpriteBoxCollider[id], mode,
             Vec2(boxColliderArray[id].x, boxColliderArray[id].y),
             Vec2(boxColliderArray[id].width, boxColliderArray[id].height));
  dm_SpriteBoxCollider[id].color = Tyra::Color(0.0f, 255.0f, 0.0, 128.0f);
  debugBoxTexture->addLink(dm_SpriteBoxCollider[id].id);
}

void createDebugBoxFill(const int id, Tyra::SpriteMode mode, Vec2 pos,
                        Vec2 size) {
  // printf("id debug box: %d\n", id);
  dm_SpriteBoxCollider[id] = Sprite();
  loadSprite(&dm_SpriteBoxCollider[id], mode, pos, size);
  debugFillBoxTexture->addLink(dm_SpriteBoxCollider[id].id);
}

void deleteDebugSprite(const int id) {
  if (spriteArray.count(id)) {
    debugBoxTexture->removeLinkById(dm_SpriteNormal[id].id);
    dm_SpriteNormal.erase(id);
  }
}

void deleteDebugSpritePivot(const int id) {
  if (spriteArray.count(id)) {
    debugPointTexture->removeLinkById(dm_SpriteNormalPivot[id].id);
    dm_SpriteNormalPivot.erase(id);
  }
}

void deleteDebugBoxCollider(const int id) {
  debugBoxTexture->removeLinkById(dm_SpriteBoxCollider[id].id);
  dm_SpriteBoxCollider.erase(id);
}

void createDebugPoint(const int id, Tyra::SpriteMode mode) {
  // printf("id point box: %d\n", id);
  dm_SpritePointCollider[id] = Sprite();
  loadSprite(&dm_SpritePointCollider[id], mode,
             Vec2(pointColliderArray[id].x - 1, pointColliderArray[id].y - 1),
             Vec2(31, 31));
  debugPointTexture->addLink(dm_SpritePointCollider[id].id);
  dm_SpritePointCollider[id].color = Tyra::Color(255.0f, 0.0f, 0.0f);
}

void deleteDebugPoint(const int id) {
  debugPointTexture->removeLinkById(dm_SpritePointCollider[id].id);
  dm_SpritePointCollider.erase(id);
}
