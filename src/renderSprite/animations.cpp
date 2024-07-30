#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include "components.hpp"
#include "systems.hpp"
#include <iostream>

void setSprite(const int entityID, const bool draw){
    if(spriteArray.count(entityID)){
      if (draw == false) {
        spritesNormalRender.erase(entityID);
        spriteNormalIdStopRender.push_back(entityID);
      }else {
        spritesNormalRender[entityID] = &spriteArray[entityID];
      }
    }else if(rotationSprite.count(entityID)){
      if (draw == false) {
        spritesRotateRender.erase(entityID);
        spritesRotateIdStopRender.push_back(entityID);
      }else {
        spritesRotateRender[entityID] = &rotationSprite[entityID];
      }
    }else{
      TYRA_WARN("Sprite don't founded in setSprite");
    }
    // printf("plant draw: %d\n", animationArray[entityID].draw);
}

AnimationState::AnimationState(){};
AnimationState::AnimationState(const unsigned int firstFrame,const unsigned int lastFrame){
  this->firstFrame = firstFrame;
  this->lastFrame = lastFrame;
}

AnimationState animationStateVector[enumMaxAnimationState];
int maxAnimID = 0;

void loadAnimationStates(){
  animationStateVector[normalZombieWalk] = AnimationState(45,91);
  animationStateVector[normalZombieAttack] = AnimationState(139,178);
}

void AnimationData::loadAnimation(const int entityID, const int animID, enumAnimationState animationState){
  loadAnimation(entityID, animID, animationStateVector[animationState].firstFrame, animationStateVector[animationState].lastFrame);
}

void AnimationData::loadAnimation(const int entityID, const int animID, const int firstFrame, const int lastFrame){
  bool rotateSprite = false;
  int spriteID;
  for (unsigned int j = 1; j < maxFrame; j++) {
    if (angleX.count(j) == true || angleY.count(j) == true) {
      rotateSprite = true;
      createSpriteRotate(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                Vec2(128 / 1.6f, 128 / 1.6f),Vec2(0.0f,0.0f));
      spriteID = rotationSprite[entityID].sprite.id;
      printf("rotationSprite id: %d\n",rotationSprite[entityID].sprite.id);
      break;
    }
  }

  if(rotateSprite == false){
    createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                Vec2(128 / 1.6f, 128 / 1.6f));
    spriteID = spriteArray[entityID].id;
    printf("sprite id: %d\n",spriteArray[entityID].id);
  }

  Tyra::Texture* newTexture;
  animationArray[entityID] = Animation(animID);

  for (unsigned int j = 1; j < maxFrame; j++) {
      if (texture.count(j) == 1) {
        // printf("frame %d\n", j);
        newTexture = texRepo->getByTextureId(texture[j]);
        newTexture->addLink(spriteID);
        originalSize[entityID] = Vec2(newTexture->getWidth(), newTexture->getHeight());
        scaleTexture[entityID] =
            Vec2(originalSize[entityID].x / newTexture->getWidth(),
                 originalSize[entityID].y / newTexture->getHeight());
        // printf("name anim: %s\n", name.c_str());
        // printf("name Texture: %s\n", newTexture->name.c_str());
        // printf("size: %s\n", spriteArray[entityID].size.getPrint().c_str());
        printf("scale: %s\n", scaleTexture[entityID].getPrint().c_str());
        break;
      }
    }

  activeAnimation(entityID, firstFrame, lastFrame);
  
  printf("termine\n\n");
}

void AnimationData::activeAnimation(const int entityID, const int firstFrame, const int lastFrame){
  animationArray[entityID].currentFrame = firstFrame;
  animationArray[entityID].firstFrame = firstFrame;
  animationArray[entityID].lastFrame = lastFrame;

  Tyra::Vec2 scale(1.0f,1.0f);
  bool drawState = false;
  if(draw.count(firstFrame) == 1){
    drawState = draw[firstFrame];
  }else{
    for(int i=firstFrame-1; i>0; i--){
      if(draw.count(i) == 1){
        drawState = draw[i];
        break;
      }
    }
  }

  if(texture.count(firstFrame) == 1){
    if(spriteArray.count(entityID) == 1){
      if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
        // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
        texRepo->getBySpriteId(spriteArray[entityID].id)
            ->removeLinkById(spriteArray[entityID].id);
      }

      // Link new Texture to the sprite entitie
      texRepo->getByTextureId(texture[firstFrame])
          ->addLink(spriteArray[entityID].id);
      originalSize[entityID] = Vec2(
          texRepo
              ->getByTextureId(texture[firstFrame])
              ->getWidth(),
          texRepo
              ->getByTextureId(texture[firstFrame])
              ->getHeight());
    }else{
      if (texRepo->getBySpriteId(rotationSprite[entityID].sprite.id) != nullptr) {
        // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
        texRepo->getBySpriteId(rotationSprite[entityID].sprite.id)
            ->removeLinkById(rotationSprite[entityID].sprite.id);
      }

      // Link new Texture to the sprite entitie
      texRepo->getByTextureId(texture[firstFrame])
          ->addLink(rotationSprite[entityID].sprite.id);
      originalSize[entityID] = Vec2(
          texRepo
              ->getByTextureId(texture[firstFrame])
              ->getWidth(),
          texRepo
              ->getByTextureId(texture[firstFrame])
              ->getHeight());
      }
  }else {
    for(int i=firstFrame-1; i>0; i--){
      if(texture.count(i) == 1){
        if(spriteArray.count(entityID) == 1){
          if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
            // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
            texRepo->getBySpriteId(spriteArray[entityID].id)
                ->removeLinkById(spriteArray[entityID].id);
          }
          // Link new Texture to the sprite entitie
          texRepo->getByTextureId(texture[i])
              ->addLink(spriteArray[entityID].id);
          originalSize[entityID] = Vec2(
              texRepo
                  ->getByTextureId(texture[i])
                  ->getWidth(),
              texRepo
                  ->getByTextureId(texture[i])
                  ->getHeight());
        }else{
          if (texRepo->getBySpriteId(rotationSprite[entityID].sprite.id) != nullptr) {
            // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
            texRepo->getBySpriteId(rotationSprite[entityID].sprite.id)
                ->removeLinkById(rotationSprite[entityID].sprite.id);
          }

          // Link new Texture to the sprite entitie
          texRepo->getByTextureId(texture[i])
              ->addLink(rotationSprite[entityID].sprite.id);
          originalSize[entityID] = Vec2(
              texRepo
                  ->getByTextureId(texture[i])
                  ->getWidth(),
              texRepo
                  ->getByTextureId(texture[i])
                  ->getHeight());
        }
        break;
      }
    }
  }

  for (unsigned int j = 1; j < maxFrame; j++) {
    if (x.count(j) == 1) {
      texPosArray[entityID].x = x[j];
    }
    if (y.count(j) == 1) {
      texPosArray[entityID].y = y[j];
    }
  }

  if(x.count(firstFrame) == 1){
    texPosArray[entityID].x = x[firstFrame];
  }else{
    for(int i=firstFrame-1; i>0; i--){
      if(x.count(i) == 1){
        texPosArray[entityID].x = x[i];
        break;
      }
    }
  }

  if(y.count(firstFrame) == 1){
    texPosArray[entityID].y = y[firstFrame];
  }else{
    for(int i=firstFrame-1; i>0; i--){
      if(y.count(i) == 1){
        texPosArray[entityID].y = y[i];
        break;
      }
    }
  }

  if(scaleX.count(firstFrame) == 1){
    scale.x = scaleX[firstFrame];
  }else{
    for(int i=firstFrame-1; i>0; i--){
      if(scaleX.count(i) == 1){
        scale.x = scaleX[i];
        break;
      }
    }
  }
  
  if(scaleY.count(firstFrame) == 1){
    scale.y = scaleY[firstFrame];
  }else{
    for(int i=firstFrame-1; i>0; i--){
      if(scaleY.count(i) == 1){
        scale.y = scaleY[i];
        break;
      }
    }
  }

  if(rotationSprite.count(entityID) == 1){
    if(angleX.count(firstFrame) == 1){
      rotationSprite[entityID].angle.x = angleX[firstFrame];
    }else{
      for(int i=firstFrame-1; i>0; i--){
        if(angleX.count(i) == 1){
          rotationSprite[entityID].angle.x = angleX[i];
          break;
        }
      }
    }
    if(angleY.count(firstFrame) == 1){
      rotationSprite[entityID].angle.y = angleY[firstFrame];
    }else{
      for(int i=firstFrame-1; i>0; i--){
        if(angleY.count(i) == 1){
          rotationSprite[entityID].angle.y = angleY[i];
          break;
        }
      }
    }
  }

  if(spriteArray.count(entityID) == 1){
    spriteArray[entityID].size = originalSize[entityID] * scale;
  }else{
    rotationSprite[entityID].sprite.size = originalSize[entityID] * scale;
  }
  animationArray[entityID].draw = drawState;
  printf("anim draw: %d\n", drawState);
  setSprite(entityID, drawState);
}

void AnimationData::setAnimationState(const int entityID, enumAnimationState animationState){
  animationArray[entityID].currentFrame = animationStateVector[animationState].firstFrame;
  animationArray[entityID].firstFrame = animationStateVector[animationState].firstFrame;
  animationArray[entityID].lastFrame = animationStateVector[animationState].lastFrame;

  activeAnimation(entityID,animationStateVector[animationState].firstFrame,animationStateVector[animationState].lastFrame);
}

void readTag(std::ifstream& MyReadFile, std::string& string, char& state){
  if(state != '<' && state != '>'){
    // printf("error char: %c\n", state);
    state = MyReadFile.get();
  }
  // printf("char: %c\n", state);
  if(state == '<'){
    std::getline(MyReadFile, string, '>');
    state = '>';
  }else if(state == '>'){
    std::getline(MyReadFile, string, '<');
    state = '<';
  }
}

void readInfo(std::ifstream& MyReadFile, std::string& insideArrow, bool& useAnim, int& animID,char& state){
  bool textureFounded = false;

  float beforeX = -400;
  float beforeY = -400;
  float x = 0;
  float y = 0;
  float beforeKx = -400;
  float beforeKY = -400;
  float kx = 0.0f;
  float ky = 0.0f;
  float beforeSx = -400;
  float beforeSY = -400;
  float sx = 1.0f;
  float sy = 1.0f;
  float beforeA = 2.0f;
  float a = 1.0f;
  int beforeDraw = -2;
  bool draw = true;
  Tyra::Texture* texture = nullptr;
  std::string fileName;
  int countframes = 1;

  std::string::size_type sz;
  bool finish = false;

  while (finish == false)
  {
    readTag(MyReadFile, insideArrow, state);
    if (insideArrow == "f"){
      readTag(MyReadFile, insideArrow, state);
      if(insideArrow == "-1"){
        printf(" NO DRAW");
        draw = false;
      }else{
        printf(" DRAW");
        draw = true;
      }
      
    } else if (insideArrow == "i") {
      readTag(MyReadFile, insideArrow, state);
      std::cout << " i: " << insideArrow;
      insideArrow.erase(0,13); // delete "IMAGE_REANIM_" from string
      insideArrow += ".png";
      for(u32 i=0; i<texRepo->getTexturesCount(); i++){
        if((*texRepo->getAll())[i]->name == insideArrow){
          textureFounded = true;
          animationDataArray[animID].texture[countframes] = (*texRepo->getAll())[i]->id;
          break;
        }
      }
      if(textureFounded == false){
        fileName = "reanim/" + insideArrow;
        std::cout << " new i: " << insideArrow;
        texture = loadTexture(fileName);

        animationDataArray[animID].texture[countframes] = texture->id;
        printf(" texture width: %d, height: %d\n",texture->getWidth(),texture->getHeight());
      }
      textureFounded = false;
      useAnim = true;
    } else if (insideArrow == "x") { // es la suma del x layer y el x del simbolo(?) igual con y
      readTag(MyReadFile, insideArrow, state);
      x = std::stof(insideArrow, &sz);
      std::cout << " X: " << x;
    } else if (insideArrow == "y") {
      readTag(MyReadFile, insideArrow, state);
      y = std::stof(insideArrow);
      std::cout << " Y: " << y;
    } else if (insideArrow == "kx") { // kx son los grados del angulo
      readTag(MyReadFile, insideArrow, state);
      std::cout << " KX: " << insideArrow;
      kx = std::stof(insideArrow);
    } else if (insideArrow == "ky") { // ky son los grados del angulo
      readTag(MyReadFile, insideArrow, state);
      std::cout << " KY: " << insideArrow;
      ky = std::stof(insideArrow);
    } else if (insideArrow == "sx") { // es la escala de la imagen
      readTag(MyReadFile, insideArrow, state);
      std::cout << " SX: " << insideArrow;
      sx = std::stof(insideArrow);
    } else if (insideArrow == "sy") { // es la escala de la imagen
      readTag(MyReadFile, insideArrow, state);
      std::cout << " SY: " << insideArrow;
      sy = std::stof(insideArrow);
    } else if (insideArrow == "a") {
      readTag(MyReadFile, insideArrow, state);
      std::cout << " a: " << insideArrow;
      a = std::stof(insideArrow);
    } else if (insideArrow == "t") {
      std::cout << "Frame " << countframes << ":";
    } else if (insideArrow == "/t") {
      std::cout << std::endl;

      if(beforeSx != sx){
        beforeSx = sx;
        animationDataArray[animID].scaleX[countframes] = sx;
      }

      if(beforeSY != sy){
        beforeSY = sy;
        animationDataArray[animID].scaleY[countframes] = sy;
      }

      if(beforeA != a){
        beforeA = a;
        animationDataArray[animID].alpha[countframes] = a;
      }

      if(beforeX != x){
        beforeX = x;
        animationDataArray[animID].x[countframes] = x;
      }

      if(beforeY != y){
        beforeY = y;
        animationDataArray[animID].y[countframes] = y;
      }

      if(beforeDraw != draw){
        beforeDraw = draw;
        animationDataArray[animID].draw[countframes] = draw;
      }

      if(beforeKx != kx){
        beforeKx = kx;
        animationDataArray[animID].angleX[countframes] = kx;
      }

      if(beforeKY != ky){
        beforeKY = ky;
        animationDataArray[animID].angleY[countframes] = ky;
      }

      countframes++;
    } else if (insideArrow == "/track") {
      // countTrack++;
      // std::cout << "Total frames from track " << countTrack << ": "
      //           << countframes << std::endl;
      animationDataArray[animID].maxFrame = countframes-1;
      countframes = 1;
      finish = true;
    }
  }
}

void readReanimFiles(std::string nameID, std::string file) {
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
      std::cout << "Los FPS son: " << intValue << std::endl;

    } else if (insideArrow == "name") {
      readTag(MyReadFile, insideArrow, state);
      std::cout << "Name: " << insideArrow << std::endl;
      if(useAnim == true){
        m_animID[nameID].push_back(maxAnimID);
        animID = maxAnimID;
        animationDataArray[animID] = AnimationData();
        maxAnimID++;
        useAnim = false;
      }else{
        animationDataArray[animID].draw.clear();
        animationDataArray[animID].angleX.clear();
        animationDataArray[animID].angleY.clear();
        animationDataArray[animID].scaleX.clear();
        animationDataArray[animID].scaleY.clear();
        animationDataArray[animID].alpha.clear();
        animationDataArray[animID].x.clear();
        animationDataArray[animID].y.clear();
        printf("borre la memoria\n");
      }
      animationDataArray[animID].name = insideArrow;

      std::cout << "animID: " << animID << std::endl;
      readInfo(MyReadFile, insideArrow, useAnim, animID, state);
    }
  }
  // Close the file
  MyReadFile.close();
}

void loadAnimation(std::string animName){
  readReanimFiles(animName,Tyra::FileUtils::fromCwd("reanim/"+animName+".reanim"));
}
