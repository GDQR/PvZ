#pragma once
#include "linearArrayKey.hpp"
#include <string>
#include <tyra>
#include <unordered_map>
#include <vector>


enum enumDraw { draw = 0, noDraw = -1 };

enum enumSpriteLayer{
  background,
  card_layer,
  plants,
  projectile_layer, 
  zombie_layer,
  sun_layer,
  player_layer
};

enum EnumAnimationProperty{
  ANIM_DRAW,
  ANIM_TEXTURE,
  ANIM_POSITION,
  ANIM_ROTATION,
  ANIM_SCALE,
  ANIM_ALPHA
};

enum EnumAnimationIndex : unsigned char {
  ANIM_Blover,
  ANIM_Cabbagepult,
  ANIM_Cactus,
  ANIM_Spikeweed,  // caltrop
  ANIM_Cattail,
  ANIM_CherryBomb,
  ANIM_Chomper,
  ANIM_CobCannon,
  ANIM_CoffeeBean,
  ANIM_Coin_gold,
  ANIM_Coin_silver,
  ANIM_Kernelpult,  // Cornpult
  ANIM_CrazyDave,
  ANIM_Credits_AnyHour,
  ANIM_Credits_BigBrain,
  ANIM_Credits_Bossdance,
  ANIM_Credits_brainplate,
  ANIM_Credits_CrazyDave,
  ANIM_Credits_DiscoLights,
  ANIM_Credits_Flower_petals,
  ANIM_Credits_Football,
  ANIM_Credits_Infantry,
  ANIM_Credits_Jackbox,
  ANIM_Credits_Main,
  ANIM_Credits_Main2,
  ANIM_Credits_Main3,
  ANIM_Credits_SolarPower,
  ANIM_Credits_stage,
  ANIM_Credits_Throat,
  ANIM_Credits_Tombstones,
  ANIM_Credits_WeAreTheUndead,
  ANIM_Credits_ZombieArmy1,
  ANIM_Credits_ZombieArmy2,
  ANIM_Diamond,
  ANIM_Digger_rising_dirt,
  ANIM_DoomShroom,
  ANIM_FinalWave,
  ANIM_Fire,
  ANIM_FirePea,
  ANIM_FumeShroom,
  ANIM_Garlic,
  ANIM_GatlingPea,
  ANIM_GloomShroom,
  ANIM_GoldMagnet,
  ANIM_GraveBuster,
  ANIM_Hammer,
  ANIM_HypnoShroom,
  ANIM_IceShroom,
  ANIM_Imitater,
  ANIM_Jalapeno,
  ANIM_LawnMower,
  ANIM_LawnMoweredZombie,
  ANIM_LilyPad,
  ANIM_LoadBar_sprout,
  ANIM_LoadBar_Zombiehead,
  ANIM_Magnetshroom,
  ANIM_Marigold,
  ANIM_Melonpult,
  ANIM_PeaShotter,  // PeashooterSingle
  ANIM_Repeater,    // Peashotter
  ANIM_Plantern,
  ANIM_PoolCleaner,
  ANIM_Portal_Circle,
  ANIM_Portal_Square,
  ANIM_FlowerPot,  // Pot
  ANIM_PotatoMine,
  ANIM_puff,
  ANIM_PuffShroom,
  ANIM_Pumpkin,
  ANIM_Rain_circle,
  ANIM_Rain_splash,
  ANIM_Rake,
  ANIM_RoofCleaner,
  ANIM_ScaredyShroom,
  ANIM_SeaShroom,
  ANIM_SelectorScreen,
  ANIM_SelectorScreen_WoodSign,
  ANIM_SlotMachine,
  ANIM_SnowPea,
  ANIM_SodRoll,
  ANIM_Spikerock,
  ANIM_splash,
  ANIM_SplitPea,
  ANIM_Squash,
  ANIM_Starfruit,
  ANIM_StartReadySetPlant,
  ANIM_Stinky,
  ANIM_Sun,
  ANIM_SunFlower,
  ANIM_SunShroom,
  ANIM_Tallnut,
  ANIM_Tanglekelp,
  ANIM_TextFadeOn,
  ANIM_TextSlideDown,
  ANIM_TextSlideOn,
  ANIM_ThreePeater,
  ANIM_Torchwood,
  ANIM_TreeFood,
  ANIM_treeofWisdom,
  ANIM_TreeOfWisdomClouds,
  ANIM_TwinSunflower,
  ANIM_UmbrellaLeaf,
  ANIM_Wallnut,
  ANIM_WinterMelon,
  ANIM_Z,
  ANIM_ZenGarden_bugspray,
  ANIM_ZenGarden_fertilizer,
  ANIM_ZenGarden_phonograph,
  ANIM_ZenGarden_sprout,
  ANIM_ZenGarden_wateringcan,
  ANIM_zombatar_zombie_head,
  ANIM_Zombie,
  ANIM_Zombie_balloon,
  ANIM_Zombie_bobsled,
  ANIM_Zombie_boss,
  ANIM_Zombie_Boss_driver,
  ANIM_Zombie_boss_fireball,
  ANIM_Zombie_boss_iceball,
  ANIM_Zombie_bungi,
  ANIM_Zombie_catapult,
  ANIM_Zombie_charred,
  ANIM_Zombie_charred_catapult,
  ANIM_Zombie_charred_digger,
  ANIM_Zombie_charred_gargantuar,
  ANIM_Zombie_charred_imp,
  ANIM_Zombie_charred_zamboni,
  ANIM_Zombie_credits_conehead,
  ANIM_Zombie_credits_dance,
  ANIM_Zombie_credits_screendoor,
  ANIM_Zombie_dancer,
  ANIM_Zombie_digger,
  ANIM_Zombie_disco,
  ANIM_Zombie_dolphinrider,
  ANIM_Zombie_flagpole,
  ANIM_Zombie_football,
  ANIM_Zombie_gargantuar,
  ANIM_Zombie_hand,
  ANIM_Zombie_imp,
  ANIM_Zombie_jackbox,
  ANIM_Zombie_Jackson,
  ANIM_Zombie_ladder,
  ANIM_Zombie_paper,
  ANIM_Zombie_pogo,
  ANIM_Zombie_PoleVaulter,
  ANIM_Zombie_snorkle,
  ANIM_Zombie_surprise,
  ANIM_Zombie_Target,
  ANIM_Zombie_yeti,
  ANIM_Zombie_zamboni,
  ANIM_ZombiesWon,
  ANIM_enumMax
};

struct FramePos{
   unsigned int frameIndex;
   unsigned int propIndex;
};

struct FrameProperties{
  unsigned int textureIndex = 0;
  unsigned int posIndex = 0;
  unsigned int angleIndex = 0;
  unsigned int drawIndex = 0;
  unsigned int scaleIndex = 0;
  unsigned int alphaIndex = 0;
};

struct FrameProperty{
 int dataIndex;
 EnumAnimationProperty type;
};

struct AnimationTime{
  unsigned short start;
  unsigned short end;
};

class AnimationLayer{
  public:
  std::vector<AnimationTime> timeLapse;
  unsigned int nameID;
  unsigned int layerDataID;
};


// Anim Frames can have 0 or N properties
// AnimationFrameData: 0 or N Properties from 1 frame of 1 layer
typedef std::vector<FrameProperty> AnimationFrameData;

// AnimationLayerData: 1 or N Frames of 1 layer
typedef std::vector<AnimationFrameData> AnimationLayerData;
// Anim Layers can have 1 or N time lapse
// Anim Layers can have 1 or N frames
// AnimationClipData: 1 or N Layers from 1 animation file (clip)
typedef std::vector<AnimationLayer> AnimationClipData;

typedef std::vector<char*> AnimationLayerNameData;

struct AnimIndex {
  
  EnumAnimationIndex type;
  
  unsigned int GetNameID(unsigned int layer);
  unsigned int GetLayerID(unsigned int layer);
  unsigned int GetLayerSize();
  std::vector<AnimationTime> GetTimeLapseFromLayer(unsigned int layer);
  AnimationFrameData& GetFrameProperties(unsigned int layer, unsigned int frame);
  unsigned int GetAnimationNameID(const char* layer);
  FrameProperties GetPropertiesFromOneFrame(unsigned int layerIndex, unsigned int frame);

  void SetOneSpriteAnimationToEntity(std::vector<int>& ids, Tyra::Vec2 size, int frame, enumSpriteLayer layer);
  void SetOneSpriteAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, int frame, enumSpriteLayer layer);
  void SetAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, int firstFrame, int lastFrame, bool repeat, enumSpriteLayer layer);
  void SetAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, const char* animFlash, unsigned int timeIndex, bool repeat, enumSpriteLayer layer);
  void SetAnimationToEntity(std::vector<int>& ids, int& father, Tyra::Vec2 size, int firstFrame, bool repeat, enumSpriteLayer layer);
  void ChangeAnimationEntity(std::vector<int>& ids, const char* animState, unsigned int timeIndex, enumSpriteLayer layer, bool repeat);

  void createAnimation(const int entityID, const int layerID,
                     const Tyra::Vec2 scaleTextures, const int firstFrame,
                     const int lastFrame, bool repeat, enumSpriteLayer layer);
  int activeAnimation(const int entityID, const int layerID,
                                   const unsigned int firstFrame,
                                   const unsigned int lastFrame, enumSpriteLayer layer);
};

class AnimationClip{
  public:
  unsigned int fps;
  unsigned int maxFrame;
  unsigned int layerCount;
};

extern AnimIndex animComponent[EnumAnimationIndex::ANIM_enumMax];

extern std::vector<int> backgroundLayer;
extern std::vector<int> cardLayer;
extern std::vector<int> plantsLayer;
extern std::vector<int> projectileLayer;
extern std::vector<int> sunLayer;
extern std::vector<int> zombieLayer;
extern std::vector<int> playerLayer;


struct FrameOut {
 int entityID;
 int animIndex;
 int layerIndex;
 int frame;
};

class FrameCounter {
 public:
  int update();
  void CheckEvent();
  bool IsLastframe();
  
  bool repeat = true;
  int entityID;
  unsigned int animIndex;
  unsigned int layerIndex;
  unsigned int framesCounter = 0;
  unsigned int currentFrame = 1;
  unsigned int framesSpeed = 24;
  unsigned int firstFrame = 1;
  unsigned int lastFrame = 1;
};

struct LayerData{
  int animID;
  unsigned int nameID;
  int startFrame;
  int endFrame;
};

extern std::vector<int> textureFrame;
extern std::vector<Tyra::Vec2> positionFrame;
extern std::vector<Tyra::Vec2> scaleFrame;
extern std::vector<Tyra::Vec2> angleFrame;
extern std::vector<float> alphaFrame;
extern std::vector<enumDraw> drawFrame;

void initAnimation();
void setSprite(const int entityID, const enumDraw draw, enumSpriteLayer layer);
void loadAnimString();
void loadAnimation(const EnumAnimationIndex animNameID);

void SetAnimationNamesID(EnumAnimationIndex animation);
void attackPlant(const int father);
void finishJump(const int entityID);
