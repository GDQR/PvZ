#include "scenes.hpp"
#include "manager.hpp"
#include "imageFiles.hpp"
#include <gs_psm.h>
#include <screenshot.h>

static int selectorScreenBackground;
static int selectorScreenCenterAlpha;
static int selectorScreenCenter;
static int selectorScreenLeftAlpha;
static int selectorScreenLeft;
static int selectorScreenAlpha;
static int selectorScreen;

static int startAdventure;
static int startAdventureHighlight;
static int miniGames;
static int miniGamesHighlight;
static int puzzle;
static int puzzleHighlight;
static int survival;
static int survivalHighlight;

static packet2_t* mypacket;
Tyra::PngPixel4 mybuffer[512 * 448];

enum SelectorScreenOptions {
  FirstOption,
  Main_Adventure,
  Mini_Games,
  Puzzle,
  Survival,
  Options,
  Help,
  Quit,
  LastOption
};

void SelectorScreen::BGLeft() {
  selectorScreenLeftAlpha = Entities::newID();
  selectorScreenLeft = Entities::newID();
  createSprite(selectorScreenLeftAlpha, Tyra::MODE_STRETCH, Vec2(0, 0),
               Vec2(512, 393));
  createTexture(selectorScreenLeftAlpha, "SelectorScreen_BG_Left_.png");
  createSprite(selectorScreenLeft, Tyra::MODE_STRETCH, Vec2(0, 0),
               Vec2(512, 393));
  createTexture(selectorScreenLeft, "SelectorScreen_BG_Left.jpg");
  
  Shader_SetAlphaToImage(spriteArray[selectorScreenLeftAlpha].textureID,spriteArray[selectorScreenLeft].textureID);

  deleteSprite(selectorScreenLeftAlpha);
  packet2_update(mypacket,
                 draw_texture_expand_alpha(mypacket->next, 128, 1, 0));
  packet2_update(mypacket, draw_finish(mypacket->next));
  dma_channel_wait(DMA_CHANNEL_GIF, 0);
  dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
  packet2_reset(mypacket, 0);
}

static BigSpriteJPG as;
void SelectorScreen::BGCenter() {
  // selectorScreenCenterAlpha = Entities::newID();
  // selectorScreenCenter = Entities::newID();
  // createSprite(selectorScreenCenterAlpha, Tyra::MODE_STRETCH, Vec2(0, 0),
  //              Vec2(512, 256));

  PngLoaderUnlimited loader;
  Tyra::TextureBuilderData* texDataAlpha = loader.load(PNG_SelectorScreenBGCenter);
  Tyra::Texture* textureAlpha = new Tyra::Texture(texDataAlpha);
  texRepo->add(textureAlpha);
  // spriteArray[selectorScreenCenterAlpha].textureID = textureAlpha->id;

  // createTexture(selectorScreenCenterAlpha, PNG_SelectorScreenBGCenter);
  // createSprite(selectorScreenCenter, Tyra::MODE_STRETCH, Vec2(0, 200),
  //              Vec2(512, 256));
  Tyra::TextureBuilderData* texData = JPGLoaderUnlimited::load(JPG_SelectorScreenBGCenter);
  Tyra::Texture* texture = new Tyra::Texture(texData);
  texRepo->add(texture);
  // spriteArray[selectorScreenCenter].textureID = texture->id;
  // createTexture(selectorScreenCenter, "REANIM/SelectorScreen_BG_Center.jpg");

  Shader_SetAlphaToImage(textureAlpha->id,texture->id);
  
  BigTexture scaleData = JpgImageScale::load(texture,TextureScale::Tex256,TextureScale::Tex256,TEXTURE_COMPONENTS_RGBA);
  SetBigImage(&as,&scaleData,Tyra::MODE_STRETCH,0,200,720/2,350/2);

  // deleteSprite(selectorScreenCenterAlpha);
  packet2_update(mypacket,
                 draw_texture_expand_alpha(mypacket->next, 128, 1, 0));
  packet2_update(mypacket, draw_finish(mypacket->next));
  dma_channel_wait(DMA_CHANNEL_GIF, 0);
  dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
  packet2_reset(mypacket, 0);
}
void SelectorScreen::BGRight() {
  selectorScreenAlpha = Entities::newID();
  selectorScreen = Entities::newID();
  createSprite(selectorScreenAlpha, Tyra::MODE_STRETCH, Vec2(0, 0),
               Vec2(512, 488));
  createTexture(selectorScreenAlpha, "SelectorScreen_BG_Right_.png");
  createSprite(selectorScreen, Tyra::MODE_STRETCH, Vec2(0, 50), Vec2(512, 488));
  createTexture(selectorScreen, "SelectorScreen_BG_Right.jpg");

  Shader_SetAlphaToImage(spriteArray[selectorScreenAlpha].textureID,spriteArray[selectorScreen].textureID);

  deleteSprite(selectorScreenAlpha);
  packet2_update(mypacket,
                 draw_texture_expand_alpha(mypacket->next, 128, 1, 0));
  packet2_update(mypacket, draw_finish(mypacket->next));
  dma_channel_wait(DMA_CHANNEL_GIF, 0);
  dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
  packet2_reset(mypacket, 0);
}

void SelectorScreen::BG() {
  selectorScreenBackground = Entities::newID();

  createSprite(selectorScreenBackground, Tyra::MODE_STRETCH, Vec2(0, 0),
               Vec2(650, 512));
  createTexture(selectorScreenBackground, "REANIM/SelectorScreen_BG.jpg");

  Tyra::Texture* background = renderer->getTextureRepository().getByTextureId(
      spriteArray[selectorScreenBackground].textureID);
  background->core->components = TEXTURE_COMPONENTS_RGBA;

  // packet2_update(mypacket,draw_texture_expand_alpha(mypacket->next,128,1,0));
  // packet2_update(mypacket,draw_finish(mypacket->next));
  // dma_channel_wait(DMA_CHANNEL_GIF, 0);
  // dma_channel_send_packet2(mypacket, DMA_CHANNEL_GIF, true);
  // packet2_reset(mypacket,0);
}

void SelectorScreen::OptionHighlight(int option, int previousOption) {
  // Desactivate Highlight
  switch (previousOption) {
    case Main_Adventure:
      spriteArray[startAdventure].color.a = 128;
      spriteArray[startAdventureHighlight].color.a = 0;
      break;
    case Mini_Games:
      spriteArray[miniGames].color.a = 128;
      spriteArray[miniGamesHighlight].color.a = 0;
      break;
    case Puzzle:
      spriteArray[puzzle].color.a = 128;
      spriteArray[puzzleHighlight].color.a = 0;
      break;
    case Survival:
      spriteArray[survival].color.a = 128;
      spriteArray[survivalHighlight].color.a = 0;
      break;
    case Options:
      break;
    case Help:
      break;
    case Quit:
      break;
    default:
      printf("Selector Screen Option Error\n");
      break;
  }

  // Activate Highlight
  switch (option) {
    case Main_Adventure:
      spriteArray[startAdventure].color.a = 0;
      spriteArray[startAdventureHighlight].color.a = 128;
      break;
    case Mini_Games:
      spriteArray[miniGames].color.a = 0;
      spriteArray[miniGamesHighlight].color.a = 128;
      break;
    case Puzzle:
      spriteArray[puzzle].color.a = 0;
      spriteArray[puzzleHighlight].color.a = 128;
      break;
    case Survival:
      spriteArray[survival].color.a = 0;
      spriteArray[survivalHighlight].color.a = 128;
      break;
    case Options:
      break;
    case Help:
      break;
    case Quit:
      break;
    default:
      printf("Selector Screen Option Error\n");
      break;
  }
}

void SelectorScreen::init() {
  mypacket = packet2_create(16, P2_TYPE_NORMAL, P2_MODE_NORMAL, 0);

  engine->renderer.core.setClearScreenColor(Tyra::Color(0, 0, 255, 0));

  BG();
  BGCenter();
  BGLeft();
  BGRight();

  // startAdventure = Entities::newID();

  // createSprite(startAdventure, Tyra::MODE_STRETCH, Vec2(250, 50),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(startAdventure,
  //               "reanim/SelectorScreen_StartAdventure_Button1.png");

  // startAdventureHighlight = Entities::newID();
  // createSprite(startAdventureHighlight, Tyra::MODE_STRETCH, Vec2(250, 50),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(startAdventureHighlight,
  //               "reanim/SelectorScreen_StartAdventure_Highlight.png");

  // miniGames = Entities::newID();

  // createSprite(miniGames, Tyra::MODE_STRETCH, Vec2(250, 150),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(miniGames, "reanim/SelectorScreen_Survival_button.png");

  // miniGamesHighlight = Entities::newID();

  // createSprite(miniGamesHighlight, Tyra::MODE_STRETCH, Vec2(250, 150),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(miniGamesHighlight,
  //               "reanim/SelectorScreen_Survival_highlight.png");

  // puzzle = Entities::newID();

  // createSprite(puzzle, Tyra::MODE_STRETCH, Vec2(250, 150),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(puzzle, "reanim/SelectorScreen_Challenges_button.png");

  // puzzleHighlight = Entities::newID();

  // createSprite(puzzleHighlight, Tyra::MODE_STRETCH, Vec2(250, 150),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(puzzleHighlight,
  //               "reanim/SelectorScreen_Challenges_highlight.png");

  // survival = Entities::newID();

  // createSprite(survival, Tyra::MODE_STRETCH, Vec2(250, 150),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(survival, "reanim/SelectorScreen_Vasebreaker_button.png");

  // survivalHighlight = Entities::newID();

  // createSprite(survivalHighlight, Tyra::MODE_STRETCH, Vec2(250, 150),
  //              Vec2(512 / 2, 512 / 2));
  // createTexture(survivalHighlight,
  //               "reanim/SelectorScreen_vasebreaker_highlight.png");

  // spriteArray[startAdventure].color.a = 0;
  // spriteArray[startAdventureHighlight].color.a = 128;

  // spriteArray[miniGames].color.a = 128;
  // spriteArray[miniGamesHighlight].color.a = 0;

  // spriteArray[puzzle].color.a = 128;
  // spriteArray[puzzleHighlight].color.a = 0;

  // spriteArray[survival].color.a = 128;
  // spriteArray[survivalHighlight].color.a = 0;

  printf("ram: %f\n", engine->info.getAvailableRAM());
}

void SelectorScreen::Levels(){
  int level = 1;
  switch (level){
    case 1:
      setScene(Game_States_enum::level1);
      break;
    case 2:
      setScene(Game_States_enum::level2);
      break;
    default:
      break;
  }
}

void SelectorScreen::update() {
  static int option = Main_Adventure;

  if (engine->pad.getClicked().DpadUp == true) {
    int previousOption = option;
    option--;
    if (option == FirstOption) {
      option = LastOption - 1;
    }
    OptionHighlight(option, previousOption);
  } else if (engine->pad.getClicked().DpadDown == true) { 
    int previousOption = option;
    option++;
    if (option == LastOption) {
      option = FirstOption + 1;
    }
    OptionHighlight(option, previousOption);
  }

  switch (option) {
    case Main_Adventure:
      if (engine->pad.getClicked().Cross == true) {
        printf("main adventure\n");
        Levels();
      }
      break;
    case Mini_Games:
      if (engine->pad.getClicked().Cross == true) {
        printf("mini games\n");
      }
      break;
    case Puzzle:
      if (engine->pad.getClicked().Cross == true) {
        printf("puzzle\n");
      }
      break;
    case Survival:
      if (engine->pad.getClicked().Cross == true) {
        printf("survival\n");
      }
      break;
    case Options:
      if (engine->pad.getClicked().Cross == true) {
        printf("Options\n");
      }
      break;
    case Help:
      if (engine->pad.getClicked().Cross == true) {
        printf("Help\n");
      }
      break;
    case Quit:
      if (engine->pad.getClicked().Cross == true) {
        printf("Quit\n");
      }
      break;
    default:
      printf("Selector Screen Option Error\n");
      break;
  }
  renderer->beginFrame();
  renderSprites.update();
  renderer->endFrame();
}