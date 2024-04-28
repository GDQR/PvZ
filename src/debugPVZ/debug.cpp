#include "debugPVZ/debug.hpp"
#include "components.hpp"
#include <iostream>
#include <iterator>

unsigned int debugOption = 0;
bool debugMode = false;
bool debugMenu = false;
bool debugAnimation = false;
bool stopAnimation = false;
bool isMainMenuAnimationActive = false;

Tyra::Texture* debugBoxTexture;
Tyra::Texture* debugFillBoxTexture;
Tyra::Texture* debugPointTexture;

int padTimer = 0;
float colorSprite = -2;

void activeDebugMode() {
  switch (debugOption) {
    case AnimationDebug:
      debugAnimation = true;
      stopAnimation = true;
      isMainMenuAnimationActive = true;
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
      isMainMenuAnimationActive = false;
      break;
    case testDebug:
      break;
    default:
      break;
  }
}

bool menuUpOption(Tyra::Pad& pad) {
  if ((pad.getPressed().DpadUp || leftJoy->v <= 100)) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuDownOption(Tyra::Pad& pad) {
  if ((pad.getPressed().DpadDown || leftJoy->v >= 200)) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuLeftOption(Tyra::Pad& pad) {
  if ((pad.getPressed().DpadLeft || leftJoy->h <= 100)) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuRightOption(Tyra::Pad& pad) {
  if ((pad.getPressed().DpadRight || leftJoy->h >= 200)) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuCrossClickedOption(Tyra::Pad& pad, const bool isActive) {
  if (pad.getClicked().Cross && isActive == true) {
    return true;
  }
  return false;
}

bool menuCircleClickedOption(Tyra::Pad& pad, const bool isActive) {
  if (pad.getClicked().Circle && isActive == true) {
    return true;
  }
  return false;
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

bool startDebug = true;
bool hideText = false;
int debugEntitieId;

int startDebugAnimationMode() {
  if (startDebug == false) {
    return 1;
  }

  if (animationArray.size() == 0) {
    if (engine->pad.getClicked().Circle) {
      debugAnimation = false;
    }
    engine->font.drawText(&myFont, "Animations not found", 30, 80, 16, black);
    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 320, 16, black);
    return 2;
  }

  printf("start debug animation\n");
  startDebug = false;
  std::map<int, Animation>::iterator it;
  it = animationArray.begin();
  printf("base id: %d\n", it->first);
  debugEntitieId = it->first;

  return 0;
}

bool playAnimation = false;

int menuDebugAnimation(Tyra::Pad& pad, Tyra::Font& font) {
  if (startDebug == true) {
    return 1;
  }
  if (isMainMenuAnimationActive == true) {
    // Main menu Animation

    spriteArray[debugEntitieId].color.a += colorSprite;
    if (spriteArray[debugEntitieId].color.a <= 30.0f) {
      colorSprite = 2;
    } else if (spriteArray[debugEntitieId].color.a >= 128.0f) {
      colorSprite = -2;
    }

    if (menuCrossClickedOption(pad, isMainMenuAnimationActive)) {
      isMainMenuAnimationActive = false;
      spriteArray[debugEntitieId].color.a = 128.0f;
    } else if (menuCircleClickedOption(pad, isMainMenuAnimationActive)) {
      debugAnimation = false;
      startDebug = true;
      spriteArray[debugEntitieId].color.a = 128.0f;
    }

    if (padTimer > 0) {
      padTimer--;
    } else if (menuUpOption(pad)) {
      spriteArray[debugEntitieId].color.a = 128.0f;

      std::map<int, Animation>::iterator it =
          animationArray.find(debugEntitieId);

      if (std::next(it)->first == animationArray.end()->first) {
        debugEntitieId = animationArray.begin()->first;
      } else {
        debugEntitieId = std::next(it)->first;
      }

    } else if (menuDownOption(pad)) {
      spriteArray[debugEntitieId].color.a = 128.0f;

      std::map<int, Animation>::iterator it =
          animationArray.find(debugEntitieId);

      if (debugEntitieId == animationArray.begin()->first) {
        debugEntitieId = animationArray.rbegin()->first;
      } else {
        debugEntitieId = std::prev(it)->first;
      }
    }
    engine->font.drawText(&myFont, "PRESS X FOR SELECT THE TEXTURE", 30, 300,
                          16, black);
  } else {
    // SubMenu for move position
    Vec2* texPos = animationDataArray[animationArray[debugEntitieId].animID]
                       .position[animationArray[debugEntitieId].key];

    if (pad.getClicked().L1) {
      if (animationArray[debugEntitieId].key > 0) {
        animationArray[debugEntitieId].key--;
      } else {
        animationArray[debugEntitieId].key =
            animationDataArray[animationArray[debugEntitieId].animID]
                .keys.size() -
            1;
      }
      animManager.debugChangeFrame(debugEntitieId,
                                   animationArray[debugEntitieId].key);
    } else if (pad.getClicked().R1) {
      animationArray[debugEntitieId].key++;
      if (animationArray[debugEntitieId].key >=
          animationDataArray[animationArray[debugEntitieId].animID]
              .keys.size()) {
        animationArray[debugEntitieId].key = 0;
      }
      animManager.debugChangeFrame(debugEntitieId,
                                   animationArray[debugEntitieId].key);
    } else if (pad.getClicked().Circle) {
      isMainMenuAnimationActive = true;
      hideText = false;
      playAnimation = false;
    } else if (pad.getClicked().Square) {
      hideText = !hideText;
    } else if (pad.getClicked().Cross) {
      playAnimation = !playAnimation;
    }

    if (padTimer > 0) {
      padTimer--;
    } else {
      if (menuUpOption(pad)) {
        texPos->y--;
        animManager.debugChangeFrame(debugEntitieId,
                                     animationArray[debugEntitieId].key);
      } else if (menuDownOption(pad)) {
        texPos->y++;
        animManager.debugChangeFrame(debugEntitieId,
                                     animationArray[debugEntitieId].key);
      }

      if (menuLeftOption(pad)) {
        texPos->x--;
        animManager.debugChangeFrame(debugEntitieId,
                                     animationArray[debugEntitieId].key);
      } else if (menuRightOption(pad)) {
        texPos->x++;
        animManager.debugChangeFrame(debugEntitieId,
                                     animationArray[debugEntitieId].key);
      }
    }

    if (playAnimation == true) {
      animManager.debugAnim(debugEntitieId);
    }

    if (hideText == false) {
      std::string position =
          "Position: " + std::to_string(posArray[debugEntitieId].x) + ", " +
          std::to_string(posArray[debugEntitieId].y);
      std::string texPosition =
          "Texture Position: " + std::to_string(texPos->x) + ", " +
          std::to_string(texPos->y);

      std::string animSize =
          "Total textures: " +
          std::to_string(
              animationDataArray[animationArray[debugEntitieId].animID]
                  .keys.size());

      std::string textKey =
          "Key: " + std::to_string(animationArray[debugEntitieId].key);

      engine->font.drawText(&myFont, textKey, 30, 120, 16, black);
      engine->font.drawText(&myFont, position, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
      engine->font.drawText(&myFont, texPosition, 30, 160, 16,
                            Tyra::Color(0, 0, 0, 128));
      engine->font.drawText(&myFont, animSize, 30, 180, 16, black);

      engine->font.drawText(&myFont, "PRESS L1 FOR Prev Texture", 30, 240, 16,
                            black);
      engine->font.drawText(&myFont, "PRESS R1 FOR Next Texture", 30, 260, 16,
                            black);
      engine->font.drawText(&myFont, "PRESS [] FOR HIDE/SHOW TEXT", 30, 280, 16,
                            black);
      engine->font.drawText(&myFont, "PRESS X FOR PLAY/STOP ANIMATION", 30, 300,
                            16, black);
    }
  }

  if (hideText == false) {
    std::string textId = "Entitie ID: " + std::to_string(debugEntitieId);
    std::string name =
        "Name Texture: " + renderer->getTextureRepository()
                               .getBySpriteId(spriteArray[debugEntitieId].id)
                               ->name;
    engine->font.drawText(&myFont, textId, 30, 80, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, name, 30, 100, 16,
                          Tyra::Color(0, 0, 0, 128));

    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 320, 16, black);
  }
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
