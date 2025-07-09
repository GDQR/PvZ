#pragma once
#include "linearArrayKey.hpp"
#include <string>
#include <tyra>
#include <unordered_map>
#include <vector>


enum class enumDraw { draw = 0, noDraw = -1 };

enum enumAnimationState {
  normalZombieWalk,
  normalZombieAttack,
  normalZombieCharred,
  poleVaulterWalk,
  explodeCherryBomb,
  enumMaxAnimationState
};

struct AnimIndex {
  enum Animation {
    Blover,
    Cabbagepult,
    Cactus,
    Spikeweed,  // caltrop
    Cattail,
    CherryBomb,
    Chomper,
    CobCannon,
    CoffeeBean,
    Coin_gold,
    Coin_silver,
    Kernelpult,  // Cornpult
    CrazyDave,
    Credits_AnyHour,
    Credits_BigBrain,
    Credits_Bossdance,
    Credits_brainplate,
    Credits_CrazyDave,
    Credits_DiscoLights,
    Credits_Flower_petals,
    Credits_Football,
    Credits_Infantry,
    Credits_Jackbox,
    Credits_Main,
    Credits_Main2,
    Credits_Main3,
    Credits_SolarPower,
    Credits_stage,
    Credits_Throat,
    Credits_Tombstones,
    Credits_WeAreTheUndead,
    Credits_ZombieArmy1,
    Credits_ZombieArmy2,
    Diamond,
    Digger_rising_dirt,
    DoomShroom,
    FinalWave,
    Fire,
    FirePea,
    FumeShroom,
    Garlic,
    GatlingPea,
    GloomShroom,
    GoldMagnet,
    Gravebuster,
    Hammer,
    HypnoShroom,
    IceShroom,
    Imitater,
    Jalapeno,
    LawnMower,
    LawnMoweredZombie,
    LilyPad,
    LoadBar_sprout,
    LoadBar_Zombiehead,
    Magnetshroom,
    Marigold,
    Melonpult,
    Peashooter,  // PeashooterSingle
    Repeater,    // Peashotter
    Plantern,
    PoolCleaner,
    Portal_Circle,
    Portal_Square,
    FlowerPot,  // Pot
    PotatoMine,
    puff,
    PuffShroom,
    Pumpkin,
    Rain_circle,
    Rain_splash,
    Rake,
    RoofCleaner,
    ScaredyShroom,
    SeaShroom,
    SelectorScreen,
    SelectorScreen_WoodSign,
    SlotMachine,
    SnowPea,
    SodRoll,
    Spikerock,
    splash,
    SplitPea,
    Squash,
    Starfruit,
    StartReadySetPlant,
    Stinky,
    Sun,
    SunFlower,
    SunShroom,
    Tallnut,
    Tanglekelp,
    TextFadeOn,
    TextSlideDown,
    TextSlideOn,
    ThreePeater,
    Torchwood,
    TreeFood,
    treeofWisdom,
    TreeOfWisdomClouds,
    TwinSunflower,
    UmbrellaLeaf,
    Wallnut,
    WinterMelon,
    Z,
    ZenGarden_bugspray,
    ZenGarden_fertilizer,
    ZenGarden_phonograph,
    ZenGarden_sprout,
    ZenGarden_wateringcan,
    zombatar_zombie_head,
    Zombie,
    Zombie_balloon,
    Zombie_bobsled,
    Zombie_boss,
    Zombie_Boss_driver,
    Zombie_boss_fireball,
    Zombie_boss_iceball,
    Zombie_bungi,
    Zombie_catapult,
    Zombie_charred,
    Zombie_charred_catapult,
    Zombie_charred_digger,
    Zombie_charred_gargantuar,
    Zombie_charred_imp,
    Zombie_charred_zamboni,
    Zombie_credits_conehead,
    Zombie_credits_dance,
    Zombie_credits_screendoor,
    Zombie_dancer,
    Zombie_digger,
    Zombie_disco,
    Zombie_dolphinrider,
    Zombie_flagpole,
    Zombie_football,
    Zombie_gargantuar,
    Zombie_hand,
    Zombie_imp,
    Zombie_jackbox,
    Zombie_Jackson,
    Zombie_ladder,
    Zombie_paper,
    Zombie_pogo,
    Zombie_PoleVaulter,
    Zombie_snorkle,
    Zombie_surprise,
    Zombie_Target,
    Zombie_yeti,
    Zombie_zamboni,
    ZombiesWon,
    enumMax
  };
};

class AnimationState {
 public:
  AnimationState();
  AnimationState(const unsigned int firstFrame, const unsigned int lastFrame);
  unsigned int firstFrame;
  unsigned int lastFrame;
};

class Animation {
 public:
  Animation();
  Animation(const int anim);
  void update(const int entityID);
  void activeDrawNormalSprites(const int entityID);
  void updateSprites(const int entityID);
  void updateAngle(const int entityID);
  void setAnimation(enumAnimationState animationState);
  void position(const int entityID);
  int debugAnim(const int entitieID);

  int animID = -1;
  int draw = (int)enumDraw::draw;
  unsigned int framesCounter = 0;
  unsigned int currentFrame = 1;
  unsigned int framesSpeed = 20;
  unsigned int firstFrame = 1;
  unsigned int lastFrame = 1;
};

struct FrameOut {
 int entityID;
 int animIndex;
 int frame;
};

class FrameCounter {
 public:
  int update();
  
  int entityID;
  unsigned int animIndex;
  unsigned int framesCounter = 0;
  unsigned int currentFrame = 1;
  unsigned int framesSpeed = 20;
  unsigned int firstFrame = 1;
  unsigned int lastFrame = 1;
};

struct FramesData{
  int animID;
  int frame;
};

extern std::vector<int> textureFrame;
extern std::vector<Tyra::Vec2> positionFrame;
extern std::vector<Tyra::Vec2> scaleFrame;
extern std::vector<Tyra::Vec2> angleFrame;
extern std::vector<float> alphaFrame;
extern std::vector<int> drawFrame;
// extern std::vector<std::vector<FramesData>> textureFrame;
// extern std::vector<std::vector<FramesData>> positionFrame;
// extern std::vector<std::vector<FramesData>> scaleFrame;
// extern std::vector<std::vector<FramesData>> angleFrame;
// std::vector<std::vector<int>> positionFrame;
// std::vector<std::vector<int>> scaleFrame;
// std::vector<std::vector<int>> angleFrame;
// std::vector<std::vector<int>> alphaFrame;
// std::vector<std::vector<int>> drawFrame;
enum EnumAnimationProperty{
  ANIM_TEXTURE,
  ANIM_POSITION,
  ANIM_ROTATION,
  ANIM_SCALE,
  ANIM_ALPHA,
  ANIM_DRAW
};

struct AnimationProperty{
 int dataIndex;
 EnumAnimationProperty type;
};

class AnimationData {
 public:
  std::unordered_map<unsigned int,std::vector<AnimationProperty>> property;
  unsigned int maxFrame;
  const char* name;
  // std::vector<
  // std::vector<int> texture;
  // std::vector<Tyra::Vec2> position;
  // std::vector<Tyra::Vec2> scale;
  // std::vector<Tyra::Vec2> angle;
  // std::vector<float> alpha;
  // std::vector<int> draw;
  // LinearArrayKey<unsigned int, int> texture;
  // LinearArrayKey<unsigned int, Tyra::Vec2> position;
  // LinearArrayKey<unsigned int, Tyra::Vec2> scale;
  // LinearArrayKey<unsigned int, Tyra::Vec2> angle;
  // LinearArrayKey<unsigned int, float> alpha;
  // LinearArrayKey<unsigned int, int> draw;
  void loadAnimation(const int entityID, const int animID,
                     const Tyra::Vec2 scaleTextures,
                     enumAnimationState animationState);
  void loadAnimation(const int entityID, const int animID,
                     const Tyra::Vec2 scaleTextures, const int firstFrame,
                     const int lastFrame);
  int activeAnimation(const int entityID, const unsigned int firstFrame,
                      const unsigned int lastFrame);
  void setAnimationState(const int entityID, enumAnimationState animationState);
};

extern AnimationState animationStateVector[enumMaxAnimationState];
extern std::string animString[AnimIndex::enumMax];

void setSprite(const int entityID, const int draw);
void loadAnimString();
void loadAnimationStates();
void loadAnimation(const AnimIndex::Animation animNameID);
void SetAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, int firstFrame, int lastFrame);
void SetAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, enumAnimationState animState);
void SetAnimationToEntity(std::vector<int>& ids, int& father, AnimIndex::Animation anim, Tyra::Vec2 size, int firstFrame);
void ChangeAnimationEntity(std::vector<int>& ids, AnimIndex::Animation anim, enumAnimationState animState);