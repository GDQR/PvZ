#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include <iostream>
// Animations animations;

int maxAnimID = 20;
// void loadAnimNameFiles() {
//   std::ifstream MyReadFile(Tyra::FileUtils::fromCwd("animNamefiles.txt"),
//                            std::ios::binary);
//   TYRA_ASSERT(MyReadFile.is_open(), "animNamefiles.txt could not be found");
//   std::string myText;
//   while (std::getline(MyReadFile, myText, ',')) {
//     // Output the text from the file
//     std::cout << myText << ": " << maxAnimID << std::endl;
//     m_animID[myText] = maxAnimID;
//     maxAnimID++;
//     std::getline(MyReadFile, myText, '\n');
//   }
// }

// void GetAnimID(std::string name, int* animID) {
//   if (m_animID.count(name)) {
//     *animID = m_animID[name];
//     std::cout << "AnimID: " << *animID << std::endl;
//   } else {
//     *animID = -1;
//     TYRA_ASSERT(
//         *animID != -1,
//         "Animation Namefile doesn't exist or you forget include ',':", name);
//   }
// }

void readReanimFiles(std::string file) {
  std::string myText;

  // Read from the text file
  std::ifstream MyReadFile(file, std::ios::binary);

  TYRA_ASSERT(MyReadFile.is_open(), "The next file could not be found:", file);

  std::string openArrow;
  std::string insideArrow;
  std::string closeArrow;
  int countTrack = 0;
  int countframes = 0;
  float floatValue;
  int intValue;
  int animID = -1;
  std::string::size_type sz;
  // int length = MyReadFile.tellg();
  bool finishCountFrames = false;
  bool passX=false;
  bool passY=false;
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
      m_animID["Sun"].push_back(maxAnimID);
      std::cout << " animID: " << maxAnimID << std::endl;
      animID = maxAnimID;
      animationDataArray[animID] = AnimationData();
      maxAnimID++;
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "i") {
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " i: " << insideArrow;
      insideArrow.erase(0,13); // delete "IMAGE_REANIM_" from string
      insideArrow += ".png";
      std::cout << " new i: " << insideArrow;
      Tyra::Texture* texture;
      texture = loadTexture(insideArrow);
      animationDataArray[animID].texture[countframes] = texture;
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
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " KX: " << insideArrow;
      animationDataArray[animID].angle[countframes] = std::stof(insideArrow);
      std::getline(MyReadFile, insideArrow, '>');
    // } else if (insideArrow == "ky") { // esto talvez lo borre
    //   std::getline(MyReadFile, insideArrow, '<');
    //   std::cout << " KY: " << insideArrow;
    //   std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "sx") { // es la escala de la imagen
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " SX: " << insideArrow;
      animationDataArray[animID].scale[countframes] = std::stof(insideArrow);
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "a") {
      std::getline(MyReadFile, insideArrow, '<');
      std::cout << " a: " << insideArrow;
      animationDataArray[animID].alpha[countframes] = std::stof(insideArrow);
      std::getline(MyReadFile, insideArrow, '>');
    } else if (insideArrow == "t") {
      std::cout << "Frame " << countframes << ":";
    } else if (insideArrow == "/t") {
      // std::getline(MyReadFile, insideArrow, '<');
      // std::getline(MyReadFile, insideArrow, '>');
      // std::cout << insideArrow << std::endl;
      std::cout << std::endl;
      if(passX == false){
        animationDataArray[animID].position[countframes].x = animationDataArray[animID].position[countframes-1].x;
      }
      if(passY == false){
        animationDataArray[animID].position[countframes].y = animationDataArray[animID].position[countframes-1].y;
      }
      countframes++;
      passX = false;
      passY = false;
    } else if (insideArrow == "track" && finishCountFrames == false) {
      int length = MyReadFile.tellg();
      // std::cout << "pos: "<<length << std::endl;
      // std::cout << "adentro del track" << std::endl;

      while (insideArrow != "/track") {
        std::getline(MyReadFile, insideArrow, '<');
        std::getline(MyReadFile, insideArrow, '>');
        if (insideArrow == "t") {
          countframes++;
        }
      }
      // std::cout << "Frames:" << countframes << std::endl;
      countframes = 0;
      finishCountFrames = true;
      MyReadFile.seekg(length, std::ios_base::beg);
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

void loadPeaShooterAnimation() {
  animationDataArray[peaShooterHead] = AnimationData();
  animationDataArray[peaShooterBody] = AnimationData();

  printf("cargando PeaShooter animation\n");
  std::string filepath;
  Tyra::Texture* texture;
  int frame = 0;
  animationDataArray[peaShooterHead].position[frame] = Tyra::Vec2(0, 0);
  for (int i = 30; i <= 54; i++) {
    filepath = "Animations/PeaShooterSingle/PeaShooterSingle00";
    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[peaShooterHead].texture[frame] = texture;
    frame++;
  }
  animationDataArray[peaShooterHead].maxFrame = frame;
  frame = 0;
  texture = loadTexture("Animations/PeaShooterSingle/PeaShooterSingle0005.png");
  animationDataArray[peaShooterBody].texture[frame] = texture;
  animationDataArray[peaShooterBody].position[frame] = Tyra::Vec2(0, 0);
  animationDataArray[peaShooterBody].maxFrame = frame;
}

void loadZombieAnimation() {
  animationDataArray[zombieWalk] = AnimationData();

  TYRA_LOG("Loading Zombie animation\n");

  std::string filepath;
  Tyra::Texture* texture;
  int frame = 0;
  filepath = "Animations/Zombie/normalZombie/Zombie_head.png";
  texture = loadTexture(filepath);
  animationDataArray[zombieWalk].texture[frame] = texture;

  // Read from the text file
  std::ifstream headPosFile("Animations/Zombie/normalZombie/headpos.txt");

  std::string index;
  while (headPosFile >> index) {
    std::string pos;
    std::string line;
    std::string str_angle;
    float x;
    float y;
    int angle;
    headPosFile >> pos >> x >> line >> y >> str_angle >> angle;
    // Output the text from the file
    // std::cout << myText << " "<< pos <<'\n';

    // std::cout << index << " " << pos << x << " " << line << " " << y << " "
    //           << str_angle << angle << '\n';
    std::cout << index << " " << x << " " << line << " " << y << '\n';
    animationDataArray[zombieWalk].position[frame] = Tyra::Vec2(x, y);
    animationDataArray[zombieWalk].angle[frame] = angle;
    frame++;
  }

  for (int i = 0; i < frame; i++) {
    printf("frame: %d pos: %f,%f\n", i,
           animationDataArray[zombieWalk].position[i].x,
           animationDataArray[zombieWalk].position[i].y);
  }
  animationDataArray[zombieWalk].maxFrame = frame;

  // Close the file
  headPosFile.close();
}

void loadDebugZombieAnimation() {
  animationDataArray[deb_zombieWalk] = AnimationData();

  TYRA_LOG("Loading DEBUG Zombie animation\n");
  std::string filepath;
  Tyra::Texture* texture;
  int frame = 0;
  animationDataArray[deb_zombieWalk].position[frame] = Tyra::Vec2(0, 0);
  for (int i = 45; i <= 91; i++) {
    filepath = "Animations/Zombie/debug/head/suav/Zombie00";
    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[deb_zombieWalk].texture[frame] = texture;
    frame++;
  }
  animationDataArray[deb_zombieWalk].maxFrame = frame;
  // printf("anim pos size: %d\n",
  // animationDataArray[deb_zombieWalk].position.size());
  frame = 0;
  animationDataArray[deb_zombieNormalAttack] = AnimationData();
  animationDataArray[deb_zombieNormalAttack].position[frame] = Tyra::Vec2(0, 0);
  for (int i = 139; i <= 178; i++) {
    filepath = "Animations/Zombie/Attack/Zombie0";
    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[deb_zombieNormalAttack].texture[frame] = texture;
    frame++;
  }
  animationDataArray[deb_zombieNormalAttack].maxFrame = frame;
}

void loadSunAnimation() {
  animationDataArray[sunAnim] = AnimationData();

  std::string filepath;
  Tyra::Texture* texture;
  int frame = 0;
  animationDataArray[sunAnim].position[frame] = Tyra::Vec2(0, 0);
  for (int i = 1; i <= 13; i++) {
    if (i < 10) {
      filepath = "Animations/sun/sun000";
    } else {
      filepath = "Animations/sun/sun00";
    }

    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[sunAnim].texture[frame] = (texture);
    frame++;
  }
  animationDataArray[sunAnim].maxFrame = frame;
}

void loadSunAnimationDebug() {
  readReanimFiles(Tyra::FileUtils::fromCwd("Sun.reanim"));
}

void loadSunFlowerAnimation() {
  animationDataArray[SunFlowerHead] = AnimationData();

  std::string filepath;
  Tyra::Texture* texture;
  int frame = 0;
  animationDataArray[SunFlowerHead].position[frame] = Tyra::Vec2(0, 0);
  for (int i = 1; i <= 1; i++) {
    if (i < 10) {
      filepath = "Animations/sunflower/SunFlower_double_petals";
    } else {
      filepath = "Animations/sunflower/SunFlower_double_petals";
    }

    // filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[SunFlowerHead].texture[frame] = (texture);
    frame++;
  }
}
