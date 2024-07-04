#pragma once

#include <vector>
#include "../components.hpp"
// #include <string>

// struct Animations
// {
//     std::vector<std::string> name;
//     std::vector<int> frames; 
// };
// // void loadPeashooterAnim(Plant* t_plant);
void loadAnimationSprite(const int entityID, const int animID);
void loadPeaShooterAnimation();
void loadZombieAnimation();
void loadDebugZombieAnimation();
void loadSunAnimation();
void loadSunFlowerAnimation();
// extern Animations animations;