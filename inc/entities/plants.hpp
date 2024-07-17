// File for all plants data

#pragma once
#include <tyra>
#include <vector>

using Tyra::Sprite;

extern Tyra::Texture* projectilePea;
extern int plantsCreated;

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
  void createSpace();

 public:
  Plant_State_enum type = NonePlant;

  std::vector<int> id;

  int father;
  void newPlant(Plant_State_enum newType);
  int attack();
  void ability();
  void erase(const int entityID);
  int attackTimer = 0;
  int row;
  int column;
};

void createPlant(Plant_State_enum typePlant, const int row, const int column);
void loadPlantCost();
void loadPlantAnimString();
int getPlantCost(Plant_State_enum typePlant);