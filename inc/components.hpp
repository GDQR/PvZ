#pragma once
#include <tyra>
#include <vector>
#include <map>
#include "debugPVZ/debug.hpp"
#include "entities/entities.hpp"
#include "renderSprite/textures.hpp"
#include "entities/plants.hpp"
#include "entities/zombie.hpp"
#include "entities/sun.hpp"

// enum enumAnimation {
//   zombieWalk,
//   zombieNormalAttack
// };

class FatherID {
 public:
  std::vector<int> id;
  void update(const int entityID);
};

class Cursor {
 public:
  int id = -1;
  Sprite sprite;
  Vec2 cursorTile;
  int cursorTimer = 0;
  float cursorSpeed = 1;
  void move();
};

class DeckCursor {
 public:
  int id = -1;
  int pos = 0;
  void move();
};

class Card {
 public:
  int seed;
  int seedShadow;
  int seedShadowTimer;
  int seedTimer;
  Plant_State_enum plant;
  int cost;
  void update();
};

class Animation {
 public:
  Animation();
  Animation(const int anim);
  void update(const int entityID);
  void activeDrawNormalSprites(const int entityID);
  void updateNormalSprites(const int entityID);
  void activeDrawRotationSprites(const int entityID);
  void updateRotationSprites(const int entityID);
  void position(const int entityID);

  int animID = -1;
  bool draw = true;
  unsigned int framesCounter = 0;
  unsigned int currentFrame = 0;
  unsigned int framesSpeed = 20;
  unsigned int firstFrame = 0;
  unsigned int lastFrame = 0;
};

class AnimationData {
 public:
  unsigned int maxFrame;
  std::string name;
  std::unordered_map<unsigned int, int> texture;
  std::unordered_map<unsigned int, float> x;
  std::unordered_map<unsigned int, float> y;
  std::unordered_map<unsigned int, float> scaleX;
  std::unordered_map<unsigned int, float> scaleY;
  std::unordered_map<unsigned int, float> angleX;
  std::unordered_map<unsigned int, float> angleY;
  std::unordered_map<unsigned int, float> alpha;
  std::unordered_map<unsigned int, bool> draw;
};

class Time {
 public:
  std::vector<int> seconds;  // can't be 0 for animations
};

class BoxCollider {
 public:
  BoxCollider();
  BoxCollider(float x, float y, float width, float height);
  BoxCollider(float x, float y, float width, float height, float offsetX,
              float offsetY);
  void move(const int entityID);
  bool collision(BoxCollider* box);
  float x;
  float y;
  float width;
  float height;
  float offsetX;
  float offsetY;
};

class RotationSprite {
 public:
  Tyra::Sprite sprite;
  Tyra::Vec2 angle;
  void update(const int entityID);
};

extern Tyra::Engine* engine;
extern Tyra::Renderer* renderer;
extern const Tyra::PadJoy* leftJoy;
extern Tyra::TextureRepository* texRepo;
extern std::map<std::string, std::vector<int>> m_animID;

// sparse array
extern std::map<int, Animation>
    animationArray;  // Link the sprite with the texture
extern std::unordered_map<int, AnimationData>
    animationDataArray;  // Save the animation textures
extern std::map<int, FatherID> fatherIDArray;
extern std::map<int, Tyra::Vec2> texPosArray;
extern std::map<int, Tyra::Vec2> posArray;
extern std::map<int, Tyra::Vec2> finalPosArray;
extern std::map<int, Tyra::Sprite> spriteArray;
extern std::map<int, Tyra::Sprite*> spritesNormalRender;
extern std::vector<int> spriteNormalIdStopRender;
extern std::vector<int> animationIdStopRender;
extern std::map<int, RotationSprite> rotationSprite;
extern std::map<int, RotationSprite*> spritesRotateRender;
extern std::vector<int> spritesRotateIdStopRender;
extern std::map<int, Tyra::Vec2> originalSize;
extern std::map<int, Tyra::Vec2> scaleTexture;
extern std::map<int, Tyra::Vec2> pointColliderArray;
extern std::map<int, BoxCollider> boxColliderArray;
extern std::map<int, int> damageArray;
extern std::map<int, int> lifeArray;
extern std::map<int, Tyra::Vec2> pivot;

const int maxPlants = 5 * 9;
extern Plant plant[maxPlants];
extern std::vector<Zombie> zombie;
extern std::vector<Sun> sun;
extern std::vector<NaturalSun> naturalSun;
extern std::vector<int> projectile;
extern std::vector<Card> cards;
extern Cursor cursor;
extern DeckCursor deckCursor;

extern bool zombieCreateRow[5];
extern bool plantCreatedInMap[5][9];
extern BoxCollider mapCollider[5][9];