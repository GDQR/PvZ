#pragma once
#include "states.hpp"

class Level1{
    public:
    static void init();
    static void update();
    static void destroy(); // tal vez sea innecesario, ahora que lo pienso es una optimizacion prematura la puta madre
};

class Level2{
    public:
    static void init();
    static void update();
    static void destroy(); // tal vez sea innecesario, ahora que lo pienso es una optimizacion prematura la puta madre
};

class Scene{
    public:
    Scene(){state = (Game_States_enum) actualState;}
    Game_States_enum state;
    void init();
    void update();
    void setScene(Game_States_enum newState) { state = newState; };
};