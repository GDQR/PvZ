// File for all plants data

#pragma once
#include <tyra>
#include <vector>

using Tyra::Sprite;

extern Tyra::Texture* projectilePea;
extern Tyra::Texture* projectileSnowPea;
extern int plantsCreated;

enum Plant_Recharge_Time_enum { fast, slow, verySlow, enumMaxRecharge };

extern int plantRechargeTime[enumMaxRecharge];

enum Plant_State_enum {
  PeaShotter,
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
  enumMaxPlants,
  NonePlant
};

extern std::string plantsAnim[enumMaxPlants];

class Plant {
 public:
  std::vector<int> id;

  Plant_State_enum type = NonePlant;
  int father;
  int row;
  int column;
  void newPlant(Plant_State_enum newType);
  int attack();
  void ability();
  void erase();
};

void createPlant(Plant_State_enum typePlant, const int row, const int column);
void loadPlantCost();
void loadPlantAnimString();
void loadPlantRechargeTime();
int getPlantCost(Plant_State_enum typePlant);
int getPlantRechargeTime(Plant_State_enum typePlant, bool isVersusMode);
bool startWithoutWait(Plant_State_enum typePlant, bool isVersusMode);