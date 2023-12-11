// File for all plants data

#pragma once
#include <tyra>
#include <vector>
#include <string>

using Tyra::Sprite;

enum Plant_State_enum {None,PeaShotter};
class Plant{
    
    void createSpace();
    public:
    Plant_State_enum type = None;
    
    std::vector <int> id;

    int* father;
    std::vector <int*> body;
    void newPlant(Plant_State_enum newType);
};
