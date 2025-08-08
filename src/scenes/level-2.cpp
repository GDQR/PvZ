#include "scenes/level-2.hpp"
#include "scenes.hpp"
#include "states.hpp"
#include "manager.hpp"

void Level2::init() {
  Entity::background = Entities::newID();
  // load background
  createSprite(Entity::background, Tyra::MODE_STRETCH, Vec2(-56, -1),
               Vec2(780, 524));  // Vec2(467, 200*2.9f)
  // printf("posArray: %s\n",posArray[background].getPrint().c_str());
  createTexture(Entity::background, "Backgrounds/DAY Unsodded.png");
  initAnimation(); 
}

static packet2_t* mypacket;
void Level2::initAnimation(){
  mypacket = packet2_create(16, P2_TYPE_NORMAL, P2_MODE_NORMAL, 0);
  Entity::sodRoll = Entities::newID();
  Entity::sodRollCap = Entities::newID();
  Entity::sodRollRow1 = Entities::newID();
  Entity::sodRollRow1Alpha = Entities::newID();
  Entity::sod3Row = Entities::newID();
  Entity::sod3RowAlpha = Entities::newID();
  createSprite(Entity::sodRoll, Tyra::MODE_STRETCH, Vec2(0, 0), Vec2(64, 141));
  createSprite(Entity::sodRollCap, Tyra::MODE_STRETCH, Vec2(0, 0), Vec2(73, 71));
  createSprite(Entity::sodRollRow1, Tyra::MODE_REPEAT, Vec2(0, 0), Vec2(771, 127));
  createSprite(Entity::sodRollRow1Alpha, Tyra::MODE_STRETCH, Vec2(0, 0), Vec2(717, 127));
  // createSprite(sod3Row, Tyra::MODE_REPEAT, Vec2(0, 0), Vec2(0, 355));
  // TODO: the image can be more than 512
  // createSprite(sod3RowAlpha, Tyra::MODE_STRETCH, Vec2(0, 0), Vec2(771, 335));
  createTexture(Entity::sodRoll, "REANIM/sodRoll.png");
  createTexture(Entity::sodRollCap, "REANIM/sodRollCap.png");
  createTexture(Entity::sodRollRow1, "IMAGES/sod1row.jpg");
  createTexture(Entity::sodRollRow1Alpha, "IMAGES/sod1row_.png");
  // createTexture(sod3Row, "IMAGES/sod3row.jpg");
  // createTexture(sod3RowAlpha, "IMAGES/sod3row_.png");
  // Tyra::Texture* alpha = renderer->getTextureRepository().getBySpriteId(
  //     spriteArray[sodRollRow1Alpha].id);
  // Tyra::Texture* background = renderer->getTextureRepository().getBySpriteId(
  //     spriteArray[sodRollRow1].id);
  // spriteArray[sodRollRow1].scale = 0.5f;
  // background->core->components = TEXTURE_COMPONENTS_RGBA;
  // int v = 0;
  
  // Tyra::PngPixel4* clutData = (Tyra::PngPixel4*)alpha->clut->data;
  // unsigned char* pixelData = alpha->core->data;
  // struct Tyra::PngPixel3* backData =
  //     (struct Tyra::PngPixel3*)background->core->data;
  // float alphaval;
  // for (int i = 0; i < 127; i++) {
  //   for (int j = 0; j < 771; j++) {
  //     alphaval = ((float)clutData[pixelData[v]].r / 255);
  //     backData[v].r *= alphaval;
  //     backData[v].g *= alphaval;
  //     backData[v].b *= alphaval;
  //     v++;
  //   }
  // }
  printf("ram: %f\n",engine->info.getAvailableRAM());

  // alpha = renderer->getTextureRepository().getBySpriteId(
  //   spriteArray[sod3RowAlpha].id);
  // background = renderer->getTextureRepository().getBySpriteId(
  //   spriteArray[sod3Row].id);
  // alpha->print();
  // background->core->components = TEXTURE_COMPONENTS_RGBA;
  // background->print();
  
  // clutData = (Tyra::PngPixel4*)alpha->clut->data;
  // pixelData = alpha->core->data;
  // backData = (struct Tyra::PngPixel3*)background->core->data;
  // v=0;
  // for (int i = 0; i < 355; i++) {
  //   for (int j = 0; j < 771; j++) {
  //     alphaval = ((float)clutData[pixelData[v]].r / 255);
  //     backData[v].r *= alphaval;
  //     backData[v].g *= alphaval;
  //     backData[v].b *= alphaval;
  //     v++;
  //   }
  // }
    
  deleteSprite(Entity::sodRollRow1Alpha);
  // deleteSprite(sod3RowAlpha);
  packet2_update(mypacket,
                 draw_texture_expand_alpha(mypacket->next, 128, 1, 0));
  packet2_update(mypacket, draw_finish(mypacket->next));
  dma_channel_wait(DMA_CHANNEL_GIF, 0);
  dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
  packet2_reset(mypacket, 0);
}
static bool firstTime=true;

void Level2::loopAnimation(){
  static int frame=0;
  frame = 0;
  if(spriteArray[Entity::sod3Row].size.x<771){
    posArray[Entity::sodRoll].x+=5;
    posArray[Entity::sodRollCap].x+=5;
    spriteArray[Entity::sod3Row].size.x+=5;
  }else{
    firstTime = false;
  }
  frame++;
}

void Level2::update() {
  // printf("FPS: %d\n", engine->info.getFps());
  if(firstTime==true){
    // loopAnimation();
  }
  renderer->beginFrame();
  
  renderSprites.update();
  renderer->endFrame();
}

void Level2::destroy() {}