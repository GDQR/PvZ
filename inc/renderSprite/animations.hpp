#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <tyra>
#include "linearArrayKey.hpp"

enum class enumDraw { draw = 0, noDraw = -1 };

enum enumAnimationState {
  normalZombieWalk,
  normalZombieAttack,
  poleVaulterWalk,
  explodeCherryBomb,
  enumMaxAnimationState
};

struct AnimIndex {
  enum Animation {
    Blover,
    Cabbagepult,
    Cactus,
    Spikeweed, //caltrop
    Cattail,
    CherryBomb,
    Chomper,
    CobCannon,
    CoffeeBean,
    Coin_gold,
    Coin_silver,
    Kernelpult, // Cornpult
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
    Peashooter, // PeashooterSingle
    Repeater, // Peashotter
    Plantern,
    PoolCleaner,
    Portal_Circle,
    Portal_Square,
    FlowerPot, // Pot
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

class AnimationData {
 public:
  unsigned int maxFrame;
  std::string name;
  LinearArrayKey<unsigned int, int> texture;
  LinearArrayKey<unsigned int, Tyra::Vec2> position;
  LinearArrayKey<unsigned int, Tyra::Vec2> scale;
  LinearArrayKey<unsigned int, Tyra::Vec2> angle;
  LinearArrayKey<unsigned int, float> alpha;
  LinearArrayKey<unsigned int, int> draw;
  void loadAnimation(const int entityID, const int animID,
                     enumAnimationState animationState);
  void loadAnimation(const int entityID, const int animID, const int firstFrame,
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
