#include "debugPVZ/debugMenuAnimation.hpp"
#include "components.hpp"

bool isMainMenuAnimationActive = true;
bool startAnimationDebug = true;
bool hideText = false;
bool playAnimation = false;
float colorSprite = -2;
int debugEntitieId;

int menuDebugAnimation(Tyra::Pad& pad, Tyra::Font& font) {
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
      startAnimationDebug = true;
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
