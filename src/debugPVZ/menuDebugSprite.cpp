#include "debugPVZ/menuDebugSprite.hpp"
#include "font/font.hpp"
#include "components.hpp"

bool startSpriteDebug = true;
bool isMainMenuActive = true;
bool animationFound = false;

void subMenuSprite(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  if (pad.getClicked().L1 && animationFound == true) {
    if (animationArray[entitieID].key > 0) {
      animationArray[entitieID].key--;
    } else {
      animationArray[entitieID].key =
          animationDataArray[animationArray[entitieID].animID].keys.size() - 1;
    }
    animManager.debugChangeFrame(entitieID, animationArray[entitieID].key);
  } else if (pad.getClicked().R1 && animationFound == true) {
    animationArray[entitieID].key++;
    if (animationArray[entitieID].key >=
        animationDataArray[animationArray[entitieID].animID].keys.size()) {
      animationArray[entitieID].key = 0;
    }
    animManager.debugChangeFrame(entitieID, animationArray[entitieID].key);
  } else if (pad.getClicked().Circle) {
    isMainMenuActive = true;
    animationFound = false;
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
      if (padPressTimer < 20) {
        padPressTimer++;

        if (padPressTimer == 10) {
          padSpeed = 2.0f;
        } else if (padPressTimer == 20) {
          padSpeed = 3.0f;
        }
      }
      posArray[entitieID].y -= padSpeed;
    } else if (menuDownOption(pad)) {
      if (padPressTimer < 20) {
        padPressTimer++;

        if (padPressTimer == 10) {
          padSpeed = 2.0f;
        } else if (padPressTimer == 20) {
          padSpeed = 3.0f;
        }
      }
      posArray[entitieID].y += padSpeed;
    }

    if (menuLeftOption(pad)) {
      if (padPressTimer < 20) {
        padPressTimer++;

        if (padPressTimer == 10) {
          padSpeed = 2.0f;
        } else if (padPressTimer == 20) {
          padSpeed = 3.0f;
        }
      }
      posArray[entitieID].x -= padSpeed;
    } else if (menuRightOption(pad)) {
      if (padPressTimer < 20) {
        padPressTimer++;

        if (padPressTimer == 10) {
          padSpeed = 2.0f;
        } else if (padPressTimer == 20) {
          padSpeed = 3.0f;
        }
      }
      posArray[entitieID].x += padSpeed;
    }

    if (menuUpOption(pad) == false && menuDownOption(pad) == false &&
    menuLeftOption(pad) == false && menuRightOption(pad) == false) {
      padPressTimer = 0;
      padSpeed = 1;
    }
  }

  if (animationFound == true && playAnimation == true) {
    animManager.debugAnim(entitieID);
  }

  if (hideText == false) {
    std::string position =
        "Position: " + std::to_string(posArray[entitieID].x) + ", " +
        std::to_string(posArray[entitieID].y);

    engine->font.drawText(&myFont, position, 30, 140, 16,
                          Tyra::Color(0, 0, 0, 128));
    if (animationFound == true) {
      Vec2* texPos = animationDataArray[animationArray[entitieID].animID]
                         .position[animationArray[entitieID].key];

      std::string textKey =
          "Key: " + std::to_string(animationArray[entitieID].key);

      std::string texPosition =
          "Texture Position: " + std::to_string(texPos->x) + ", " +
          std::to_string(texPos->y);

      std::string animSize =
          "Total textures: " +
          std::to_string(
              animationDataArray[animationArray[entitieID].animID].keys.size());

      engine->font.drawText(&myFont, textKey, 30, 120, 16, black);

      engine->font.drawText(&myFont, texPosition, 30, 160, 16,
                            Tyra::Color(0, 0, 0, 128));

      engine->font.drawText(&myFont, animSize, 30, 180, 16, black);

      engine->font.drawText(&myFont, "PRESS L1 FOR Prev Texture", 30, 340, 16,
                            black);
      engine->font.drawText(&myFont, "PRESS R1 FOR Next Texture", 30, 360, 16,
                            black);
      engine->font.drawText(&myFont, "PRESS X FOR PLAY/STOP ANIMATION", 30, 400,
                          16, black);
    }

    engine->font.drawText(&myFont, "PRESS [] FOR HIDE/SHOW TEXT", 30, 380, 16,
                          black);
    
  }
}

void menuDebugSprite(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  if (isMainMenuActive == true) {
    // Main menu Sprite

    spriteArray[entitieID].color.a += colorSprite;
    if (spriteArray[entitieID].color.a <= 30.0f) {
      colorSprite = 2;
    } else if (spriteArray[entitieID].color.a >= 128.0f) {
      colorSprite = -2;
    }

    if (menuCrossClickedOption(pad, true)) {
      isMainMenuActive = false;
      spriteArray[entitieID].color.a = debugAlphaColor;
      if (animationArray.count(entitieID) == 1) {
        animationFound = true;
      }
    } else if (menuCircleClickedOption(pad, true)) {
      debugSprite = false;
      animationFound = false;
      startSpriteDebug = true;
      spriteArray[entitieID].color.a = debugAlphaColor;
    }

    if (padTimer > 0) {
      padTimer--;
    } else if (menuUpOption(pad) || menuRightOption(pad)) {
      spriteArray[entitieID].color.a = debugAlphaColor;

      std::map<int, Sprite>::iterator it = spriteArray.find(entitieID);

      if (std::next(it)->first == spriteArray.end()->first) {
        entitieID = spriteArray.begin()->first;
      } else {
        entitieID = std::next(it)->first;
      }
      debugAlphaColor = spriteArray[entitieID].color.a;

    } else if (menuDownOption(pad) || menuLeftOption(pad)) {
      spriteArray[entitieID].color.a = debugAlphaColor;

      std::map<int, Sprite>::iterator it = spriteArray.find(entitieID);

      if (entitieID == spriteArray.begin()->first) {
        entitieID = spriteArray.rbegin()->first;
      } else {
        entitieID = std::prev(it)->first;
      }
      debugAlphaColor = spriteArray[entitieID].color.a;
    }
    engine->font.drawText(&myFont, "PRESS X FOR SELECT THE TEXTURE", 30, 400,
                          16, black);
  } else {
    // SubMenu for move position
    subMenuSprite(pad, font, entitieID);
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
