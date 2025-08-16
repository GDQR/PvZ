#include "debug/debug.hpp"
#include "file/file_utils.hpp"
#include "font/font.hpp"
#include "fontFiles.hpp"
#include "scenes.hpp"
#include "imageTools.hpp"
#include "manager.hpp"
#include <stdio.h>
#include <string.h>
#include <string>
#include <tyra>

using namespace Tyra;

static BigSpriteJPG entidad;

void Level4::init() {
  loadFonts();
  // PngLoaderUnlimited loader;
  // Tyra::TextureBuilderData* textureData = loader.load("SLOT.PNG");
  // Tyra::Texture* texture = new Texture(textureData);
  // texRepo->add(texture);

  // int ent=0;
  // ent = Entities::newID();
  // createSprite(ent,Tyra::SpriteMode::MODE_STRETCH,Vec2(20,20),Vec2(32,32));
  // createTexture(ent,"SLOT.PNG");
  // // spriteArray[ent].textureID = texture->id;
  // // texture->addLink(spriteArray[ent].id);
  // Tyra::Texture* tex = texRepo->getByTextureId(spriteArray[ent].textureID);
  // tex->print();
  // int k=0;
  // Tyra::PngPixel4* pixels = (Tyra::PngPixel4*) tex->clut->data;
  // for(int i=0; i< tex->clut->height; i++){
  //   for(int j=0; j< tex->clut->width; j++){
  //     printf("clut[%d] %d,%d,%d,%d\n",k,pixels[k].r,pixels[k].g,pixels[k].b,pixels[k].a);
  //     k++;
  //   }
  // }
  // k=0;
  // int m=0;
  
  // printf("datos de la imagen\n");
  // for(int i=0; i< tex->getHeight()/2; i++){
  //   for(int j=0; j< tex->getWidth(); j++){
  //     printf("pixel[%d] %d,%x\n",k,tex->core->data[m]&0xf,tex->core->data[m]);
  //     k++;
  //     printf("pixel[%d] %d,%x\n",k,tex->core->data[m]>>4,tex->core->data[m]); 
  //     // 01000001 = 41 hex = (4) es el pixel 2, (1) es el pixel 1
  //     // printf("pixel[%d] %d,%x\n",k,tex->core->data[m],tex->core->data[m]); 
  //     // k++;
  //     // printf("pixel[%d] %d,%x\n",k,tex->core->data[m],tex->core->data[m]);
  //     k++;
  //     m++;
  //   }
  // }

  // Tyra::TextureBuilderData* textureData = loader.load(FONT_BrianneTod12);
  // Tyra::Texture texture(textureData);
  // texture.print();
  // JpgScaleData scaleData = PNGImageScale::load(&texture,TextureScale::Tex128,TextureScale::Tex64,0);
  
  // esto no por ahora
  // SetBigImage(&entidad,&scaleData,Tyra::SpriteMode::MODE_STRETCH,10,0,128,64);
  //   loader.load("test5.png");

  std::string text;
  // text = "el abecedario\nvamos a decir";
  text = "ABC";
  CreateTextData(text,0,0,FontBrianneTod12ID);
  CreateTextData(text,50,50,FontPicoID);
  
  CreateTextData(text,100,100,HouseofTerror16ID);

  Sprite sprFont;
  int pase=Entities::newID();
  createSprite(pase,Tyra::SpriteMode::MODE_STRETCH,Vec2(10,150),Vec2(512,512), enumSpriteLayer::background);
  
  spriteArray[pase].textureID = fonts[HouseofTerror16ID].textureID;
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