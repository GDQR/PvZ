#pragma once
#include <tyra>
#include <stdio.h>
#include "../font/font.hpp"
#include "../renderSprite/textures.hpp"

enum debugModes { AnimationDebug, SpriteDebug, testDebug, debugModesSize};

extern unsigned int debugOption;

extern bool debugMode;
extern bool debugMenu;
extern bool debugAnimation;
extern bool stopAnimation;
extern bool debugSprite;

extern std::map <int,Tyra::Sprite> debugSpritePointCollider;
extern std::map <int,Tyra::Sprite> debugSpriteBoxCollider;

extern Tyra::Texture* debugBoxTexture;
extern Tyra::Texture* debugFillBoxTexture;
extern Tyra::Texture* debugPointTexture;

void menuDebugMode(Tyra::Pad& pad);
void activeDebugMode();
void deactiveDebugMode();
int startDebugAnimationMode(Tyra::Pad& pad, Tyra::Font& font);

void loadDebugTextures();

void createDebugBoxCollider(const int id, Tyra::SpriteMode mode);
void createDebugBoxFill(const int id, Tyra::SpriteMode mode, Vec2 pos, Vec2 size);
void createDebugPoint(const int id, Tyra::SpriteMode mode);

void deleteDebugBoxCollider(const int id);
void deleteDebugPoint(const int id);