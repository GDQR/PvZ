#include "components.hpp"
#include "systems.hpp"

void Controller::update(const int entityID) {
  if (engine->pad.getClicked().Cross) {
    // create plant
    plantsManager.create();
  }
  if (engine->pad.getClicked().DpadLeft) {
    deckCursor[entityID].moveLeft();
  }
  if (engine->pad.getClicked().DpadRight) {
    deckCursor[entityID].moveRight();
  }
  if (engine->pad.getClicked().R1 && debugMode == false) {
    debugMode = true;
    debugMenu = true;
    printf("\nDEBUG MODE ACTIVE\n");
  }

  if (debugMenu == true) {
    debugModeClass.mainMenu();
  }
}