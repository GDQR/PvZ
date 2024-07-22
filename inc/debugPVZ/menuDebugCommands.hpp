#pragma once
#include <tyra>

extern const Tyra::PadJoy* leftJoy;
extern int padTimer;
extern int padPressTimer;
extern int padSpeed;
extern bool hideText;
extern bool playAnimation;
extern float colorSprite;
extern bool crossOption;

bool menuUpOptionLeftJoy(Tyra::Pad& pad);
bool menuDownOptionLeftJoy(Tyra::Pad& pad);
bool menuLeftOptionLeftJoy(Tyra::Pad& pad);
bool menuRightOptionLeftJoy(Tyra::Pad& pad);
bool menuUpOptionRightJoy(Tyra::Pad& pad);
bool menuDownOptionRightJoy(Tyra::Pad& pad);
bool menuLeftOptionRightJoy(Tyra::Pad& pad);
bool menuRightOptionRightJoy(Tyra::Pad& pad);
bool menuCrossClickedOption();
bool menuCircleClickedOption(Tyra::Pad& pad, const bool isActive);