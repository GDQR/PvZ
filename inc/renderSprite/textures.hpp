#pragma once
#include <tyra>
#include <vector>
#include <string>

using Tyra::Sprite;
using Tyra::Vec2;

void loadSprite(Sprite* sprite);
void loadSprite(Sprite* sprite, Vec2 size);
void loadSprite(Sprite* sprite,Tyra::SpriteMode mode, Vec2 position, Vec2 size);

void loadTexture(Sprite* sprite, std::string fileImage);
void loadTexture(int spriteID, std::string fileImage);
Tyra::Texture* loadTexture(std::string fileImage);
// for debug: copy sprite1 texture and paste in sprite2 
void copyTexture(Sprite* sprite1, Sprite* sprite2); 