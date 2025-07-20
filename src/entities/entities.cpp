#include <entities/entities.hpp>
#include <components.hpp>
#include <systems.hpp>
#include <stdio.h>

Tyra::Vec2 cameraPos(0.0f, 0.0f);
bool rewardExist = false;


void Player::init(){
  printf("init Player\n");
  static int countPlayer = 0;
  id = cursor.size();
  // controllerID = countPlayer;
  Controller newController;
  newController.playerID = countPlayer;
  controller.push_back(newController);
  countPlayer++;
}

void Player::initCursor(Tyra::Vec2 cursorPos){
  Cursor newCursor;
  newCursor.id = Entities::newID();
  createSprite(newCursor.id, Tyra::MODE_STRETCH, cursorPos, Vec2(56, 48));
  createTexture(newCursor.id, "cursor6.png");
  createBoxCollider(newCursor.id, BoxColliderEnum::BOXCOLLIDER_PLAYER, BoxCollider(newCursor.id,cursorPos.x + 28 / 2, cursorPos.y + 24 / 2, 24, 24));
  createDebugBoxCollider(newCursor.id, BoxColliderEnum::BOXCOLLIDER_PLAYER, Tyra::MODE_STRETCH);

  cursor.push_back(newCursor);
}


void Player::initDeckCard(Tyra::Vec2 pos){
  if(cards.size() == 0){
    TYRA_TRAP("CARDS DOESN'T EXIST");
  }

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
}  // namespace Entity

unsigned int Entities::counter = 1;
std::vector<unsigned int> Entities::aliveEntities;
std::vector<unsigned int> Entities::deadEntities;

unsigned int Entities::newID() {
  // printf("deadEntities.size(): %d\n",deadEntities.size());
  if (deadEntities.size() == 0) {
    printf("net entity: %d\n",counter);
    return counter++;
  }
  unsigned int oldID = deadEntities.front();
  deadEntities.erase(deadEntities.begin());
  return oldID;
}

void Entities::deleteID(unsigned int& id) {
  int newID = id;
  deadEntities.push_back(newID);
  printf("entity Deleted: %d\n",newID);
  id = 0;
}

void Entities::deleteID(int& id) {
  int newID = id;
  deadEntities.push_back(newID);
  printf("entity Deleted: %d\n",newID);
  id = 0;
}
