#include "debugPVZ/debug.hpp"
#include "components.hpp"
#include <iostream>
#include <iterator>

unsigned int debugOption = 0;
bool debugMode = false;
bool debugMenu = false;
bool debugAnimation = false;
bool stopAnimation = false;

Tyra::Texture* debugBoxTexture;
Tyra::Texture* debugFillBoxTexture;
Tyra::Texture* debugPointTexture;

int padTimer = 0;

bool menuUpOption(Tyra::Pad& pad) {
  if ((pad.getPressed().DpadUp || leftJoy->v <= 100) && padTimer <= 0) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuDownOption(Tyra::Pad& pad) {
  if ((pad.getPressed().DpadDown || leftJoy->v >= 200) && padTimer <= 0) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuCrossClickedOption(Tyra::Pad& pad, const bool isActive){
  if(pad.getClicked().Cross && isActive == true){
    return true;
  }
  return false;
}

bool menuCircleClickedOption(Tyra::Pad& pad, const bool isActive){
  if(pad.getClicked().Circle && isActive == true){
    return true;
  }
  return false;
}


void debugMenuMode() {
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
int debugSprite;

void debugOptions(Tyra::Pad& pad, Tyra::Font& font) {
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

    if (menuCrossClickedOption(pad,true)) {
      activeDebugMode();
      debugMenu = false;
    } else if (menuCrossClickedOption(pad,true)) {
      deactiveDebugMode();
      debugMode = false;
      debugMenu = false;
      printf("\nDEBUG MODE DEACTIVE\n");
    }
  
}

void activeDebugMode() {
  switch (debugOption) {
    case AnimationDebug:
      debugAnimation = true;
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
    case testDebug:
      break;
    default:
      break;
  }
}

int startDebugAnimationMode() {
  if (startDebug == false) {
    return 1;
  }
  startDebug = false;
  printf("start debug animation\n");
  printf("sprites size: %d\n", spriteArray.size());
  std::map<int, Sprite>::iterator it;
  it = spriteArray.begin();
  // it++;
  printf("base id: %d\n", it->first);
  debugSprite = it->first;
  // debugSprite = Entities::newID();
  // createDebugBoxFill(debugSprite,
  // Tyra::SpriteMode::MODE_STRETCH,it->second.position,it->second.size);
  // debugSpriteBoxCollider[debugSprite].color = Tyra::Color(255.0f, 0.0f, 0,
  // 100.0f);

  return 0;
}

float colorSprite = -2;
void debugAnimationMode(Tyra::Pad& pad, Tyra::Font& font) {
  spriteArray[debugSprite].color.a += colorSprite;
  if (spriteArray[debugSprite].color.a <= 30.0f) {
    colorSprite = 2;
  } else if (spriteArray[debugSprite].color.a >= 128.0f) {
    colorSprite = -2;
  }

  if (pad.getClicked().Cross) {

  }else if(pad.getClicked().Circle){

  }

  if (padTimer > 0) {
    padTimer--;
  } else if (menuUpOption(pad)) {
    spriteArray[debugSprite].color.a = 128.0f;

    std::map<int, Sprite>::iterator it = spriteArray.find(debugSprite);

    if (std::next(it)->first == spriteArray.end()->first) {
      debugSprite = spriteArray.begin()->first;
    } else {
      debugSprite = std::next(it)->first;
    }

  } else if (menuDownOption(pad)) {
    spriteArray[debugSprite].color.a = 128.0f;

    std::map<int, Sprite>::iterator it = spriteArray.find(debugSprite);

    if (debugSprite == spriteArray.begin()->first) {
      debugSprite = spriteArray.rbegin()->first;
    } else {
      debugSprite = std::prev(it)->first;
    }
  }
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

void menuDebugAnimation(Tyra::Font& font) {
  std::string textId = "Entitie ID: " + std::to_string(debugSprite);
  std::string name = "Name Texture: " + renderer->getTextureRepository().getBySpriteId(spriteArray[debugSprite].id)->name;
  std::string position =
      "Position: " + std::to_string(spriteArray[debugSprite].position.x) +
      ", " + std::to_string(spriteArray[debugSprite].position.y);
  engine->font.drawText(&myFont, textId, 30, 80, 16, Tyra::Color(0, 0, 0, 128));
  engine->font.drawText(&myFont, name, 30, 100, 16, Tyra::Color(0, 0, 0, 128));
  engine->font.drawText(&myFont, position, 30, 120, 16,
                        Tyra::Color(0, 0, 0, 128));
}