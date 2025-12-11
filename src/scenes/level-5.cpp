#include "debug/debug.hpp"
#include "file/file_utils.hpp"
#include "font/font.hpp"
#include "fontFiles.hpp"
#include "scenes.hpp"
#include "imageTools.hpp"
#include "imageFiles.hpp"
#include "manager.hpp"
#include <stdio.h>
#include <string.h>
#include <string>
#include <tyra>
using namespace Tyra;

void Level5::init() {
  srand(time(NULL));
  
  loadFonts();
  loadPlantCost();
  loadAnimString();
  loadPlantRechargeTime();
  loadDebugTextures();
  
  Entity::zombieFlagMeter = Entities::newID();
  Entity::fullFlagMeter = Entities::newID();

  createSprite(Entity::fullFlagMeter, MODE_REPEAT, Vec2(255, 410), Vec2(158, 24), enumSpriteLayer::background);
  spriteArray[Entity::fullFlagMeter].scale = 1;
  spriteArray[Entity::fullFlagMeter].offset.y = 27;
  spriteArray[Entity::fullFlagMeter].size.x = 0;
  // spriteArray[fullFlagMeter].flipHorizontal = true;
  createTexture(Entity::fullFlagMeter, IMG_FlagMeter);

  
  createSprite(Entity::zombieFlagMeter, MODE_REPEAT, Vec2(405, 410), Vec2(28, 25), enumSpriteLayer::background); //pos(255,410) es el final
  spriteArray[Entity::zombieFlagMeter].scale = 1;
  createTexture(Entity::zombieFlagMeter, IMG_FlagMeterParts);


  loadAnimation(EnumAnimationIndex::ANIM_Wallnut);
  loadAnimation(EnumAnimationIndex::ANIM_LawnMower);
  loadAnimation(EnumAnimationIndex::ANIM_Zombie);
  loadAnimation(EnumAnimationIndex::ANIM_Zombie_charred);
  Entity::backgroundIDs.initJPG(background1unsodded,SpriteMode::MODE_STRETCH,-141,0,81,95,TextureScale::Tex128,TextureScale::Tex128);

  PngLoaderUnlimited pngloader;

  TextureBuilderData* texData2 = pngloader.load(IMG_ConveyorBelt_backdrop);
  Tyra::Texture* tex2 = new Tyra::Texture(texData2);
  int ConveyorBelt_backdrop = Entities::newID();
  createSprite(ConveyorBelt_backdrop,Tyra::SpriteMode::MODE_STRETCH,Vec2(0,0),Vec2(516/2,86/2),enumSpriteLayer::background);
  spriteArray[ConveyorBelt_backdrop].textureID = tex2->id;

  texRepo->add(tex2);

  TextureBuilderData* texData = pngloader.load(IMG_ConveyorBelt);
  Tyra::Texture* tex = new Tyra::Texture(texData);
  int ConveyorBelt = Entities::newID();
  createSprite(ConveyorBelt,Tyra::SpriteMode::MODE_REPEAT,Vec2(6/2,0),Vec2(502/2,18/2/*18/2*/),enumSpriteLayer::background);
  spriteArray[ConveyorBelt].textureID = tex->id;

  texRepo->add(tex);

  // BigTexture bigTexture;

  // PNGImageScale::load(tex)


  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      plantCreatedInMap[i][j] = false;
      map[i][j] = Entities::newID();
      createBoxCollider(map[i][j],BoxColliderEnum::BOXCOLLIDER_MAP,
        BoxCollider(20 + (52 * j),
        58 + (75 * i),
        52,
        75));
      // createDebugBoxCollider(map[i][j],SpriteMode::MODE_STRETCH);
    }
  }
  mapEnable[2] = true;
  maxZombies = 1;  // this is used for when you win the level
  zombieCreateRow[2].maxZombiesInRow = 10;
  zombiescreated = 0;
  createCard(WallnutBowling,false);
  
  Entity::player.init(Vec2(mapCollider[0][0].x, mapCollider[0][0].y + 30),Tyra::Vec2(posArray[cards[0].seed].x - 3, -10));

  // cameraPos.x = -150;
  printf("ram: %f\n",engine->info.getAvailableRAM());
}

void Level5::update() {
  boxColliderManager.update();
  playerControl.update();
  cardManager.update();
  zombiesManager.update();
  frameManager.update();
  // sunManager.update();
  // lawnMoverManager.update();
  plantsManager.update();
  createZombieMain();

  projectileManager.update();

  // rewardManager.update();

  renderer->beginFrame();

  renderSprites.update();

  renderer->endFrame();
}