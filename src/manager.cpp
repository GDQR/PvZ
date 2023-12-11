#include "manager.hpp"
#include "states.hpp"
#include "scenes.hpp"

int actualState;
States states;
Scene scene;

Manager::Manager(Engine* t_engine) : engine(t_engine) {}

Manager::~Manager() {}

void Manager::init(){
    for(int i= level1; i < lastGameState; i++){
        states.id.push_back(i);
        states.isActive.push_back(false);
    }
    
    actualState = states.id[0];
    scene.setScene((Game_States_enum)actualState);

}

void Manager::loop(){   
    if(states.isActive[actualState] == false){
        scene.init();
    }

    scene.update();
    
}
