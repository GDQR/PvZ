#pragma once
#include <vector>
#include <string>
void setSprite(const int entityID, const int animID, const bool draw);
void activeAnimation(const int entityID, const int animID, const int firstFrame, const int lastFrame);
void loadAnimationSprite(const int entityID, const int animID);
void loadAnimation(std::string animName);
