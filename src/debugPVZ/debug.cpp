#include "debugPVZ/debug.hpp"
#include "debugPVZ/debugMenuAnimation.hpp"
#include "components.hpp"
#include <iostream>
#include <iterator>

unsigned int debugOption = 0;
bool debugMode = false;
bool debugMenu = false;
bool debugAnimation = false;
bool stopAnimation = false;
bool debugSprite = false;

Tyra::Texture* debugBoxTexture;
Tyra::Texture* debugFillBoxTexture;
Tyra::Texture* debugPointTexture;

void activeDebugMode() {
  switch (debugOption) {
    case AnimationDebug:
      debugAnimation = true;
      stopAnimation = true;
      // isMainMenuAnimationActive = true;
      break;
    case SpriteDebug:
      debugSprite = true;
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
      // isMainMenuAnimationActive = false;
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
  } else if (menuUpOption(pad)) {
    if (debugOption == 0) {
      debugOption = debugModesSize - 1;
    } else {
      debugOption--;
    }
  } else if (menuDownOption(pad)) {
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
    printf("\nDEBUG MODE DEACTIVE\n");
  }

  Tyra::Color colorMenu;
  for (unsigned int i = 0; i < debugModesSize; i++) {
    if (debugOption != i) {
      colorMenu = black;
    } else {
      colorMenu = orange;
    }

    switch (i) {
      case AnimationDebug:
        engine->font.drawText(&myFont, "Animation Debug", 30, 100, 16,
                              colorMenu);
        break;
      case testDebug:
        engine->font.drawText(&myFont, "Test Debug", 30, 120, 16, colorMenu);
        break;
      default:
        break;
    }
  }

  engine->font.drawText(&myFont, "PRESS X FOR ACTIVE", 30, 300, 16, black);
  engine->font.drawText(&myFont, "PRESS O FOR DESACTIVE", 30, 320, 16, black);
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

  menuDebugAnimation(pad, font);
  return 0;
}

void loadDebugTextures() {
  debugBoxTexture = loadTexture("asset_box.png");
  debugFillBoxTexture = loadTexture("debug_fillBox.png");
  debugPointTexture = loadTexture("debugPoint.png");
}

void createDebugBoxCollider(const int id, Tyra::SpriteMode mode) {
  // printf("id debug box: %d\n", id);
  debugSpriteBoxCollider[id] = Sprite();
  loadSprite(&debugSpriteBoxCollider[id], mode,
             Vec2(boxColliderArray[id].x, boxColliderArray[id].y),
             Vec2(boxColliderArray[id].width, boxColliderArray[id].height));
  debugBoxTexture->addLink(debugSpriteBoxCollider[id].id);
}

void createDebugBoxFill(const int id, Tyra::SpriteMode mode, Vec2 pos,
                        Vec2 size) {
  // printf("id debug box: %d\n", id);
  debugSpriteBoxCollider[id] = Sprite();
  loadSprite(&debugSpriteBoxCollider[id], mode, pos, size);
  debugFillBoxTexture->addLink(debugSpriteBoxCollider[id].id);
}

void deleteDebugBoxCollider(const int id) {
  debugBoxTexture->removeLinkById(debugSpriteBoxCollider[id].id);
  debugSpriteBoxCollider.erase(id);
}

void createDebugPoint(const int id, Tyra::SpriteMode mode) {
  // printf("id point box: %d\n", id);
  debugSpritePointCollider[id] = Sprite();
  loadSprite(&debugSpritePointCollider[id], mode,
             Vec2(pointColliderArray[id].x - 1, pointColliderArray[id].y - 1),
             Vec2(31, 31));
  debugPointTexture->addLink(debugSpritePointCollider[id].id);
  debugSpritePointCollider[id].color = Tyra::Color(255.0f, 0.0f, 0.0f);
}

void deleteDebugPoint(const int id) {
  debugPointTexture->removeLinkById(debugSpritePointCollider[id].id);
  debugSpritePointCollider.erase(id);
}
