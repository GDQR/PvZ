#include "debugPVZ/menuDebugAnimation.hpp"
#include "font/font.hpp"
#include "components.hpp"

bool isMainMenuAnimationActive = true;
bool startAnimationDebug = true;

void subMenu(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  Vec2* texPos = animationDataArray[animationArray[entitieID].animID]
                     .position[animationArray[entitieID].key];

  if (pad.getClicked().L1) {
    if (animationArray[entitieID].key > 0) {
      animationArray[entitieID].key--;
    } else {
      animationArray[entitieID].key =
          animationDataArray[animationArray[entitieID].animID].keys.size() - 1;
    }
    animManager.debugChangeFrame(entitieID, animationArray[entitieID].key);
  } else if (pad.getClicked().R1) {
    animationArray[entitieID].key++;
    if (animationArray[entitieID].key >=
        animationDataArray[animationArray[entitieID].animID].keys.size()) {
      animationArray[entitieID].key = 0;
    }
    animManager.debugChangeFrame(entitieID, animationArray[entitieID].key);
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
    } else if (menuDownOption(pad)) {
      texPos->y++;
    }

    if (menuLeftOption(pad)) {
      texPos->x--;
    } else if (menuRightOption(pad)) {
      texPos->x++;
    }
  }

  if (playAnimation == true) {
    animManager.debugAnim(entitieID);
  }

  if (hideText == false) {
    std::string position =
        "Position: " + std::to_string(posArray[entitieID].x) + ", " +
        std::to_string(posArray[entitieID].y);
    std::string texPosition = "Texture Position: " + std::to_string(texPos->x) +
                              ", " + std::to_string(texPos->y);

    std::string animSize =
        "Total textures: " +
        std::to_string(
            animationDataArray[animationArray[entitieID].animID].keys.size());

    std::string textKey =
        "Key: " + std::to_string(animationArray[entitieID].key);

    engine->font.drawText(&myFont, textKey, 30, 120, 16, black);
    engine->font.drawText(&myFont, position, 30, 140, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, texPosition, 30, 160, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, animSize, 30, 180, 16, black);

    engine->font.drawText(&myFont, "PRESS L1 FOR Prev Texture", 30, 340, 16,
                          black);
    engine->font.drawText(&myFont, "PRESS R1 FOR Next Texture", 30, 360, 16,
                          black);
    engine->font.drawText(&myFont, "PRESS [] FOR HIDE/SHOW TEXT", 30, 380, 16,
                          black);
    engine->font.drawText(&myFont, "PRESS X FOR PLAY/STOP ANIMATION", 30, 400,
                          16, black);
  }
}

void menuDebugAnimation(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  if (isMainMenuAnimationActive == true) {
    // Main menu Animation

    spriteArray[entitieID].color.a += colorSprite;
    if (spriteArray[entitieID].color.a <= 30.0f) {
      colorSprite = 2;
    } else if (spriteArray[entitieID].color.a >= 128.0f) {
      colorSprite = -2;
    }

    if (menuCrossClickedOption(pad, isMainMenuAnimationActive)) {
      isMainMenuAnimationActive = false;
      spriteArray[entitieID].color.a = 128.0f;
    } else if (menuCircleClickedOption(pad, isMainMenuAnimationActive)) {
      debugAnimation = false;
      startAnimationDebug = true;
      spriteArray[entitieID].color.a = 128.0f;
    }

    if (padTimer > 0) {
      padTimer--;
    } else if (menuUpOption(pad) || menuRightOption(pad)) {
      spriteArray[entitieID].color.a = 128.0f;

      std::map<int, Animation>::iterator it = animationArray.find(entitieID);

      if (std::next(it)->first == animationArray.end()->first) {
        entitieID = animationArray.begin()->first;
      } else {
        entitieID = std::next(it)->first;
      }

    } else if (menuDownOption(pad) || menuLeftOption(pad)) {
      spriteArray[entitieID].color.a = 128.0f;

      std::map<int, Animation>::iterator it = animationArray.find(entitieID);

      if (entitieID == animationArray.begin()->first) {
        entitieID = animationArray.rbegin()->first;
      } else {
        entitieID = std::prev(it)->first;
      }
    }
    engine->font.drawText(&myFont, "PRESS X FOR SELECT THE TEXTURE", 30, 400,
                          16, black);
  } else {
    // SubMenu for move position
    subMenu(pad, font, entitieID);
  }

  if (hideText == false) {
    std::string textId = "Entitie ID: " + std::to_string(entitieID);
    std::string name =
        "Name Texture: " + renderer->getTextureRepository()
                               .getBySpriteId(spriteArray[entitieID].id)
                               ->name;
    engine->font.drawText(&myFont, textId, 30, 80, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, name, 30, 100, 16,
                          Tyra::Color(0, 0, 0, 128));

    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 420, 16, black);
  }
}
