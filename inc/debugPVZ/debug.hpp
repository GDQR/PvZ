#pragma once
#include <tyra>
#include <stdio.h>
#include "../font/font.hpp"
#include "../renderSprite/textures.hpp"

enum debugModes { AnimationDebug, testDebug, debugModesSize};

extern unsigned int debugOption;

extern bool debugMode;
extern bool debugMenu;
extern bool debugAnimation;
extern bool stopAnimation;

extern std::map <int,Tyra::Sprite> debugSpritePointCollider;
extern std::map <int,Tyra::Sprite> debugSpriteBoxCollider;

extern Tyra::Texture* debugBoxTexture;
extern Tyra::Texture* debugFillBoxTexture;
extern Tyra::Texture* debugPointTexture;

void debugMenuMode();
void activeDebugMode();
void deactiveDebugMode();
void debugOptions(Tyra::Pad& pad, Tyra::Font& font);
int startDebugAnimationMode();
void debugAnimationMode(Tyra::Pad& pad, Tyra::Font& font);
void menuDebugAnimation(Tyra::Font& font);

void loadDebugTextures();

void createDebugBoxCollider(const int id, Tyra::SpriteMode mode);
void createDebugBoxFill(const int id, Tyra::SpriteMode mode, Vec2 pos, Vec2 size);
void createDebugPoint(const int id, Tyra::SpriteMode mode);

void deleteDebugBoxCollider(const int id);
void deleteDebugPoint(const int id);