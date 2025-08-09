#include "PVZ.hpp"
#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include <iostream>


std::string animString[AnimIndex::enumMax];

void loadAnimString() {
  angleFrame.push_back(Tyra::Vec2(0,0));
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
  animString[AnimIndex::Zombie_charred_gargantuar] =
      "Zombie_charred_gargantuar";
  animString[AnimIndex::Zombie_charred_imp] = "Zombie_charred_imp";
  animString[AnimIndex::Zombie_charred_zamboni] = "Zombie_charred_zamboni";
  animString[AnimIndex::Zombie_credits_conehead] = "Zombie_credits_conehead";
  animString[AnimIndex::Zombie_credits_dance] = "Zombie_credits_dance";
  animString[AnimIndex::Zombie_credits_screendoor] =
      "Zombie_credits_screendoor";
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
  if (spriteRenderIDArray.count(entityID) == 1 && draw == -1) {
    // spritesNormalRender.erase(entityID);
    spriteRenderIDArray.erase(entityID);
    // spriteNormalIdStopRender.push_back(entityID);
  } else if (spriteRenderIDArray.count(entityID) == 0 && draw == 0) {
    spriteRenderIDArray.insert(entityID, 0);
    int renderSize = spriteRenderIDArray.first.size();
    for(int j=renderSize-1;j>1;j--){
      if(spriteRenderIDArray.first[j] < spriteRenderIDArray.first[j-1]){         
        int aux= spriteRenderIDArray.first[j];
        spriteRenderIDArray.first[j] = spriteRenderIDArray.first[j-1];
        spriteRenderIDArray.first[j-1] = aux;
      }
    }
  }
  // printf("plant draw: %d\n", animationArray[entityID].draw);
}

AnimationState::AnimationState(){};
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
  bool hasRotation = false;                                  
  unsigned int dataSize;
  for(unsigned int i=1;i<=maxFrame;i++){
    std::vector<AnimationProperty>& animProp = property[i];
    dataSize = animProp.size();
    for(unsigned int j=0;j<dataSize;j++){
      // printf("test animID:%d i:%d j:%d type:%d\n",animID,i,j,animProp[j].type);
      if(animProp[j].type == ANIM_ROTATION){
        i=maxFrame;
        hasRotation = true;
        break;
      }
    }
  }

  if(hasRotation == true){
    // printf("crear rotate\n");
    createSpriteRotate(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                         Vec2(128 / 1.6f, 128 / 1.6f), Vec2(0.0f, 0.0f));
  }else {
    createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                 Vec2(128 / 1.6f, 128 / 1.6f));
  }

  FrameCounter frameCounter;
  frameCounter.entityID = entityID;
  frameCounter.currentFrame = firstFrame;
  frameCounter.firstFrame = firstFrame;
  frameCounter.lastFrame = lastFrame;
  frameCounter.animIndex = animID;
  frameCounterArray.push_back(frameCounter);

  texPosArray.insert(entityID, Tyra::Vec2());

  scaleTexture[entityID] = scaleTextures;

  activeAnimation(entityID, firstFrame, lastFrame);

  // printf("termine\n\n");
}

std::vector<int> textureFrame;
std::vector<Tyra::Vec2> positionFrame;
std::vector<Tyra::Vec2> scaleFrame;
std::vector<Tyra::Vec2> angleFrame;
std::vector<float> alphaFrame;
std::vector<int> drawFrame;

int AnimationData::activeAnimation(const int entityID,
                                   const unsigned int firstFrame,
                                   const unsigned int lastFrame) {
  bool drawPropertyFounded = false;
  bool scalePropertyFounded = false;
  bool posPropertyFounded = false;
  bool alphaPropertyFounded = false;
  bool texturePropertyFounded = false;
  bool anglePropertyFounded = false;
  int scaleIndex = -1;
  int textureIndex = -1;
  int posIndex = -1;
  unsigned int dataSize;
  
  // printf("textureFrame size:%d\n",textureFrame.size());
  // printf("textureFrame[0] size:%d\n",textureFrame[0].size());

  int counter = firstFrame;
  while ((texturePropertyFounded == false || posPropertyFounded == false) && counter > 0){
    std::vector<AnimationProperty>& animProp = property[counter];
    dataSize = animProp.size();
    //  printf("start entity: %d, Frame: %d\n",entityID,counter);
    for(unsigned int i=0; i<dataSize;i++){
      if(animProp[i].type == ANIM_POSITION && posPropertyFounded == false){
        posPropertyFounded = true;
        posIndex = animProp[i].dataIndex;
      }else if(animProp[i].type == ANIM_TEXTURE && texturePropertyFounded == false){
        texturePropertyFounded = true;
        textureIndex = animProp[i].dataIndex;
      }else if(animProp[i].type == ANIM_SCALE && scalePropertyFounded == false){
        scalePropertyFounded = true;
        scaleIndex = animProp[i].dataIndex;
      }else if(animProp[i].type == ANIM_ROTATION && anglePropertyFounded == false){
        anglePropertyFounded = true;
        angleArray[entityID] = angleFrame[animProp[i].dataIndex];
      }else if(animProp[i].type == ANIM_ALPHA && alphaPropertyFounded == false){
        alphaPropertyFounded = true;
        spriteArray[entityID].color.a = alphaFrame[animProp[i].dataIndex];
      }else if (animProp[i].type == ANIM_DRAW && drawPropertyFounded == false){
        drawPropertyFounded = true;
        // printf("draw: %d\n",drawFrame[animProp[i].dataIndex]);
        setSprite(entityID,drawFrame[animProp[i].dataIndex]);
      }
    }
    
    counter--;
  }

  texPosArray[entityID] = positionFrame[posIndex] * scaleTexture[entityID];

  Tyra::Texture* oldTexture = texRepo->getByTextureId(spriteArray[entityID].textureID);
  Tyra::Texture* newTexture = texRepo->getByTextureId(textureFrame[textureIndex]);

  if (oldTexture != newTexture) {
    // printf("texture id: %d\n",newTexture->id);
    // printf("linking sprite id\n");
    if(newTexture != nullptr){
      // Link new Texture to the sprite entitie

      spriteArray[entityID].textureID = newTexture->id;
      originalSize[entityID] =
          Vec2(newTexture->getWidth(), newTexture->getHeight());

    }
  }

  spriteArray[entityID].size = 
          originalSize[entityID] * scaleTexture[entityID] * scaleFrame[scaleIndex];

  if(anglePropertyFounded == false){
    angleArray[entityID] = Vec2(0,0);
  }

  return 0;
}

void AnimationData::setAnimationState(const int entityID,
                                      enumAnimationState animationState) {
  activeAnimation(entityID, animationStateVector[animationState].firstFrame,
                  animationStateVector[animationState].lastFrame);
}

void readTag(char* line, std::string& string, int& indexText) {
  // printf("start\n");
  // printf("line: %s\n",line);
  // printf("indexText: %d: %c\n",indexText,line[indexText] );
  string.clear();
  if(line[indexText] == '<'){
    indexText++;
    while(line[indexText] != '>'){
      string += line[indexText];
      indexText++;
    }
  }else if(line[indexText] == '>'){
    indexText++;
    while(line[indexText] != '<'){
      string += line[indexText];
      indexText++;
    }
  }
  // printf("val: %s\n",string.c_str());
}

void readInfo(FILE* MyReadFile, char* textLine, std::string& insideArrow,
              bool& useAnim, int& animID, int& indexText) {
  bool textureFounded = false;
  bool finish = false;

  float beforeX = -400;
  float x = 0;
  float beforeY = -400;
  float y = 0;
  float beforeKx = 0;
  float kx = 0.0f;
  float beforeKY = 0;
  float ky = 0.0f;
  float beforeSx = -400;
  float sx = 1.0f;
  float beforeSY = -400;
  float sy = 1.0f;
  float beforeA = 2.0f;
  float a = 1.0f;
  int beforeDraw = -2;
  int draw = 0;
  unsigned int countframes = 1;
  Tyra::Texture* texture = nullptr;
  std::string fileName;
  AnimationProperty property;
  bool hasRotation = false;

  indexText = 0;
  fgets(textLine, 512, MyReadFile);
  while (finish == false) {
    readTag(textLine, insideArrow, indexText);
    if (insideArrow == "f") {
      readTag(textLine, insideArrow, indexText);
      draw = std::stoi(insideArrow);
      // std::cout << " draw: " << draw;
    } else if (insideArrow == "i") {
      readTag(textLine, insideArrow, indexText);
      // std::cout << " i: " << insideArrow;
      insideArrow.erase(0, 13);  // delete "IMAGE_REANIM_" from string
      insideArrow += ".png";
      for (u32 i = 0; i < texRepo->getTexturesCount(); i++) {
        if ((*texRepo->getAll())[i]->name == insideArrow) {
          textureFounded = true;

          textureFrame.push_back((*texRepo->getAll())[i]->id);
          property.dataIndex = textureFrame.size()-1;
          property.type = EnumAnimationProperty::ANIM_TEXTURE;
          animationDataArray[animID].property[countframes].push_back(property);
          // printf("texture id: %d, type: %d, data:%d\n",(*texRepo->getAll())[i]->id,property.type,property.dataIndex);
          break;
        }
      }
      if (textureFounded == false) {
        fileName = "reanim/" + insideArrow;
        // std::cout << " new i: " << insideArrow;
        texture = loadTexture(fileName);
        
        textureFrame.push_back(texture->id);
        property.dataIndex = textureFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_TEXTURE;
        animationDataArray[animID].property[countframes].push_back(property);
        // printf("texture id: %d, type: %d, data:%d\n",texture->id,property.type,property.dataIndex);
        // printf("framesData animID: %d, frame: %d\n",framesData.animID,framesData.frame);
        // // printf(" texture width: %d, height: %d\n", texture->getWidth(),
        // //        texture->getHeight());
      }
      textureFounded = false;
      useAnim = true;
    } else if (insideArrow == "x") {  // es la suma del x layer y el x del
                                      // simbolo(?) igual con y
      readTag(textLine, insideArrow, indexText);
      x = std::stof(insideArrow);
      // std::cout << " X: " << x;
    } else if (insideArrow == "y") {
      readTag(textLine, insideArrow, indexText);
      y = std::stof(insideArrow);
      // std::cout << " Y: " << y;
    } else if (insideArrow == "kx") {  // kx son los grados del angulo
      readTag(textLine, insideArrow, indexText);
      // std::cout << " KX: " << insideArrow;
      kx = std::stof(insideArrow);
    } else if (insideArrow == "ky") {  // ky son los grados del angulo
      readTag(textLine, insideArrow, indexText);
      // std::cout << " KY: " << insideArrow;
      ky = std::stof(insideArrow);
    } else if (insideArrow == "sx") {  // es la escala de la imagen
      readTag(textLine, insideArrow, indexText);
      // std::cout << " SX: " << insideArrow;
      sx = std::stof(insideArrow);
    } else if (insideArrow == "sy") {  // es la escala de la imagen
      readTag(textLine, insideArrow, indexText);
      // std::cout << " SY: " << insideArrow;
      sy = std::stof(insideArrow);
    } else if (insideArrow == "a") {
      readTag(textLine, insideArrow, indexText);
      // std::cout << " a: " << insideArrow;
      a = std::stof(insideArrow);
    } else if (insideArrow == "t") {
      // std::cout << "Frame " << countframes << ":";
    } else if (insideArrow == "/t") {
      // std::cout << std::endl;

      if (beforeSx != sx || beforeSY != sy) {
        // if(countframes-1 >= scaleFrame.size()){
        //   std::vector<FramesData> data;
        //   scaleFrame.push_back(data);
        // }
        beforeSx = sx;
        beforeSY = sy;
        scaleFrame.push_back(Tyra::Vec2(sx, sy));
        property.dataIndex = scaleFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_SCALE;
        animationDataArray[animID].property[countframes].push_back(property);
        // framesData.animID = animID;
        // framesData.frame = animationDataArray[animID].scale.size();
        // animationDataArray[animID].scale.push_back(Tyra::Vec2(sx, sy));
        // scaleFrame[countframes-1].push_back(framesData);
        // animVec2.data.x = sx;
        // animVec2.data.y = sy;
        // animVec2.frame = countframes;
        // animationDataArray[animID].scale.push_back(animVec2);
        // animationDataArray[animID].scale.insert(countframes,
        //                                         Tyra::Vec2(sx, sy));
      }

      if (beforeA != a) {
        beforeA = a;
        alphaFrame.push_back(a*128);
        property.dataIndex = alphaFrame.size() - 1;
        property.type = ANIM_ALPHA;
        animationDataArray[animID].property[countframes].push_back(property);
        // printf("frame: %d, dataIndex:%d, data: %f\n",countframes,property.dataIndex,a);
      }

      if (beforeX != x || beforeY != y) {
        beforeX = x;
        beforeY = y;
        positionFrame.push_back(Tyra::Vec2(x, y));
        property.dataIndex = positionFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_POSITION;
        animationDataArray[animID].property[countframes].push_back(property);
      }

      if (beforeDraw != draw) {
        beforeDraw = draw;
        drawFrame.push_back(draw);
        property.dataIndex = drawFrame.size()-1;
        property.type = ANIM_DRAW;
        animationDataArray[animID].property[countframes].push_back(property);
        // printf("frame: %d, data: %d\n",countframes,draw);
        // animInt.data = draw;
        // animInt.frame = countframes;
        // animationDataArray[animID].draw.push_back(animInt);
        // animationDataArray[animID].draw.insert(countframes, draw);
      }

      if (beforeKx != kx || beforeKY != ky) {
        beforeKx = kx;
        beforeKY = ky;
        angleFrame.push_back(Tyra::Vec2(kx, ky));
        property.dataIndex = angleFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_ROTATION;
        animationDataArray[animID].property[countframes].push_back(property);
        hasRotation = true;
        // printf("animID: %d, frame:%d, type:%d, index:%d\n",animID,countframes,property.type,property.dataIndex);
      }

      countframes++;
      
      indexText = 0;
      fgets(textLine, 512, MyReadFile);
    } else if (insideArrow == "/track") {
      // countTrack++;
      // std::cout << "Total frames from track " << countTrack << ": "
      //           << countframes << std::endl;
      
      if(hasRotation == true){
        bool hasRotationProperty = false;
        for(unsigned int i=0;i<animationDataArray[animID].property[1].size();i++){
          if(animationDataArray[animID].property[1][i].type == ANIM_ROTATION){
            hasRotationProperty = true;
            break;
          }
        }
        if(hasRotationProperty == false){
          // printf("cree rotacion propiedad\n");
          property.dataIndex = 0;
          property.type = ANIM_ROTATION;
          animationDataArray[animID].property[1].push_back(property);
        }
      }
       
      animationDataArray[animID].maxFrame = countframes - 1;
      countframes = 1;
      finish = true;
    }
  }
}

void readReanimFiles(int nameID, std::string file){
  std::string myText;

  // Read from the text file
  FILE* MyReadFile;
  MyReadFile = fopen(file.c_str(), "rb");

  TYRA_ASSERT(MyReadFile != NULL, "The next file could not be found:", file);

  std::string insideArrow;
  // int countTrack = 0;

  int intValue;
  int animID = -1;
  bool useAnim = true;
  int indexText = 0;
  char text [512];

  while (fgets (text , 512 , MyReadFile) != NULL) {
    indexText = 0;
    readTag(text, insideArrow, indexText);
    if (insideArrow == "fps") {
      readTag(text, insideArrow, indexText);

      intValue = std::stoi(insideArrow);
      // std::cout << "Los FPS son: " << intValue << std::endl;

    } else if (insideArrow == "name") {
      readTag(text, insideArrow, indexText);
      // std::cout << "Name: " << insideArrow << std::endl;
      if (useAnim == true) {
        m_animID[nameID].push_back(maxAnimID);
        animID = maxAnimID;
        animationDataArray[animID] = AnimationData();
        maxAnimID++;
        useAnim = false;
      }else{
        animationDataArray[animID].property.clear();
      }
      // printf("inside arrow: %s\n",insideArrow.c_str());
      int size = insideArrow.size()+1;
      char* name = (char*) malloc(size*sizeof(char));
      strcpy(name, insideArrow.c_str());
      animationDataArray[animID].name = name;
      // std::cout << "animID: " << animID << std::endl;
      readInfo(MyReadFile, text, insideArrow, useAnim, animID, indexText);
    }
  }
  // Close the file
  fclose(MyReadFile);
}

void loadAnimation(const AnimIndex::Animation animNameID) {
  readReanimFiles(
      animNameID,
      Tyra::FileUtils::fromCwd("reanim/" + animString[animNameID] + ".reanim"));
}
void SetOneSpriteAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, int frame){
  size_t animSize = m_animID[anim].size() + ids.size();
  int entityID = -1;
  int animID;
  bool hasRotation;                                  
  unsigned int dataSize;
  bool drawPropertyFounded = false;
  bool scalePropertyFounded = false;
  bool posPropertyFounded = false;
  bool alphaPropertyFounded = false;
  bool texturePropertyFounded = false;
  bool anglePropertyFounded = false;
  int scaleIndex = -1;
  int textureIndex = -1;
  int posIndex = -1;
  for (size_t i = ids.size(); i < animSize; i++) {
    ids.push_back(Entities::newID());
    entityID = ids[i];
    printf("entityID: %d\n",entityID);
    animID = m_animID[anim][i];

    newFatherID(&father, &ids[i]);
    scaleTexture[entityID] = size;
    
    // hasRotation = false;

    // for(unsigned int j=1;j<=animationDataArray[animID].maxFrame;j++){
    //   std::vector<AnimationProperty>& animProp = animationDataArray[animID].property[j];
    //   dataSize = animProp.size();
    //   for(unsigned int k=0;k<dataSize;k++){
    //     // printf("test animID:%d i:%d j:%d type:%d\n",animID,i,j,animProp[j].type);
    //     if(animProp[k].type == ANIM_ROTATION){
    //       j=animationDataArray[animID].maxFrame;
    //       hasRotation = true;
    //       break;
    //     }
    //   }
    // }

    // if(hasRotation == true){
      createSpriteRotate(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                          Vec2(128 / 1.6f, 128 / 1.6f), Vec2(0.0f, 0.0f));
    // }else {
    //   createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
    //               Vec2(128 / 1.6f, 128 / 1.6f));
    // }
    
    texPosArray.insert(entityID, Tyra::Vec2());

    drawPropertyFounded = false;
    scalePropertyFounded = false;
    posPropertyFounded = false;
    alphaPropertyFounded = false;
    texturePropertyFounded = false;
    anglePropertyFounded = false;
    scaleIndex = -1;
    textureIndex = -1;
    posIndex = -1;
  
    int counter = frame;
    while ((texturePropertyFounded == false || posPropertyFounded == false || anglePropertyFounded == false) && counter > 0){
      std::vector<AnimationProperty>& animProp = animationDataArray[animID].property[counter];
      dataSize = animProp.size();
      // printf("start entity: %d, Frame: %d\n",entityID,counter);
      for(unsigned int j=0; j<dataSize;j++){
        if(animProp[j].type == ANIM_POSITION && posPropertyFounded == false){
          posPropertyFounded = true;
          posIndex = animProp[j].dataIndex;
        }else if(animProp[j].type == ANIM_TEXTURE && texturePropertyFounded == false){
          texturePropertyFounded = true;
          textureIndex = animProp[j].dataIndex;
        }else if(animProp[j].type == ANIM_SCALE && scalePropertyFounded == false){
          scalePropertyFounded = true;
          scaleIndex = animProp[j].dataIndex;
        }else if(animProp[j].type == ANIM_ROTATION && anglePropertyFounded == false){
          anglePropertyFounded = true;
          angleArray[entityID] = angleFrame[animProp[j].dataIndex];
        }else if(animProp[j].type == ANIM_ALPHA && alphaPropertyFounded == false){
          alphaPropertyFounded = true;
          spriteArray[entityID].color.a = alphaFrame[animProp[j].dataIndex];
        }else if (animProp[j].type == ANIM_DRAW && drawPropertyFounded == false){
          drawPropertyFounded = true;
          // printf("draw: %d\n",drawFrame[animProp[j].dataIndex]);
          setSprite(entityID,drawFrame[animProp[j].dataIndex]);
        }
      }
      
      counter--;
    }                             
    texPosArray[entityID] = positionFrame[posIndex] * scaleTexture[entityID]; 

    const int spriteID = spriteArray[entityID].id;
    Tyra::Texture* oldTexture = texRepo->getBySpriteId(spriteID);
    Tyra::Texture* newTexture = texRepo->getByTextureId(textureFrame[textureIndex]);
    
    if (oldTexture != newTexture) {
      // printf("texture id: %d\n",newTexture->id);
      // printf("linking sprite id\n");
      // Link new Texture to the sprite entitie
      spriteArray[entityID].textureID = newTexture->id;
      originalSize[entityID] =
          Vec2(newTexture->getWidth(), newTexture->getHeight());

    }

    spriteArray[entityID].size = 
            originalSize[entityID] * scaleTexture[entityID] * scaleFrame[scaleIndex];
  }
}

void SetAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, int firstFrame, int lastFrame){
  size_t animSize = m_animID[anim].size();
  int entityID = -1;
  int animID;
  for (size_t i = 0; i < animSize; i++) {
    ids.push_back(Entities::newID());

    entityID = ids[i];
    animID = m_animID[anim][i];

    newFatherID(&father, &ids[i]);
    animationDataArray[animID].loadAnimation(entityID, animID, size, firstFrame, lastFrame);
  }
}

void SetAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, enumAnimationState animState){
  size_t animSize = m_animID[anim].size();
  int entityID = -1;
  int animID;
  for (size_t i = 0; i < animSize; i++) {
    ids.push_back(Entities::newID());

    entityID = ids[i];
    animID = m_animID[anim][i];

    newFatherID(&father, &ids[i]);
    animationDataArray[animID].loadAnimation(entityID, animID, size, animationStateVector[animState].firstFrame, animationStateVector[animState].lastFrame);

  }
}

void SetAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, int firstFrame){
  size_t animSize = m_animID[anim].size();
  int entityID = -1;
  int animID;
  for (size_t i = 0; i < animSize; i++) {
    ids.push_back(Entities::newID());

    entityID = ids[i];
    animID = m_animID[anim][i];

    newFatherID(&father, &ids[i]);
    animationDataArray[animID].loadAnimation(entityID, animID, size, firstFrame,animationDataArray[animID].maxFrame);
  }
}

void ChangeAnimationEntity(std::vector<int>& ids, AnimIndex::Animation anim, enumAnimationState animState){
  unsigned int frameIndex = frameCounterArray.size();
  for(size_t i=0;i<frameCounterArray.size();i++){
    if(frameCounterArray[i].entityID == ids[0]){
      frameIndex = i;
      break;
    }
  }

  if(frameIndex == frameCounterArray.size()){
    return;
  }

  size_t size = frameIndex+ids.size();
  for(size_t i=frameIndex; i < size; i++){
    frameCounterArray[i].currentFrame = animationStateVector[animState].firstFrame;
    frameCounterArray[i].firstFrame = frameCounterArray[i].currentFrame;
    frameCounterArray[i].lastFrame = animationStateVector[animState].lastFrame;
  }
  
  std::vector<int>& anim_2 = m_animID[anim];
  for(size_t i=0; i< anim_2.size();i++){
    animationDataArray[anim_2[i]].activeAnimation(ids[i],animationStateVector[animState].firstFrame,animationStateVector[animState].lastFrame);
  }
  
  //TODO: esto debe estar separado para las animaciones de los zombies
  if(anim == AnimIndex::Zombie){
    for(size_t i=0; i< anim_2.size();i++){
      SetZombieAnimation(ids[i],anim_2[i],Zombie_State_enum::normalZombie);
    }
  }
}