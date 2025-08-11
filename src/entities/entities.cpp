#include "PVZ.hpp"
#include "font/font.hpp"
#include "imageFiles.hpp"
#include <stdio.h>

Tyra::Vec2 cameraPos(0.0f, 0.0f);
bool rewardExist = false;

Tyra::Engine* engine;
Tyra::Renderer* renderer;
Tyra::Renderer2D* renderer2D;
Tyra::Pad* pad;
const Tyra::PadJoy* leftJoy;
Tyra::TextureRepository* texRepo;

int zombiescreated;
ZombieRow zombieCreateRow[5];
bool mapEnable[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

Plant plant[maxPlants];
Tyra::Sprite d_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpritePointCollider;
std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpriteNormal;
std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;

void BackgroundEntity::initJPG(const char* JPGfile, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight){
  JpgScaleData textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(JPGfile).c_str(),scaleWidth,scaleHeight);
  SetBigImage(this, &textures,mode,x,y,width,height);
  rowTextures = textures.width;

  while (textures.data.size()!=0)
  {
    delete textures.data[0];
    textures.data.erase(textures.data.begin()+0);
  }
}

void BackgroundEntity::initJPG(Tyra::Texture* texture, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight){
  // JpgScaleData textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(JPGfile).c_str(),scaleWidth,scaleHeight);
  JpgScaleData textures = JpgImageScale::load(texture,scaleWidth,scaleHeight,TEXTURE_COMPONENTS_RGBA);
  SetBigImage(this, &textures,mode,x,y,width,height);
  rowTextures = textures.width;

  // while (textures.data.size()!=0)
  // {
  //   delete textures.data[0];
  //   textures.data.erase(textures.data.begin()+0);
  // }
}

void BackgroundEntity::move(){
  for(unsigned int i=0;i<id.size();i++){
    posArray[id[i]].x--;
  }
}

void BackgroundEntity::scale(){
  if(engine->pad.getClicked().DpadLeft){
    int k=0;
    int l=0;
    for(unsigned int i=0;i<id.size();i++){
      posArray[id[i]].x -= k;
      posArray[id[i]].y -= l;
      spriteArray[id[i]].size.x--;
      spriteArray[id[i]].size.y--;
      k++;
      if(k==7){
        k=0;
        l++;
      }
    }
    spriteArray[id[0]].size.print();
  }else if(engine->pad.getClicked().DpadRight){
    int k=0;
    int l=0;
    for(unsigned int i=0;i<id.size();i++){
      posArray[id[i]].x += k;
      posArray[id[i]].y += l;
      spriteArray[id[i]].size.x++;
      spriteArray[id[i]].size.y++;
      k++;
      if(k==7){
        k=0;
        l++;
      }
    }
    spriteArray[id[0]].size.print();
  }
}

void BackgroundEntity::scaleTest(int width, int height){
  int k=0;
  int l=0;
  for(unsigned int i=0;i<id.size();i++){
    posArray[id[i]].x += k;
    posArray[id[i]].y += l;
    spriteArray[id[i]].size.x += width;
    spriteArray[id[i]].size.y += height;
    k++;
    if(k == rowTextures){
      k=0;
      l++;
    }
  }
  spriteArray[id[0]].size.print();
}

void createPlantCard(int& plantID,AnimIndex::Animation plantAnim, const Tyra::Vec2 pos, const Tyra::Vec2 size, const int frame) {
  posArray.insert(plantID, pos);
  fatherIDArray.insert(plantID, FatherID());
  PlantAnimation anim;
  anim.id = plantID;

  SetOneSpriteAnimationToEntity(anim.entity, plantID, plantAnim, size, frame);

  plantAnims.push_back(anim);
}

void createPlantCard(int& plantID,AnimIndex::Animation plantAnim, const Tyra::Vec2 pos, const Tyra::Vec2 size, const Tyra::Color color, const int frame) {
  posArray.insert(plantID, pos);
  fatherIDArray.insert(plantID, FatherID());
  PlantAnimation anim;
  anim.id = plantID;

  SetOneSpriteAnimationToEntity(anim.entity, plantID, plantAnim, size, frame);

  for(size_t i=0; i < anim.entity.size();i++){
    spriteArray[anim.entity[i]].color = color;
  }

  plantAnims.push_back(anim);
}

void createCard(const Plant_State_enum typePlant, const bool isVersusMode) {
  Card card;
  card.seed = Entities::newID();
  card.plantID = Entities::newID();
  printf("seed ID:%d\n",card.seed);
  
  Tyra::Vec2 pos;
  pos.x = 120;
  pos.y = 10;

  pos.x += cards.size() * 60;

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

void Player::init(Tyra::Vec2 cursorPos,Tyra::Vec2 deckPos){
  printf("init Player\n");
  static int countPlayer = 0;
  id = cursor.size();
  printf("playerID: %d\n",id);
  // controllerID = countPlayer;
  Controller newController;
  newController.playerID = countPlayer;
  controller.push_back(newController);
  countPlayer++;
  initCursor(cursorPos);
  initDeckCard(deckPos);
  initPlant();
}

void Player::initCursor(Tyra::Vec2 cursorPos){
  printf("init Cursor\n");
  Cursor newCursor;
  newCursor.id = Entities::newID();
  createSprite(newCursor.id, Tyra::MODE_STRETCH, cursorPos, Vec2(56, 48));
  createTexture(newCursor.id, "cursor6.png");
  createBoxCollider(newCursor.id, BoxColliderEnum::BOXCOLLIDER_PLAYER, BoxCollider(newCursor.id,cursorPos.x + 28 / 2, cursorPos.y + 24 / 2, 24, 24));
  // createDebugBoxCollider(newCursor.id, BoxColliderEnum::BOXCOLLIDER_PLAYER, Tyra::MODE_STRETCH);

  cursor.push_back(newCursor);
}

void Player::initDeckCard(Tyra::Vec2 pos){
  if(cards.size() == 0){
    TYRA_TRAP("CARDS DOESN'T EXIST");
  }
  printf("init Deck\n");

  DeckCursor newDeckCursor;

  newDeckCursor.id = Entities::newID();
  // printf("deck cursor id: %d\n", deckCursor[controllerID].id);
  createSprite(newDeckCursor.id, Tyra::MODE_STRETCH, pos, Vec2(56, 48));
  createTexture(newDeckCursor.id, "cursor6.png");
  deckCursor.push_back(newDeckCursor);

  // boxColliderArray[deckCursor[*player].id] = BoxCollider(
  //     pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  // createDebugBoxCollider(deckCursor[*player].id, Tyra::MODE_STRETCH);
}

void Player::initPlant(){
  printf("init plant\n");
  
  std::vector<BoxCollider>& vec = boxColliderArray[BOXCOLLIDER_MAP];
  int mapID = map[cursor[id].tileX][cursor[id].tileY];
  Tyra::Vec2 pos = Vec2(vec[boxColliderArrayID[mapID]].x,vec[boxColliderArrayID[mapID]].y);
  switch (cards[deckCursor[id].pos].plant){
  case Plant_State_enum::PeaShotter:
    createPlantCard(id,AnimIndex::Peashooter, pos, Vec2(0.6f, 0.6f),Tyra::Color(128,128,128,64),80);
    break;
  case Plant_State_enum::SunFlower:
    createPlantCard(id,AnimIndex::SunFlower, pos, Vec2(0.6f, 0.6f),Tyra::Color(128,128,128,64),8);
    break;
  case Plant_State_enum::CherryBomb:
    createPlantCard(id,AnimIndex::CherryBomb, pos, Vec2(0.6f, 0.6f),Tyra::Color(128,128,128,64),1);
    break;
  default:
    TYRA_TRAP("Error Creating the plant");
    break;
  }
}

void LawnMower::move(){
    if(canMove == true && posArray[id[0]].x < 550){
        posArray[id[0]].x+=2;
        for(BoxCollider& box: boxColliderLawnmower){
          if(box.id == id[0]){
            box.x+=2;
            break;
          }
        }
    }
}

using namespace Entity;
void rewardLevel1(Tyra::Vec2 pos) {
  reward.father = Entities::newID();
  int id;
  int animID;

  createSprite(reward.father, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(reward.father, "UI/Seeds.png");
  spriteArray[reward.father].offset.x = 100;

  fatherIDArray.insert(reward.father, FatherID());

  for (unsigned int i = 0; i < m_animID[AnimIndex::SunFlower].size(); i++) {
    id = Entities::newID();
    reward.id.push_back(id);
    animID = m_animID[AnimIndex::SunFlower][i];
    newFatherID(&reward.father, &id);
    animationDataArray[animID].loadAnimation(id, animID, Tyra::Vec2(0.6f, 0.6f),
                                             8, 8);
  }
  createBoxCollider(reward.father,BoxColliderEnum::BOXCOLLIDER_REWARD,BoxCollider(pos.x, pos.y, 28, 38));

  createDebugBoxCollider(reward.father,BoxColliderEnum::BOXCOLLIDER_REWARD, Tyra::MODE_STRETCH);
  rewardExist = true;
}

void eraseRewardLevel1() {
  deletePosArray(reward.father);
  unsigned int animSize = m_animID[AnimIndex::SunFlower].size();
  for (unsigned int i = 0; i < animSize; i++) {
    deletePosArray(reward.id[i]);
    deleteFinalPosArray(reward.id[i]);
    deleteFatherIDChild(reward.father, &reward.id[i]);

    deleteSprite(reward.id[i]);

    for(size_t j=0; j<frameCounterArray.size();j++){
      if(frameCounterArray[j].entityID == reward.id[i]){
        frameCounterArray.erase(frameCounterArray.begin() + j);
        break;
      }
    }
    deleteTexPosArray(reward.id[i]);
    Entities::deleteID(reward.id[i]);
  }
  deleteSprite(reward.father);
  deleteFatherID(reward.father);
  // boxColliderArray.erase(reward.father);
  deleteDebugBoxCollider(reward.father);
  Entities::deleteID(reward.father);
  rewardExist = false;
}

void eraseReward() { eraseRewardLevel1(); }

void createReward(Tyra::Vec2 pos) {
  if (maxZombies == zombiesDefeated) {
    printf("crear premio\n");
    rewardLevel1(pos);
  }
}

int sunsCreated = 0;
int sunCounter = 1000;
int sunTimer = 60 * 6;
SunManager sunManager;

void SunManager::create(Tyra::Vec2 position, sunCost cost,
                        bool createdByPlant) {  
  Sun newSun;           
  newSun.cost = cost;
  newSun.father = Entities::newID();
  posArray.insert(newSun.father, position);

  fatherIDArray.insert(newSun.father, FatherID());

  if (createdByPlant == false) {
    NaturalSun newNaturalSun;
    newNaturalSun.father = newSun.father;
    naturalSun.push_back(newNaturalSun);
  }
  
  SetAnimationToEntity(newSun.id,newSun.father,AnimIndex::Sun,Tyra::Vec2(0.5f, 0.5f), 1, 12);

  // HitBox
  createBoxCollider(newSun.father,BoxColliderEnum::BOXCOLLIDER_SUN,BoxCollider(newSun.father, position.x-16,
                  position.y-16, 32, 32));
  createDebugBoxCollider(newSun.father, BoxColliderEnum::BOXCOLLIDER_SUN, Tyra::MODE_STRETCH);

  sunsCreated++;
  sun.push_back(newSun);
}

void SunManager::update(){
  if (debugMode == false) {
    updateNaturalSun();
  }

  if (stopAnimation == false) {
    createByTime();
    erase(cursor[0].id);
  }
}

void Sun::erase(const int cursorID) {
    printf("Deleting sun\n");
    sunCounter += cost;
    textArray[sunCounterText].text = std::to_string(sunCounter);

    for(size_t i=0; i<boxColliderSun.size();i++){
      if(boxColliderSun[i].id == father){
        boxColliderSun.erase(boxColliderSun.begin() + i);
      }
    }
    
    int size;
    while (id.size() > 0) {
      size = id.size()-1;
      // deleteDebugSprite(id[i]);
      // deleteDebugSpritePivot(id[i]);
      deleteSprite(id[size]);
      deleteTexPosArray(id[size]);
      deleteFatherIDChild(father, &id[size]);
      for(size_t j=0; j<frameCounterArray.size();j++){
        if(frameCounterArray[j].entityID == id[size]){
          frameCounterArray.erase(frameCounterArray.begin() + j);
        }
      }
      Entities::deleteID(id[size]);
      id.erase(id.begin()+size);
    }

    // delete natural sun if exists
    for (unsigned int i = 0; i < naturalSun.size(); i++) {
      if (naturalSun[i].father == father) {
        naturalSun.erase(naturalSun.begin() + i);
        break;
      }
    }

    deletePosArray(father);
    deleteFatherID(father);
    Entities::deleteID(father);
    sunsCreated--;
}

void NaturalSun::move() {
  Tyra::Vec2& pos = posArray[father];
  if (pos.y < 370) {
    pos.y++;
    for(size_t i=0;i<boxColliderSun.size();i++){
      if(boxColliderSun[i].id == father){
        boxColliderSun[i].y++;
        break;
      }
    }
  }
}

void SunManager::createByTime() {
  if (sunTimer > 0) {
    sunTimer--;
  } else {
    sunTimer = 60 * 6;  // 6 seconds
    // min:50 max:420
    float x = 50 + rand() % 420;
    create(Vec2(x, 10), sunCost::normalSun, false);
  }
}

void SunManager::erase(const int cursorID) {
  size_t size = responseCollisionSunCursor.size();
  size_t sunSize;
  for(size_t i=0; i < size; i++){
    sunSize = sun.size();
    for(size_t j=0;j< sunSize;j++){
      if(sun[j].father == responseCollisionSunCursor[i].sunID){
        sun[j].erase(responseCollisionSunCursor[i].cursorID);
        break;
      }
    }
  }
}
void SunManager::updateNaturalSun() {
  for (NaturalSun& sun: naturalSun){
    sun.move();
  }
}

namespace Entity {
Reward reward;
Player player;
int background;
BackgroundEntity backgroundIDs;
BackgroundEntity awardbackground;
int sodRoll;
int sodRollCap;
int sodRollRow1;
int sodRollRow1Alpha;
int sod3Row;
int sod3RowAlpha;
int fullFlagMeter;
int zombieFlagMeter;
}  // namespace Entity

unsigned int Entities::counter = 1;
std::vector<unsigned int> Entities::aliveEntities;
std::vector<unsigned int> Entities::deadEntities;

unsigned int Entities::newID() {
  // printf("deadEntities.size(): %d\n",deadEntities.size());
  if (deadEntities.size() == 0) {
    // printf("net entity: %d\n",counter);
    return counter++;
  }
  unsigned int oldID = deadEntities.front();
  deadEntities.erase(deadEntities.begin());
  return oldID;
}

void Entities::deleteID(unsigned int& id) {
  int newID = id;
  deadEntities.push_back(newID);
  // printf("entity Deleted: %d\n",newID);
  id = 0;
}

void Entities::deleteID(int& id) {
  int newID = id;
  deadEntities.push_back(newID);
  // printf("entity Deleted: %d\n",newID);
  id = 0;
}
