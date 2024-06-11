#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
#include <iostream>
// Animations animations;

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
    std::cout << index << " " <<  x << " " << line << " " << y << '\n';
    animationDataArray[zombieWalk].position[frame] = Tyra::Vec2(x, y);
    animationDataArray[zombieWalk].angle[frame] = angle;
    frame++;
  }

  for(int i=0; i<frame; i++) {
    printf("frame: %d pos: %f,%f\n",i,animationDataArray[zombieWalk].position[i].x,animationDataArray[zombieWalk].position[i].y);
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
