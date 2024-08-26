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
    Peashooter,
    SunFlower,
    CherryBomb,
    Wallnut,
    PotatoMine,
    SnowPea,
    Chomper,
    Repeater,
    PuffShroom,
    SunShroom,
    FumeShroom,
    GraveBuster,
    HypnoShroom,
    ScaredyShroom,
    IceShroom,
    DoomShroom,
    LilyPad,
    Squash,
    Threepeater,
    Tanglekelp,
    Jalapeno,
    Spikeweed,
    Torchwood,
    Tallnut,
    SeaShroom,
    Plantern,
    Cactus,
    Blover,
    SplitPea,
    Starfruit,
    Pumpkin,
    Magnetshroom,
    Cabbagepult,
    FlowerPot,
    Kernelpult,
    CoffeeBean,
    Garlic,
    UmbrellaLeaf,
    Marigold,
    Melonpult,
    GatlingPea,
    TwinSunflower,
    GloomShroom,
    Cattail,
    WinterMelon,
    GoldMagnet,
    Spikerock,
    CobCannon,
    Imitator,
    Sun,
    Zombie,
    ZombiePoleVaulter,
    ZombieCharred,
    LawnMower,
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
