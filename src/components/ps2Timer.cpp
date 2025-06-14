#include "components.hpp"
static u32 globalTime;

void GetTime(){
  globalTime = GetTimerSystemTime() / (kBUSCLK / CLOCKS_PER_SEC);
}

PS2Timer::PS2Timer() { resetCounter(); }
void PS2Timer::setLastTime() { lastTime = actualTime; }

u32 PS2Timer::getTimeInMS() {
  actualTime = globalTime;
  return actualTime - lastTime;
}

void PS2Timer::resetCounter() {
  lastTime = globalTime;
  actualTime = lastTime;
  counterMS = 0;
}

void PS2Timer::addMSinCounter() {
  setLastTime();
  counterMS += getTimeInMS();
}