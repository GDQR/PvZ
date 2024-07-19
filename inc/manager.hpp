#pragma once

#include <tyra>

using namespace Tyra;

class Manager{
  public:
  /**
   * This function will be called once,
   * immediatly after initializing Tyra features
   */
  void init();

  /**
   * This function will be called every frame
   */
  void loop();
};
