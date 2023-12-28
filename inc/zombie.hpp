#pragma once
#include <tyra>
#include <vector>
enum Zombie_State_enum{NoneZombie,ZombieNormal};

class Zombie
{
private:
    void createSpace();
public:
    Zombie_State_enum type = NoneZombie;
    
    int timer = 0;
    int attackTimer = 0;
    bool attack = false;
    
    std::vector <int> id;

    int* father;
    std::vector <int*> body;
    void newZombie(Zombie_State_enum newType);
};

void createZombie(Tyra::Vec2 pos);