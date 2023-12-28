// File for all plants data

#pragma once
#include <tyra>
#include <vector>

using Tyra::Sprite;

extern Tyra::Texture* projectilePea;
extern int plantsCreated;

enum Plant_State_enum {NonePlant,PeaShotter};
class Plant{
    
    void createSpace();
    public:
    Plant_State_enum type = NonePlant;
    
    std::vector <int> id;

    int* father;
    std::vector <int*> body;
    void newPlant(Plant_State_enum newType);
    int attackTimer = 0;
    int row;
    int column;
};

void deletePeashotter(const int pos);
void createPlant(const int row, const int column);