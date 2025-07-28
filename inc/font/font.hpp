#pragma once
#include <string>
#include <tyra>

// this is usefull for the future, DONT DELETE
// class Font {
//  public:
//   Tyra::Sprite textFont[1][3];
// };

struct RectListFont {
  unsigned int val[4];
};

struct OffsetListFont {
  int val[2];
};

struct FontData{
  int charlist[160];
  int widthlist[160];
  RectListFont rectlist[160];
  OffsetListFont offsetlist[160];
  int spaceWidth;
  int spaceHeight;
  int textureID;
};

struct TextData{
  std::string text;
  float x;
  float y;
  int fontID;
};

void loadFonts();
int CreateTextData(std::string text, float x, float y, int fontID);
void drawText(FontData* font, std::string text, float x, float y);

extern std::vector<TextData> textArray;
extern std::vector<FontData> fonts;
extern int FontPicoID;
extern int FontBrianneTod12ID;
extern int HouseofTerror16ID;
extern Tyra::FontData myFont;
extern Tyra::Color black;
extern Tyra::Color orange;