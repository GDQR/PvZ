#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
// Animations animations;

void loadPeaShooterAnimation() {
  animationDataArray[peaShooterHead] = AnimationData();
  animationTime[peaShooterHead] = Time();
  animationDataArray[peaShooterBody] = AnimationData();
  animationTime[peaShooterBody] = Time();

  printf("cargando PeaShooter animation\n");
  std::string filepath;
  Tyra::Texture* texture;
  for (int i = 30; i <= 54; i++) {
    filepath = "Animations/PeaShooterSingle/PeaShooterSingle00";
    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[peaShooterHead].keys.push_back(texture);
    animationDataArray[peaShooterHead].position.push_back(new Tyra::Vec2(0,0));
    animationTime[peaShooterHead].seconds.push_back(2);
  }
  texture = loadTexture("Animations/PeaShooterSingle/PeaShooterSingle0005.png");
  animationDataArray[peaShooterBody].keys.push_back(texture);
  animationTime[peaShooterBody].seconds.push_back(20);
}

void loadZombieAnimation() {
  animationDataArray[zombieWalk] = AnimationData();
  animationTime[zombieWalk] = Time();

  printf("cargando Zombie animation\n");
  std::string filepath;
  Tyra::Texture* texture;
  for (int i = 45; i <= 91; i++) {
    filepath = "Animations/Zombie/Zombie00";
    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[zombieWalk].keys.push_back(texture);
    animationDataArray[zombieWalk].position.push_back(new Tyra::Vec2(0,0));
    animationTime[zombieWalk].seconds.push_back(2);
  }

  animationDataArray[zombieNormalAttack] = AnimationData();
  animationTime[zombieNormalAttack] = Time();

  for (int i = 139; i <= 178; i++) {
    filepath = "Animations/Zombie/Attack/Zombie0";
    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[zombieNormalAttack].keys.push_back(texture);
    animationDataArray[zombieNormalAttack].position.push_back(new Tyra::Vec2(0,0));
    animationTime[zombieNormalAttack].seconds.push_back(2);
  }
}

void loadSunAnimation() {
  animationDataArray[sunAnim] = AnimationData();
  animationTime[sunAnim] = Time();

  std::string filepath;
  Tyra::Texture* texture;
  for (int i = 1; i <= 13; i++) {
    if (i < 10) {
      filepath = "Animations/sun/sun000";
    } else {
      filepath = "Animations/sun/sun00";
    }

    filepath += std::to_string(i);
    filepath += ".png";
    texture = loadTexture(filepath);
    animationDataArray[sunAnim].keys.push_back(texture);
    animationDataArray[sunAnim].position.push_back(new Tyra::Vec2(0,0));
    animationTime[sunAnim].seconds.push_back(2);
  }
}

// borrar
// void loadSunSuavizadoAnimation() {
//   animationDataArray[sunAnim2] = AnimationData();
//   animationTime[sunAnim2] = Time();

//   std::string filepath;
//   Tyra::Texture* texture;
//   for (int i = 1; i <= 13; i++) {
//     if(i < 10){
//         filepath = "Animations/sun/suavizado/sun000";
//     }else{
//         filepath = "Animations/sun/suavizado/sun00";
//     }

//     filepath += std::to_string(i);
//     filepath += ".png";
//     texture = loadTexture(filepath);
//     animationDataArray[sunAnim2].keys.push_back(texture);
//     animationTime[sunAnim2].seconds.push_back(2);
//   }
// }