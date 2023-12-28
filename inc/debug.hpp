#pragma once
#include <tyra>
#include <stdio.h>
#include "renderSprite/textures.hpp"

enum debugModes { AnimationDebug, testDebug, debugModesSize};

extern unsigned int debugOption;

extern bool debugMode ;
extern bool debugAnimation;
extern bool stopAnimation;

extern std::map <int,Tyra::Sprite> debugSpritePointCollider;
extern std::map <int,Tyra::Sprite> debugSpriteBoxCollider;

extern Tyra::Texture* debugBoxTexture;
extern Tyra::Texture* debugPointTexture;

void debugMenu();
void activeDebugMode();
void deactiveDebugMode();
void loadDebugTextures();

void createDebugBoxCollider(const int id, Tyra::SpriteMode mode);
void createDebugPoint(const int id, Tyra::SpriteMode mode);

void deleteDebugBoxCollider(const int id);
void deleteDebugPoint(const int id);