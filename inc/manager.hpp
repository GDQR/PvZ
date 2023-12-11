#pragma once

#include <tyra>

using namespace Tyra;

class Manager: public Game{
  public:
  Manager(Engine* engine);
  ~Manager();

  /**
   * This function will be called once,
   * immediatly after initializing Tyra features
   */
  void init();

  /**
   * This function will be called every frame
   */
  void loop();

 private:
  Engine* engine;
};
