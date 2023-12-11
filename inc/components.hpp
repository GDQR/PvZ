#pragma once
#include <tyra>
#include <vector>
#include <map>
#include "renderSprite/textures.hpp"

enum enumAnimation {peaShooterHead,peaShooterBody};

class MultipleID{
    public:
    MultipleID(const int fatherID);
    std::vector<int> id;
};

class Animation{
    public:
    int time = 0;
    int animID = -1;
    unsigned int key = 0;
};

class AnimationData{
    public:
    std::vector <Tyra::Texture*> keys;
};

class AnimationManager{
    public:
    Tyra::TextureRepository* texRepo;
    void update();
    void debug();
};

class Time{
    public:
    std::vector <int> seconds;
};

class BoxCollider{
    public:
    BoxCollider();
    BoxCollider(float x, float y, float width, float height);
    BoxCollider(float x, float y, float width, float height, float offsetX, float offsetY);
    float x;
    float y;
    float width;
    float height;
    float offsetX;
    float offsetY;
};

// sparse array
extern std::map <int,Animation> animationArray;
extern std::map <int,Time> animationTime;
extern std::unordered_map <int,AnimationData> animationDataArray;
extern std::vector <MultipleID*> componentMultipleID;
extern std::map<int,Tyra::Vec2> vec2Array;
extern std::map <int,Tyra::Sprite> spriteArray; 
extern std::vector <Tyra::Texture*> textureArray;  // tal vez es innecesario
extern std::map <int,BoxCollider> boxColliderArray;
extern std::map <int,Tyra::Sprite> debugBoxColliderArray;

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position, Tyra::Vec2 size);
void createTexture(int id, std::string fileImage);
void createDebugBoxCollider(int id, Tyra::SpriteMode mode);