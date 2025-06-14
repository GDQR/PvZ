#include "components.hpp"
#include "systems.hpp"

void Controller::update() {
  if (pad->getClicked().Cross) {
    // create plant
    printf("press cross\n");
    plantsManager.create(playerID);
  }
  if (pad->getClicked().DpadLeft) {
    deckCursor[playerID].moveLeft();
  }
  if (pad->getClicked().DpadRight) {
    deckCursor[playerID].moveRight();
  }

  if (debugMode == false) {
    cursor[playerID].move();
    boxColliderArray[BOXCOLLIDER_PLAYER]
    [boxColliderArrayID[cursor[playerID].id]].move(cursor[playerID].id, 28 / 2,
                                               24 / 2);
  }

  if (pad->getClicked().R1 && debugMode == false) {
    debugMode = true;
    debugMenu = true;
    printf("\nDEBUG MODE ACTIVE\n");
  }

  if (debugMenu == true) {
    debugModeClass.mainMenu();
  }
}