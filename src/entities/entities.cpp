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

std::vector<PlantAnimation> cardsAnimations;

void BigSpriteJPG::initJPG(const char* JPGfile, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight){
  BigTexture textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(JPGfile).c_str(),scaleWidth,scaleHeight);
  SetBigImage(this, &textures,mode,x,y,width,height);
  rowTextures = textures.width;

  while (textures.data.size()!=0)
  {
    delete textures.data[0];
    textures.data.erase(textures.data.begin()+0);
  }
}

void BigSpriteJPG::initJPG(Tyra::Texture* texture, Tyra::SpriteMode mode, float x, float y, float width, float height, TextureScale scaleWidth, TextureScale scaleHeight){
  // BigTexture textures = JpgImageScale::load(Tyra::FileUtils::fromCwd(JPGfile).c_str(),scaleWidth,scaleHeight);
  BigTexture textures = JpgImageScale::load(texture,scaleWidth,scaleHeight,TEXTURE_COMPONENTS_RGBA);
  SetBigImage(this, &textures,mode,x,y,width,height);
  rowTextures = textures.width;

  // while (textures.data.size()!=0)
  // {
  //   delete textures.data[0];
  //   textures.data.erase(textures.data.begin()+0);
  // }
}

void BigSpriteJPG::move(){
  for(unsigned int i=0;i<id.size();i++){
    posArray[id[i]].x--;
  }
}

void BigSpriteJPG::scale(){
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

void BigSpriteJPG::scaleTest(int width, int height){
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

void createPlantCard(int& plantID,EnumAnimationIndex plantAnim, const Tyra::Vec2 pos, const Tyra::Vec2 size, const int frame) {
  posArray.insert(plantID, pos);
  fatherIDArray.insert(plantID, FatherID());
  PlantAnimation anim;
  anim.id = plantID;

  animComponent[plantAnim].SetOneSpriteAnimationToEntity(anim.entity,plantID, Tyra::Vec2(0.6f,0.6f), frame, card_layer);

  plantAnims.push_back(anim);

  PlantAnimation cardAnim;
  animComponent[plantAnim].SetOneSpriteAnimationToEntity(cardAnim.entity, Tyra::Vec2(0.6f,0.6f), frame, card_layer);
    
  for(size_t i=0; i < cardAnim.entity.size();i++){
    if(spriteArray.count(cardAnim.entity[i]) == 1){
      bool hasRender = false;
      for(size_t j=0; j < cardLayer.size();j++){
        if(cardLayer[j] == cardAnim.entity[i]){
          hasRender = true;
          break;
        }
      }
      if(hasRender == true){
        spriteArray[cardAnim.entity[i]].color = Tyra::Color(128,128,128,64);
      }else{
        spriteArray.erase(cardAnim.entity[i]);
      }
    }
  }

  cardsAnimations.push_back(cardAnim);
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

  createSprite(card.seed, Tyra::MODE_REPEAT, pos, Vec2(50, 70), enumSpriteLayer::card_layer);
  createTexture(card.seed, IMG_seeds);
  spriteArray[card.seed].offset.x = 100;

  // printf("plant type: %d\n",typePlant);
  if (typePlant == Plant_State_enum::PeaShotter) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_PeaShotter, Vec2(pos.x, pos.y), Vec2(0.6f, 0.6f),80);
  } else if (typePlant == Plant_State_enum::SunFlower) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_SunFlower, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),8);
  } else if (typePlant == Plant_State_enum::CherryBomb) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_CherryBomb, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),1);
  } else if (typePlant == Plant_State_enum::Wallnut || typePlant == Plant_State_enum::WallnutBowling || typePlant == Plant_State_enum::WallnutBowlingExplosion) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_Wallnut, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),1);
  } else if (typePlant == Plant_State_enum::PotatoMine) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_PotatoMine, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),31);
  } else if (typePlant == Plant_State_enum::SnowPea) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_SnowPea, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),80);
  } else if (typePlant == Plant_State_enum::Chomper) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_Chomper, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),1);
  } else if (typePlant == Plant_State_enum::Repeater) {
    createPlantCard(card.plantID, EnumAnimationIndex::ANIM_Repeater, Vec2(pos.x, pos.y+5), Vec2(0.6f, 0.6f),80);
  }
  
  card.seedShadow = Entities::newID();
  card.seedShadowTimer = Entities::newID();
  // printf("seedShadow ID:%d\n",card.seedShadow);
  // printf("seedShadowTimer ID:%d\n",card.seedShadowTimer);

  createSprite(card.seedShadow, Tyra::MODE_REPEAT, pos, Vec2(50, 70), enumSpriteLayer::card_layer);
  createTexture(card.seedShadow, IMG_seeds);
  spriteArray[card.seedShadow].offset.x = 100;
  spriteArray[card.seedShadow].color = Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);

  // TODO: hacer que el seedshadowtimer aparezca despues del "start set plant"
  // cuando el startwitoutwait sea verdadero
  // y crear un efecto para cuando el seed shadow (lo de arriba) se va porque el
  // costo de soles es mayor

  createSprite(card.seedShadowTimer, Tyra::MODE_REPEAT, pos, Vec2(50.0f, 70.0f), enumSpriteLayer::card_layer);
  createTexture(card.seedShadowTimer, IMG_seeds);
  spriteArray[card.seedShadowTimer].offset.x = 100;
  spriteArray[card.seedShadowTimer].color =
      Tyra::Color(0.0F, 0.0F, 0.0F, 60.0F);
  
  PS2Timer timer;
  timer.maxMS = getPlantRechargeTime(typePlant, isVersusMode);
  if (startWithoutWait(typePlant, isVersusMode) == true) {
    // printf("I started without waiting\n");
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
  id = Entities::newID();
  cursorID = cursor.size();
  // printf("playerID: %d\n",id);
  // controllerID = countPlayer;
  Controller newController;
  newController.playerID = id;
  newController.cursorID = cursorID;
  controller.push_back(newController);
  countPlayer++;
  initCursor(cursorPos);
  initDeckCard(deckPos);
  initPlant();
}

void Player::initCursor(Tyra::Vec2 cursorPos){
  // printf("init Cursor\n");
  Cursor newCursor;
  newCursor.id = Entities::newID();
  // printf("cursorID: %d\n",newCursor.id);
  createSprite(newCursor.id, Tyra::MODE_STRETCH, cursorPos, Vec2(56, 48), enumSpriteLayer::player_layer);
  createTexture(newCursor.id, "cursor6.png");
  createBoxCollider(newCursor.id, BoxColliderEnum::BOXCOLLIDER_PLAYER, BoxCollider(newCursor.id,cursorPos.x + 28 / 2, cursorPos.y + 24 / 2, 24, 24));
  // createDebugBoxCollider(newCursor.id, BoxColliderEnum::BOXCOLLIDER_PLAYER, Tyra::MODE_STRETCH);

  cursor.push_back(newCursor);
}

void Player::initDeckCard(Tyra::Vec2 pos){
  if(cards.size() == 0){
    TYRA_TRAP("CARDS DOESN'T EXIST");
  }
  // printf("init Deck\n");

  DeckCursor newDeckCursor;

  newDeckCursor.id = Entities::newID();
  // printf("deck cursor id: %d\n", deckCursor[controllerID].id);
  createSprite(newDeckCursor.id, Tyra::MODE_STRETCH, pos, Vec2(56, 48), enumSpriteLayer::player_layer);
  createTexture(newDeckCursor.id, "cursor6.png");
  deckCursor.push_back(newDeckCursor);

  // boxColliderArray[deckCursor[*player].id] = BoxCollider(
  //     pos.x, pos.y, 24, 24, 28 / 2, 24 / 2);
  // createDebugBoxCollider(deckCursor[*player].id, Tyra::MODE_STRETCH);
}

void Player::initPlant(){
  // printf("init plant\n");
  
  std::vector<BoxCollider>& vec = boxColliderArray[BOXCOLLIDER_MAP];
  // printf("cursor index: %d\n",cursorID);
  int mapID = map[cursor[cursorID].tileX][cursor[cursorID].tileY];
  Tyra::Vec2 pos = Vec2(vec[boxColliderArrayID[mapID]].x,vec[boxColliderArrayID[mapID]].y);
  
  posArray.insert(id, pos);
  fatherIDArray.insert(id, FatherID());

  size_t deckCursorPos = deckCursor[cursorID].pos;
  size_t size = cardsAnimations.size();
  for(size_t j=0; j < size; j++){
    PlantAnimation& anim = cardsAnimations[j];
    anim.id = id;
    if(deckCursorPos == j){
      for(size_t i=0;i<anim.entity.size();i++){
        newFatherID(&id,&anim.entity[i]);
      }
    }else{
      for(size_t i=0;i<anim.entity.size();i++){
        setSprite(anim.entity[i],noDraw,card_layer);
      }
    }
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

  createSprite(reward.father, Tyra::MODE_REPEAT, pos, Vec2(50, 70), enumSpriteLayer::background);
  createTexture(reward.father, "UI/Seeds.png");
  spriteArray[reward.father].offset.x = 100;

  fatherIDArray.insert(reward.father, FatherID());

  for (unsigned int i = 0; i < animComponent[EnumAnimationIndex::ANIM_SunFlower].GetLayerSize(); i++) {
    id = Entities::newID();
    reward.id.push_back(id);
    newFatherID(&reward.father, &id);
    animComponent[EnumAnimationIndex::ANIM_SunFlower].createAnimation(id, i, Tyra::Vec2(0.6f, 0.6f),
                                             8, 8, true, enumSpriteLayer::background);
  }
  createBoxCollider(reward.father,BoxColliderEnum::BOXCOLLIDER_REWARD,BoxCollider(pos.x, pos.y, 28, 38));

  createDebugBoxCollider(reward.father,BoxColliderEnum::BOXCOLLIDER_REWARD, Tyra::MODE_STRETCH);
  rewardExist = true;
}

void eraseRewardLevel1() {
  deletePosArray(reward.father);
  deleteFinalPosArray(reward.father);
  unsigned int animSize = animComponent[EnumAnimationIndex::ANIM_SunFlower].GetLayerSize();
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

  animComponent[EnumAnimationIndex::ANIM_Sun].SetAnimationToEntity(newSun.id,newSun.father,Tyra::Vec2(0.5f, 0.5f), 1, 12, enumSpriteLayer::sun_layer);

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
      deletePosArray(id[size]);
      deleteFinalPosArray(id[size]);
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
BigSpriteJPG backgroundIDs;
BigSpriteJPG awardbackground;
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
std::vector<unsigned int> Entities::deadEntities;
std::vector<IndexComponent> entityComponents; // position [0] is not used
std::vector<unsigned int> entityKeySparse[COMPONENTS_MAX];
std::vector<unsigned int> entityKeyDense[COMPONENTS_MAX];

unsigned int Entities::newID() {
  // printf("deadEntities.size(): %d\n",deadEntities.size());
  if (deadEntities.size() == 0) {
    // printf("net entity: %d\n",counter);
    if(counter >= entityComponents.size()){
      IndexComponent components;
      entityComponents.push_back(components);
      // printf("entityComponents size: %d\n",counter);
    }
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
  // for(size_t i = deadEntities.size()-1; i>0; i--){
  //   if(deadEntities[i] < deadEntities[i-1]){
  //     newID = deadEntities[i];
  //     deadEntities[i] = deadEntities[i-1];
  //     deadEntities[i-1] = newID;
  //   }
  // }
  // printf("entity Deleted: %d\n",newID);
  id = 0;
}

void setEntityComponent(const int id, const enumComponents component){
  entityComponents[id].component[component] = true;
}

void deleteEntityComponent(const int id, const enumComponents component){
  entityComponents[id].component[component] = false;
}

bool hasEntityComponent(const int id, const enumComponents component){
  return entityComponents[id].component[component];
}

void deleteEntity(const int id){
  // printf("deleting entity: %d\n",id);
  if(fatherIDArray.count(id) == true){
    for(size_t i=0; i< fatherIDArray.second[id].id.size();i++){
      deleteFatherIDChild(id, &fatherIDArray.second[id].id[i]);
    }
  } 
  deleteFatherID(id);
  deleteSprite(id);
  deletePosArray(id);
  deleteFinalPosArray(id);
  deleteTexPosArray(id);
}
