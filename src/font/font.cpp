#include "font/font.hpp"
#include "components.hpp"
#include "fontFiles.hpp"
#include "imageTools.hpp"
#include "renderSprite/textures.hpp"
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

// Font font;
int FontPicoID;
int FontBrianneTod12ID;
int HouseofTerror16ID;
Tyra::FontData myFont;
Tyra::Color black(0, 0, 0, 128);
Tyra::Color orange(255.0f, 128, 0, 128);
static Tyra::Sprite spriteFont;
// static Tyra::TextureAtlas textureAtlasFont;
std::vector<TextData> textArray;
std::vector<FontData> fonts;

struct Image {
  int width;
  int height;
  unsigned char* data;
};

// this is usefull for the future, DONT DELETE

// std::vector <int> BriannedTod12;
// std::wstring BriannedTod12;

// const int BriannedTod12[] {
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

// const int BriannedTod12Width[192]{
//     9, 10, 10, 8, 9, 8,  11, 9,  4,  9,  10, 9,  10, 8, 9, 8, 9,  10, 8,  10,
//     9, 9,  11, 8, 7, 8,  7,  7,  6,  7,  6,  8,  7,  7, 4, 6, 8,  3,  9,  8,
//     7, 6,  7,  7, 6, 7,  7,  6,  8,  6,  7,  7,  7,  3, 8, 8, 7,  8,  8,  8,
//     8, 8,  8,  3, 4, 10, 11, 9,  11, 5,  7,  8,  6,  6, 7, 8, 8,  8,  5,  8,
//     5, 8,  4,  4, 3, 5,  4,  8,  4,  8,  4,  6,  3,  6, 9, 7, 8,  9,  9,  6,
//     9, 9,  9,  9, 9, 9,  12, 10, 10, 10, 10, 10, 4,  4, 4, 3, 8,  8,  10, 9,
//     9, 10, 10, 9, 9, 9,  9,  9,  7,  10, 8,  8,  8,  8, 8, 8, 10, 9,  6,  6,
//     6, 6,  4,  4, 4, 4,  7,  8,  7,  7,  7,  7,  7,  7, 7, 7, 6,  7,  7,  7};

// static int charlist[160];
// static int widthlist[160];
// static RectListFont rectlist[160];
// static OffsetListFont offsetlist[160];
// static int spaceWidth;
// static int spaceHeight;

Image CopyTexture4Bits(unsigned char* dataSrc, int srcWidth, int srcHeight,
                       int x, int y, int width, int height) {
  Image image;
  image.width = width;
  image.height = height;
  image.data = static_cast<unsigned char*>(memalign(128, width * height/2));
  // printf("image: %d,%d,%d,%d\n",x,y,width,height);
  for (int i = 0; i < width * height/2; i++) {
    image.data[i] = 0;
  }

  int k = 0;
  int maxWidth = ceilf(((float)width/2));
  // printf("maxWidth: %d\n",maxWidth + (x/2));
  for (int i = y; i < height + y; i++) {
    for (int j = x/2; j < maxWidth + (x/2); j++) {
      // printf("pixel[%d]: %d=%d: %d\n",k,k,(i*(srcWidth/2))+j,dataSrc[(i * (srcWidth/2)) + j]);
      image.data[k] = dataSrc[(i * (srcWidth/2)) + j];
      k++;
    }
  }

  return image;
}


void SaveImage4BitsInTexture(Image image, unsigned char* data,
                        Tyra::TextureAtlas* atlas, unsigned int widthTexture,
                        unsigned int heightTexture) {
  int k = 0;
  int maxWidth = ceilf(((float)image.width/2));

  if (maxWidth + atlas->x > (widthTexture/2)) {
    atlas->x = 0;
    atlas->y += atlas->maxHeight;
  }

  if (image.height + atlas->y > heightTexture){
    TYRA_TRAP("ERROR MAX TEXTURE");
  }

  // printf("save in x,y: %d,%d\n",atlas->x,atlas->y);

  for (unsigned int i = atlas->y; i < image.height + atlas->y; i++) {
    for (unsigned int j = atlas->x; j < maxWidth + atlas->x; j++) {
      data[(i * (widthTexture/2)) + j] = image.data[k];
      // printf("save pixel[%d]: %d\n",(i*(widthTexture/2))+j,k);
      k++;
    }
  }
}


Image CopyTexture8Bits(unsigned char* dataSrc, int srcWidth, int srcHeight,
                       int x, int y, int width, int height) {
  Image image;
  image.width = width;
  image.height = height;
  image.data = static_cast<unsigned char*>(memalign(128, width * height));
  // printf("image: %d,%d,%d,%d\n",x,y,width,height);
  // Tyra::PngPixel3* pixel = (Tyra::PngPixel3*)image.data;
  // Tyra::PngPixel3* src = (Tyra::PngPixel3*)dataSrc;
  for (int i = 0; i < width * height; i++) {
    image.data[i] = 0;
  }

  int k = 0;
  for (int i = y; i < height + y; i++) {
    for (int j = x; j < width + x; j++) {
      // printf("pixel[%d]: %d=%d\n",k,k,(i*srcWidth)+j);
      // printf("%d\n",(i*width)+j);
      // printf("%d\n",(i*srcWidth)+j);
      // pixel[k] = src[(i * srcWidth) + j];
      image.data[k] = dataSrc[(i * srcWidth) + j];
      k++;
    }
  }

  // return data;
  return image;
}

void SaveImage8BitsInTexture(Image image, unsigned char* data,
                        Tyra::TextureAtlas* atlas, unsigned int widthTexture,
                        unsigned int heightTexture) {
  // Tyra::PngPixel3* pixel = (Tyra::PngPixel3*)image.data;
  // Tyra::PngPixel3* src = (Tyra::PngPixel3*)data;
  int k = 0;
  // printf("save in x,y: %d,%d\n",atlas->x,atlas->y);
  
  if (image.width + atlas->x > widthTexture) {
    atlas->x = 0;
    atlas->y += atlas->maxHeight;
  }

  if (image.height + atlas->y > heightTexture){
    TYRA_TRAP("ERROR MAX TEXTURE");
  }

  for (unsigned int i = atlas->y; i < image.height + atlas->y; i++) {
    for (unsigned int j = atlas->x; j < image.width + atlas->x; j++) {
      data[(i * widthTexture) + j] = image.data[k];
      // printf("pixel[%d]: %d\n",(i*widthTexture)+j,k);
      k++;

      // printf("%d\n",(i*width)+j);
      // printf("%d\n",(i*srcWidth)+j);
      // pixel[(i*width)+j] = src[(i*srcWidth)+j];
      // k++;
    }
  }
}

Image CopyTexture24Bits(unsigned char* dataSrc, int srcWidth, int srcHeight,
                        int x, int y, int width, int height) {
  // unsigned char* data = static_cast<unsigned char*>(memalign(128, width *
  // height * 3)); //RGBA
  Image image;
  image.width = width;
  image.height = height;
  image.data =
      static_cast<unsigned char*>(memalign(128, width * height * 3));  // RGB
  // printf("image: %d,%d,%d,%d\n",x,y,width,height);
  Tyra::PngPixel3* pixel = (Tyra::PngPixel3*)image.data;
  Tyra::PngPixel3* src = (Tyra::PngPixel3*)dataSrc;
  for (int i = 0; i < width * height * 3; i++) {
    image.data[i] = 0;
  }

  int k = 0;
  for (int i = y; i < height + y; i++) {
    for (int j = x; j < width + x; j++) {
      // printf("pixel[%d]: %d=%d\n",k,k,(i*srcWidth)+j);
      // printf("%d\n",(i*width)+j);
      // printf("%d\n",(i*srcWidth)+j);
      pixel[k] = src[(i * srcWidth) + j];
      k++;
    }
  }

  // return data;
  return image;
}

void SaveImageInTexture(Image image, unsigned char* data,
                        Tyra::TextureAtlas* atlas, unsigned int widthTexture,
                        unsigned int heightTexture) {
  Tyra::PngPixel3* pixel = (Tyra::PngPixel3*)image.data;
  Tyra::PngPixel3* src = (Tyra::PngPixel3*)data;
  int k = 0;
  printf("save in x,y: %d,%d\n",atlas->x,atlas->y);
  if (image.width + atlas->x > widthTexture) {
    atlas->x = 0;
    atlas->y += atlas->maxHeight;
  }

  for (unsigned int i = atlas->y; i < image.height + atlas->y; i++) {
    for (unsigned int j = atlas->x; j < image.width + atlas->x; j++) {
      src[(i * widthTexture) + j] = pixel[k];
      // printf("pixel[%d]: %d\n",(i*widthTexture)+j,k);
      k++;

      // printf("%d\n",(i*width)+j);
      // printf("%d\n",(i*srcWidth)+j);
      // pixel[(i*width)+j] = src[(i*srcWidth)+j];
      // k++;
    }
  }
}

void ReadFontFile(FontData* font, const char* font_txt) {
  FILE* file;
  file = fopen(font_txt, "r");
  std::string text;
  int c;
  int exitCount = 0;
  int pos = 0;
  int pos2 = 0;
  int val;
  // unsigned int bytes;
  // printf("valor: %d\n",engine->font.getCodepoint("ÿ",&bytes));
  while ((c = fgetc(file)) != EOF) {
    // printf("%c",c);
    text += c;
    // printf("saltodelinea\n");
    // printf("texto: %s\n",text.c_str());
    if (text == "Define CharList") {
      printf("estoy en Define CharList\n");
      text.clear();
      while ((c = fgetc(file)) != ';') {
        if (c == '\'') {
          while ((c = fgetc(file)) != '\'') {
            // printf("pos[%d]: %c\n", pos, c);
            font->charlist[pos] = c;
            pos++;
          }
        } else if (c == '"') {
          while ((c = fgetc(file)) != '"') {
            // printf("pos[%d]: %c\n", pos, c);
            font->charlist[pos] = c;
            pos++;
          }
        }
      }
      pos = 0;
    } else if (text == "Define WidthList") {
      printf("estoy en Define WidthList\n");
      text.clear();
      while (exitCount < 1) {
        c = fgetc(file);
        if (c >= '0' && c <= '9') {
          text += c;
        } else if (c == ',' || c == ')') {
          val = atoi(text.c_str());
          font->widthlist[pos] = val;
          pos++;
          text.clear();
        } else if (c == ';') {
          exitCount++;
        }
      }
      exitCount = 0;
      pos = 0;
      text.clear();
    } else if (text == "Define RectList") {
      printf("estoy en Define RectList\n");
      text.clear();
      while (exitCount == 0) {
        c = fgetc(file);
        if (c == '(') {
          while (exitCount == 0) {
            c = fgetc(file);
            if ((c >= '0' && c <= '9')) {
              text += c;
            } else if (c == ',') {
              val = atoi(text.c_str());
              font->rectlist[pos].val[pos2] = val;
              pos2++;
              text.clear();
            } else if (c == ')') {
              val = atoi(text.c_str());
              font->rectlist[pos].val[pos2] = val;
              pos2 = 0;
              text.clear();
              exitCount = 1;
            }
          }
          exitCount = 0;
          pos++;
          // printf("\n");
        } else if (c == ';') {
          exitCount = 1;
        }
      }
      exitCount = 0;
      pos = 0;
      pos2 = 0;
    } else if (text == "Define OffsetList") {
      printf("estoy en Define OffsetList\n");
      text.clear();
      while (exitCount == 0) {
        c = fgetc(file);
        if (c == '(') {
          while (exitCount == 0) {
            c = fgetc(file);
            if ((c >= '0' && c <= '9') || c == '-') {
              text += c;
            } else if (c == ',') {
              val = atoi(text.c_str());
              font->offsetlist[pos].val[pos2] = val;
              pos2++;
              text.clear();
            } else if (c == ')') {
              val = atoi(text.c_str());
              font->offsetlist[pos].val[pos2] = val;
              pos2 = 0;
              text.clear();
              exitCount = 1;
            }
          }
          pos++;
          exitCount = 0;
        } else if (c == ';') {
          exitCount = 1;
        }
      }
    } else if (text == "LayerSetCharWidths") {
      text.clear();
      while ((c = fgetc(file)) != ';') {
        if (c >= '0' && c <= '9') {
          font->spaceWidth = c - '0';
        }
      }
      // printf("spaceWidth: %d\n", spaceWidth);

      // text.clear();
    } else if (text == "SetDefaultPointSize") {
      text.clear();
      while ((c = fgetc(file)) != ';') {
        if (c >= '0' && c <= '9') {
          // spaceHeight = c - '0';
          text += c;
        }
      }
      font->spaceHeight = atoi(text.c_str());
      // printf("spaceHeight: %d\n", spaceHeight);

      // text.clear();
    } else if (c == '\n') {
      text.clear();
    }
  }

  fclose(file);
}

void ReadFontImage(FontData* font, Tyra::TextureAtlas* textureAtlasFont, const char* image) {
  PngLoaderUnlimited loader;
  Tyra::TextureBuilderData* textureData = loader.load(image);
  Tyra::Texture* texture = new Tyra::Texture(textureData);
  texture->print();
  
  // printf("pase 1\n");

  Tyra::TextureBuilderData* textureData2 = new Tyra::TextureBuilderData();
  textureData2->width = 256;
  textureData2->height = 128;
  
  if (texture->core->bpp == Tyra::bpp4){
    textureData2->width = 512;
    textureData2->height = 512;
    textureData2->data = static_cast<unsigned char*>(
        memalign(128, textureData2->width * textureData2->height/2));
    
    for (int i = 0; i < textureData2->width * textureData2->height/2; i++) {
      textureData2->data[i] = 0;
    }

    textureData2->name = "copia";
    textureData2->bpp = Tyra::bpp4;
    textureData2->gsComponents = TEXTURE_COMPONENTS_RGBA;
    textureData2->clutGsComponents = TEXTURE_COMPONENTS_RGBA;
    textureData2->clutWidth = textureData->clutWidth;
    textureData2->clutHeight = textureData->clutHeight;
    textureData2->clutBpp = textureData->clutBpp;
    
    textureData2->clut = static_cast<unsigned char*>(
      memalign(128, textureData2->clutWidth * textureData2->clutHeight*4));

    textureData2->clut = textureData->clut;

    // Convert the black color in transparent
    for(int i=0; i<16*4;){
      if( textureData2->clut[i] == 0 &&
        textureData2->clut[i+1] == 0 &&
        textureData2->clut[i+2] == 0 &&
        textureData2->clut[i+3] == 128){
          textureData2->clut[i+3] = 0;
          break;
        }
      i=i+4;
    }

    for (int i = 0; i < 160; i++) {
      Image image = CopyTexture4Bits(texture->core->data, texture->core->width,
                                     texture->core->height, font->rectlist[i].val[0],
                                     font->rectlist[i].val[1], font->rectlist[i].val[2],
                                     font->rectlist[i].val[3]);

      if (font->rectlist[i].val[3] > textureAtlasFont->maxHeight) {
        textureAtlasFont->maxHeight += font->rectlist[i].val[3];
      }

      SaveImage4BitsInTexture(image, textureData2->data, textureAtlasFont,
                         textureData2->width, textureData2->height);
      font->rectlist[i].val[0] = textureAtlasFont->x*2;
      font->rectlist[i].val[1] = textureAtlasFont->y;
      int maxWidth = ceilf(((float)image.width/2));
      textureAtlasFont->x += (maxWidth);
      free(image.data);
    }
  }else if (texture->core->bpp == Tyra::bpp8) {
    textureData2->data = static_cast<unsigned char*>(
        memalign(128, textureData2->width * textureData2->height));

    for (int i = 0; i < textureData2->width * textureData2->height; i++) {
      textureData2->data[i] = 0;
    }

    textureData2->name = "copia";
    textureData2->bpp = Tyra::bpp8;
    textureData2->gsComponents = TEXTURE_COMPONENTS_RGBA;
    textureData2->clutGsComponents = TEXTURE_COMPONENTS_RGBA;
    textureData2->clutWidth = textureData->clutWidth;
    textureData2->clutHeight = textureData->clutHeight;
    textureData2->clutBpp = textureData->clutBpp;

    textureData2->clut = static_cast<unsigned char*>(
      memalign(128, textureData2->clutWidth * textureData2->clutHeight*4));

    textureData2->clut = textureData->clut;
    for (int i = 0; i < 160; i++) {
      // printf("val: %d\n",i);
      Image image = CopyTexture8Bits(texture->core->data, texture->core->width,
                                     texture->core->height, font->rectlist[i].val[0],
                                     font->rectlist[i].val[1], font->rectlist[i].val[2],
                                     font->rectlist[i].val[3]);
      // textureAtlasFont.x = rectlist[i].val[0];
      if (font->rectlist[i].val[3] > textureAtlasFont->maxHeight) {
        textureAtlasFont->maxHeight += font->rectlist[i].val[3];
      }
      // printf("ram: %f\n",engine->info.getAvailableRAM());
      SaveImage8BitsInTexture(image, textureData2->data, textureAtlasFont,
                         textureData2->width, textureData2->height);
      font->rectlist[i].val[0] = textureAtlasFont->x;
      font->rectlist[i].val[1] = textureAtlasFont->y;
      textureAtlasFont->x += font->rectlist[i].val[2];
      free(image.data);
    }
    
    // free(textureData->clut);
  } else if (texture->core->bpp == Tyra::bpp24) {
    
    // printf("estoy en 24\n");
    textureData2->data = static_cast<unsigned char*>(
        memalign(128, textureData2->width * textureData2->height * 3));

    for (int i = 0; i < textureData2->width * textureData2->height * 3; i++) {
      textureData2->data[i] = 0;
    }

    textureData2->bpp = Tyra::bpp24;
    textureData2->gsComponents = TEXTURE_COMPONENTS_RGBA;

    for (int i = 0; i < 160; i++) {
      Image image = CopyTexture24Bits(texture->core->data, texture->core->width,
                                      texture->core->height, font->rectlist[i].val[0],
                                      font->rectlist[i].val[1], font->rectlist[i].val[2],
                                      font->rectlist[i].val[3]);
      // textureAtlasFont.x = rectlist[i].val[0];
      if (font->rectlist[i].val[3] > textureAtlasFont->maxHeight) {
        textureAtlasFont->maxHeight += font->rectlist[i].val[3];
      }
      // printf("ram: %f\n",engine->info.getAvailableRAM());
      SaveImageInTexture(image, textureData2->data, textureAtlasFont,
                         textureData2->width, textureData2->height);
      font->rectlist[i].val[0] = textureAtlasFont->x;
      font->rectlist[i].val[1] = textureAtlasFont->y;
      textureAtlasFont->x += font->rectlist[i].val[2];
      free(image.data);
    }
  }else{
    TYRA_TRAP("Doesn't support this format for the font");
  }

  Tyra::Texture* texture2 = new Tyra::Texture(textureData2);
  texture2->print();
  // texture2->addLink(spriteFont.id);
  texRepo->add(texture2);
  font->textureID = texture2->id;
  spriteFont.size = Vec2(textureData2->width, textureData2->height);
  spriteFont.mode = Tyra::SpriteMode::MODE_REPEAT;

  free(textureData->data);
}

void loadFonts() {
  Tyra::TextureAtlas textureAtlasFont;
  FontData font;
  ReadFontFile(&font, FONT_TXT_BrianneTod12);
  ReadFontImage(&font, &textureAtlasFont, FONT_BrianneTod12);

  fonts.push_back(font);

  FontBrianneTod12ID = fonts.size()-1;

  textureAtlasFont.x = 0;
  textureAtlasFont.y = 0;
  textureAtlasFont.maxHeight = 0;
  
  FontData font2;
  ReadFontFile(&font2, FONT_TXT_Pico129);
  ReadFontImage(&font2, &textureAtlasFont, FONT_Pico129);
  
  // Tyra::PngPixel4* pixels = (Tyra::PngPixel4*) texRepo->getByTextureId(font2.textureID)->clut;
  // pixels[0].r = 0;
  // pixels[0].g = 0;
  // pixels[0].b = 0;
  // pixels[0].a = 0;
  // printf("VIENDO EL CLUT\n");
  // printf("valor pixel 1: %d\n",texRepo->getByTextureId(font2.textureID)->core->data[0]);
  // for(int i=0; i < 7;i++){
  //   printf("pixel[%d]: %d,%d,%d,%d\n",i,pixels[i].r,pixels[i].g,pixels[i].b,pixels[i].a);
  //   pixels[i].r = 0;
  //   pixels[i].g = 0;
  //   pixels[i].b = 0;
  //   // if(pixels[i].r == 0 && pixels[i].g == 0 && pixels[i].b == 0){
  //   //   pixels[i].a = 0;
  //   //   printf("lo encontre el color en: %d\n",i);
  //   // }
  // }

  fonts.push_back(font2);
  
  FontPicoID = fonts.size()-1;
  
  textureAtlasFont.x = 0;
  textureAtlasFont.y = 0;
  textureAtlasFont.maxHeight = 0;
  
  FontData font3;
  ReadFontFile(&font3, FONT_TXT_HouseofTerror16);
  ReadFontImage(&font3, &textureAtlasFont, FONT_HouseofTerror16);
  fonts.push_back(font3);
  
  HouseofTerror16ID = fonts.size()-1;
  
  printf("ram: %f\n",engine->info.getAvailableRAM());

  // printf("CharList values\n");

  // for(int i=0; i<160;i++){
  //   printf("char[%d]: %d\n",i,charlist[i]);
  // }

  // printf("widthlist values\n");

  // for (int i = 0; i < 160; i++) {
  //   printf("Width[%d]: %d\n", i, widthlist[i]);
  // }

  // printf("rectlist values\n");
  // for (int i = 0; i < 160; i++) {
  //   printf("rect[%d]:%d,%d,%d,%d\n", i, font.rectlist[i].val[0], font.rectlist[i].val[1],
  //     font.rectlist[i].val[2], font.rectlist[i].val[3]);
  // }

  // printf("offset values\n");
  // for(int i=0; i<160;i++){
  //   printf("offset[%d]:
  //   %d,%d\n",i,offsetlist[i].val[0],offsetlist[i].val[1]);
  // }
}

int CreateTextData(std::string text, float x, float y, int fontID) {
  TextData texdata;
  texdata.text = text;
  texdata.x = x;
  texdata.y = y;
  texdata.fontID = fontID;
  textArray.push_back(texdata);
  return textArray.size() - 1;
}

int getLetterPos(int* charlist, int letter) {
  for (unsigned int i = 0; i < 160; i++) {
    if (letter == charlist[i]) {
      return i;
    }
  }
  for (unsigned int i = 0; i < 160; i++){
    if(' ' == charlist[i]){
      return i;
    }
  }
  return 0;
}

int getCodepoint(const char* text, unsigned int* bytes) {
  /* UTF-8 more info in https://en.wikipedia.org/wiki/UTF-8
    Code point ↔ UTF-8 conversion
    First code and last code point are in hexadecimal.
    If use 2 bytes or more, from the byte 2 they need to be 10xxxxxx until
    the last byte used. The "x" means can be 1 or 0.
    |----------------------------------------------------------------------|
    |First code point |Last code point |Byte 1  |Byte 2  |Byte 3  |Byte 4  |
    |(0000-0000)      |(0000-007F)     |0xxxxxxx|nothing |nothing |nothing |
    |(0000-0080)      |(0000-07FF)     |110xxxxx|10xxxxxx|nothing |nothing |
    |(0000-0800)      |(0000-FFFF)     |1110xxxx|10xxxxxx|10xxxxxx|nothing |
    |(0001-0000)      |(0010-FFFF)     |11110xxx|10xxxxxx|10xxxxxx|10xxxxxx|
    |----------------------------------------------------------------------|
    0x80 = 1000-0000
    0xC0 = 1100-0000
    0xE0 = 1110-0000
    0xF0 = 1111-0000
    0xF8 = 1111-1000
  */

  int codepoint = 0x3f;  // char '?'
  *bytes = 1;

  // 0x00 minimum value allowed, 0x80 minimum value NOT allowed
  if (0x00 == (0x80 & (unsigned char) text[0])) {
    codepoint = text[0];
  }  // 0xC0 minimum value allowed, 0xE0 minimum value NOT allowed
  else if (0xC0 == (0xE0 & (unsigned char) text[0])) {
    if ((text[1] & 0xC0) == 0x80) {  // verify that it is 10xxxxxx.
      codepoint = (((unsigned char) text[0] ^ 0xC0) << 6) | (((unsigned char)text[1] ^ 0x80));
      *bytes = 2;
    }
  }  // 0xE0 minimum value allowed, 0xF0 minimum value NOT allowed
  else if (0xE0 == (0xF0 & text[0])) {
    if ((text[1] & 0xC0) == 0x80 && (text[2] & 0xC0) == 0x80) {
      codepoint = (((unsigned char)text[0] ^ 0xE0) << 12) | (((unsigned char)text[1] ^ 0x80) << 6) |
                  (((unsigned char)text[2] ^ 0x80));
      *bytes = 3;
    }
  }  // 0xF0 minimum value allowed, 0xF8 minimum value NOT allowed
  else if (0xF0 == (0xF8 & text[0])) {
    if ((text[1] & 0xC0) == 0x80 && (text[2] & 0xC0) == 0x80 &&
        (text[3] & 0xC0) == 0x80) {
      codepoint = (((unsigned char)text[0] ^ 0xF0) << 18) | (((unsigned char)text[1] ^ 0x80) << 12) |
                  (((unsigned char)text[2] ^ 0x80) << 6) | (((unsigned char)text[3] ^ 0x80));
      *bytes = 4;
    }
  }
  return codepoint;
}

void drawText(FontData* font, std::string text, float x, float y) {
  // renderer->renderer2D.render(spriteFont);
  unsigned int maxLetters = text.size();
  int ascii;
  int offsetX = 0;
  int offsetY = 0;
  // int part;
  Tyra::Texture* texture = texRepo->getByTextureId(font->textureID);
  if(texture == nullptr){
    TYRA_TRAP("trampa");
  }
  // printf("spritefont size\n");
  // spriteFont.size.print();
  // texture->print();
  texture->addLink(spriteFont.id);
  spriteFont.textureID = texture->id;
  // renderer->renderer2D.render(spriteFont);
  unsigned int indexGlyph = 0;
  std::vector<int> codepoints;
  for (unsigned int i = 0; i < maxLetters;) {
    codepoints.push_back(getCodepoint(&text[i], &indexGlyph));
    i += indexGlyph;
  }
  // sizeof(font->offsetlist);
  maxLetters = codepoints.size();
  // printf("maxletters 2: %d\n",maxLetters);
  for (unsigned int i = 0; i < maxLetters; i++) {
    // printf("text: %c,%d\n", (unsigned char)codepoints[i],codepoints[i]);
    if (codepoints[i] == ' ') {
      offsetX += font->spaceWidth;
    } else if (codepoints[i] == '\n') {
      offsetY += font->spaceHeight;
      offsetX = 0;
    } else {
      ascii = getLetterPos(font->charlist, codepoints[i]);
      spriteFont.position.x = x + offsetX ;//+ font->offsetlist[ascii].val[0];
      spriteFont.position.y = y + offsetY;
      spriteFont.offset.x = font->rectlist[ascii].val[0];
      spriteFont.offset.y = font->rectlist[ascii].val[1];
      spriteFont.size.x = font->rectlist[ascii].val[2];
      spriteFont.size.y = font->rectlist[ascii].val[3] - font->offsetlist[ascii].val[1];
      renderer->renderer2D.render(spriteFont);
      offsetX += font->widthlist[ascii];
    }
  }
  texRepo->getByTextureId(font->textureID)->removeLinkById(spriteFont.id);
}