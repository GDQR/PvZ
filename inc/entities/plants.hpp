// File for all plants data

#pragma once
#include <tyra>
#include <vector>

using Tyra::Sprite;

extern Tyra::Texture* projectilePea;
extern int plantsCreated;

enum Plant_State_enum {
  NonePlant,
  PeaShotter,
  SunFlower,
  CherryBomb,
  Wall_Nut,
  PotatoMine,
  SnowPea,
  Chomper,
  Repeater,
  Puff_shroom,
  Sun_shroom,
  Fume_shroom,
  GraveBuster,
  Hypno_shroom,
  Scaredy_shroom,
  Ice_shroom,
  Doom_shroom,
  LilyPad,
  Squash,
  Threepeater,
  Tangle_Kelp,
  Jalapeno,
  Spikeweed,
  Torchwood,
  Tall_nut,
  Sea_shroom,
  Plantern,
  Cactus,
  Blover,
  SplitPea,
  Starfruit,
  Pumpkin,
  Magnet_shroom,
  Cabbage_pult,
  Flower_Pot,
  Kernel_pult,
  CoffeeBean,
  Garlic,
  UmbrellaLeaf,
  Marigold,
  Melon_pult,
  GatlingPea,
  TwinSunflower,
  Gloom_shroom,
  Cattail,
  WinterMelon,
  GoldMagnet,
  Spikerock,
  CobCannon
};

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
int getPlantCost(Plant_State_enum typePlant);