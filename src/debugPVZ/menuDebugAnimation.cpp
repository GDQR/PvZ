#include "debugPVZ/menuDebugAnimation.hpp"
#include "components.hpp"
#include "font/font.hpp"
#include "systems.hpp"

bool isMainMenuAnimationActive = true;
bool startAnimationDebug = true;

void subMenu(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  // TODO: Fix this texpos
  Tyra::Vec2* texPos;
  texPos = &animationDataArray[animationArray[entitieID].animID]
                     .position[animationArray[entitieID].currentFrame];

  if (pad.getClicked().L1) {
    if (animationArray[entitieID].currentFrame > 0) {
      animationArray[entitieID].currentFrame--;
    } else {
      animationArray[entitieID].currentFrame =
          animationDataArray[animationArray[entitieID].animID].texture.first.size() - 1;
    }
    animManager.debugChangeFrame(entitieID, animationArray[entitieID].currentFrame);
  } else if (pad.getClicked().R1) {
    animationArray[entitieID].currentFrame++;
    if (animationArray[entitieID].currentFrame >=
        animationDataArray[animationArray[entitieID].animID].texture.first.size()) {
      animationArray[entitieID].currentFrame = 0;
    }
    animManager.debugChangeFrame(entitieID, animationArray[entitieID].currentFrame);
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
    if (menuUpOptionLeftJoy(pad)) {
      texPos->y--;
    } else if (menuDownOptionLeftJoy(pad)) {
      texPos->y++;
    }

    if (menuLeftOptionLeftJoy(pad)) {
      texPos->x--;
    } else if (menuRightOptionLeftJoy(pad)) {
      texPos->x++;
    }
  }

  if (playAnimation == true) {
    animationArray[entitieID].debugAnim(entitieID);
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
            animationDataArray[animationArray[entitieID].animID].texture.first.size());

    std::string textKey =
        "Key: " + std::to_string(animationArray[entitieID].currentFrame);

    engine->font.drawText(&myFont, textKey.c_str(), 30, 120, 16, black);
    engine->font.drawText(&myFont, position.c_str(), 30, 140, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, texPosition.c_str(), 30, 160, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, animSize.c_str(), 30, 180, 16, black);

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

    // if (menuCrossClickedOption(pad, isMainMenuAnimationActive)) {
    //   isMainMenuAnimationActive = false;
    //   spriteArray[entitieID].color.a = 128.0f;
    // } else if (menuCircleClickedOption(pad, isMainMenuAnimationActive)) {
    //   debugAnimation = false;
    //   startAnimationDebug = true;
    //   spriteArray[entitieID].color.a = 128.0f;
    // }

    if (padTimer > 0) {
      padTimer--;
    } else if (menuUpOptionLeftJoy(pad) || menuRightOptionLeftJoy(pad)) {
      spriteArray[entitieID].color.a = 128.0f;

      // fix this
      // std::map<int, Animation>::iterator it = animationArray.find(entitieID);

      // if (std::next(it)->first == animationArray.end()->first) {
      //   entitieID = animationArray.begin()->first;
      // } else {
      //   entitieID = std::next(it)->first;
      // }

    } else if (menuDownOptionLeftJoy(pad) || menuLeftOptionLeftJoy(pad)) {
      spriteArray[entitieID].color.a = 128.0f;
    // fix this
    //   std::map<int, Animation>::iterator it = animationArray.find(entitieID);

    //   if (entitieID == animationArray.begin()->first) {
    //     entitieID = animationArray.rbegin()->first;
    //   } else {
    //     entitieID = std::prev(it)->first;
    //   }
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
    engine->font.drawText(&myFont, textId.c_str(), 30, 80, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, name.c_str(), 30, 100, 16,
                          Tyra::Color(0, 0, 0, 128));

    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 420, 16, black);
  }
}
