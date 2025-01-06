#pragma once
#include "../renderSprite/textures.hpp"
#include <stdio.h>
#include <tyra>


enum debugModes {
  AnimationDebug,
  SpriteDebug,
  testDebug,
  debugModesSize,
  debugMain
};

extern unsigned int debugState;
extern unsigned int debugOption;

extern bool debugMode;
extern bool debugMenu;
extern bool debugAnimation;
extern bool stopAnimation;
extern bool debugSprite;
extern float debugAlphaColor;
extern float d_texPosXNull;
extern float* d_texPosX;
extern float d_texPosYNull;
extern float* d_texPosY;
extern float* d_scale;
extern float d_angleXNull;
extern float* d_angleX;
extern float d_angleYNull;
extern float* d_angleY;
extern bool d_hasScale;
extern int d_framesCounter;
extern bool d_saveFramesCounter;
extern std::string d_name;
extern int debugEntityId;

extern std::map<int, Tyra::Sprite> dm_SpritePointCollider;
extern std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
extern std::map<int, Tyra::Sprite> dm_SpriteNormal;
extern std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;

// Normal or rotate sprites IDs
extern std::map<int, Tyra::Sprite*> debugSpritesType;
extern std::vector<int> debugStopRenderRotateSprites;
extern std::vector<int> debugStopRenderNormalSprites;

extern Tyra::Texture* debugBoxTexture;
extern Tyra::Texture* debugFillBoxTexture;
extern Tyra::Texture* debugPointTexture;

class DebugMode {
 public:
  bool startDebug = true;
  void mainMenu();
  void spriteModeMenu();
  void drawMainMenu();
  int drawSpriteModeMenu();
};

extern DebugMode debugModeClass;
void activeDebugMode();
void deactiveDebugMode();
int startDebugAnimationMode(Tyra::Pad& pad, Tyra::Font& font);
void loadDebugTextures();

void createDebugSprite(const int id, Tyra::SpriteMode mode);
void createDebugSpritePivot(const int id, Tyra::SpriteMode mode);
void createDebugBoxCollider(const int id, Tyra::SpriteMode mode);
void createDebugBoxFill(const int id, Tyra::SpriteMode mode, Vec2 pos,
                        Vec2 size);
void createDebugPoint(const int id, Tyra::SpriteMode mode);

void deleteDebugSprite(const int id);
void deleteDebugSpritePivot(const int id);
void deleteDebugBoxCollider(const int id);
void deleteDebugPoint(const int id);