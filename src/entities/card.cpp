#include "systems.hpp"

void createCardPeashotter(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  fatherIDArray.insert(plantID[0], FatherID());

  for (unsigned int i = 0;
       i < m_animID[AnimIndex::Peashooter].size(); i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::Peashooter][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 80, 80);
    // spriteArray[entityID].scale = 0.5f;
    // scaleTexture[entityID] = Vec2(0.5f,0.5f);
    // printf("scaleTexture: %s\n",scaleTexture[entityID].getPrint().c_str());
  }
}

void createCardSunFlower(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  fatherIDArray.insert(plantID[0], FatherID());

  for (unsigned int i = 0; i < m_animID[AnimIndex::SunFlower].size();
       i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::SunFlower][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 8, 8);
  }
}

void createCardCherryBomb(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  fatherIDArray.insert(plantID[0], FatherID());

  for (unsigned int i = 0;
       i < m_animID[AnimIndex::CherryBomb].size(); i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::CherryBomb][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 1, 1);
  }
}

void createCardWallnut(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  for (unsigned int i = 0; i < m_animID[AnimIndex::Wallnut].size();
       i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::Wallnut][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 1, 1);
  }
}

void createCardPotatoMine(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  for (unsigned int i = 0;
       i < m_animID[AnimIndex::PotatoMine].size(); i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::PotatoMine][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 31, 31);
  }
}

void createCardSnowPea(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  for (unsigned int i = 0; i < m_animID[AnimIndex::SnowPea].size();
       i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::SnowPea][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 80, 80);
  }
}

void createCardChomper(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  for (unsigned int i = 0; i < m_animID[AnimIndex::Chomper].size();
       i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::Chomper][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 1, 1);
  }
}

void createCardRepeater(std::vector<int>& plantID, const Tyra::Vec2 pos) {
  int entityID;
  int animID;

  plantID.push_back(Entities::newID());
  posArray.insert(plantID[0], pos);
  for (unsigned int i = 0;
       i < m_animID[AnimIndex::Repeater].size(); i++) {
    entityID = Entities::newID();
    plantID.push_back(entityID);
    animID = m_animID[AnimIndex::Repeater][i];
    newFatherID(&plantID[0], &entityID);
    animationDataArray[animID].loadAnimation(entityID, animID, Tyra::Vec2(0.6f,0.6f), 80, 80);
  }
}

void createCard(const Plant_State_enum typePlant, const Tyra::Vec2 pos,
                const bool isVersusMode) {
  Card card;
  card.seed = Entities::newID();
  card.seedShadow = Entities::newID();
  card.seedShadowTimer = Entities::newID();

  createSprite(card.seed, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seed, "UI/Seeds.png");
  spriteArray[card.seed].offset.x = 100;

  createSprite(card.seedShadow, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seedShadow, "UI/Seeds.png");
  spriteArray[card.seedShadow].color = Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);

  // TODO: hacer que el seedshadowtimer aparezca despues del "start set plant"
  // cuando el startwitoutwait sea verdadero
  // y crear un efecto para cuando el seed shadow (lo de arriba) se va porque el
  // costo de soles es mayor

  createSprite(card.seedShadowTimer, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(card.seedShadowTimer, "UI/Seeds.png");
  spriteArray[card.seedShadowTimer].color =
      Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);

  timerArray.insert(card.seedShadowTimer, PS2Timer());
  timerArray[card.seedShadowTimer].maxMS = 0;
  // getPlantRechargeTime(typePlant, isVersusMode);
  if (startWithoutWait(typePlant, isVersusMode) == true) {
    timerArray[card.seedShadowTimer].counterMS =
        timerArray[card.seedShadowTimer].maxMS;
  }

  card.plant = typePlant;

  card.cost = getPlantCost(typePlant);

  if (typePlant == Plant_State_enum::PeaShotter) {
    createCardPeashotter(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::SunFlower) {
    createCardSunFlower(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::CherryBomb) {
    createCardCherryBomb(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::Wallnut) {
    createCardWallnut(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::PotatoMine) {
    createCardPotatoMine(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::SnowPea) {
    createCardSnowPea(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::Chomper) {
    createCardChomper(card.plantID, Vec2(pos.x, pos.y));
  } else if (typePlant == Plant_State_enum::Repeater) {
    createCardRepeater(card.plantID, Vec2(pos.x, pos.y));
  }

  cards.push_back(card);
}