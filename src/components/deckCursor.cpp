#include "components.hpp"

void DeckCursor::moveLeft() {
  pos--;
  if (pos < 0) {
    pos = cards.size() - 1;
  }
  posArray[id].x = posArray[cards[pos].seed].x - 3;
}

void DeckCursor::moveRight() {
  pos++;
  if (pos >= (int)cards.size()) {
    pos = 0;
  }
  posArray[id].x = posArray[cards[pos].seed].x - 3;
}
