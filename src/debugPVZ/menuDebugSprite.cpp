#include "debugPVZ/menuDebugSprite.hpp"
#include "font/font.hpp"
#include "components.hpp"

bool startSpriteDebug = true;
bool isMainMenuActive = true;
bool animationFound = false;
bool rotateFound = false;
bool rotateMode = false;
bool sizeMode = false;
bool hideSprite = false;

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
      spritesRotateRender[id] = &spritesRotate[id];
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

void getNextFrame(int& entitieID) {
  animationArray[entitieID].currentFrame++;
  if (animationArray[entitieID].currentFrame >=
      animationDataArray[animationArray[entitieID].animID].maxFrame) {
    animationArray[entitieID].currentFrame = 0;
  }
  animManager.debugChangeFrame(entitieID, animationArray[entitieID].currentFrame);
}

void getPrevFrame(int& entitieID) {
  if (animationArray[entitieID].currentFrame > 0) {
    animationArray[entitieID].currentFrame--;
  } else {
    animationArray[entitieID].currentFrame =
        animationDataArray[animationArray[entitieID].animID].maxFrame - 1;
  }
  animManager.debugChangeFrame(entitieID, animationArray[entitieID].currentFrame);
}

void subMenuSprite(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  if (animationFound == true && animationDataArray[animationArray[entitieID].animID].position.count(
          animationArray[entitieID].currentFrame) == 1) {
    texPos = &animationDataArray[animationArray[entitieID].animID]
                 .position[animationArray[entitieID].currentFrame];
  } else if (texPos == NULL) {
    texPos = new Vec2(0.0f, 0.0f);
    printf("texpos created: %p\n", texPos);
  }

  if (rotateFound == true && animationDataArray[animationArray[entitieID].animID].angle.count(
          animationArray[entitieID].currentFrame) == 1) {
    d_angle = &animationDataArray[animationArray[entitieID].animID]
                 .angle[animationArray[entitieID].currentFrame];
    // printf("angle from frame %d, angle:%f\n",animationArray[entitieID].currentFrame,*d_angle);
  } else if (rotateFound == true && d_angle == NULL) {
    d_angle = new float(0.0f);
    printf("angle created: %p\n", texPos);
  }

  if (animationDataArray[animationArray[entitieID].animID].scale.count(
          animationArray[entitieID].currentFrame) == 1) {
    d_scale = &animationDataArray[animationArray[entitieID].animID]
                 .scale[animationArray[entitieID].currentFrame];
    d_hasScale = true;
    // printf("size from frame %d, size:%f,%f\n",animationArray[entitieID].currentFrame,*d_size->x,*d_size->y);
  } else if (d_scale == NULL) {
    d_scale = new float(1);
    d_hasScale = false;
    printf("size created: %p\n", texPos);
  }

  if (pad.getClicked().Circle) {
    isMainMenuActive = true;
    hideText = false;
    playAnimation = false;
    rotateMode = false;
    sizeMode = false;
    hideSprite = false;
    activateRender();
    if (animationFound == false) {
      posArray[entitieID].y -= texPos->y;
      posArray[entitieID].x -= texPos->x;
      delete texPos;
    }
    if (rotateFound == false) {
      delete d_angle; // maybe this give me problems in the future
    }
    if(d_hasScale == false){
      delete d_scale; // maybe this give me problems in the future
    }
    texPos = NULL;
    d_angle = NULL;
    d_scale = NULL;
    animationFound = false;
    rotateFound = false;
  } else if (pad.getClicked().Square) {
    hideText = !hideText;
  } else if (pad.getClicked().L3) {
    sizeMode = !sizeMode;
    if (rotateMode == true) {
      rotateMode = false;
    }
  } else if (pad.getClicked().R3) {
    hideSprite = !hideSprite;
    if (hideSprite == true) {
      if (rotateFound == true) {
        spritesRotateRender.erase(entitieID);
        debugStopRenderRotateSprites.push_back(entitieID);
      } else {
        spritesNormalRender.erase(entitieID);
        debugStopRenderNormalSprites.push_back(entitieID);
      }
    } else {
      activateRender();
    }
  } else if (pad.getClicked().Triangle && rotateFound == true) {
    rotateMode = !rotateMode;
    if (sizeMode == true) {
      sizeMode = false;
    }
  } else if (animationFound == true) {
    if (pad.getClicked().L1) {
      getPrevFrame(entitieID);
    } else if (pad.getClicked().R1) {
      getNextFrame(entitieID);
    } else if (pad.getClicked().Cross) {
      playAnimation = !playAnimation;
    }
  }

  if (padTimer > 0) {
    padTimer--;
  } else {
    if (menuUpOptionLeftJoy(pad)) {
      speedDebugOptions();
      if (rotateMode == false && sizeMode == false) {
        posArray[entitieID].y -= padSpeed;
      } else if (sizeMode == false) {
        *d_angle += padSpeed;
        angles[entitieID] = *d_angle;
      } else {
        debugSpritesType[entitieID]->size.y -= padSpeed;
      }

    } else if (menuDownOptionLeftJoy(pad)) {
      speedDebugOptions();

      if (rotateMode == false && sizeMode == false) {
        posArray[entitieID].y += padSpeed;
      } else if (sizeMode == false) {
        *d_angle -= padSpeed;
        angles[entitieID] = *d_angle;
      } else {
        debugSpritesType[entitieID]->size.y += padSpeed;
      }
    }

    if (menuLeftOptionLeftJoy(pad)) {
      speedDebugOptions();

      if (rotateMode == false && sizeMode == false) {
        posArray[entitieID].x -= padSpeed;
      } else if (sizeMode == false) {
        *d_angle -= padSpeed;
        angles[entitieID] = *d_angle;
      } else {
        debugSpritesType[entitieID]->size.x -= padSpeed;
      }
    } else if (menuRightOptionLeftJoy(pad)) {
      speedDebugOptions();

      if (rotateMode == false && sizeMode == false) {
        posArray[entitieID].x += padSpeed;
      } else if (sizeMode == false) {
        *d_angle += padSpeed;
        angles[entitieID] = *d_angle;
      } else {
        debugSpritesType[entitieID]->size.x += padSpeed;
      }
    }

    if (menuUpOptionLeftJoy(pad) == false &&
        menuDownOptionLeftJoy(pad) == false &&
        menuLeftOptionLeftJoy(pad) == false &&
        menuRightOptionLeftJoy(pad) == false) {
      if (menuUpOptionRightJoy(pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[entitieID].y -= padSpeed;
        }
        texPos->y -= padSpeed;
      } else if (menuDownOptionRightJoy(pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[entitieID].y += padSpeed;
        }
        texPos->y += padSpeed;
      }

      if (menuLeftOptionRightJoy(pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[entitieID].x -= padSpeed;
        }
        texPos->x -= padSpeed;
      } else if (menuRightOptionRightJoy(pad)) {
        speedDebugOptions();
        if (animationFound == false) {
          posArray[entitieID].x += padSpeed;
        }
        texPos->x += padSpeed;
      }

      if (menuUpOptionRightJoy(pad) == false &&
          menuDownOptionRightJoy(pad) == false &&
          menuLeftOptionRightJoy(pad) == false &&
          menuRightOptionRightJoy(pad) == false) {
        if (pad.getPressed().L2 && sizeMode == true) {
          speedDebugOptions();
          padTimer = 10;
          debugSpritesType[entitieID]->size -= padSpeed;
        } else if (pad.getPressed().R2 && sizeMode == true) {
          speedDebugOptions();
          padTimer = 10;
          debugSpritesType[entitieID]->size += padSpeed;
        } else {
          padPressTimer = 0;
          padSpeed = 1;
        }
      }
    }
  }

  if(texPos != NULL) {
    texPosArray[entitieID] = *texPos;
  }

  if (animationFound == true && playAnimation == true) {
    animManager.debugAnim(entitieID);
  }

  if (hideText == false && isMainMenuActive == false) {
    if (rotateFound == true) {
      engine->font.drawText(&myFont, "PRESS A FOR ROTATION MODE", 30, 300, 16,
                            black);
    }
    if (rotateMode == false && sizeMode == false) {
      std::string position =
          "Position: " + std::to_string(posArray[entitieID].x) + ", " +
          std::to_string(posArray[entitieID].y);

      engine->font.drawText(&myFont, position, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
    } else if (sizeMode == false) {
      std::string angle = "Angle: " + std::to_string(*d_angle);
      engine->font.drawText(&myFont, angle, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
    } else {
      std::string size =
          "Size: " + std::to_string(debugSpritesType[entitieID]->size.x) +
          ", " + std::to_string(debugSpritesType[entitieID]->size.y);
      engine->font.drawText(&myFont, size, 30, 140, 16,
                            Tyra::Color(0, 0, 0, 128));
    }

    std::string texPosition = "Texture Position: " + std::to_string(texPos->x) +
                              ", " + std::to_string(texPos->y);
    engine->font.drawText(&myFont, texPosition, 30, 160, 16,
                          Tyra::Color(0, 0, 0, 128));

    // animation
    if (animationFound == true) {
      std::string textKey =
          "Key: " + std::to_string(animationArray[entitieID].currentFrame);

      std::string animSize =
          "Total textures: " +
          std::to_string(
              animationDataArray[animationArray[entitieID].animID].texture.size());

      engine->font.drawText(&myFont, textKey, 30, 120, 16, black);

      engine->font.drawText(&myFont, animSize, 30, 180, 16, black);
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

void mainMenuSprite(Tyra::Pad& pad, int& entitieID) {
  debugSpritesType[entitieID]->color.a += colorSprite;

  if (debugSpritesType[entitieID]->color.a <= 30.0f) {
    colorSprite = 2;
  } else if (debugSpritesType[entitieID]->color.a >= 128.0f) {
    colorSprite = -2;
  }

  if (menuCrossClickedOption(pad, true)) {
    isMainMenuActive = false;
    debugSpritesType[entitieID]->color.a = debugAlphaColor;
    if (animationArray.count(entitieID) == 1) {
      animationFound = true;
    }
    if (spritesRotate.count(entitieID) == 1) {
      rotateFound = true;
    }
  } else if (menuCircleClickedOption(pad, true)) {
    debugSprite = false;
    animationFound = false;
    rotateFound = false;
    startSpriteDebug = true;
    debugSpritesType[entitieID]->color.a = debugAlphaColor;
  }

  if (padTimer > 0) {
    padTimer--;
  } else if (menuUpOptionLeftJoy(pad) || menuRightOptionLeftJoy(pad)) {
    getNextSprite(entitieID);
  } else if (menuDownOptionLeftJoy(pad) || menuLeftOptionLeftJoy(pad)) {
    getPrevSprite(entitieID);
  }
  engine->font.drawText(&myFont, "PRESS X FOR SELECT THE TEXTURE", 30, 400, 16,
                        black);
}

void menuDebugSprite(Tyra::Pad& pad, Tyra::Font& font, int& entitieID) {
  if (isMainMenuActive == true) {
    mainMenuSprite(pad, entitieID);
  } else {
    subMenuSprite(pad, font, entitieID);
  }

  if (hideText == false) {
    std::string textId = "Entitie ID: " + std::to_string(entitieID);
    std::string name =
        "Name Texture: " + renderer->getTextureRepository()
                               .getBySpriteId(debugSpritesType[entitieID]->id)
                               ->name;
    engine->font.drawText(&myFont, textId, 30, 80, 16,
                          Tyra::Color(0, 0, 0, 128));
    engine->font.drawText(&myFont, name, 30, 100, 16,
                          Tyra::Color(0, 0, 0, 128));

    engine->font.drawText(&myFont, "PRESS O FOR GO BACK", 30, 420, 16, black);
  }
}
