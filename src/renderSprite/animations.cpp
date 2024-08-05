#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include "entities/entities.hpp"
#include "components.hpp"
#include "systems.hpp"
#include <iostream>

void setSprite(const int entityID, const int draw) {
  if (spriteArray.count(entityID)) {
    if (draw == -1) {
      // spritesNormalRender.erase(entityID);
      spriteRenderIDArray.erase(entityID);
      spriteNormalIdStopRender.push_back(entityID);
    } else if (spriteRenderIDArray.count(entityID) == 0) {
      spriteRenderIDArray.insert(entityID,0);
      // spritesNormalRender[entityID] = &spriteArray[entityID];
    }
  } else {
    TYRA_WARN("Sprite don't founded in setSprite");
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
}

void AnimationData::loadAnimation(const int entityID, const int animID,
                                  enumAnimationState animationState) {
  loadAnimation(entityID, animID,
                animationStateVector[animationState].firstFrame,
                animationStateVector[animationState].lastFrame);
}

void AnimationData::loadAnimation(const int entityID, const int animID,
                                  const int firstFrame, const int lastFrame) {
  bool rotateSprite = false;
  int spriteID;
  for (unsigned int j = 1; j < maxFrame; j++) {
    if (angleX.count(j) == true || angleY.count(j) == true) {
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

  spriteID = spriteArray[entityID].id;

  animationArray.insert(entityID, Animation(animID));

  std::unordered_map<unsigned int, int>::iterator itTexture =
      texture.find(firstFrame);
  int pos = firstFrame - 1;

  while (itTexture == texture.end() && pos >= 1) {
    itTexture = texture.find(pos);
    pos--;
  }

  if (itTexture != texture.end()) {
    Tyra::Texture* newTexture;
    newTexture = texRepo->getByTextureId(itTexture->second);
    newTexture->addLink(spriteID);
    originalSize[entityID] =
        Vec2(newTexture->getWidth(), newTexture->getHeight());
    scaleTexture[entityID] =
        Vec2(originalSize[entityID].x / newTexture->getWidth(),
             originalSize[entityID].y / newTexture->getHeight());
    texPosArray.insert(entityID, Tyra::Vec2());
  }

  // for (unsigned int j = 1; j < maxFrame; j++) {
  //   if (texture.count(j) == 1) {
  //     // printf("frame %d\n", j);
  //     newTexture = texRepo->getByTextureId(texture[j]);
  //     newTexture->addLink(spriteID);
  //     originalSize[entityID] =
  //         Vec2(newTexture->getWidth(), newTexture->getHeight());
  //     scaleTexture[entityID] =
  //         Vec2(originalSize[entityID].x / newTexture->getWidth(),
  //              originalSize[entityID].y / newTexture->getHeight());
  //     // printf("name anim: %s\n", name.c_str());
  //     // printf("name Texture: %s\n", newTexture->name.c_str());
  //     // printf("size: %s\n", spriteArray[entityID].size.getPrint().c_str());
  //     // printf("scale: %s\n", scaleTexture[entityID].getPrint().c_str());
  //     break;
  //   }
  // }

  activeAnimation(entityID, firstFrame, lastFrame);

  // printf("termine\n\n");
}

int AnimationData::activeAnimation(const int entityID, const int firstFrame,
                                   const int lastFrame) {
  animationArray[entityID].currentFrame = firstFrame;
  animationArray[entityID].firstFrame = firstFrame;
  animationArray[entityID].lastFrame = lastFrame;

  Tyra::Vec2 scale(1.0f, 1.0f);

  std::unordered_map<unsigned int, int>::iterator itInteger =
      draw.find(firstFrame);
  int pos = firstFrame - 1;

  while (itInteger == draw.end()) {
    itInteger = draw.find(pos);
    pos--;
  }

  animationArray[entityID].draw = itInteger->second;
  setSprite(entityID, itInteger->second);
  if (itInteger->second == (int)enumDraw::noDraw) {
    return 1;
  }

  itInteger = texture.find(firstFrame);
  pos = firstFrame - 1;

  while (itInteger == texture.end() && pos >= 1) {
    itInteger = texture.find(pos);
    pos--;
  }

  if (texRepo->getBySpriteId(spriteArray[entityID].id) != nullptr) {
    // printf("unlink sprite id: %d\n", spriteArray[entityID].id);
    texRepo->getBySpriteId(spriteArray[entityID].id)
        ->removeLinkById(spriteArray[entityID].id);
  }
  // Link new Texture to the sprite entitie
  texRepo->getByTextureId(itInteger->second)->addLink(spriteArray[entityID].id);
  originalSize[entityID] =
      Vec2(texRepo->getByTextureId(itInteger->second)->getWidth(),
           texRepo->getByTextureId(itInteger->second)->getHeight());

  std::unordered_map<unsigned int, float>::iterator it = x.find(firstFrame);
  pos = firstFrame - 1;
  while (it == x.end()) {
    it = x.find(pos);
    pos--;
  }

  texPosArray[entityID].x = it->second;

  it = y.find(firstFrame);
  pos = firstFrame - 1;

  while (it == y.end()) {
    it = y.find(pos);
    pos--;
  }

  texPosArray[entityID].y = it->second;

  it = scaleX.find(firstFrame);
  pos = firstFrame - 1;

  while (it == scaleX.end()) {
    it = scaleX.find(pos);
    pos--;
  }

  scale.x = it->second;

  it = scaleY.find(firstFrame);
  pos = firstFrame - 1;

  while (it == scaleY.end()) {
    it = scaleY.find(pos);
    pos--;
  }

  scale.y = it->second;

  spriteArray[entityID].size = originalSize[entityID] * scale;

  if (angleArray.count(entityID) == 1) {
    it = angleX.find(firstFrame);
    pos = firstFrame - 1;

    while (it == angleX.end()) {
      it = angleX.find(pos);
      pos--;
    }

    angleArray[entityID].x = it->second;

    it = angleY.find(firstFrame);
    pos = firstFrame - 1;

    while (it == angleY.end()) {
      it = angleY.find(pos);
      pos--;
    }

    angleArray[entityID].y = it->second;
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
      std::cout << " draw: " << draw;
    } else if (insideArrow == "i") {
      readTag(MyReadFile, insideArrow, state);
      std::cout << " i: " << insideArrow;
      insideArrow.erase(0, 13);  // delete "IMAGE_REANIM_" from string
      insideArrow += ".png";
      for (u32 i = 0; i < texRepo->getTexturesCount(); i++) {
        if ((*texRepo->getAll())[i]->name == insideArrow) {
          textureFounded = true;
          animationDataArray[animID].texture[countframes] =
              (*texRepo->getAll())[i]->id;
          break;
        }
      }
      if (textureFounded == false) {
        fileName = "reanim/" + insideArrow;
        std::cout << " new i: " << insideArrow;
        texture = loadTexture(fileName);

        animationDataArray[animID].texture[countframes] = texture->id;
        printf(" texture width: %d, height: %d\n", texture->getWidth(),
               texture->getHeight());
      }
      textureFounded = false;
      useAnim = true;
    } else if (insideArrow == "x") {  // es la suma del x layer y el x del
                                      // simbolo(?) igual con y
      readTag(MyReadFile, insideArrow, state);
      x = std::stof(insideArrow);
      std::cout << " X: " << x;
    } else if (insideArrow == "y") {
      readTag(MyReadFile, insideArrow, state);
      y = std::stof(insideArrow);
      std::cout << " Y: " << y;
    } else if (insideArrow == "kx") {  // kx son los grados del angulo
      readTag(MyReadFile, insideArrow, state);
      std::cout << " KX: " << insideArrow;
      kx = std::stof(insideArrow);
    } else if (insideArrow == "ky") {  // ky son los grados del angulo
      readTag(MyReadFile, insideArrow, state);
      std::cout << " KY: " << insideArrow;
      ky = std::stof(insideArrow);
    } else if (insideArrow == "sx") {  // es la escala de la imagen
      readTag(MyReadFile, insideArrow, state);
      std::cout << " SX: " << insideArrow;
      sx = std::stof(insideArrow);
    } else if (insideArrow == "sy") {  // es la escala de la imagen
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

      if (beforeSx != sx) {
        beforeSx = sx;
        animationDataArray[animID].scaleX[countframes] = sx;
      }

      if (beforeSY != sy) {
        beforeSY = sy;
        animationDataArray[animID].scaleY[countframes] = sy;
      }

      if (beforeA != a) {
        beforeA = a;
        animationDataArray[animID].alpha[countframes] = a;
      }

      if (beforeX != x) {
        beforeX = x;
        animationDataArray[animID].x[countframes] = x;
      }

      if (beforeY != y) {
        beforeY = y;
        animationDataArray[animID].y[countframes] = y;
      }

      if (beforeDraw != draw) {
        beforeDraw = draw;
        animationDataArray[animID].draw[countframes] = draw;
      }

      if (beforeKx != kx) {
        beforeKx = kx;
        animationDataArray[animID].angleX[countframes] = kx;
      }

      if (beforeKY != ky) {
        beforeKY = ky;
        animationDataArray[animID].angleY[countframes] = ky;
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
      std::cout << "Los FPS son: " << intValue << std::endl;

    } else if (insideArrow == "name") {
      readTag(MyReadFile, insideArrow, state);
      std::cout << "Name: " << insideArrow << std::endl;
      if (useAnim == true) {
        m_animID[nameID].push_back(maxAnimID);
        animID = maxAnimID;
        animationDataArray[animID] = AnimationData();
        maxAnimID++;
        useAnim = false;
      } else {
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

void loadAnimation(const enumAnimName animNameID, std::string animName) {
  readReanimFiles(animNameID,
                  Tyra::FileUtils::fromCwd("reanim/" + animName + ".reanim"));
}
