#include "PVZ.hpp"
#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include <iostream>

AnimIndex animComponent[EnumAnimationIndex::ANIM_enumMax];
std::string animString[EnumAnimationIndex::ANIM_enumMax];
AnimationClip animClips[EnumAnimationIndex::ANIM_enumMax]; // animClips[animIndex]
AnimationClipData animClipLayers[EnumAnimationIndex::ANIM_enumMax]; // animClipLayers[animIndex][layerIndex].layerID
std::vector<AnimationLayerNameData> animLayerNames[EnumAnimationIndex::ANIM_enumMax]; // animLayerNames[animIndex][layerIndex]
std::vector<AnimationLayerData> animLayerFrames; // animLayerFrames[layerIndex][frame][prop].type

std::vector<int> backgroundLayer;
std::vector<int> cardLayer;
std::vector<int> plantsLayer;
std::vector<int> projectileLayer;
std::vector<int> sunLayer;
std::vector<int> zombieLayer;
std::vector<int> playerLayer;


unsigned int AnimIndex::GetNameID(unsigned int layer){
  return animClipLayers[type][layer].nameID;
}

unsigned int AnimIndex::GetLayerID(unsigned int layer){
  return animClipLayers[type][layer].layerDataID;
}

unsigned int AnimIndex::GetLayerSize(){
  return animClips[type].layerCount;
}

unsigned int AnimIndex::GetAnimationNameID(const char* layer){
  std::vector<AnimationLayerNameData>& layerNames = animLayerNames[type];
  size_t size = layerNames.size();
  for(size_t i=0; i < size;i++){
    // printf("layer: %d, name: %s\n",i,layerNames[i][0]);
    if(strcmp(layer, layerNames[i][0]) == 0){
      return i;
    }
  }
  TYRA_TRAP("ANIMATION NAME NOT FOUND");
  return size;
}


AnimationFrameData& AnimIndex::GetFrameProperties(unsigned int layer, unsigned int frame){
  unsigned int layerIndex = animClipLayers[type][layer].layerDataID;
  return animLayerFrames[layerIndex][frame];
}

void AnimIndex::createAnimation(const int entityID, const int animlayerID,
                                  const Tyra::Vec2 scaleTextures,
                                  const int firstFrame, const int lastFrame, bool repeat, enumSpriteLayer layer) {
  unsigned int maxFrame = animClips[type].maxFrame;

  bool hasRotation = false;
  bool hasImage = false;                                  
  unsigned int dataSize;
  for(unsigned int i=1;i<=maxFrame;i++){
    std::vector<FrameProperty>& animProp = GetFrameProperties(animlayerID,i);
    dataSize = animProp.size();
    for(unsigned int j=0;j<dataSize;j++){
      // printf("test animID:%d animLayer:%d i:%d j:%d type:%d\n",type,animlayerID,i,j,animProp[j].type);
      if(animProp[j].type == ANIM_ROTATION){
        hasRotation = true;
      }else if(animProp[j].type == ANIM_TEXTURE){
        hasImage = true;
      }
    }
  }

  // aca se creaun bug porque tiene que crear la rotacion pero no tiene imagen
  if(hasImage == true){
    if(hasRotation == true){
      // printf("crear rotate\n");
      createSpriteRotate(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                          Vec2(128 / 1.6f, 128 / 1.6f), Vec2(0.0f, 0.0f), layer);
    }else {
      createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                  Vec2(128 / 1.6f, 128 / 1.6f), layer);
    }
  }else{
    finalPosArray.insert(entityID, Vec2(0.0f, 0.0f));
    posArray.insert(entityID, Vec2(0.0f,0.0f));
    if(hasRotation == true){
      angleArray.insert(entityID, Vec2(0.0f,0.0f));
    }
  }

  FrameCounter frameCounter;
  frameCounter.entityID = entityID;
  frameCounter.currentFrame = firstFrame;
  frameCounter.firstFrame = firstFrame;
  frameCounter.lastFrame = lastFrame;
  frameCounter.animIndex = type;
  frameCounter.layerIndex = animlayerID;
  frameCounter.repeat = repeat;
  frameCounterArray.push_back(frameCounter);
  // printf("fisrt frame: %d last: %d\n",frameCounter.firstFrame,frameCounter.lastFrame);

  texPosArray.insert(entityID, Tyra::Vec2());

  scaleTexture[entityID] = scaleTextures;

  activeAnimation(entityID, animlayerID, firstFrame, lastFrame, layer);

  // printf("termine\n\n");
}


int AnimIndex::activeAnimation(const int entityID, const int layerID,
                                   const unsigned int firstFrame,
                                   const unsigned int lastFrame, enumSpriteLayer layer) {
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
    std::vector<FrameProperty>& animProp = GetFrameProperties(layerID,counter);
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
        if(spriteArray.count(entityID) == 1){
          spriteArray[entityID].color.a = alphaFrame[animProp[i].dataIndex];
        }
      }else if (animProp[i].type == ANIM_DRAW && drawPropertyFounded == false){
        drawPropertyFounded = true;
        // printf("draw: %d\n",drawFrame[animProp[i].dataIndex]);
        setSprite(entityID,drawFrame[animProp[i].dataIndex], layer);
      }
    }
    
    counter--;
  }

  texPosArray[entityID] = positionFrame[posIndex] * scaleTexture[entityID];

  if(spriteArray.count(entityID) == 1){
    Tyra::Texture* oldTexture = texRepo->getByTextureId(spriteArray[entityID].textureID);
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

  if(anglePropertyFounded == false){
    angleArray.insert(entityID, Vec2(0.0f,0.0f));
  }

  return 0;
}

FrameProperties AnimIndex::GetPropertiesFromOneFrame(unsigned int layerIndex, unsigned int frame) {
  FrameProperties properties;
  int counter = frame;
  size_t dataSize;
  while ((properties.textureIndex == 0 || properties.posIndex == 0 || properties.angleIndex == 0) && counter > 0){
    std::vector<FrameProperty>& animProp = GetFrameProperties(layerIndex,counter);
    dataSize = animProp.size();
    for(unsigned int j=0; j<dataSize;j++){
      switch (animProp[j].type){
        case ANIM_TEXTURE:
          if(properties.textureIndex == 0){
            properties.textureIndex = counter;
          }
          break;
        case ANIM_POSITION:
          if(properties.posIndex == 0){
            properties.posIndex = counter;
          }
          break;
        case ANIM_ROTATION:
          if(properties.angleIndex == 0){
            properties.angleIndex = counter;
          }
          break;
        case ANIM_SCALE:
          if(properties.scaleIndex == 0){
            properties.scaleIndex = counter;
          }
          break;
        case ANIM_ALPHA:
          if(properties.alphaIndex == 0){
            properties.alphaIndex = counter;
          }
          break;
        case ANIM_DRAW:
          if(properties.drawIndex == 0){
            properties.drawIndex = counter;
          }
          break;
        default:
          break;
      }
    }
    
    counter--;
  }
  return properties;
}



void AnimIndex::SetOneSpriteAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, int frame, enumSpriteLayer layer){
  size_t animSize = GetLayerSize();
  int entityID = -1;           
  unsigned int dataSize;
  int scaleIndex = -1;
  int textureIndex = -1;
  int posIndex = -1;
  int angleIndex = -1;
  bool alphaFound = false;
  bool drawFound = false;
  // printf("animacion ID:%d\n",type);
  // printf("animacion layer size:%d\n",animSize);
  for (size_t i = 0; i < animSize; i++) {
    entityID = Entities::newID();
    newFatherID(&father, &entityID);
    // printf("entityID:%d\n",entityID);
    scaleTexture[entityID] = size;

    scaleIndex = -1;
    textureIndex = -1;
    posIndex = -1;
    angleIndex = -1;
    alphaFound = false;
    drawFound = false;

    createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                                Vec2(128 / 1.6f, 128 / 1.6f), layer);
    texPosArray.insert(entityID, Tyra::Vec2());

    // FrameProperties properties = GetPropertiesFromOneFrame(i,frame);
    
    // std::vector<FrameProperty> animProp = GetFrameProperties(i,properties.alphaIndex);
    // dataSize = animProp.size();
    // for(unsigned int j=0; j<dataSize;j++){

    // }
    int counter = frame;
    while ((textureIndex == -1 || posIndex == -1 || angleIndex == -1) && counter > 0){
      std::vector<FrameProperty>& animProp = GetFrameProperties(i,counter);
      dataSize = animProp.size();
      for(unsigned int j=0; j<dataSize;j++){
        switch (animProp[j].type){
          case ANIM_TEXTURE:
            if(textureIndex == -1){
              textureIndex = animProp[j].dataIndex;
              // printf("found tex: %d\n",textureIndex);
            }
            break;
          case ANIM_POSITION:
            if(posIndex == -1){
              if(posArray.count(entityID) == false){
                posArray.insert(entityID,Tyra::Vec2(0,0));
                finalPosArray.insert(entityID,Tyra::Vec2(0,0));
              }
              posIndex = animProp[j].dataIndex;
            }
            break;
          case ANIM_ROTATION:
            if(angleIndex == -1){
              angleIndex = 0;
              if(angleArray.count(entityID) == false){
                angleArray.insert(entityID,Tyra::Vec2(0,0));
              }
              angleArray[entityID] = angleFrame[animProp[j].dataIndex];;
            }
            break;
          case ANIM_SCALE:
            if(scaleIndex == -1){
              scaleIndex = animProp[j].dataIndex;
            }
            break;
          case ANIM_ALPHA:
            if(alphaFound == false && spriteArray.count(entityID) == 1){
              alphaFound = true;
              spriteArray[entityID].color.a = alphaFrame[animProp[j].dataIndex];
            }
            break;
          case ANIM_DRAW:
            if(drawFound == false){
              drawFound = true;
              // printf("draw data: %d, frame:%d\n",drawFrame[animProp[j].dataIndex], counter);
              setSprite(entityID,drawFrame[animProp[j].dataIndex], layer);
            }
            break;
          default:
            break;
        }
      }
      
      counter--;
    }

    // printf("drawFound: %d\n",drawFound);
    // if(spriteRenderIDArray.count(entityID) == false){
    //   printf("no se dibuja: %d\n",entityID);
    // }else{
    //   printf("se dibuja: %d\n",entityID);
    // }

    if(spriteArray.count(entityID) == 1){
      // printf("textureIndex: %d\n",textureIndex);
      if(textureIndex != -1){
        texPosArray[entityID] = positionFrame[posIndex] * scaleTexture[entityID]; 

        const int oldTextureID = spriteArray[entityID].textureID;
        Tyra::Texture* oldTexture = texRepo->getByTextureId(oldTextureID);
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
      }else{
        deleteSprite(entityID);
        deleteTexPosArray(entityID);
      }
      
    }
  
    ids.push_back(entityID);
  }
}
void AnimIndex::SetOneSpriteAnimationToEntity(std::vector<int>& ids, Tyra::Vec2 size, int frame, enumSpriteLayer layer){
  size_t animSize = GetLayerSize();
  int entityID = -1;           
  unsigned int dataSize;
  int scaleIndex = -1;
  int textureIndex = -1;
  int posIndex = -1;
  int angleIndex = -1;
  bool alphaFound = false;
  bool drawFound = false;
  // printf("animacion ID:%d\n",type);
  // printf("animacion layer size:%d\n",animSize);
  for (size_t i = 0; i < animSize; i++) {
    entityID = Entities::newID();
    // printf("entityID:%d\n",entityID);
    scaleTexture[entityID] = size;

    scaleIndex = -1;
    textureIndex = -1;
    posIndex = -1;
    angleIndex = -1;
    alphaFound = false;
    drawFound = false;

    createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                                Vec2(128 / 1.6f, 128 / 1.6f), layer);
    texPosArray.insert(entityID, Tyra::Vec2());

    // FrameProperties properties = GetPropertiesFromOneFrame(i,frame);
    
    // std::vector<FrameProperty> animProp = GetFrameProperties(i,properties.alphaIndex);
    // dataSize = animProp.size();
    // for(unsigned int j=0; j<dataSize;j++){

    // }
    int counter = frame;
    while ((textureIndex == -1 || posIndex == -1 || angleIndex == -1) && counter > 0){
      std::vector<FrameProperty>& animProp = GetFrameProperties(i,counter);
      dataSize = animProp.size();
      for(unsigned int j=0; j<dataSize;j++){
        switch (animProp[j].type){
          case ANIM_TEXTURE:
            if(textureIndex == -1){
              textureIndex = animProp[j].dataIndex;
            }
            break;
          case ANIM_POSITION:
            if(posIndex == -1){
              if(posArray.count(entityID) == false){
                posArray.insert(entityID,Tyra::Vec2(0,0));
                finalPosArray.insert(entityID,Tyra::Vec2(0,0));
              }
              posIndex = animProp[j].dataIndex;
            }
            break;
          case ANIM_ROTATION:
            if(angleIndex == -1){
              angleIndex = 0;
              if(angleArray.count(entityID) == false){
                angleArray.insert(entityID,Tyra::Vec2(0,0));
              }
              angleArray[entityID] = angleFrame[animProp[j].dataIndex];;
            }
            break;
          case ANIM_SCALE:
            if(scaleIndex == -1){
              scaleIndex = animProp[j].dataIndex;
            }
            break;
          case ANIM_ALPHA:
            if(alphaFound == false && spriteArray.count(entityID) == 1){
              alphaFound = true;
              spriteArray[entityID].color.a = alphaFrame[animProp[j].dataIndex];
            }
            break;
          case ANIM_DRAW:
            if(drawFound == false){
              drawFound = true;
              setSprite(entityID,drawFrame[animProp[j].dataIndex], layer);
            }
            break;
          default:
            break;
        }
      }
      
      counter--;
    }

    // printf("drawFound: %d\n",drawFound);
    // if(spriteRenderIDArray.count(entityID) == false){
    //   printf("no se dibuja: %d\n",entityID);
    // }else{
    //   printf("se dibuja: %d\n",entityID);
    // }

    if(spriteArray.count(entityID) == 1){
      // printf("textureIndex: %d\n",textureIndex);
      if(textureIndex != -1){
        texPosArray[entityID] = positionFrame[posIndex] * scaleTexture[entityID]; 

        const int oldTextureID = spriteArray[entityID].textureID;
        Tyra::Texture* oldTexture = texRepo->getByTextureId(oldTextureID);
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
      }else{
        deleteSprite(entityID);
        deleteTexPosArray(entityID);
      }
      
    }
  
    ids.push_back(entityID);
  }
}

void AnimIndex::SetAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, int firstFrame, int lastFrame, bool repeat, enumSpriteLayer layer){
  size_t animSize = GetLayerSize();
  int entityID = -1;
  for (size_t i = 0; i < animSize; i++) {
    entityID = Entities::newID();
    ids.push_back(entityID);

    newFatherID(&father, &ids[i]);
    createAnimation(entityID, i, size, firstFrame, lastFrame, repeat, layer);
  }
}

void AnimIndex::SetAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, const char* animFlash, unsigned int timeIndex, bool repeat, enumSpriteLayer layer){
  size_t animSize = GetLayerSize();
  int entityID = -1;
  
  LayerData fd;
  fd.startFrame = 0;
  fd.endFrame = 0;
  unsigned int layerID = GetAnimationNameID(animFlash);
  // printf("layerID name: %d\n",layerID);
  if(timeIndex >= animClipLayers[type][layerID].timeLapse.size()){
    timeIndex = 0;
  }
  fd.startFrame = animClipLayers[type][layerID].timeLapse[timeIndex].start;
  fd.endFrame = animClipLayers[type][layerID].timeLapse[timeIndex].end;

  // printf("start: %d end: %d\n",fd.startFrame,fd.endFrame);
  for (size_t i = 0; i < animSize; i++) {
    entityID = Entities::newID();
    
    ids.push_back(entityID);

    // printf("entity ID: %d\n",entityID);
    newFatherID(&father, &entityID);
    createAnimation(entityID, i, size, fd.startFrame, fd.endFrame, repeat, layer);
  }
}

void AnimIndex::SetAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, int firstFrame, bool repeat, enumSpriteLayer layer){
  size_t animSize = GetLayerSize();
  size_t maxFrame = animClips[type].maxFrame;
  int entityID = -1;
  for (size_t i = 0; i < animSize; i++) {
    entityID = Entities::newID();

    ids.push_back(entityID);

    newFatherID(&father, &entityID);
    createAnimation(entityID, i, size, firstFrame, maxFrame, repeat, layer);
  }
}

void AnimIndex::ChangeAnimationEntity(std::vector<int>& ids, const char* animState, unsigned int timeIndex, enumSpriteLayer layer, bool repeat){
  
  // Get the Frame from the entity Animation
  unsigned int frameIndex = frameCounterArray.size();
  for(size_t i=0;i<frameCounterArray.size();i++){
    if(frameCounterArray[i].entityID == ids[0]){
      frameIndex = i;
      // printf("frame index: %d\n",i);
      break;
    }
  }

  if(frameIndex == frameCounterArray.size()){
    TYRA_TRAP("FRAME NOT FOUND");
    return;
  }

  LayerData fd;
  fd.startFrame = 0;
  fd.endFrame = 0;
  unsigned int layerID = GetAnimationNameID(animState);
  // printf("layerID name: %d\n",layerID);
  if(timeIndex >= animClipLayers[type][layerID].timeLapse.size()){
    timeIndex = 0;
  }
  fd.startFrame = animClipLayers[type][layerID].timeLapse[timeIndex].start;
  fd.endFrame = animClipLayers[type][layerID].timeLapse[timeIndex].end;
  // printf("startFrame: %d, endFrame:%d\n",fd.startFrame,fd.endFrame);

  size_t size = frameIndex+ids.size();
  for(size_t i=frameIndex; i < size; i++){
    frameCounterArray[i].currentFrame = fd.startFrame;
    frameCounterArray[i].firstFrame = frameCounterArray[i].currentFrame;
    frameCounterArray[i].lastFrame = fd.endFrame;
    frameCounterArray[i].repeat = repeat;
  }

  for(size_t i=0; i< GetLayerSize();i++){
    activeAnimation(ids[i],i,fd.startFrame,fd.endFrame, layer);
  }
}

void initAnimation(){
  unsigned char i = 0;
  while (i != EnumAnimationIndex::ANIM_enumMax)
  {
    animComponent[i].type = (EnumAnimationIndex) i;
    i++;
  } 
}

void loadAnimString() {
  angleFrame.push_back(Tyra::Vec2(0,0));
  animString[EnumAnimationIndex::ANIM_Blover] = "Blover";
  animString[EnumAnimationIndex::ANIM_Cabbagepult] = "Cabbagepult";
  animString[EnumAnimationIndex::ANIM_Cactus] = "Cactus";
  animString[EnumAnimationIndex::ANIM_Spikeweed] = "Caltrop";
  animString[EnumAnimationIndex::ANIM_Cattail] = "Cattail";
  animString[EnumAnimationIndex::ANIM_CherryBomb] = "CherryBomb";
  animString[EnumAnimationIndex::ANIM_Chomper] = "Chomper";
  animString[EnumAnimationIndex::ANIM_CobCannon] = "CobCannon";
  animString[EnumAnimationIndex::ANIM_CoffeeBean] = "Coffeebean";
  animString[EnumAnimationIndex::ANIM_Coin_gold] = "Coin_gold";
  animString[EnumAnimationIndex::ANIM_Coin_silver] = "Coin_silver";
  animString[EnumAnimationIndex::ANIM_Kernelpult] = "Cornpult";
  animString[EnumAnimationIndex::ANIM_CrazyDave] = "CrazyDave";
  animString[EnumAnimationIndex::ANIM_Credits_AnyHour] = "Credits_AnyHour";
  animString[EnumAnimationIndex::ANIM_Credits_BigBrain] = "Credits_BigBrain";
  animString[EnumAnimationIndex::ANIM_Credits_Bossdance] = "Credits_Bossdance";
  animString[EnumAnimationIndex::ANIM_Credits_brainplate] = "Credits_brainplate";
  animString[EnumAnimationIndex::ANIM_Credits_CrazyDave] = "Credits_CrazyDave";
  animString[EnumAnimationIndex::ANIM_Credits_DiscoLights] = "Credits_DiscoLights";
  animString[EnumAnimationIndex::ANIM_Credits_Flower_petals] = "Credits_Flower_petals";
  animString[EnumAnimationIndex::ANIM_Credits_Football] = "Credits_Football";
  animString[EnumAnimationIndex::ANIM_Credits_Infantry] = "Credits_Infantry";
  animString[EnumAnimationIndex::ANIM_Credits_Jackbox] = "Credits_Jackbox";
  animString[EnumAnimationIndex::ANIM_Credits_Main] = "Credits_Main";
  animString[EnumAnimationIndex::ANIM_Credits_Main2] = "Credits_Main2";
  animString[EnumAnimationIndex::ANIM_Credits_Main3] = "Credits_Main3";
  animString[EnumAnimationIndex::ANIM_Credits_SolarPower] = "Credits_SolarPower";
  animString[EnumAnimationIndex::ANIM_Credits_stage] = "Credits_stage";
  animString[EnumAnimationIndex::ANIM_Credits_Throat] = "Credits_Throat";
  animString[EnumAnimationIndex::ANIM_Credits_Tombstones] = "Credits_Tombstones";
  animString[EnumAnimationIndex::ANIM_Credits_WeAreTheUndead] = "Credits_WeAreTheUndead";
  animString[EnumAnimationIndex::ANIM_Credits_ZombieArmy1] = "Credits_ZombieArmy1";
  animString[EnumAnimationIndex::ANIM_Credits_ZombieArmy2] = "Credits_ZombieArmy2";
  animString[EnumAnimationIndex::ANIM_Diamond] = "Diamond";
  animString[EnumAnimationIndex::ANIM_Digger_rising_dirt] = "Digger_rising_dirt";
  animString[EnumAnimationIndex::ANIM_FinalWave] = "FinalWave";
  animString[EnumAnimationIndex::ANIM_Fire] = "Fire";
  animString[EnumAnimationIndex::ANIM_FirePea] = "FirePea";
  animString[EnumAnimationIndex::ANIM_FumeShroom] = "FumeShroom";
  animString[EnumAnimationIndex::ANIM_Garlic] = "Garlic";
  animString[EnumAnimationIndex::ANIM_GatlingPea] = "GatlingPea";
  animString[EnumAnimationIndex::ANIM_GloomShroom] = "GloomShroom";
  animString[EnumAnimationIndex::ANIM_GoldMagnet] = "GoldMagnet";
  animString[EnumAnimationIndex::ANIM_GraveBuster] = "Gravebuster";
  animString[EnumAnimationIndex::ANIM_Hammer] = "Hammer";
  animString[EnumAnimationIndex::ANIM_HypnoShroom] = "HypnoShroom";
  animString[EnumAnimationIndex::ANIM_IceShroom] = "IceShroom";
  animString[EnumAnimationIndex::ANIM_Imitater] = "Imitater";
  animString[EnumAnimationIndex::ANIM_Jalapeno] = "Jalapeno";
  animString[EnumAnimationIndex::ANIM_LawnMower] = "LawnMower";
  animString[EnumAnimationIndex::ANIM_LawnMoweredZombie] = "LawnMoweredZombie";
  animString[EnumAnimationIndex::ANIM_LilyPad] = "LilyPad";
  animString[EnumAnimationIndex::ANIM_LoadBar_sprout] = "LoadBar_sprout";
  animString[EnumAnimationIndex::ANIM_LoadBar_Zombiehead] = "LoadBar_Zombiehead";
  animString[EnumAnimationIndex::ANIM_Magnetshroom] = "Magnetshroom";
  animString[EnumAnimationIndex::ANIM_Marigold] = "Marigold";
  animString[EnumAnimationIndex::ANIM_Melonpult] = "Melonpult";
  animString[EnumAnimationIndex::ANIM_PeaShotter] = "PeaShooterSingle";
  animString[EnumAnimationIndex::ANIM_Repeater] = "PeaShooter";
  animString[EnumAnimationIndex::ANIM_Plantern] = "Plantern";
  animString[EnumAnimationIndex::ANIM_PoolCleaner] = "PoolCleaner";
  animString[EnumAnimationIndex::ANIM_Portal_Circle] = "Portal_Circle";
  animString[EnumAnimationIndex::ANIM_Portal_Square] = "Portal_Square";
  animString[EnumAnimationIndex::ANIM_FlowerPot] = "Pot";
  animString[EnumAnimationIndex::ANIM_PotatoMine] = "PotatoMine";
  animString[EnumAnimationIndex::ANIM_puff] = "puff";
  animString[EnumAnimationIndex::ANIM_PuffShroom] = "PuffShroom";
  animString[EnumAnimationIndex::ANIM_Pumpkin] = "Pumpkin";
  animString[EnumAnimationIndex::ANIM_Rain_circle] = "Rain_circle";
  animString[EnumAnimationIndex::ANIM_Rain_splash] = "Rain_splash";
  animString[EnumAnimationIndex::ANIM_Rake] = "Rake";
  animString[EnumAnimationIndex::ANIM_RoofCleaner] = "RoofCleaner";
  animString[EnumAnimationIndex::ANIM_ScaredyShroom] = "ScaredyShroom";
  animString[EnumAnimationIndex::ANIM_SeaShroom] = "SeaShroom";
  animString[EnumAnimationIndex::ANIM_SelectorScreen] = "SelectorScreen";
  animString[EnumAnimationIndex::ANIM_SelectorScreen_WoodSign] = "SelectorScreen_WoodSign";
  animString[EnumAnimationIndex::ANIM_SlotMachine] = "SlotMachine";
  animString[EnumAnimationIndex::ANIM_SnowPea] = "SnowPea";
  animString[EnumAnimationIndex::ANIM_SodRoll] = "SodRoll";
  animString[EnumAnimationIndex::ANIM_Spikerock] = "SpikeRock";
  animString[EnumAnimationIndex::ANIM_splash] = "splash";
  animString[EnumAnimationIndex::ANIM_SplitPea] = "SplitPea";
  animString[EnumAnimationIndex::ANIM_Squash] = "Squash";
  animString[EnumAnimationIndex::ANIM_Starfruit] = "Starfruit";
  animString[EnumAnimationIndex::ANIM_StartReadySetPlant] = "StartReadySetPlant";
  animString[EnumAnimationIndex::ANIM_Stinky] = "Stinky";
  animString[EnumAnimationIndex::ANIM_Sun] = "Sun";
  animString[EnumAnimationIndex::ANIM_SunFlower] = "SunFlower";
  animString[EnumAnimationIndex::ANIM_SunShroom] = "SunShroom";
  animString[EnumAnimationIndex::ANIM_Tallnut] = "Tallnut";
  animString[EnumAnimationIndex::ANIM_Tanglekelp] = "Tanglekelp";
  animString[EnumAnimationIndex::ANIM_TextFadeOn] = "TextFadeOn";
  animString[EnumAnimationIndex::ANIM_TextSlideDown] = "TextSlideDown";
  animString[EnumAnimationIndex::ANIM_TextSlideOn] = "TextSlideOn";
  animString[EnumAnimationIndex::ANIM_ThreePeater] = "ThreePeater";
  animString[EnumAnimationIndex::ANIM_Torchwood] = "Torchwood";
  animString[EnumAnimationIndex::ANIM_TreeFood] = "TreeFood";
  animString[EnumAnimationIndex::ANIM_treeofWisdom] = "treeofWisdom";
  animString[EnumAnimationIndex::ANIM_TreeOfWisdomClouds] = "TreeOfWisdomClouds";
  animString[EnumAnimationIndex::ANIM_TwinSunflower] = "TwinSunflower";
  animString[EnumAnimationIndex::ANIM_UmbrellaLeaf] = "Umbrellaleaf";
  animString[EnumAnimationIndex::ANIM_Wallnut] = "Wallnut";
  animString[EnumAnimationIndex::ANIM_WinterMelon] = "WinterMelon";
  animString[EnumAnimationIndex::ANIM_Z] = "Z";
  animString[EnumAnimationIndex::ANIM_ZenGarden_bugspray] = "ZenGarden_bugspray";
  animString[EnumAnimationIndex::ANIM_ZenGarden_fertilizer] = "ZenGarden_fertilizer";
  animString[EnumAnimationIndex::ANIM_ZenGarden_phonograph] = "ZenGarden_phonograph";
  animString[EnumAnimationIndex::ANIM_ZenGarden_sprout] = "ZenGarden_sprout";
  animString[EnumAnimationIndex::ANIM_ZenGarden_wateringcan] = "ZenGarden_wateringcan";
  animString[EnumAnimationIndex::ANIM_zombatar_zombie_head] = "zombatar_zombie_head";
  animString[EnumAnimationIndex::ANIM_Zombie] = "Zombie";
  animString[EnumAnimationIndex::ANIM_Zombie_balloon] = "Zombie_balloon";
  animString[EnumAnimationIndex::ANIM_Zombie_bobsled] = "Zombie_bobsled";
  animString[EnumAnimationIndex::ANIM_Zombie_boss] = "Zombie_boss";
  animString[EnumAnimationIndex::ANIM_Zombie_Boss_driver] = "Zombie_Boss_driver";
  animString[EnumAnimationIndex::ANIM_Zombie_boss_fireball] = "Zombie_boss_fireball";
  animString[EnumAnimationIndex::ANIM_Zombie_boss_iceball] = "Zombie_boss_iceball";
  animString[EnumAnimationIndex::ANIM_Zombie_bungi] = "Zombie_bungi";
  animString[EnumAnimationIndex::ANIM_Zombie_catapult] = "Zombie_catapult";
  animString[EnumAnimationIndex::ANIM_Zombie_charred] = "Zombie_charred";
  animString[EnumAnimationIndex::ANIM_Zombie_charred_catapult] = "Zombie_charred_catapult";
  animString[EnumAnimationIndex::ANIM_Zombie_charred_digger] = "Zombie_charred_digger";
  animString[EnumAnimationIndex::ANIM_Zombie_charred_gargantuar] =
      "ZombieEnumAnimationIndexgargantuar";
  animString[EnumAnimationIndex::ANIM_Zombie_charred_imp] = "Zombie_charred_imp";
  animString[EnumAnimationIndex::ANIM_Zombie_charred_zamboni] = "Zombie_charred_zamboni";
  animString[EnumAnimationIndex::ANIM_Zombie_credits_conehead] = "Zombie_credits_conehead";
  animString[EnumAnimationIndex::ANIM_Zombie_credits_dance] = "Zombie_credits_dance";
  animString[EnumAnimationIndex::ANIM_Zombie_credits_screendoor] =
      "ZombieEnumAnimationIndexscreendoor";
  animString[EnumAnimationIndex::ANIM_Zombie_dancer] = "Zombie_dancer";
  animString[EnumAnimationIndex::ANIM_Zombie_digger] = "Zombie_digger";
  animString[EnumAnimationIndex::ANIM_Zombie_disco] = "Zombie_disco";
  animString[EnumAnimationIndex::ANIM_Zombie_dolphinrider] = "Zombie_dolphinrider";
  animString[EnumAnimationIndex::ANIM_Zombie_flagpole] = "Zombie_flagpole";
  animString[EnumAnimationIndex::ANIM_Zombie_football] = "Zombie_football";
  animString[EnumAnimationIndex::ANIM_Zombie_gargantuar] = "Zombie_gargantuar";
  animString[EnumAnimationIndex::ANIM_Zombie_hand] = "Zombie_hand";
  animString[EnumAnimationIndex::ANIM_Zombie_imp] = "Zombie_imp";
  animString[EnumAnimationIndex::ANIM_Zombie_jackbox] = "Zombie_jackbox";
  animString[EnumAnimationIndex::ANIM_Zombie_Jackson] = "Zombie_Jackson";
  animString[EnumAnimationIndex::ANIM_Zombie_ladder] = "Zombie_ladder";
  animString[EnumAnimationIndex::ANIM_Zombie_paper] = "Zombie_paper";
  animString[EnumAnimationIndex::ANIM_Zombie_pogo] = "Zombie_pogo";
  animString[EnumAnimationIndex::ANIM_Zombie_PoleVaulter] = "Zombie_polevaulter";
  animString[EnumAnimationIndex::ANIM_Zombie_snorkle] = "Zombie_snorkle";
  animString[EnumAnimationIndex::ANIM_Zombie_surprise] = "Zombie_surprise";
  animString[EnumAnimationIndex::ANIM_Zombie_Target] = "Zombie_Target";
  animString[EnumAnimationIndex::ANIM_Zombie_yeti] = "Zombie_yeti";
  animString[EnumAnimationIndex::ANIM_Zombie_zamboni] = "Zombie_zamboni";
  animString[EnumAnimationIndex::ANIM_ZombiesWon] = "ZombiesWon";
}

void setSprite(const int entityID, const enumDraw draw, enumSpriteLayer layer) {
    // printf("set sprite id: %d,draw: %d\n",entityID, draw);
  if (spriteRenderIDArray.count(entityID) == 1 && draw == -1) {
    // printf("delete render sprite id: %d\n",entityID);
    // spritesNormalRender.erase(entityID);
    spriteRenderIDArray.erase(entityID);
    // spriteNormalIdStopRender.push_back(entityID);
    if(layer == enumSpriteLayer::background){
      for(size_t i=0; i < backgroundLayer.size(); i++ ){
        if(backgroundLayer[i] == entityID){
          backgroundLayer.erase(backgroundLayer.begin() + i);
          break;
        }
      }
    }else if(layer == enumSpriteLayer::card_layer){
      for(size_t i=0; i < cardLayer.size(); i++ ){
        if(cardLayer[i] == entityID){
          cardLayer.erase(cardLayer.begin() + i);
          break;
        }
      }
    }else if(layer == enumSpriteLayer::plants){
      for(size_t i=0; i < plantsLayer.size(); i++ ){
        if(plantsLayer[i] == entityID){
          plantsLayer.erase(plantsLayer.begin() + i);
          break;
        }
      }
    }else if(layer == enumSpriteLayer::projectile_layer){
      for(size_t i=0; i < projectileLayer.size(); i++ ){
        if(projectileLayer[i] == entityID){
          projectileLayer.erase(projectileLayer.begin() + i);
          break;
        }
      }
    }else if(layer == enumSpriteLayer::sun_layer){
      for(size_t i=0; i < sunLayer.size(); i++ ){
        if(sunLayer[i] == entityID){
          sunLayer.erase(sunLayer.begin() + i);
          break;
        }
      }
    }else if(layer == enumSpriteLayer::zombie_layer){
      for(size_t i=0; i < zombieLayer.size(); i++ ){
        if(zombieLayer[i] == entityID){
          zombieLayer.erase(zombieLayer.begin() + i);
          break;
        }
      }
    }else if(layer == enumSpriteLayer::player_layer){
      for(size_t i=0; i < playerLayer.size(); i++ ){
        if(playerLayer[i] == entityID){
          playerLayer.erase(playerLayer.begin() + i);
          break;
        }
      }
    }
  } else if (spriteRenderIDArray.count(entityID) == 0 && spriteArray.count(entityID) == 1 && draw == 0) {
    spriteRenderIDArray.insert(entityID, 0);
    // int renderSize = spriteRenderIDArray.first.size();
    // for(int j=renderSize-1;j>1;j--){
    //   if(spriteRenderIDArray.first[j] < spriteRenderIDArray.first[j-1]){         
    //     int aux= spriteRenderIDArray.first[j];
    //     spriteRenderIDArray.first[j] = spriteRenderIDArray.first[j-1];
    //     spriteRenderIDArray.first[j-1] = aux;
    //   }
    // }
    if(layer == enumSpriteLayer::background){
      backgroundLayer.push_back(entityID);
    }else if(layer == enumSpriteLayer::card_layer){
      cardLayer.push_back(entityID);
    }else if(layer == enumSpriteLayer::plants){
      plantsLayer.push_back(entityID);
    }else if(layer == enumSpriteLayer::projectile_layer){
      projectileLayer.push_back(entityID);
    }else if(layer == enumSpriteLayer::sun_layer){
      sunLayer.push_back(entityID);
    }else if(layer == enumSpriteLayer::zombie_layer){
      zombieLayer.push_back(entityID);
    }else if(layer == enumSpriteLayer::player_layer){
      playerLayer.push_back(entityID);
    }
  }
  // printf("plant draw: %d\n", animationArray[entityID].draw);
}

int maxAnimID = 0;

std::vector<int> textureFrame;
std::vector<Tyra::Vec2> positionFrame;
std::vector<Tyra::Vec2> scaleFrame;
std::vector<Tyra::Vec2> angleFrame;
std::vector<float> alphaFrame;
std::vector<enumDraw> drawFrame;

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

void readInfo(FILE* MyReadFile, char* textLine, std::string& insideArrow, const EnumAnimationIndex animIndex, unsigned int& layerID, int& indexText) {
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
  enumDraw draw = enumDraw::draw;
  unsigned int countframes = 1;
  Tyra::Texture* texture = nullptr;
  std::string fileName;
  FrameProperty property;
  bool hasRotation = false;

  indexText = 0;
  fgets(textLine, 512, MyReadFile);

  animLayerFrames.push_back(AnimationLayerData());
  animLayerFrames[layerID].push_back(AnimationFrameData()); // Frame 0, Not used
  // printf("layerID: %d\n",layerID);
  while (finish == false) {
    readTag(textLine, insideArrow, indexText);
    if(insideArrow == "t"){
      animLayerFrames[layerID].push_back(AnimationFrameData());
      // animLayerKeyTime[animIndex][layerID].push_back(KEY_NO_EXISTS);
    }else if (insideArrow == "f") {
      readTag(textLine, insideArrow, indexText);
      draw = (enumDraw) std::stoi(insideArrow);
      // std::cout << " draw: " << draw;
    } else if (insideArrow == "i") {
      readTag(textLine, insideArrow, indexText);
      // keys[keys.size()-1] = KEY_EXISTS;
      // std::cout << " i: " << insideArrow;
      insideArrow.erase(0, 13);  // delete "IMAGE_REANIM_" from string
      insideArrow += ".png";
      fileName = insideArrow;
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
      AnimationFrameData& frameData = animLayerFrames[layerID][countframes];
      if (beforeDraw != draw) {
        beforeDraw = draw;
        drawFrame.push_back(draw);
        property.dataIndex = drawFrame.size()-1;
        property.type = ANIM_DRAW;
        frameData.push_back(property);
        if(draw == 0){
          AnimationTime at;
          at.start = countframes;
          int lastClipLayer = animClipLayers[animIndex].size()-1;
          animClipLayers[animIndex][lastClipLayer].timeLapse.push_back(at);
        }else if(draw == -1){
          int lastClipLayer = animClipLayers[animIndex].size()-1;
          unsigned int lastPos = animClipLayers[animIndex][lastClipLayer].timeLapse.size();
          if(lastPos > 0){
            lastPos--;
            animClipLayers[animIndex][lastClipLayer].timeLapse[lastPos].end = countframes;
          }
        }
        // printf("frame: %d, data: %d\n",countframes,draw);
      }

      if(fileName != ""){
        std::vector<Tyra::Texture*>& allTex = *texRepo->getAll();
        for (u32 i = 0; i < texRepo->getTexturesCount(); i++) {
          if (allTex[i]->name == fileName){
            textureFounded = true;

            textureFrame.push_back(allTex[i]->id);
            property.dataIndex = textureFrame.size()-1;
            property.type = EnumAnimationProperty::ANIM_TEXTURE;
            frameData.push_back(property);

            // printf("texture id: %d, type: %d, data:%d\n",(*texRepo->getAll())[i]->id,property.type,property.dataIndex);
            break;
          }
        }
        if (textureFounded == false) {
          fileName = "reanim/" + fileName;
          // printf("new i: %s\n",fileName.c_str());
          texture = loadTexture(fileName);
          
          textureFrame.push_back(texture->id);
          property.dataIndex = textureFrame.size()-1;
          property.type = EnumAnimationProperty::ANIM_TEXTURE;
          frameData.push_back(property);
          // printf("texture id: %d, type: %d, data:%d\n",texture->id,property.type,property.dataIndex);
        }
        textureFounded = false;
      }

      if (beforeSx != sx || beforeSY != sy) {
        beforeSx = sx;
        beforeSY = sy;
        scaleFrame.push_back(Tyra::Vec2(sx, sy));
        property.dataIndex = scaleFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_SCALE;
        
        frameData.push_back(property);
      }

      if (beforeA != a) {
        beforeA = a;
        alphaFrame.push_back(a*128);
        property.dataIndex = alphaFrame.size() - 1;
        property.type = ANIM_ALPHA;
        frameData.push_back(property);
        // printf("frame: %d, dataIndex:%d, data: %f\n",countframes,property.dataIndex,a);
      }

      if (beforeX != x || beforeY != y) {
        beforeX = x;
        beforeY = y;
        positionFrame.push_back(Tyra::Vec2(x, y));
        property.dataIndex = positionFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_POSITION;
        frameData.push_back(property);
      }

      if (beforeKx != kx || beforeKY != ky) {
        beforeKx = kx;
        beforeKY = ky;
        angleFrame.push_back(Tyra::Vec2(kx, ky));
        property.dataIndex = angleFrame.size()-1;
        property.type = EnumAnimationProperty::ANIM_ROTATION;
        frameData.push_back(property);
        hasRotation = true;
        // printf("animID: %d, frame:%d, type:%d, index:%d\n",animID,countframes,property.type,property.dataIndex);
      }

      countframes++;
      
      indexText = 0;
      fileName = "";
      fgets(textLine, 512, MyReadFile);
    } else if (insideArrow == "/track") {
      // countTrack++;
      // std::cout << "Total frames from track " << countTrack << ": "
      //           << countframes << std::endl;
      int lastClipLayer = animClipLayers[animIndex].size()-1;
      unsigned int lastPos = animClipLayers[animIndex][lastClipLayer].timeLapse.size();
      if(lastPos > 0){
        lastPos--;
        if(animClipLayers[animIndex][lastClipLayer].timeLapse[lastPos].end == 0){
          animClipLayers[animIndex][lastClipLayer].timeLapse[lastPos].end = countframes;
        }
      }
      
      if(hasRotation == true){
        bool hasRotationProperty = false;
        
        for(unsigned int i=0;i<animLayerFrames[layerID][1].size();i++){
          if(animLayerFrames[layerID][1][i].type == ANIM_ROTATION){
            hasRotationProperty = true;
            break;
          }
        }
        if(hasRotationProperty == false){
          // printf("cree rotacion propiedad\n");
          property.dataIndex = 0;
          property.type = ANIM_ROTATION;
          animLayerFrames[layerID][1].push_back(property);
        }
      }
      
      animClips[animIndex].maxFrame = countframes - 1;
      // printf("countframes: %d\n",countframes-1);
      countframes = 1;
      finish = true;
    }
  }
}
void readReanimFiles(const EnumAnimationIndex animationNameID, const char* file){
  // Read from the text file
  FILE* MyReadFile;
  MyReadFile = fopen(file, "rb");

  TYRA_ASSERT(MyReadFile != NULL, "The next file could not be found:", file);
  std::string insideArrow;
  // int countTrack = 0;

  unsigned int layerID = 0;
  int indexText = 0;
  char text[512];

  AnimationClip& clip = animClips[animationNameID];
  AnimationClipData& layerData = animClipLayers[animationNameID];
  std::vector<AnimationLayerNameData>& layerName = animLayerNames[animationNameID];
  while (fgets (text , 512 , MyReadFile) != NULL) {
    indexText = 0;
    readTag(text, insideArrow, indexText);
    if (insideArrow == "fps") {
      readTag(text, insideArrow, indexText);
      clip.fps = std::stoi(insideArrow);
    }else if (insideArrow == "name") {
      readTag(text, insideArrow, indexText);
      layerID = maxAnimID;
      maxAnimID++;

      size_t size = insideArrow.size()+1;
      if(size >= 512){
        TYRA_TRAP("ERROR: FILE NAME IS TO BIG");
      }

      char* name = (char*) malloc(size*sizeof(char));
      strncpy(name, insideArrow.c_str(), size);
      layerAnimNames[layerID].push_back(name);
      layerName.push_back(std::vector<char*>());
      layerName[layerName.size()-1].push_back(name);
      // printf("name: %s\n",layerName[layerName.size()-1][0]);
      layerData.push_back(AnimationLayer()); // Create layer in the clip
      layerData[layerData.size()-1].nameID = layerName.size()-1;
      layerData[layerData.size()-1].layerDataID = layerID;

      readInfo(MyReadFile, text, insideArrow, animationNameID, layerID, indexText);      

    }
  }
  clip.layerCount = layerData.size();

  fclose(MyReadFile);
}

void loadAnimation(const EnumAnimationIndex animNameID) {
  readReanimFiles(
      animNameID,
      Tyra::FileUtils::fromCwd("reanim/" + animString[animNameID] + ".reanim").c_str());
  
  SetAnimationNamesID(animNameID);
}