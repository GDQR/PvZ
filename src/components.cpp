#include "components.hpp"
#include "debugPVZ/menuDebugCommands.hpp"
#include "entities/entities.hpp"
#include <iostream>

Tyra::Engine* engine;
Tyra::Renderer* renderer;
const Tyra::PadJoy* leftJoy;
Tyra::TextureRepository* texRepo;

// sparse array
std::unordered_map<int, std::vector<int>> m_animID;
ArrayKey<int, Animation> animationArray(enumComponents::animation);
std::unordered_map<int, AnimationData> animationDataArray;
ArrayKey<int, FatherID> fatherIDArray(enumComponents::fatherID);
ArrayKey<int, Tyra::Vec2> posArray(enumComponents::pos);
ArrayKey<int, Tyra::Vec2> texPosArray(enumComponents::texPos);
ArrayKey<int, Tyra::Vec2> finalPosArray(enumComponents::finalPos);
ArrayKey<int, Tyra::Sprite> spriteArray(enumComponents::sprite);
ArrayKey<int, int> spriteRenderIDArray(enumComponents::spriteRender);
// std::vector<int> spriteNormalIdStopRender;
// std::vector<int> animationIdStopRender;
ArrayKey<int, Tyra::Vec2> angleArray(enumComponents::angle);
std::unordered_map<int, Tyra::Vec2> originalSize;
std::unordered_map<int, Tyra::Vec2> scaleTexture;
std::unordered_map<int, Tyra::Vec2> pointColliderArray;
std::unordered_map<int, BoxCollider> boxColliderArray;
std::unordered_map<int, TriggerBoxCollider> resultBoxCollider;
ArrayKey<int, PS2Timer> timerArray(enumComponents::timer);
std::unordered_map<int, float> speedArray;
std::unordered_map<int, int> damageArray;
ArrayKey<int, int> lifeArray(enumComponents::life);
std::map<int, Tyra::Vec2> pivot;
std::map<int, Controller> controller;

Plant plant[maxPlants];
std::vector<Zombie> zombie;
std::vector<Sun> sun;
std::vector<NaturalSun> naturalSun;
std::vector<Proyectile> projectile;
std::vector<Explosion> explosion;
std::vector<Card> cards;
std::vector<LawnMower> lawnMower;
int player;
std::map<int, Cursor> cursor;
std::map<int, DeckCursor> deckCursor;
Tyra::Vec2 camera(0.0F, 0.0F);

int zombiescreated;
ZombieRow zombieCreateRow[5];
bool mapEnable[5];
bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

std::map<int, Tyra::Sprite> dm_SpritePointCollider;
std::map<int, Tyra::Sprite> dm_SpriteBoxCollider;
std::map<int, Tyra::Sprite> dm_SpriteNormal;
std::map<int, Tyra::Sprite> dm_SpriteNormalPivot;
