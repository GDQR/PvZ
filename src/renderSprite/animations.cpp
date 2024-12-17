#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include "entities/entities.hpp"
#include "components.hpp"
#include "systems.hpp"
#include <iostream>

std::string animString[AnimIndex::enumMax];

void loadAnimString(){
  animString[AnimIndex::Blover] = "Blover";
  animString[AnimIndex::Cabbagepult] = "Cabbagepult";
  animString[AnimIndex::Cactus] = "Cactus";
  animString[AnimIndex::Spikeweed] = "Caltrop";
  animString[AnimIndex::Cattail] = "Cattail";
  animString[AnimIndex::CherryBomb] = "CherryBomb";
  animString[AnimIndex::Chomper] = "Chomper";
  animString[AnimIndex::CobCannon] = "CobCannon";
  animString[AnimIndex::CoffeeBean] = "Coffeebean";
  animString[AnimIndex::Coin_gold] = "Coin_gold";
  animString[AnimIndex::Coin_silver] = "Coin_silver";
  animString[AnimIndex::Kernelpult] = "Cornpult";
  animString[AnimIndex::CrazyDave] = "CrazyDave";
  animString[AnimIndex::Credits_AnyHour] = "Credits_AnyHour";
  animString[AnimIndex::Credits_BigBrain] = "Credits_BigBrain";
  animString[AnimIndex::Credits_Bossdance] = "Credits_Bossdance";
  animString[AnimIndex::Credits_brainplate] = "Credits_brainplate";
  animString[AnimIndex::Credits_CrazyDave] = "Credits_CrazyDave";
  animString[AnimIndex::Credits_DiscoLights] = "Credits_DiscoLights";
  animString[AnimIndex::Credits_Flower_petals] = "Credits_Flower_petals";
  animString[AnimIndex::Credits_Football] = "Credits_Football";
  animString[AnimIndex::Credits_Infantry] = "Credits_Infantry";
  animString[AnimIndex::Credits_Jackbox] = "Credits_Jackbox";
  animString[AnimIndex::Credits_Main] = "Credits_Main";
  animString[AnimIndex::Credits_Main2] = "Credits_Main2";
  animString[AnimIndex::Credits_Main3] = "Credits_Main3";
  animString[AnimIndex::Credits_SolarPower] = "Credits_SolarPower";
  animString[AnimIndex::Credits_stage] = "Credits_stage";
  animString[AnimIndex::Credits_Throat] = "Credits_Throat";
  animString[AnimIndex::Credits_Tombstones] = "Credits_Tombstones";
  animString[AnimIndex::Credits_WeAreTheUndead] = "Credits_WeAreTheUndead";
  animString[AnimIndex::Credits_ZombieArmy1] = "Credits_ZombieArmy1";
  animString[AnimIndex::Credits_ZombieArmy2] = "Credits_ZombieArmy2";
  animString[AnimIndex::Diamond] = "Diamond";
  animString[AnimIndex::Digger_rising_dirt] = "Digger_rising_dirt";
  animString[AnimIndex::FinalWave] = "FinalWave";
  animString[AnimIndex::Fire] = "Fire";
  animString[AnimIndex::FirePea] = "FirePea";
  animString[AnimIndex::FumeShroom] = "FumeShroom";
  animString[AnimIndex::Garlic] = "Garlic";
  animString[AnimIndex::GatlingPea] = "GatlingPea";
  animString[AnimIndex::GloomShroom] = "GloomShroom";
  animString[AnimIndex::GoldMagnet] = "GoldMagnet";
  animString[AnimIndex::Gravebuster] = "Gravebuster";
  animString[AnimIndex::Hammer] = "Hammer";
  animString[AnimIndex::HypnoShroom] = "HypnoShroom";
  animString[AnimIndex::IceShroom] = "IceShroom";
  animString[AnimIndex::Imitater] = "Imitater";
  animString[AnimIndex::Jalapeno] = "Jalapeno";
  animString[AnimIndex::LawnMower] = "LawnMower";
  animString[AnimIndex::LawnMoweredZombie] = "LawnMoweredZombie";
  animString[AnimIndex::LilyPad] = "LilyPad";
  animString[AnimIndex::LoadBar_sprout] = "LoadBar_sprout";
  animString[AnimIndex::LoadBar_Zombiehead] = "LoadBar_Zombiehead";
  animString[AnimIndex::Magnetshroom] = "Magnetshroom";
  animString[AnimIndex::Marigold] = "Marigold";
  animString[AnimIndex::Melonpult] = "Melonpult";
  animString[AnimIndex::Peashooter] = "PeaShooterSingle";
  animString[AnimIndex::Repeater] = "PeaShooter";
  animString[AnimIndex::Plantern] = "Plantern";
  animString[AnimIndex::PoolCleaner] = "PoolCleaner";
  animString[AnimIndex::Portal_Circle] = "Portal_Circle";
  animString[AnimIndex::Portal_Square] = "Portal_Square";
  animString[AnimIndex::FlowerPot] = "Pot";
  animString[AnimIndex::PotatoMine] = "PotatoMine";
  animString[AnimIndex::puff] = "puff";
  animString[AnimIndex::PuffShroom] = "PuffShroom";
  animString[AnimIndex::Pumpkin] = "Pumpkin";
  animString[AnimIndex::Rain_circle] = "Rain_circle";
  animString[AnimIndex::Rain_splash] = "Rain_splash";
  animString[AnimIndex::Rake] = "Rake";
  animString[AnimIndex::RoofCleaner] = "RoofCleaner";
  animString[AnimIndex::ScaredyShroom] = "ScaredyShroom";
  animString[AnimIndex::SeaShroom] = "SeaShroom";
  animString[AnimIndex::SelectorScreen] = "SelectorScreen";
  animString[AnimIndex::SelectorScreen_WoodSign] = "SelectorScreen_WoodSign";
  animString[AnimIndex::SlotMachine] = "SlotMachine";
  animString[AnimIndex::SnowPea] = "SnowPea";
  animString[AnimIndex::SodRoll] = "SodRoll";
  animString[AnimIndex::Spikerock] = "SpikeRock";
  animString[AnimIndex::splash] = "splash";
  animString[AnimIndex::SplitPea] = "SplitPea";
  animString[AnimIndex::Squash] = "Squash";
  animString[AnimIndex::Starfruit] = "Starfruit";
  animString[AnimIndex::StartReadySetPlant] = "StartReadySetPlant";
  animString[AnimIndex::Stinky] = "Stinky";
  animString[AnimIndex::Sun] = "Sun";
  animString[AnimIndex::SunFlower] = "SunFlower";
  animString[AnimIndex::SunShroom] = "SunShroom";
  animString[AnimIndex::Tallnut] = "Tallnut";
  animString[AnimIndex::Tanglekelp] = "Tanglekelp";
  animString[AnimIndex::TextFadeOn] = "TextFadeOn";
  animString[AnimIndex::TextSlideDown] = "TextSlideDown";
  animString[AnimIndex::TextSlideOn] = "TextSlideOn";
  animString[AnimIndex::ThreePeater] = "ThreePeater";
  animString[AnimIndex::Torchwood] = "Torchwood";
  animString[AnimIndex::TreeFood] = "TreeFood";
  animString[AnimIndex::treeofWisdom] = "treeofWisdom";
  animString[AnimIndex::TreeOfWisdomClouds] = "TreeOfWisdomClouds";
  animString[AnimIndex::TwinSunflower] = "TwinSunflower";
  animString[AnimIndex::UmbrellaLeaf] = "Umbrellaleaf";
  animString[AnimIndex::Wallnut] = "Wallnut";
  animString[AnimIndex::WinterMelon] = "WinterMelon";
  animString[AnimIndex::Z] = "Z";
  animString[AnimIndex::ZenGarden_bugspray] = "ZenGarden_bugspray";
  animString[AnimIndex::ZenGarden_fertilizer] = "ZenGarden_fertilizer";
  animString[AnimIndex::ZenGarden_phonograph] = "ZenGarden_phonograph";
  animString[AnimIndex::ZenGarden_sprout] = "ZenGarden_sprout";
  animString[AnimIndex::ZenGarden_wateringcan] = "ZenGarden_wateringcan";
  animString[AnimIndex::zombatar_zombie_head] = "zombatar_zombie_head";
  animString[AnimIndex::Zombie] = "Zombie";
  animString[AnimIndex::Zombie_balloon] = "Zombie_balloon";
  animString[AnimIndex::Zombie_bobsled] = "Zombie_bobsled";
  animString[AnimIndex::Zombie_boss] = "Zombie_boss";
  animString[AnimIndex::Zombie_Boss_driver] = "Zombie_Boss_driver";
  animString[AnimIndex::Zombie_boss_fireball] = "Zombie_boss_fireball";
  animString[AnimIndex::Zombie_boss_iceball] = "Zombie_boss_iceball";
  animString[AnimIndex::Zombie_bungi] = "Zombie_bungi";
  animString[AnimIndex::Zombie_catapult] = "Zombie_catapult";
  animString[AnimIndex::Zombie_charred] = "Zombie_charred";
  animString[AnimIndex::Zombie_charred_catapult] = "Zombie_charred_catapult";
  animString[AnimIndex::Zombie_charred_digger] = "Zombie_charred_digger";
  animString[AnimIndex::Zombie_charred_gargantuar] = "Zombie_charred_gargantuar";
  animString[AnimIndex::Zombie_charred_imp] = "Zombie_charred_imp";
  animString[AnimIndex::Zombie_charred_zamboni] = "Zombie_charred_zamboni";
  animString[AnimIndex::Zombie_credits_conehead] = "Zombie_credits_conehead";
  animString[AnimIndex::Zombie_credits_dance] = "Zombie_credits_dance";
  animString[AnimIndex::Zombie_credits_screendoor] = "Zombie_credits_screendoor";
  animString[AnimIndex::Zombie_dancer] = "Zombie_dancer";
  animString[AnimIndex::Zombie_digger] = "Zombie_digger";
  animString[AnimIndex::Zombie_disco] = "Zombie_disco";
  animString[AnimIndex::Zombie_dolphinrider] = "Zombie_dolphinrider";
  animString[AnimIndex::Zombie_flagpole] = "Zombie_flagpole";
  animString[AnimIndex::Zombie_football] = "Zombie_football";
  animString[AnimIndex::Zombie_gargantuar] = "Zombie_gargantuar";
  animString[AnimIndex::Zombie_hand] = "Zombie_hand";
  animString[AnimIndex::Zombie_imp] = "Zombie_imp";
  animString[AnimIndex::Zombie_jackbox] = "Zombie_jackbox";
  animString[AnimIndex::Zombie_Jackson] = "Zombie_Jackson";
  animString[AnimIndex::Zombie_ladder] = "Zombie_ladder";
  animString[AnimIndex::Zombie_paper] = "Zombie_paper";
  animString[AnimIndex::Zombie_pogo] = "Zombie_pogo";
  animString[AnimIndex::Zombie_PoleVaulter] = "Zombie_polevaulter";
  animString[AnimIndex::Zombie_snorkle] = "Zombie_snorkle";
  animString[AnimIndex::Zombie_surprise] = "Zombie_surprise";
  animString[AnimIndex::Zombie_Target] = "Zombie_Target";
  animString[AnimIndex::Zombie_yeti] = "Zombie_yeti";
  animString[AnimIndex::Zombie_zamboni] = "Zombie_zamboni";
  animString[AnimIndex::ZombiesWon] = "ZombiesWon";
}

void setSprite(const int entityID, const int draw) {
  if (draw == -1) {
    // spritesNormalRender.erase(entityID);
    spriteRenderIDArray.erase(entityID);
    // spriteNormalIdStopRender.push_back(entityID);
  } else if (spriteRenderIDArray.count(entityID) == 0) {
    spriteRenderIDArray.insert(entityID, 0);
    // spritesNormalRender[entityID] = &spriteArray[entityID];
  }
  // printf("plant draw: %d\n", animationArray[entityID].draw);
}

AnimationState::AnimationState() {};
AnimationState::AnimationState(const unsigned int firstFrame,
                               const unsigned int lastFrame) {
  this->firstFrame = firstFrame;
  this->lastFrame = lastFrame;
}

AnimationState animationStateVector[enumMaxAnimationState];
int maxAnimID = 0;

void loadAnimationStates() {
  animationStateVector[normalZombieWalk] = AnimationState(45, 91);
  animationStateVector[normalZombieAttack] = AnimationState(139, 178);
  animationStateVector[normalZombieCharred] = AnimationState(1, 43);
  animationStateVector[poleVaulterWalk] = AnimationState(14, 50);
  animationStateVector[explodeCherryBomb] = AnimationState(1, 8);
}

void AnimationData::loadAnimation(const int entityID, const int animID,
                                  const Tyra::Vec2 scaleTextures,
                                  enumAnimationState animationState) {
  loadAnimation(entityID, animID, scaleTextures,
                animationStateVector[animationState].firstFrame,
                animationStateVector[animationState].lastFrame);
}

void AnimationData::loadAnimation(const int entityID, const int animID, 
                                  const Tyra::Vec2 scaleTextures,
                                  const int firstFrame, const int lastFrame) {
  bool rotateSprite = false;

  for (unsigned int j = 1; j < maxFrame; j++) {
    if (angle.count(j) == true) {
      rotateSprite = true;
      createSpriteRotate(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                         Vec2(128 / 1.6f, 128 / 1.6f), Vec2(0.0f, 0.0f));
      break;
    }
  }

  if (rotateSprite == false) {
    createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                 Vec2(128 / 1.6f, 128 / 1.6f));
  }

  animationArray.insert(entityID, Animation(animID));

  animationArray[entityID].currentFrame = firstFrame;
  animationArray[entityID].firstFrame = firstFrame;
  animationArray[entityID].lastFrame = lastFrame;

  texPosArray.insert(entityID, Tyra::Vec2());

  scaleTexture[entityID] = scaleTextures;

  activeAnimation(entityID, firstFrame, lastFrame);

  // printf("termine\n\n");
}

int AnimationData::activeAnimation(const int entityID,
                                   const unsigned int firstFrame,
                                   const unsigned int lastFrame) {
  int index = 0;

  for (unsigned int i = 0; i < draw.first.size(); i++) {
    if (draw.first[i] <= firstFrame) {
      index = i;
    }
  }

  animationArray[entityID].draw = draw.second[index];
  setSprite(entityID, draw.second[index]);
  if (draw.second[index] == (int)enumDraw::noDraw) {
    return 1;
  }

  for (unsigned int i = 0; i < texture.first.size(); i++) {
    if (texture.first[i] <= firstFrame) {
      index = i;
    }
  }

  const int spriteID = spriteArray[entityID].id;
  Tyra::Texture* oldTexture = texRepo->getBySpriteId(spriteID);
  Tyra::Texture* newTexture = texRepo->getByTextureId(texture.second[index]);

  if (oldTexture != newTexture) {
    if (oldTexture != nullptr) {
      // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
      oldTexture->removeLinkById(spriteID);
    }

    // Link new Texture to the sprite entitie
    newTexture->addLink(spriteID);
    originalSize[entityID] =
        Vec2(newTexture->getWidth(), newTexture->getHeight());
  }

  for (unsigned int i = 0; i < position.first.size(); i++) {
    if (position.first[i] <= firstFrame) {
      index = i;
    }
  }

  texPosArray[entityID] = position.second[index] * scaleTexture[entityID];

  for (unsigned int i = 0; i < scale.first.size(); i++) {
    if (scale.first[i] <= firstFrame) {
      index = i;
    }
  }

  spriteArray[entityID].size = originalSize[entityID] * scaleTexture[entityID] * scale.second[index];

  for (unsigned int i = 0; i < alpha.first.size(); i++) {
    if (alpha.first[i] <= firstFrame) {
      index = i;
    }
  }

  spriteArray[entityID].color.a = alpha.second[index];

  if (angleArray.count(entityID) == 1) {
    for (unsigned int i = 0; i < angle.first.size(); i++) {
      if (angle.first[i] <= firstFrame) {
        index = i;
      }
    }

    angleArray[entityID] = angle.second[index];
  }
  // printf("anim draw: %d\n", drawState);
  return 0;
}

void AnimationData::setAnimationState(const int entityID,
                                      enumAnimationState animationState) {
  activeAnimation(entityID, animationStateVector[animationState].firstFrame,
                  animationStateVector[animationState].lastFrame);
}

void readTag(std::ifstream& MyReadFile, std::string& string, char& state) {
  if (state != '<' && state != '>') {
    // printf("error char: %c\n", state);
    state = MyReadFile.get();
  }
  // printf("char: %c\n", state);
  if (state == '<') {
    std::getline(MyReadFile, string, '>');
    state = '>';
  } else if (state == '>') {
    std::getline(MyReadFile, string, '<');
    state = '<';
  }
}

void readInfo(std::ifstream& MyReadFile, std::string& insideArrow,
              bool& useAnim, int& animID, char& state) {
  bool textureFounded = false;
  bool finish = false;

  float beforeX = -400;
  float x = 0;
  float beforeY = -400;
  float y = 0;
  float beforeKx = -400;
  float kx = 0.0f;
  float beforeKY = -400;
  float ky = 0.0f;
  float beforeSx = -400;
  float sx = 1.0f;
  float beforeSY = -400;
  float sy = 1.0f;
  float beforeA = 2.0f;
  float a = 1.0f;
  int beforeDraw = -2;
  int draw = 0;
  int countframes = 1;
  Tyra::Texture* texture = nullptr;
  std::string fileName;

  while (finish == false) {
    readTag(MyReadFile, insideArrow, state);
    if (insideArrow == "f") {
      readTag(MyReadFile, insideArrow, state);
      draw = std::stoi(insideArrow);
      // std::cout << " draw: " << draw;
    } else if (insideArrow == "i") {
      readTag(MyReadFile, insideArrow, state);
      // std::cout << " i: " << insideArrow;
      insideArrow.erase(0, 13);  // delete "IMAGE_REANIM_" from string
      insideArrow += ".png";
      for (u32 i = 0; i < texRepo->getTexturesCount(); i++) {
        if ((*texRepo->getAll())[i]->name == insideArrow) {
          textureFounded = true;
          animationDataArray[animID].texture.insert(
              countframes, (*texRepo->getAll())[i]->id);
          break;
        }
      }
      if (textureFounded == false) {
        fileName = "reanim/" + insideArrow;
        // std::cout << " new i: " << insideArrow;
        texture = loadTexture(fileName);

        animationDataArray[animID].texture.insert(countframes, texture->id);
        // printf(" texture width: %d, height: %d\n", texture->getWidth(),
        //        texture->getHeight());
      }
      textureFounded = false;
      useAnim = true;
    } else if (insideArrow == "x") {  // es la suma del x layer y el x del
                                      // simbolo(?) igual con y
      readTag(MyReadFile, insideArrow, state);
      x = std::stof(insideArrow);
      // std::cout << " X: " << x;
    } else if (insideArrow == "y") {
      readTag(MyReadFile, insideArrow, state);
      y = std::stof(insideArrow);
      // std::cout << " Y: " << y;
    } else if (insideArrow == "kx") {  // kx son los grados del angulo
      readTag(MyReadFile, insideArrow, state);
      // std::cout << " KX: " << insideArrow;
      kx = std::stof(insideArrow);
    } else if (insideArrow == "ky") {  // ky son los grados del angulo
      readTag(MyReadFile, insideArrow, state);
      // std::cout << " KY: " << insideArrow;
      ky = std::stof(insideArrow);
    } else if (insideArrow == "sx") {  // es la escala de la imagen
      readTag(MyReadFile, insideArrow, state);
      // std::cout << " SX: " << insideArrow;
      sx = std::stof(insideArrow);
    } else if (insideArrow == "sy") {  // es la escala de la imagen
      readTag(MyReadFile, insideArrow, state);
      // std::cout << " SY: " << insideArrow;
      sy = std::stof(insideArrow);
    } else if (insideArrow == "a") {
      readTag(MyReadFile, insideArrow, state);
      // std::cout << " a: " << insideArrow;
      a = std::stof(insideArrow);
    } else if (insideArrow == "t") {
      // std::cout << "Frame " << countframes << ":";
    } else if (insideArrow == "/t") {
      // std::cout << std::endl;

      if (beforeSx != sx || beforeSY != sy) {
        beforeSx = sx;
        beforeSY = sy;
        animationDataArray[animID].scale.insert(countframes,
                                                Tyra::Vec2(sx, sy));
      }

      if (beforeA != a) {
        beforeA = a;
        animationDataArray[animID].alpha.insert(countframes, a * 128);
      }

      if (beforeX != x || beforeY != y) {
        beforeX = x;
        beforeY = y;
        animationDataArray[animID].position.insert(countframes, Vec2(x, y));
      }

      if (beforeDraw != draw) {
        beforeDraw = draw;
        animationDataArray[animID].draw.insert(countframes, draw);
      }

      if (beforeKx != kx || beforeKY != ky) {
        beforeKx = kx;
        beforeKY = ky;
        animationDataArray[animID].angle.insert(countframes,
                                                Tyra::Vec2(kx, ky));
      }

      countframes++;
    } else if (insideArrow == "/track") {
      // countTrack++;
      // std::cout << "Total frames from track " << countTrack << ": "
      //           << countframes << std::endl;
      animationDataArray[animID].maxFrame = countframes - 1;
      countframes = 1;
      finish = true;
    }
  }
}

void readReanimFiles(int nameID, std::string file) {
  std::string myText;

  // Read from the text file
  std::ifstream MyReadFile(file, std::ios::binary);

  TYRA_ASSERT(MyReadFile.is_open(), "The next file could not be found:", file);

  std::string insideArrow;
  // int countTrack = 0;

  int intValue;
  int animID = -1;
  bool useAnim = true;
  char state = '0';

  while (!MyReadFile.eof()) {
    readTag(MyReadFile, insideArrow, state);
    if (insideArrow == "fps") {
      readTag(MyReadFile, insideArrow, state);

      intValue = std::stoi(insideArrow);
      // std::cout << "Los FPS son: " << intValue << std::endl;

    } else if (insideArrow == "name") {
      readTag(MyReadFile, insideArrow, state);
      // std::cout << "Name: " << insideArrow << std::endl;
      if (useAnim == true) {
        m_animID[nameID].push_back(maxAnimID);
        animID = maxAnimID;
        animationDataArray[animID] = AnimationData();
        maxAnimID++;
        useAnim = false;
      } else {
        animationDataArray[animID].draw.clear();
        animationDataArray[animID].position.clear();
        animationDataArray[animID].scale.clear();
        animationDataArray[animID].angle.clear();
        animationDataArray[animID].alpha.clear();
        // printf("borre la memoria\n");
      }
      animationDataArray[animID].name = insideArrow;

      // std::cout << "animID: " << animID << std::endl;
      readInfo(MyReadFile, insideArrow, useAnim, animID, state);
    }
  }
  // Close the file
  MyReadFile.close();
}

void loadAnimation(const AnimIndex::Animation animNameID) {
  readReanimFiles(animNameID,
                  Tyra::FileUtils::fromCwd("reanim/" + animString[animNameID] + ".reanim"));
}
