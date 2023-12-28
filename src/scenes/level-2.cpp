#include "states.hpp"
#include "scenes.hpp"
#include "scenes/level-2.hpp"
#include "components.hpp"



void Level2::init(){
    printf("estoy en nivel 2\n");

}

void Level2::update(){
    printf("FPS: %d\n",engine->info.getFps());
    renderer->beginFrame();
    renderer->endFrame();
}

void Level2::destroy(){

}