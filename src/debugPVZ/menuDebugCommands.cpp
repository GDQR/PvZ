#include "debugPVZ/menuDebugCommands.hpp"

int padTimer = 0;
bool hideText = false;
bool playAnimation = false;
float colorSprite = -2;

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