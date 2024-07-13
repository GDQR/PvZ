#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include "components.hpp"
#include "systems.hpp"
#include <iostream>

int maxAnimID = 0;

void loadAnimationSprite(const int entityID, const int animID){
    bool rotateSprite = false;
    bool hasAlpha = false;
  
    for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
      if (animationDataArray[animID].alpha.count(j) == true) {
        hasAlpha = true;
      }
      if (animationDataArray[animID].angle.count(j) == true) {
        rotateSprite = true;
      }
      if (rotateSprite == true && hasAlpha == true) {
        break;
      }
    }

    if(rotateSprite == false){
      printf("entre en normal\n");
      createSprite(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                 Vec2(128 / 1.6f, 128 / 1.6f));

      int spriteID = spriteArray[entityID].id;
      Tyra::Texture* texture;
      animationArray[entityID] = Animation(animID);

      // printf("sprite ID: %d\n", spriteID);

      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].texture.count(j) == 1) {
          // printf("frame %d\n", j);
          texture = texRepo->getByTextureId(animationDataArray[animID].texture[j]);
          texture->addLink(spriteID);
          originalSize[entityID] = Vec2(texture->getWidth(), texture->getHeight());
          scaleTexture[entityID] =
              Vec2(originalSize[entityID].x / texture->getWidth(),
                   originalSize[entityID].y / texture->getHeight());
          // printf("name anim: %s\n", animationDataArray[animID].name.c_str());
          // printf("name Texture: %s\n", texture->name.c_str());
          // printf("size: %s\n", spriteArray[entityID].size.getPrint().c_str());
          // printf("scale: %s\n", scaleTexture[entityID].getPrint().c_str());
          break;
        }
      }

      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].scale.count(j) == 1) {
          spriteArray[entityID].size = originalSize[entityID] * animationDataArray[animID].scale[j];
          break;
        }
      }

      // if (animationDataArray[animID].draw.count(0)) {
      // // setSprite(entityID, animID);
      // }

    }else{
      printf("entre en rotate\n");
      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].angle.count(j) == 1) {
          createSpriteRotate(entityID, Tyra::MODE_STRETCH, Vec2(0, 0),
                 Vec2(128 / 1.6f, 128 / 1.6f),animationDataArray[animID].angle[j]);
        }
      }
      
      int spriteID = rotationSprite[entityID].sprite.id;
      Tyra::Texture* texture;
      animationArray[entityID] = Animation(animID);

      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].position.count(j) == 1) {
          texPosArray[entityID] = animationDataArray[animID].position[j];
        }
      }

      // printf("sprite ID: %d\n", spriteID);

      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].texture.count(j) == 1) {
          // printf("frame %d\n", j);
          texture = texRepo->getByTextureId(animationDataArray[animID].texture[j]);
          texture->addLink(spriteID);
          originalSize[entityID] = Vec2(texture->getWidth(), texture->getHeight());
          scaleTexture[entityID] =
              Vec2(originalSize[entityID].x / texture->getWidth(),
                   originalSize[entityID].y / texture->getHeight());
          printf("name anim: %s\n", animationDataArray[animID].name.c_str());
          // printf("name Texture: %s\n", texture->name.c_str());
          // printf("size: %s\n", spritesRotate[entityID].size.getPrint().c_str());
          // printf("scale: %s\n", scaleTexture[entityID].getPrint().c_str());
          break;
        }
      }

      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].scale.count(j) == 1) {
          rotationSprite[entityID].sprite.size = originalSize[entityID] * animationDataArray[animID].scale[j];
          break;
        }
      }

      for (unsigned int j = 0; j < animationDataArray[animID].maxFrame; j++) {
        if (animationDataArray[animID].draw.count(j) == 1) {
          animationArray[entityID].draw = animationDataArray[animID].draw[j];
          setSprite(entityID, animID, animationArray[entityID].draw);
          break;
        }
      }
      // if (animationDataArray[animID].draw.count(0)) {
      // // setSprite(entityID, animID);
      // }
    }
    
    printf("termine\n\n");
}

void setSprite(const int entityID, const int animID, const bool draw){
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

void activeAnimation(const int entityID, const int animID, const int firstFrame, const int lastFrame){
  animationArray[entityID].currentFrame = firstFrame;
  animationArray[entityID].firstFrame = firstFrame;
  animationArray[entityID].lastFrame = lastFrame;
  bool draw = false;
  if(animationDataArray[animID].alpha.count(firstFrame) == 1){
    draw = true;
  }else if(animationDataArray[animID].angle.count(firstFrame) == 1){
    draw = true;
  }else if(animationDataArray[animID].position.count(firstFrame) == 1){
    draw = true;
  }else if(animationDataArray[animID].scale.count(firstFrame) == 1){
    draw = true;
  }else if(animationDataArray[animID].texture.count(firstFrame) == 1){
    draw = true;
  }
  animationArray[entityID].draw = draw;
  setSprite(entityID, animID, draw);
}

void readReanimFiles(std::string nameID, std::string file) {
  std::string myText;

  // Read from the text file
  std::ifstream MyReadFile(file, std::ios::binary);

  TYRA_ASSERT(MyReadFile.is_open(), "The next file could not be found:", file);

  std::string insideArrow;
  std::string fileName;
  int countTrack = 0;
  int countframes = 0;
  float floatValue;
  int intValue;
  int animID = -1;
  std::string::size_type sz;
  // int length = MyReadFile.tellg();
  bool passX=false;
  bool passY=false;
  bool passSX=false;
  bool passSY=false;
  bool passKX=false;
  bool passKY=false;
  bool passAlpha=false;
  bool useAnim = true;
  bool textureFounded = false;
  bool save = true;
  float kx = 0.0f;
  float ky = 0.0f;
  float sx = 1.0f;
  float sy = 1.0f;
  float a = 1.0f;
  int beforeDraw = -2;
  bool draw = true;
  Tyra::Texture* texture = nullptr;
  while (!MyReadFile.eof()) {
    // int length = MyReadFile.tellg();
    //     std::cout << "pos: "<<length << std::endl;
    std::getline(MyReadFile, insideArrow, '<');
    std::getline(MyReadFile, insideArrow, '>');
    // std::cout <<"test: " << insideArrow << std::endl;
    if (insideArrow == "fps") {
      std::getline(MyReadFile, insideArrow, '<');

      intValue = std::stoi(insideArrow);
      std::cout << "Los FPS son: " << intValue << std::endl;

      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "name") {
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << "Name: " << insideArrow << std::endl;
      ky = 0.0f;
      kx = 0.0f;
      sx = 1.0f;
      sy = 1.0f;
      a = 1.0f;
      beforeDraw = -2;
      draw = true;
      save = true;
      if(useAnim == true){
        m_animID[nameID].push_back(maxAnimID);
        animID = maxAnimID;
        animationDataArray[animID] = AnimationData();
        maxAnimID++;
        useAnim = false;
      }else{
        animationDataArray[animID].draw.clear();
        animationDataArray[animID].position.clear();
        printf("borre la memoria\n");
      }
      animationDataArray[animID].name = insideArrow;

      std::cout << " animID: " << animID << std::endl;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "f"){
      std::getline(MyReadFile, insideArrow, '<');
      if(insideArrow == "-1"){
        printf(" NO DRAW");
        save = false;
        draw = false;
      }else{
        printf(" DRAW");
        save = true;
        draw = true;
      }  
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "i") {
      std::getline(MyReadFile, insideArrow, '<');
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
      }
      textureFounded = false;
      useAnim = true;
      printf(" texture width: %d, height: %d\n",texture->getWidth(),texture->getHeight());
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "x") { // es la suma del x layer y el x del simbolo(?) igual con y 
      passX = true;
      std::getline(MyReadFile, insideArrow, '<');
      floatValue = std::stof(insideArrow, &sz);
      std::cout << " X: " << floatValue;
      animationDataArray[animID].position[countframes].x = std::stof(insideArrow);
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "y") {
      passY = true;
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " Y: " << insideArrow;
      animationDataArray[animID].position[countframes].y = std::stof(insideArrow);
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "kx") { // kx son los grados del angulo
      passKX = true;
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " KX: " << insideArrow;
      kx = std::stof(insideArrow);
      animationDataArray[animID].angle[countframes].x = kx;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "ky") { // ky son los grados del angulo
      passKY = true;
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " KY: " << insideArrow;
      ky = std::stof(insideArrow);
      animationDataArray[animID].angle[countframes].y = ky;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "sx") { // es la escala de la imagen
      passSX = true;
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " SX: " << insideArrow;
      sx = std::stof(insideArrow);
      animationDataArray[animID].scale[countframes].x = sx;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "sy") { // es la escala de la imagen
      passSY = true;
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " SY: " << insideArrow;
      sy = std::stof(insideArrow);
      animationDataArray[animID].scale[countframes].y = sy;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "a") {
      passAlpha = true;
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " a: " << insideArrow;
      a = std::stof(insideArrow);
      animationDataArray[animID].alpha[countframes] = a;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "t") {
      std::cout << "Frame " << countframes << ":";
    } else if (insideArrow == "/t") {
      // std::getline(MyReadFile, insideArrow, '<');
      // std::getline(MyReadFile, insideArrow, '>');
      // std::cout << insideArrow << std::endl;
      std::cout << std::endl;
      

      if(save == true){
        if(passX == false){
          animationDataArray[animID].position[countframes].x = animationDataArray[animID].position[countframes-1].x;
        }
        if(passY == false){
          animationDataArray[animID].position[countframes].y = animationDataArray[animID].position[countframes-1].y;
        }
        if(passSX == false){
          animationDataArray[animID].scale[countframes].x = sx;
        }
        if(passSY == false){
          animationDataArray[animID].scale[countframes].y = sy;
        }
        if(passAlpha == false){
          animationDataArray[animID].alpha[countframes] = a;
        }
        // printf("alpha: %f\n",animationDataArray[animID].alpha[countframes]);
      }

      if(beforeDraw != draw){
        beforeDraw = draw;
        animationDataArray[animID].draw[countframes] = draw;
        printf("draw: %d\n",animationDataArray[animID].draw[countframes]);
      }
      

      if(passKX == true && passKY == false){
        animationDataArray[animID].angle[countframes].y = ky;
      }else if(passKX == false && passKY == true){
        animationDataArray[animID].angle[countframes].x = kx;
      }

      countframes++;
      passX = false;
      passY = false;
      passSX = false;
      passSY = false;
      passKX = false;
      passKY = false;
      passAlpha = false;
    } else if (insideArrow == "/track") {
      countTrack++;
      std::cout << "Total frames from track " << countTrack << ": "
                << countframes << std::endl;
      animationDataArray[animID].maxFrame = countframes;
      countframes = 0;
    }
  }
  // Close the file
  MyReadFile.close();
}

void loadAnimation(std::string animName){
  readReanimFiles(animName,Tyra::FileUtils::fromCwd("reanim/"+animName+".reanim"));
}
