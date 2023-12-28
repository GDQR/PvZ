#pragma once
#include <tyra>
#include <vector>
#include <map>
#include "debug.hpp"
#include "entities.hpp"
#include "renderSprite/textures.hpp"
#include "plants.hpp"
#include "zombie.hpp"

extern Tyra::Engine* engine;
extern Tyra::Renderer* renderer;
extern const Tyra::PadJoy* leftJoy;

enum enumAnimation {peaShooterHead,peaShooterBody,zombieWalk,zombieNormalAttack};

class MultipleID{
    public:
    MultipleID(const int fatherID);
    std::vector<int> id;
};

class Animation{
    public:
    Animation();
    Animation(enumAnimation anim);
    int time = 0;
    int animID = -1;
    unsigned int key = 0;
};

class AnimationData{
    public:
    std::vector <Tyra::Texture*> keys;
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
extern std::map <int,Tyra::Vec2> pointColliderArray;
extern std::map <int,BoxCollider> boxColliderArray;
extern std::map <int,int> damageArray;
extern std::map <int,int> lifeArray;

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Zombie> zombie;

extern std::vector<int> projectile;  

extern bool zombieCreateRow[5];
extern bool plantCreatedInMap[5][9];
extern BoxCollider mapCollider[5][9];

class AnimationManager{
    public:
    Tyra::TextureRepository* texRepo;
    void update();
    void debug();
};

class RendererDebugSpritesManager{
    public:
    void update();
};

class RendererSprites{
    public:
    void update();
};

class ZombiesManager{
    public:
    int timer=0;
    void update();
    int collision();
};

class ProjectileManager {
 public:
  void update();
  void zombieCollision();
};


void newCursor(int* cursor, Tyra::Vec2 pos);
void newProjectile(Vec2 position);
void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position, Tyra::Vec2 size);
void deleteSprite(const int id);
void createTexture(int id, std::string fileImage);
bool boxCollision(BoxCollider* col1, BoxCollider* col2);