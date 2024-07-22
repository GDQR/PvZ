#include "debugPVZ/menuDebugCommands.hpp"
#include "components.hpp"

int padTimer = 0;
int padPressTimer = 0;
int padSpeed = 1;
bool hideText = false;
bool playAnimation = false;
float colorSprite = -2;
bool crossOption = true;

bool menuUpOptionLeftJoy(Tyra::Pad& pad) {
  if (pad.getPressed().DpadUp || leftJoy->v <= 100) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuDownOptionLeftJoy(Tyra::Pad& pad) {
  if (pad.getPressed().DpadDown || leftJoy->v >= 200) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuLeftOptionLeftJoy(Tyra::Pad& pad) {
  if (pad.getPressed().DpadLeft || leftJoy->h <= 100) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuRightOptionLeftJoy(Tyra::Pad& pad) {
  if (pad.getPressed().DpadRight || leftJoy->h >= 200) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuUpOptionRightJoy(Tyra::Pad& pad) {
  if (pad.getRightJoyPad().v <= 100) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuDownOptionRightJoy(Tyra::Pad& pad) {
  if (pad.getRightJoyPad().v >= 200) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuLeftOptionRightJoy(Tyra::Pad& pad) {
  if (pad.getRightJoyPad().h <= 100) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuRightOptionRightJoy(Tyra::Pad& pad) {
  if (pad.getRightJoyPad().h >= 200) {
    padTimer = 10;
    return true;
  }
  return false;
}

bool menuCrossClickedOption() {
  if (engine->pad.getClicked().Cross && crossOption == true) {
    crossOption = false;
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