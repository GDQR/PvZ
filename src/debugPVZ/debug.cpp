#include "font/font.hpp"
#include "debugPVZ/debug.hpp"
#include "debugPVZ/menuDebugAnimation.hpp"
#include "debugPVZ/menuDebugSprite.hpp"
#include "components.hpp"
#include <iostream>
#include <iterator>

unsigned int debugOption = 0;
bool debugMode = false;
bool debugMenu = false;
bool debugAnimation = false;
bool stopAnimation = false;
bool debugSprite = false;
float debugAlphaColor;
int debugEntitieId;
Vec2* texPos = NULL;
float* d_scale = NULL;
float* d_angle = NULL;
bool d_hasScale = false;

std::map<int, Tyra::Sprite*> debugSpritesType;  // Normal or rotated sprites
std::vector<int> debugStopRenderRotateSprites;
std::vector<int> debugStopRenderNormalSprites;

Tyra::Texture* debugBoxTexture;
Tyra::Texture* debugFillBoxTexture;
Tyra::Texture* debugPointTexture;

void activeDebugMode() {
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

void menuDebugMode(Tyra::Pad& pad) {
  if (padTimer > 0) {
    padTimer--;
  } else if (menuUpOptionLeftJoy(pad)) {
    if (debugOption == 0) {
      debugOption = debugModesSize - 1;
    } else {
      debugOption--;
    }
  } else if (menuDownOptionLeftJoy(pad)) {
    if (debugOption == debugModesSize - 1) {
      debugOption = 0;
    } else {
      debugOption++;
    }
  }

  if (menuCrossClickedOption(pad, true)) {
    activeDebugMode();
    // debugMenu = false;
  } else if (menuCircleClickedOption(pad, true)) {
    deactiveDebugMode();
    debugMode = false;
    debugMenu = false;
    if (debugSpritesType.empty() == false) {
      debugSpritesType.clear();
    }
    printf("\nDEBUG MODE DEACTIVE\n");
  }

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

int startDebugAnimationMode(Tyra::Pad& pad, Tyra::Font& font) {
  if (animationArray.size() == 0) {
    // ERROR MENU
    if (engine->pad.getClicked().Circle) {
      debugAnimation = false;
    }
    engine->font.drawText(&myFont, "Animations not found", 30, 80, 16, black);
    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 320, 16, black);
    return 1;
  }

  if (startAnimationDebug == true) {
    printf("start debug animation\n");
    startAnimationDebug = false;
    std::map<int, Animation>::iterator it;
    it = animationArray.begin();
    printf("base id: %d\n", it->first);
    debugEntitieId = it->first;
  }

  menuDebugAnimation(pad, font, debugEntitieId);
  return 0;
}

int startDebugSpriteMode(Tyra::Pad& pad, Tyra::Font& font) {
  if (spriteArray.size() == 0) {
    // ERROR MENU
    if (engine->pad.getClicked().Circle) {
      debugAnimation = false;
    }
    engine->font.drawText(&myFont, "Sprites not found", 30, 80, 16, black);
    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 320, 16, black);
    return 1;
  }

  if (startSpriteDebug == true) {
    printf("start debug sprite\n");
    startSpriteDebug = false;

    // Get all normal and rotated sprites
    std::map<int, Sprite>::iterator it;
    for (it = spriteArray.begin(); it != spriteArray.end(); it++) {
      debugSpritesType[it->first] = &it->second;
    }

    for (it = spritesRotate.begin(); it != spritesRotate.end(); it++) {
      debugSpritesType[it->first] = &it->second;
    }

    debugEntitieId = debugSpritesType.begin()->first;
    debugAlphaColor = debugSpritesType.begin()->second->color.a;
    printf("base id: %d\n", debugEntitieId);
  }

  menuDebugSprite(pad, font, debugEntitieId);
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
  }else{
    dm_SpriteRotate[id] = Sprite(); 
    loadSprite(&dm_SpriteRotate[id], mode, spritesRotate[id].position,
               spritesRotate[id].size);
    debugBoxTexture->addLink(dm_SpriteRotate[id].id);
  }
}

void createDebugSpritePivot(const int id, Tyra::SpriteMode mode) {
  if (spriteArray.count(id)) {
    dm_SpriteNormalPivot[id] = Sprite();
    loadSprite(&dm_SpriteNormalPivot[id], mode, spriteArray[id].position,
               spriteArray[id].size);
    debugPointTexture->addLink(dm_SpriteNormalPivot[id].id);
    dm_SpriteNormalPivot[id].color = Tyra::Color(255.0f, 0.0f, 0.0f, 128.0f);
  }else{
    dm_SpriteRotatePivot[id] = Sprite(); 
    loadSprite(&dm_SpriteRotatePivot[id], mode, spritesRotate[id].position,
               spritesRotate[id].size);
    debugPointTexture->addLink(dm_SpriteRotatePivot[id].id);
    dm_SpriteRotatePivot[id].color = Tyra::Color(255.0f, 0.0f, 0.0f, 128.0f);
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
  }else{
    debugBoxTexture->removeLinkById(dm_SpriteRotate[id].id);
    dm_SpriteRotate.erase(id);
  }
}

void deleteDebugSpritePivot(const int id) {
  if (spriteArray.count(id)) {
    debugPointTexture->removeLinkById(dm_SpriteNormalPivot[id].id);
    dm_SpriteNormalPivot.erase(id);
  }else{
    debugPointTexture->removeLinkById(dm_SpriteRotatePivot[id].id);
    dm_SpriteRotatePivot.erase(id);
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
