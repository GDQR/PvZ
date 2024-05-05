#pragma once
#include <tyra>

extern const Tyra::PadJoy* leftJoy;
extern int padTimer;
extern int padPressTimer;
extern int padSpeed;
extern bool hideText;
extern bool playAnimation;
extern float colorSprite;

bool menuUpOption(Tyra::Pad& pad);
bool menuDownOption(Tyra::Pad& pad);
bool menuLeftOption(Tyra::Pad& pad);
bool menuRightOption(Tyra::Pad& pad);
bool menuCrossClickedOption(Tyra::Pad& pad, const bool isActive);
bool menuCircleClickedOption(Tyra::Pad& pad, const bool isActive);