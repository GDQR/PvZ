#pragma once
#include <tyra>
#include <string>
// this is usefull for the future, DONT DELETE
class Font {
 public:
  Tyra::Sprite textFont[1][3];
};

void loadFonts();
void drawText(std::string text, float x, float y);

extern Tyra::FontData myFont;
extern Tyra::Color black;
extern Tyra::Color orange;