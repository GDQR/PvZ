#include "systems.hpp"
#include "font/font.hpp"
#include "imageFiles.hpp"
#include <string>

void createPlantCard(int& plantID,AnimIndex::Animation plantAnim, const Tyra::Vec2 pos, const Tyra::Vec2 size, const int frame) {
  posArray.insert(plantID, pos);
  fatherIDArray.insert(plantID, FatherID());
  PlantAnimation anim;
  anim.id = plantID;

  SetOneSpriteAnimationToEntity(anim.entity, plantID, plantAnim, size, frame);

  plantAnims.push_back(anim);
}

void createCard(const Plant_State_enum typePlant, const Tyra::Vec2 pos,
                const bool isVersusMode) {
  Card card;
  card.seed = Entities::newID();
  card.plantID = Entities::newID();
  printf("seed ID:%d\n",card.seed);

  createSprite(card.seed, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seed, IMG_seeds);
  spriteArray[card.seed].offset.x = 100;

  if (typePlant == Plant_State_enum::PeaShotter) {
    createPlantCard(card.plantID, AnimIndex::Peashooter, Vec2(pos.x, pos.y), Vec2(0.6f, 0.6f),80);
  } else if (typePlant == Plant_State_enum::SunFlower) {
    createPlantCard(card.plantID, AnimIndex::SunFlower, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),8);
  } else if (typePlant == Plant_State_enum::CherryBomb) {
    createPlantCard(card.plantID, AnimIndex::CherryBomb, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),1);
  } else if (typePlant == Plant_State_enum::Wallnut) {
    createPlantCard(card.plantID, AnimIndex::Wallnut, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),1);
  } else if (typePlant == Plant_State_enum::PotatoMine) {
    createPlantCard(card.plantID, AnimIndex::PotatoMine, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),31);
  } else if (typePlant == Plant_State_enum::SnowPea) {
    createPlantCard(card.plantID, AnimIndex::SnowPea, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),80);
  } else if (typePlant == Plant_State_enum::Chomper) {
    createPlantCard(card.plantID, AnimIndex::Chomper, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),1);
  } else if (typePlant == Plant_State_enum::Repeater) {
    createPlantCard(card.plantID, AnimIndex::Repeater, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),80);
  }
  
  card.seedShadow = Entities::newID();
  card.seedShadowTimer = Entities::newID();
  printf("seedShadow ID:%d\n",card.seedShadow);
  printf("seedShadowTimer ID:%d\n",card.seedShadowTimer);

  createSprite(card.seedShadow, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seedShadow, IMG_seeds);
  spriteArray[card.seedShadow].offset.x = 100;
  spriteArray[card.seedShadow].color = Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);

  // TODO: hacer que el seedshadowtimer aparezca despues del "start set plant"
  // cuando el startwitoutwait sea verdadero
  // y crear un efecto para cuando el seed shadow (lo de arriba) se va porque el
  // costo de soles es mayor

  createSprite(card.seedShadowTimer, Tyra::MODE_REPEAT, pos, Vec2(50.0f, 70.0f));
  createTexture(card.seedShadowTimer, IMG_seeds);
  spriteArray[card.seedShadowTimer].offset.x = 100;
  spriteArray[card.seedShadowTimer].color =
      Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);
  
  PS2Timer timer;
  timer.maxMS = getPlantRechargeTime(typePlant, isVersusMode);
  if (startWithoutWait(typePlant, isVersusMode) == true) {
    printf("empece sin esperar\n");
    timer.counterMS = timer.maxMS;
  }
  
  timerArray.insert(card.seedShadowTimer, timer);

  card.plant = typePlant;

  card.cost = getPlantCost(typePlant);

  std::string text;
  text = std::to_string(card.cost);
  card.textID = CreateTextData(text,pos.x+10,pos.y + 55,FontPicoID);

  cards.push_back(card);
}