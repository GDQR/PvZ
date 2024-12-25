#include "components.hpp"

PS2Timer::PS2Timer() { resetCounter(); }
void PS2Timer::setLastTime() { lastTime = actualTime; }

u64 PS2Timer::getTimeInMS() {
  actualTime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
  return actualTime - lastTime;
}

void PS2Timer::resetCounter() {
  lastTime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
  actualTime = lastTime;
  counterMS = 0;
}

void PS2Timer::addMSinCounter() {
  setLastTime();
  counterMS += getTimeInMS();
}