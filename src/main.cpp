#include "PVZ.hpp"
#include "text.hpp"
#include "scenes.hpp"

void ArrayKeyFailCase(const int entityID, const enumComponents type, const int failCase) {
  std::string text;
  if(type == enumComponents::angle){
    text = "ANGLE";
  }else if(type == enumComponents::animation){
    text = "ANIMATION";
  }else if(type == enumComponents::fatherID){
    text = "fatherID";
  }else if(type == enumComponents::FRAMECOUNTER){
    text = "FRAMECOUNTER";
  }else if(type == enumComponents::finalPos){
    text = "finalPos";
  }else if(type == enumComponents::life){
    text = "life";
  }else if(type == enumComponents::pos){
    text = "pos";
  }else if(type == enumComponents::sprite){
    text = "sprite";
  }else if(type == enumComponents::spriteRender){
    text = "spriteRender";
  }else if(type == enumComponents::texPos){
    text = "texPos";
  }else if(type == enumComponents::timer){
    text = "timer";
  }else{
    text = "TYPE NOT INCLUDED";
  }
  
  if(failCase == 1){
    TYRA_TRAP("ERROR SEARCHING KEY, KEY IS BIGGER THAN EXPECTED:", entityID,
                "COMPONENT:", type, text);
  }else if(failCase == 2){

    TYRA_TRAP("ERROR SEARCHING KEY, KEY NOT FOUNDED:", entityID,
              "COMPONENT:", type, text);
  }
}

size_t GetIndexToErase(const unsigned int key, const enumComponents type){
  std::vector<unsigned int>& keyDense = entityKeyDense[type];
  unsigned int size = keyDense.size();
  for (size_t i = 0; i < size; i++) {
    if (keyDense[i] == key) {
      return i;
    }
  }
  return size;
}

static int actualState;
static States states;

void setScene(Game_States_enum newState){ actualState = newState;}

void initScene() {
  states.isActive[actualState] = true;
  switch (actualState) {
    case sceneSelectorScreen:
      SelectorScreen::init();
      break;
    case level1:
      Level1::init();
      break;
    case level2:
      Level2::init();
      break;
    case level3:
      Level3::init();
      break;
    case level4:
      Level4::init();
      break;
    case level5:
      Level5::init();
      break;
    default:
      break;
  }
}

void updateScene() {
  switch (actualState) {
    case sceneSelectorScreen:
      SelectorScreen::update();
      break;
    case level1:
      Level1::update();
      break;
    case level2:
      Level2::update();
      break;
    case level3:
      Level3::update();
      break;
    case level4:
      Level4::update();
      break;
    case level5:
      Level5::update();
      break;
    default:
      break;
  }
}

void GameLoop(){
  if (states.isActive[actualState] == false) {
    initScene();
  }
  updateScene();
}

int main() {
  Tyra::Engine e;
  engine = &e;
  renderer = &e.renderer;
  renderer2D = &e.renderer.renderer2D;
  pad = &e.pad;
  leftJoy = &e.pad.getLeftJoyPad();
  texRepo = &engine->renderer.getTextureRepository();
  ReadTextFile();
  // loadFonts();
  initAnimation();
  entityComponents.push_back(IndexComponent());
  states.isActive.reserve(lastGameState);
  
  for (int i = 0; i < lastGameState; i++) {
    states.isActive[i] = false;
  }

  setScene(Game_States_enum::level1);

  while (true) {
    GetTime();
    e.pad.update();
    GameLoop();
    e.info.update();
  }

  // SleepThread();
  return 0;
}
