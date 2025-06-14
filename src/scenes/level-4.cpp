#include "components.hpp"
#include "debug/debug.hpp"
#include "file/file_utils.hpp"
#include "font/font.hpp"
#include "fontFiles.hpp"
#include "scenes.hpp"
#include "imageTools.hpp"
#include "systems.hpp"
#include <stdio.h>
#include <string.h>
#include <string>
#include <tyra>

using namespace Tyra;

static BackgroundEntity entidad;

void Level4::init() {
  loadFonts();
  // PngLoaderUnlimited loader;
  // Tyra::TextureBuilderData* textureData = loader.load(FONT_BrianneTod12);
  // Tyra::Texture texture(textureData);
  // texture.print();
  // JpgScaleData scaleData = PNGImageScale::load(&texture,TextureScale::Tex128,TextureScale::Tex64,0);
  
  // esto no por ahora
  // SetBigImage(&entidad,&scaleData,Tyra::SpriteMode::MODE_STRETCH,10,0,128,64);
  //   loader.load("test5.png");
  std::string text;
  text = "el abecedario\nvamos a decir";
  CreateTextData(text,0,0,FontBrianneTod12ID);
  CreateTextData(text,50,50,FontPicoID);
}
void Level4::update() {
  
  renderer->beginFrame();
  
  fontManager.update();
  // drawText(&fonts[FontBrianneTod12ID], "el abecedario\nvamos a decir",0,0);
  
  // drawText(&fonts[FontPicoID], "el abecedario\nvamos a decir",50,50);
  // drawText("A",0,0);
  renderSprites.update();
  renderer->endFrame();
}