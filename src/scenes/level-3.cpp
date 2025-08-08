#include "scenes.hpp"
#include "states.hpp"
#include "imageTools.hpp"
#include "imageFiles.hpp"
#include "manager.hpp"

static BackgroundEntity sodnormal;
static BackgroundEntity sodnormalAlpha;
static packet2_t* mypacket;

void Level3::init() {
  engine->renderer.core.setClearScreenColor(Tyra::Color(255,0,0));
  // JpgScaleData textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(IMG_sod1row).c_str(),TextureScale::Tex256,TextureScale::Tex128);
  // SetBigImage(&sodnormal, &textures,0,0,81,95);
  // textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(IMG_sod1row_).c_str(),TextureScale::Tex256,TextureScale::Tex128);
  // SetBigImage(&sodnormalAlpha, &textures,0,0,81,95);
  Entity::sodRollRow1 = Entities::newID();
  Entity::sodRollRow1Alpha = Entities::newID();
  createSprite(Entity::sodRollRow1, Tyra::MODE_REPEAT, Vec2(12, 202), Vec2(132, 132));
  createSprite(Entity::sodRollRow1Alpha, Tyra::MODE_STRETCH, Vec2(0, 0), Vec2(717, 127));
  createTexture(Entity::sodRollRow1, IMG_sod1row);
  createTexture(Entity::sodRollRow1Alpha, IMG_sod1row_);
  // JpgScaleData textures = PNGImageScale::load(texRepo->getBySpriteId(spriteArray[Entity::sodRollRow1Alpha].id),TextureScale::Tex256,TextureScale::Tex128);
  // textures = JpgImageScale::load(texRepo->getBySpriteId(spriteArray[Entity::sodRollRow1Alpha].id),TextureScale::Tex256,TextureScale::Tex128);
  // SetBigImage(&sodnormalAlpha, &textures,0,0,81,95);
  Tyra::Texture* alpha = renderer->getTextureRepository().getBySpriteId(
      spriteArray[Entity::sodRollRow1Alpha].id);
  Tyra::Texture* background = renderer->getTextureRepository().getBySpriteId(
      spriteArray[Entity::sodRollRow1].id);
  spriteArray[Entity::sodRollRow1].scale = 0.64f;
  background->core->components = TEXTURE_COMPONENTS_RGBA;
  
  Tyra::PngPixel4* clutData = (Tyra::PngPixel4*)alpha->clut->data;
  unsigned char* pixelData = alpha->core->data;

  unsigned char* clutDataNormal= RotateClut(clutData);
  Tyra::PngPixel4* newClutData = (Tyra::PngPixel4*)clutDataNormal;
  
  struct Tyra::PngPixel3* backData =
      (struct Tyra::PngPixel3*)background->core->data;
  SetAlphaFrom8BppToJPG(backData,newClutData,pixelData,128,771);

  free(clutDataNormal);
  
  JpgScaleData textures = JpgImageScale::load(texRepo->getBySpriteId(spriteArray[Entity::sodRollRow1].id),TextureScale::Tex256,TextureScale::Tex128,TEXTURE_COMPONENTS_RGBA);
  SetBigImage(&sodnormal, &textures,Tyra::SpriteMode::MODE_STRETCH,0,0,256/2,128/2);
  deleteSprite(Entity::sodRollRow1);
  deleteSprite(Entity::sodRollRow1Alpha);
  // JpgScaleData textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(AwardScreen_Back).c_str(),TextureScale::Tex128,TextureScale::Tex128);
  // SetBigImage(&Entity::backgroundIDs, &textures,0,0,81,95);

  // while (textures.data.size()!=0)
  // {
  //   delete textures.data[0];
  //   textures.data.erase(textures.data.begin()+0);
  // }
  
  mypacket = packet2_create(16, P2_TYPE_NORMAL, P2_MODE_NORMAL, 0);
  packet2_update(mypacket,
    draw_texture_expand_alpha(mypacket->next, 128, 1, 0));
packet2_update(mypacket, draw_finish(mypacket->next));
dma_channel_wait(DMA_CHANNEL_GIF, 0);
dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
packet2_reset(mypacket, 0);
}


void Level3::update() {
  // backgroundIDs.move();
  Entity::backgroundIDs.scale();
    renderer->beginFrame();
    
    renderSprites.update();
    renderer->endFrame();
}