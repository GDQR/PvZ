#pragma once

enum enumPARTICLETYPE{
    PEASPLAT
};

class ParticleComponent{
    public:
    int id;
    short duration;
    short time = 0;
    bool update();
    void erase();
};

extern std::vector<ParticleComponent> particleArray;

void CreateParticle(Tyra::Vec2 pos, enumPARTICLETYPE type);