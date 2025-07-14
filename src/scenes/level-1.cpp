#include "components.hpp"
#include "debugPVZ/debug.hpp"
#include "debugPVZ/menuDebugCommands.hpp"
#include "entities/entities.hpp"
#include "font/font.hpp"
#include "renderSprite/textures.hpp"
#include "scenes.hpp"
#include "states.hpp"
#include "systems.hpp"
#include "entities/zombie.hpp"
#include "imageTools.hpp"
#include "imageFiles.hpp"
#include "text.hpp"
#include <stdlib.h>

using namespace Tyra;

#include <iostream>

int seedBank;
int zombieDebug;
int flagMeterTimer = 0;
int emptyFlagMeter;
int seedChooser;
int sunCounterText = 0;
int tutorialText = 0;
static int awardBackground;
bool firstTime = true;

int map[5][9];
int xMap = 9;
int yMap = 5;

using namespace Entity;

void Level1::init() {
  printf("ram: %f\n",engine->info.getAvailableRAM());
  // stapip.setRenderer(&renderer->core);
  srand(time(NULL));
  loadFonts();
  loadPlantCost();
  loadAnimString();
  loadPlantRechargeTime();
  loadAnimationStates();
  loadDebugTextures();
  
  Entity::backgroundIDs.initJPG(background1unsodded,SpriteMode::MODE_STRETCH,-141,0,81,95,TextureScale::Tex128,TextureScale::Tex128);

  seedBank = Entities::newID();
  zombieDebug = Entities::newID();
  emptyFlagMeter = Entities::newID();
  fullFlagMeter = Entities::newID();
  zombieFlagMeter = Entities::newID();
  seedChooser = Entities::newID();
  awardBackground = Entities::newID();
  // // TODO: Fix size seedBank
  createSprite(seedBank, MODE_STRETCH, Vec2(63, 10),
               Vec2(512 / 1.5f, 128 / 1.5f));
  createTexture(seedBank, IMG_seedBank);

  
  createSprite(emptyFlagMeter, MODE_REPEAT, Vec2(255, 410), Vec2(158, 24));
  spriteArray[emptyFlagMeter].scale = 1;
  createTexture(emptyFlagMeter, IMG_FlagMeter);
  
  createSprite(fullFlagMeter, MODE_REPEAT, Vec2(255, 410), Vec2(158, 24));
  spriteArray[fullFlagMeter].scale = 1;
  spriteArray[fullFlagMeter].offset.y = 27;
  spriteArray[fullFlagMeter].size.x = 0;
  // spriteArray[fullFlagMeter].flipHorizontal = true;
  createTexture(fullFlagMeter, IMG_FlagMeter);


  createSprite(zombieFlagMeter, MODE_REPEAT, Vec2(405, 410), Vec2(28, 25)); //pos(255,410) es el final
  spriteArray[zombieFlagMeter].scale = 1;
  createTexture(zombieFlagMeter, IMG_FlagMeterParts);

  bool isVersusMode = false;
  loadAnimation(AnimIndex::Peashooter);
  loadAnimation(AnimIndex::SunFlower);
  loadAnimation(AnimIndex::CherryBomb);
  loadAnimation(AnimIndex::Chomper);
  loadAnimation(AnimIndex::LawnMower);
  loadAnimation(AnimIndex::Zombie);
  loadAnimation(AnimIndex::Zombie_charred);
  loadAnimation(AnimIndex::Sun);
  createCard(Plant_State_enum::PeaShotter, Vec2(120, 10), isVersusMode);
  createCard(SunFlower, Vec2(180, 10), isVersusMode);
  createCard(CherryBomb, Vec2(240, 10), isVersusMode);
  createLawnMower(Tyra::Vec2(-35, 200));

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      plantCreatedInMap[i][j] = false;
      // mapCollider[i][j].x = 20 + (52 * j);
      // mapCollider[i][j].y = 58 + (75 * i);
      // mapCollider[i][j].width = 52;
      // mapCollider[i][j].height = 75;
      map[i][j] = Entities::newID();
      createBoxCollider(map[i][j],BoxColliderEnum::BOXCOLLIDER_MAP,
        BoxCollider(20 + (52 * j),
        58 + (75 * i),
        52,
        75));
      // boxColliderArray[map[i][j]] = mapCollider[i][j];
      // createDebugBoxCollider(map[i][j],SpriteMode::MODE_STRETCH);
    }
  }
  mapEnable[2] = true;

  maxZombies = 5;  // this is used for when you win the level
  zombieCreateRow[2].maxZombiesInRow = 10;
  zombiescreated = 0;
  player.init();
  player.initCursor(Vec2(mapCollider[0][0].x, mapCollider[0][0].y + 30));
  player.initDeckCard(Tyra::Vec2(posArray[cards[0].seed].x - 3, -10));
  loadProjectile();
  // sunManager.create(Vec2(277, 77), sunCost::normalSun, false);
  
  std::string text;
  text = std::to_string(sunCounter);
  sunCounterText = CreateTextData(text,70,40,FontBrianneTod12ID);
  tutorialText =  CreateTextData(ADVICE_CLICK_SEED_PACKET,70,270,FontBrianneTod12ID);
  firstTime = false;
  if (firstTime == true) {
    initAnimation();
  }
  printf("ram: %f\n",engine->info.getAvailableRAM());
}
static packet2_t* mypacket;
static BackgroundEntity sodnormal;
void Level1::initAnimation(){
  mypacket = packet2_create(16, P2_TYPE_NORMAL, P2_MODE_NORMAL, 0);
  
  sodRoll = Entities::newID();
  sodRollCap = Entities::newID();
  sodRollRow1 = Entities::newID();
  sodRollRow1Alpha = Entities::newID();
  createSprite(sodRoll, MODE_STRETCH, Vec2(0, 0), Vec2(64, 141));
  createSprite(sodRollCap, MODE_STRETCH, Vec2(0, 0), Vec2(73, 71));
  createSprite(sodRollRow1, MODE_REPEAT, Vec2(12, 202), Vec2(0, 132));
  createSprite(sodRollRow1Alpha, MODE_STRETCH, Vec2(0, 0), Vec2(717, 127));
  createTexture(sodRoll, "REANIM/SodRoll.png");
  createTexture(sodRollCap, "REANIM/SodRollCap.png");
  createTexture(sodRollRow1, IMG_sod1row);
  createTexture(sodRollRow1Alpha, IMG_sod1row_);
  Tyra::Texture* alpha = renderer->getTextureRepository().getBySpriteId(
    spriteArray[Entity::sodRollRow1Alpha].id);
  Tyra::Texture* background = renderer->getTextureRepository().getBySpriteId(
      spriteArray[Entity::sodRollRow1].id);
  // spriteArray[Entity::sodRollRow1].scale = 0.64f;
  background->core->components = TEXTURE_COMPONENTS_RGBA;

  Tyra::PngPixel4* clutData = (Tyra::PngPixel4*)alpha->clut->data;
  unsigned char* pixelData = alpha->core->data;

  unsigned char* clutDataNormal= RotateClut(clutData);
  Tyra::PngPixel4* newClutData = (Tyra::PngPixel4*)clutDataNormal;

  struct Tyra::PngPixel3* backData =
      (struct Tyra::PngPixel3*)background->core->data;
  SetAlphaFrom8BppToJPG(backData,newClutData,pixelData,128,771);

  free(clutDataNormal);

  sodnormal.initJPG(texRepo->getBySpriteId(spriteArray[Entity::sodRollRow1].id),SpriteMode::MODE_REPEAT,13,200,256,128,TextureScale::Tex256,TextureScale::Tex128);
  for(unsigned int i=0;i<sodnormal.id.size();i++){
    spriteArray[sodnormal.id[i]].size.x = -1.0f;
    spriteArray[sodnormal.id[i]].scale = 0.64f;
    posArray[sodnormal.id[i]].x = posArray[sodnormal.id[0]].x + i + (256*spriteArray[sodnormal.id[i]].scale)*i;
    // posArray[sodnormal.id[i]].print();
  }
  deleteSprite(Entity::sodRollRow1);
  deleteSprite(Entity::sodRollRow1Alpha);
  Entities::deleteID(Entity::sodRollRow1);
  Entities::deleteID(Entity::sodRollRow1Alpha);

  packet2_update(mypacket,
                 draw_texture_expand_alpha(mypacket->next, 128, 1, 0));
  packet2_update(mypacket, draw_finish(mypacket->next));
  dma_channel_wait(DMA_CHANNEL_GIF, 0);
  dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
  packet2_reset(mypacket, 0);
}

void Level1::loopAnimation(){
  static int frame=0;
  frame = 0;
  if(spriteArray[sodnormal.id[0]].size.x<256){
    posArray[sodRoll].x+=5;
    posArray[sodRollCap].x+=5;
    spriteArray[sodnormal.id[0]].size.x+=5;
    if(spriteArray[sodnormal.id[0]].size.x > 256){
      spriteArray[sodnormal.id[0]].size.x = 256;
    }
  }else if(spriteArray[sodnormal.id[1]].size.x<256){
    posArray[sodRoll].x+=5;
    posArray[sodRollCap].x+=5;
    spriteArray[sodnormal.id[1]].size.x+=5;
    if(spriteArray[sodnormal.id[1]].size.x > 256){
      spriteArray[sodnormal.id[1]].size.x = 256;
    }  
  }else if(spriteArray[sodnormal.id[2]].size.x<255){
    posArray[sodRoll].x+=5;
    posArray[sodRollCap].x+=5;
    spriteArray[sodnormal.id[2]].size.x+=5;    
    if(spriteArray[sodnormal.id[2]].size.x > 255){
      spriteArray[sodnormal.id[2]].size.x = 255;
    }    
  }else if(spriteArray[sodnormal.id[3]].size.x<256){
    // It is longer than necessary
    posArray[sodRoll].x+=5;
    posArray[sodRollCap].x+=5;
    spriteArray[sodnormal.id[3]].size.x+=5;      
  }else{
    firstTime = false;
  }
  frame++;
}

void Level1::update() {
  if (firstTime == true) {
    loopAnimation();
  } else {
    boxColliderManager.update();
    // boxColliderManager.testUpdate();
    playerControl.update();

    cardManager.update();

    if (stopAnimation == false) {
      zombiesManager.update();
      // animManager.update();
      frameManager.update();
    }
    if (debugMode == false) {
      sunManager.updateNaturalSun();
    }

    if (stopAnimation == false) {
      sunManager.createByTime();
      // sunManager.erase(cursor.id);
    }

    // printf("FPS: %d\n",engine->info.getFps()) ;
    // printf("ram: %f\n",engine->info.getAvailableRAM());
    // printf("texture free space:
    // %f\n",engine->renderer.core.gs.vram.getFreeSpaceInMB());
    
    lawnMoverManager.update();
    // shoot zombies
    plantsManager.update();

    createZombieMain();

    projectileManager.update();

    rewardManager.update();

    // if (spriteArray[emptyFlagMeter].size.x /*flagMeterTimer*/ > 0) {
    //   // printf("size flag: %f\n",spriteArray[emptyFlagMeter].size.x);
    //   spriteArray[emptyFlagMeter].size.x--;
    // }
  }

  renderer->beginFrame();

  // static u64 mytime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);

  renderSprites.update();

  // static u64 mytime2 = GetTimerSystemTime()/ (kBUSCLK / CLOCKS_PER_SEC);

  // std::cout << "Time taken by function: "
  //        << mytime2-mytime << " miliseconds" << std::endl;

  // renderDebugSpritesManager.update();
  // engine->font.drawText(&myFont, std::to_string(sunCounter).c_str(), 30, 30, 16,
  //                       Color(255, 255, 255, 128));

  fontManager.update();

  // if (debugMenu == true) {
  //   if (debugState == debugMain) {
  //     debugModeClass.drawMainMenu();
  //     if (stopAnimation == true) {
  //       animManager.debug();
  //     }
  //   }

  //   if (debugAnimation) {
  //     startDebugAnimationMode(engine->pad, engine->font);
  //     animManager.debug();
  //   } else if (debugState == SpriteDebug) {
  //     debugModeClass.drawSpriteModeMenu();
  //   }
  // }

  renderer->endFrame();
  // for(unsigned int i=0;i<sodnormal.id.size();i++){
  //   spriteArray[sodnormal.id[i]].size.print();
  // }
}

void Level1::destroy() {}
