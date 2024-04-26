#include "font/font.hpp"
#include "renderSprite/textures.hpp"
#include "components.hpp"
#include <sstream>
#include <fstream>
#include <codecvt>
#include <iostream>
Font font;
Tyra::FontData myFont;
Tyra::Color black(0, 0, 0, 128);
Tyra::Color orange(255.0f, 128, 0, 128);
// this is usefull for the future, DONT DELETE

// std::vector <int> BriannedTod12;
std::wstring BriannedTod12;

// const int BriannedTod12[192]{
//    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
//    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
//    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
//    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
//    '8', '9', '~', '`',
//    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[',
//    '{',
//    ']', '}', ';', ':','\'', '"', ',', '<', '.', '>', '/', '?', '¡', '¢', '£',
//    '¥', '§', '©', '®', '¿', 'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç', 'È', 'É',
//    'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', 'Ø', 'Ù',
//    'Ú', 'Û', 'Ü', 'Ý', 'ß', 'à', 'á', 'â', 'ã', 'ä', 'å', 'æ', 'ç', 'è', 'é',
//    'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ð', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ö', 'ø', 'ù',
//    'ú', 'û', 'ü', 'ý', 'ÿ'};

const int BriannedTod12Width[192]{
    9, 10, 10, 8, 9, 8,  11, 9,  4,  9,  10, 9,  10, 8, 9, 8, 9,  10, 8,  10,
    9, 9,  11, 8, 7, 8,  7,  7,  6,  7,  6,  8,  7,  7, 4, 6, 8,  3,  9,  8,
    7, 6,  7,  7, 6, 7,  7,  6,  8,  6,  7,  7,  7,  3, 8, 8, 7,  8,  8,  8,
    8, 8,  8,  3, 4, 10, 11, 9,  11, 5,  7,  8,  6,  6, 7, 8, 8,  8,  5,  8,
    5, 8,  4,  4, 3, 5,  4,  8,  4,  8,  4,  6,  3,  6, 9, 7, 8,  9,  9,  6,
    9, 9,  9,  9, 9, 9,  12, 10, 10, 10, 10, 10, 4,  4, 4, 3, 8,  8,  10, 9,
    9, 10, 10, 9, 9, 9,  9,  9,  7,  10, 8,  8,  8,  8, 8, 8, 10, 9,  6,  6,
    6, 6,  4,  4, 4, 4,  7,  8,  7,  7,  7,  7,  7,  7, 7, 7, 6,  7,  7,  7};

void loadFonts() {
  std::ifstream fs("FONTS/BRIANNETOD/12/BrianneTod12.txt");
  // std::wfstream fs("FONTS/BRIANNETOD/12/BrianneTod12.txt");
  // char letter;
  std::wstring letter;
  bool save = false;
  int i = 0;

  int lines = 1;

  while (lines != 2) {
    fs.ignore(20, '\n');
    lines++;
  }

  while (lines != 11) {
    letter[0] = fs.get();

    if (letter[0] == '\n') {
      lines++;
    }
    if (letter[0] == '\'') {
      save = !save;
    }

    if (save == true && letter[0] != '\'') {
      BriannedTod12.push_back(letter[0]);
      printf("i:%d. %d %c\n", i, BriannedTod12[BriannedTod12.size() - 1],
             BriannedTod12[BriannedTod12.size() - 1]);
      // std::cout << BriannedTod12[BriannedTod12.size()-1] << std::endl;
      i++;
    }
  }

  loadSprite(&font.textFont[0][0], Tyra::MODE_REPEAT, Vec2(0, 0), Vec2(31, 16));
  loadSprite(&font.textFont[0][1], Tyra::MODE_REPEAT, Vec2(0, 0), Vec2(31, 16));
  loadSprite(&font.textFont[0][2], Tyra::MODE_REPEAT, Vec2(0, 0), Vec2(31, 16));
  loadTexture(&font.textFont[0][0],
              "FONTS/BRIANNETOD/12/_BrianneTod12part1.png");
  loadTexture(&font.textFont[0][1],
              "FONTS/BRIANNETOD/12/_BrianneTod12part2.png");
  loadTexture(&font.textFont[0][2],
              "FONTS/BRIANNETOD/12/_BrianneTod12part3.png");
}

int getLetterPos(int letter) {
  for (unsigned int i = 0; i < 192; i++) {
    if (letter == BriannedTod12[i]) {
      return i;
    }
  }
  return 32;
}

void drawText(std::string text, float x, float y) {
  unsigned int maxLetters = text.size();
  int ascii;
  int part;
  for (unsigned int i = 0; i < maxLetters; i++) {
    printf("text: %c\n", (unsigned char)text[i]);
    ascii = getLetterPos(text[i]);
    if (text[i] < BriannedTod12[52] /*0*/) {
      part = 0;
    } else if (text[i] <= BriannedTod12[145] /*'Ï'*/) {
      part = 1;
    } else {
      part = 2;
    }
    printf("ascii: %d\n", ascii);
    printf("0: %d\n", '0');
    printf("BriannedTod12['0']: %d\n", BriannedTod12['0']);
    printf("part: %d\n", part);
    font.textFont[0][part].size.x = BriannedTod12Width[ascii];
    // font.textFont[0].offset.x =
    font.textFont[0][part].position = Tyra::Vec2(x, y);
    renderer->renderer2D.render(font.textFont[0][part]);
  }
}