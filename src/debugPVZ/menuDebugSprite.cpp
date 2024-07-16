#include "debugPVZ/menuDebugSprite.hpp"
#include "components.hpp"
#include "font/font.hpp"
#include "systems.hpp"

bool startSpriteDebug = true;
bool isMainMenuActive = true;
bool animationFound = false;
bool rotateFound = false;
bool rotateMode = false;
bool sizeMode = false;
bool hideSprite = false;
DebugSpriteMode debugSpriteMode;

void speedDebugOptions() {
  if (padPressTimer < 20) {
    padPressTimer++;

    if (padPressTimer == 10) {
      padSpeed = 2.0f;
    } else if (padPressTimer == 20) {
      padSpeed = 3.0f;
    }
  }
}

void activateRender() {
  int id;
  if (rotateFound == true) {
    for (unsigned int i = 0; i < debugStopRenderRotateSprites.size(); i++) {
      id = debugStopRenderRotateSprites.front();
      spritesRotateRender[id] = &rotationSprite[id];
      debugStopRenderRotateSprites.pop_back();
    }
  } else {
    for (unsigned int i = 0; i < debugStopRenderNormalSprites.size(); i++) {
      id = debugStopRenderNormalSprites.front();
      spritesNormalRender[id] = &spriteArray[id];
      debugStopRenderNormalSprites.pop_back();
    }
  }
}

void getNextFrame(int& entitieID) {
  animationArray[entitieID].currentFrame++;
  if (animationArray[entitieID].currentFrame >=
      animationDataArray[animationArray[entitieID].animID].maxFrame) {
    animationArray[entitieID].currentFrame = 0;
  }
  animManager.debugChangeFrame(entitieID,
                               animationArray[entitieID].currentFrame);
}

void getPrevFrame(int& entitieID) {
  if (animationArray[entitieID].currentFrame > 0) {
    animationArray[entitieID].currentFrame--;
  } else {
    animationArray[entitieID].currentFrame =
        animationDataArray[animationArray[entitieID].animID].maxFrame - 1;
  }
  animManager.debugChangeFrame(entitieID,
                               animationArray[entitieID].currentFrame);
}
void getNextSprite(int& entitieID) {
  debugSpritesType[entitieID]->color.a = debugAlphaColor;

  std::map<int, Sprite*>::iterator it = debugSpritesType.find(entitieID);
  if (std::next(it)->first == debugSpritesType.end()->first) {
    entitieID = debugSpritesType.begin()->first;
  } else {
    entitieID = std::next(it)->first;
  }

  debugAlphaColor = debugSpritesType[entitieID]->color.a;
}

void getPrevSprite(int& entitieID) {
  debugSpritesType[entitieID]->color.a = debugAlphaColor;

  std::map<int, Sprite*>::iterator it = debugSpritesType.find(entitieID);
  if (entitieID == debugSpritesType.begin()->first) {
    entitieID = debugSpritesType.rbegin()->first;
  } else {
    entitieID = std::prev(it)->first;
  }

  debugAlphaColor = debugSpritesType[entitieID]->color.a;
}

void DebugSpriteMode::menu() {
  if (isMainMenuActive == true) {
    firstMenu();
  } else {
    secondMenu();
  }
}

void DebugSpriteMode::drawMenu() {
  if (isMainMenuActive == true) {
    drawFirstMenu();
  } else {
    drawSecondMenu();
  }

  if (hideText == false) {
    std::string textId = "Entitie ID: " + std::to_string(debugEntityId);

    engine->font.drawText(&myFont, textId, 30, 80, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, name, 30, 100, 16,
                          Tyra::Color(0, 0, 0, 128));

    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 420, 16,
    black);
  }
}

void DebugSpriteMode::firstMenu() {
  debugSpritesType[debugEntityId]->color.a += colorSprite;

  if (debugSpritesType[debugEntityId]->color.a <= 30.0f) {
    colorSprite = 2;
  } else if (debugSpritesType[debugEntityId]->color.a >= 128.0f) {
    colorSprite = -2;
  }

  if (engine->pad.getClicked().Cross) {
    isMainMenuActive = false;
    debugSpritesType[debugEntityId]->color.a = debugAlphaColor;
    if (animationArray.count(debugEntityId) == 1) {
      animationFound = true;
    }
    if (rotationSprite.count(debugEntityId) == 1) {
      rotateFound = true;
    }
  } else if (engine->pad.getClicked().Circle) {
    debugSprite = false;
    animationFound = false;
    rotateFound = false;
    startSpriteDebug = true;
    debugSpritesType[debugEntityId]->color.a = debugAlphaColor;
  }

  if (padTimer > 0) {
    padTimer--;
  } else if (menuUpOptionLeftJoy(engine->pad) ||
             menuRightOptionLeftJoy(engine->pad)) {
    getNextSprite(debugEntityId);
  } else if (menuDownOptionLeftJoy(engine->pad) ||
             menuLeftOptionLeftJoy(engine->pad)) {
    getPrevSprite(debugEntityId);
  }
}
void DebugSpriteMode::drawFirstMenu() {
  if (renderer->getTextureRepository().getBySpriteId(
          debugSpritesType[debugEntityId]->id) != nullptr) {
    name = "Name Texture: " +
           renderer->getTextureRepository()
               .getBySpriteId(debugSpritesType[debugEntityId]->id)
               ->name;
  } else {
    name = "Name Texture: frame without texture";
  }

  engine->font.drawText(&myFont, "PRESS X FOR SELECT THE TEXTURE", 30, 400, 16,
                        black);
}

void DebugSpriteMode::secondMenu(){
 // TODO:FIX texPos
  if (animationFound == true &&
      animationDataArray[animationArray[debugEntityId].animID].x.count(
          animationArray[debugEntityId].currentFrame) == 1) {
    texPos->x = animationDataArray[animationArray[debugEntityId].animID]
                    .x[animationArray[debugEntityId].currentFrame];
  } else if (texPos == NULL) {
    texPos = new Vec2(0.0f, 0.0f);
    printf("texpos created: %p\n", texPos);
  }

  // TODO: fix this
  // if (rotateFound == true &&
  //     animationDataArray[animationArray[debugEntityId].animID].angle.count(
  //         animationArray[debugEntityId].currentFrame) == 1) {
  //   d_angle = &animationDataArray[animationArray[debugEntityId].animID]
  //                  .angle[animationArray[debugEntityId].currentFrame];
  //   // printf("angle from frame %d,
  //   // angle:%f\n",animationArray[debugEntityId].currentFrame,*d_angle);
  // } else if (rotateFound == true && d_angle == NULL) {
  //   d_angle = new Vec2(0.0f,0.0f);
  //   printf("angle created: %p\n", texPos);
  // }

  if (engine->pad.getClicked().Circle) {
    isMainMenuActive = true;
    hideText = false;
    playAnimation = false;
    rotateMode = false;
    sizeMode = false;
    hideSprite = false;
    activateRender();
    if (animationFound == false) {
      posArray[debugEntityId] -= *texPos;
      delete texPos;
    }
    if (rotateFound == false) {
      delete d_angle;  // maybe this give me problems in the future
    }
    texPos = NULL;
    d_angle = NULL;
    animationFound = false;
    rotateFound = false;
  } else if (engine->pad.getClicked().Square) {
    hideText = !hideText;
  } else if (engine->pad.getClicked().L3) {
    sizeMode = !sizeMode;
    if (rotateMode == true) {
      rotateMode = false;
    }
  } else if (engine->pad.getClicked().R3) {
    hideSprite = !hideSprite;
    if (hideSprite == true) {
      if (rotateFound == true) {
        spritesRotateRender.erase(debugEntityId);
        debugStopRenderRotateSprites.push_back(debugEntityId);
      } else {
        spritesNormalRender.erase(debugEntityId);
        debugStopRenderNormalSprites.push_back(debugEntityId);
      }
    } else {
      activateRender();
    }
  } else if (engine->pad.getClicked().Triangle && rotateFound == true) {
    rotateMode = !rotateMode;
    if (sizeMode == true) {
      sizeMode = false;
    }
  } else if (animationFound == true) {
    if (engine->pad.getClicked().L1) {
      getPrevFrame(debugEntityId);
    } else if (engine->pad.getClicked().R1) {
      getNextFrame(debugEntityId);
    } else if (engine->pad.getClicked().Cross) {
      playAnimation = !playAnimation;
    }
  }

  if (padTimer > 0) {
    padTimer--;
  } else {
    if (menuUpOptionLeftJoy(engine->pad)) {
      speedDebugOptions();
      if (rotateMode == false && sizeMode == false) {
        posArray[debugEntityId].y -= padSpeed;
      } else if (sizeMode == false) {
        d_angle->y += padSpeed;
        rotationSprite[debugEntityId].angle = *d_angle;
      } else {
        originalSize[debugEntityId].y -= padSpeed;
        if (animationDataArray[animationArray[debugEntityId].animID].texture.count(
                animationArray[debugEntityId].currentFrame) == 0) {
          printf("no hay textura\n");
        }
        Tyra::Texture* texture =
            engine->renderer.getTextureRepository().getBySpriteId(
                debugSpritesType[debugEntityId]->id);
        scaleTexture[debugEntityId].y =
            originalSize[debugEntityId].y / texture->getHeight();
      }

    } else if (menuDownOptionLeftJoy(engine->pad)) {
      speedDebugOptions();

      if (rotateMode == false && sizeMode == false) {
        posArray[debugEntityId].y += padSpeed;
      } else if (sizeMode == false) {
        d_angle->y -= padSpeed;
        rotationSprite[debugEntityId].angle = *d_angle;
      } else {
        originalSize[debugEntityId].y += padSpeed;
        if (animationDataArray[animationArray[debugEntityId].animID].texture.count(
                animationArray[debugEntityId].currentFrame) == 0) {
          printf("no hay textura\n");
        }
        Tyra::Texture* texture =
            engine->renderer.getTextureRepository().getBySpriteId(
                debugSpritesType[debugEntityId]->id);

        scaleTexture[debugEntityId].y =
            originalSize[debugEntityId].y / texture->getHeight();
        // TODO: FIX this
        // debugSpritesType[debugEntityId]->size = originalSize[debugEntityId] *
        // animationDataArray[animationArray[debugEntityId].animID]
        //       .scale[animationArray[debugEntityId].currentFrame];
      }
    }

    if (menuLeftOptionLeftJoy(engine->pad)) {
      speedDebugOptions();

      if (rotateMode == false && sizeMode == false) {
        posArray[debugEntityId].x -= padSpeed;
      } else if (sizeMode == false) {
        d_angle->x -= padSpeed;
        rotationSprite[debugEntityId].angle = *d_angle;
      } else {
        originalSize[debugEntityId].x -= padSpeed;
        Tyra::Texture* texture =
            engine->renderer.getTextureRepository().getBySpriteId(
                debugSpritesType[debugEntityId]->id);
        scaleTexture[debugEntityId].x =
            originalSize[debugEntityId].x / texture->getWidth();
        // TODO: FIX this
        // debugSpritesType[debugEntityId]->size = originalSize[debugEntityId] *
        // animationDataArray[animationArray[debugEntityId].animID]
        //       .scale[animationArray[debugEntityId].currentFrame];
      }
    } else if (menuRightOptionLeftJoy(engine->pad)) {
      speedDebugOptions();

      if (rotateMode == false && sizeMode == false) {
        posArray[debugEntityId].x += padSpeed;
      } else if (sizeMode == false) {
        d_angle->x += padSpeed;
        rotationSprite[debugEntityId].angle = *d_angle;
      } else {
        originalSize[debugEntityId].x += padSpeed;
        Tyra::Texture* texture =
            engine->renderer.getTextureRepository().getBySpriteId(
                debugSpritesType[debugEntityId]->id);
        scaleTexture[debugEntityId].x =
            originalSize[debugEntityId].x / texture->getWidth();
        // TODO: FIX this
        // debugSpritesType[debugEntityId]->size = originalSize[debugEntityId] *
        // animationDataArray[animationArray[debugEntityId].animID]
        //       .scale[animationArray[debugEntityId].currentFrame];
      }
    }

    if (menuUpOptionLeftJoy(engine->pad) == false &&
        menuDownOptionLeftJoy(engine->pad) == false &&
        menuLeftOptionLeftJoy(engine->pad) == false &&
        menuRightOptionLeftJoy(engine->pad) == false) {
      if (menuUpOptionRightJoy(engine->pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[debugEntityId].y -= padSpeed;
        }
        texPos->y -= padSpeed;
        texPosArray[debugEntityId].y--;
      } else if (menuDownOptionRightJoy(engine->pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[debugEntityId].y += padSpeed;
        }
        texPos->y += padSpeed;
        texPosArray[debugEntityId].y++;
      }

      if (menuLeftOptionRightJoy(engine->pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[debugEntityId].x -= padSpeed;
        }
        texPos->x -= padSpeed;
        texPosArray[debugEntityId].x--;
      } else if (menuRightOptionRightJoy(engine->pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[debugEntityId].x += padSpeed;
        }
        texPos->x += padSpeed;
        texPosArray[debugEntityId].x++;
      }

      if (menuUpOptionRightJoy(engine->pad) == false &&
          menuDownOptionRightJoy(engine->pad) == false &&
          menuLeftOptionRightJoy(engine->pad) == false &&
          menuRightOptionRightJoy(engine->pad) == false) {
        if (engine->pad.getPressed().L2 && sizeMode == true) {
          speedDebugOptions();
          padTimer = 10;
          originalSize[debugEntityId] -= padSpeed;
          Tyra::Texture* texture =
              engine->renderer.getTextureRepository().getBySpriteId(
                  debugSpritesType[debugEntityId]->id);
          scaleTexture[debugEntityId] =
              Vec2(originalSize[debugEntityId].x / texture->getWidth(),
                   originalSize[debugEntityId].y / texture->getHeight());
          // TODO: FIX this
          // debugSpritesType[debugEntityId]->size = originalSize[debugEntityId] *
          // animationDataArray[animationArray[debugEntityId].animID]
          //     .scale[animationArray[debugEntityId].currentFrame];
        } else if (engine->pad.getPressed().R2 && sizeMode == true) {
          speedDebugOptions();
          padTimer = 10;
          originalSize[debugEntityId] += padSpeed;
          Tyra::Texture* texture =
              engine->renderer.getTextureRepository().getBySpriteId(
                  debugSpritesType[debugEntityId]->id);
          scaleTexture[debugEntityId] =
              Vec2(originalSize[debugEntityId].x / texture->getWidth(),
                   originalSize[debugEntityId].y / texture->getHeight());
          // TODO: FIX this
          // debugSpritesType[debugEntityId]->size = originalSize[debugEntityId] *
          // animationDataArray[animationArray[debugEntityId].animID]
          //     .scale[animationArray[debugEntityId].currentFrame];
        } else {
          padPressTimer = 0;
          padSpeed = 1;
        }
      }
    }
  }
}
void DebugSpriteMode::drawSecondMenu(){
  if (animationFound == true && playAnimation == true) {
    animManager.debugAnim(debugEntityId);
  }

  if (hideText == false && isMainMenuActive == false) {
    if (rotateFound == true) {
      engine->font.drawText(&myFont, "PRESS A FOR ROTATION MODE", 30, 300, 16,
                            black);
    }
    if (rotateMode == false && sizeMode == false) {
      std::string position =
          "Position: " + std::to_string(posArray[debugEntityId].x) + ", " +
          std::to_string(posArray[debugEntityId].y);

      engine->font.drawText(&myFont, position, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
    } else if (sizeMode == false) {
      std::string angle = "Angle: " + std::to_string(d_angle->x) + "," +
                          std::to_string(d_angle->y);
      engine->font.drawText(&myFont, angle, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
    } else {
      std::string size = "Size: " + std::to_string(originalSize[debugEntityId].x) +
                         ", " + std::to_string(originalSize[debugEntityId].y);
      engine->font.drawText(&myFont, size, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
    }

    std::string texPosition = "Texture Position: " + std::to_string(texPos->x) +
                              ", " + std::to_string(texPos->y);
    engine->font.drawText(&myFont, texPosition, 30, 160, 16,
                          Tyra::Color(0, 0, 0, 128));

    std::string textScale =
        "Scale: " + std::to_string(debugSpritesType[debugEntityId]->scale);
    engine->font.drawText(&myFont, textScale, 30, 180, 16,
                          Tyra::Color(0, 0, 0, 128));

    // animation
    if (animationFound == true) {
      std::string textKey =
          "Key: " + std::to_string(animationArray[debugEntityId].currentFrame);

      std::string animSize =
          "Total textures: " +
          std::to_string(animationDataArray[animationArray[debugEntityId].animID]
                             .texture.size());

      engine->font.drawText(&myFont, textKey, 30, 120, 16, black);

      engine->font.drawText(&myFont, animSize, 30, 200, 16, black);
      engine->font.drawText(&myFont, "PRESS X FOR PLAY/STOP ANIMATION", 30, 280,
                            16, black);
      // general y anim
      engine->font.drawText(&myFont, "PRESS L1 FOR Prev key", 30, 320, 16,
                            black);
      engine->font.drawText(&myFont, "PRESS R1 FOR Next Key", 30, 340, 16,
                            black);
    }

    // general
    engine->font.drawText(&myFont, "PRESS R3 FOR HIDE SPRITE", 30, 360, 16,
                          black);
    engine->font.drawText(&myFont, "PRESS L3 FOR SIZE MODE", 30, 380, 16,
                          black);
    engine->font.drawText(&myFont, "PRESS [ ] FOR HIDE/SHOW TEXT", 30, 400, 16,
                          black);
  }
}
