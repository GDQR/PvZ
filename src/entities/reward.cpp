#include "entities/entities.hpp"
#include "systems.hpp"
#include <tyra>

void rewardLevel1(Tyra::Vec2 pos) {
  reward.father = Entities::newID();
  int id;
  int animID;

  createSprite(reward.father, Tyra::MODE_REPEAT, pos, Vec2(50, 70));
  createTexture(reward.father, "UI/Seeds.png");
  spriteArray[reward.father].offset.x = 100;

  fatherIDArray.insert(reward.father, FatherID());

  for (unsigned int i = 0; i < m_animID[AnimIndex::SunFlower].size(); i++) {
    id = Entities::newID();
    reward.id.push_back(id);
    animID = m_animID[AnimIndex::SunFlower][i];
    newFatherID(&reward.father, &id);
    animationDataArray[animID].loadAnimation(id, animID, Tyra::Vec2(0.6f, 0.6f),
                                             8, 8);
  }
  boxColliderArray[reward.father] = BoxCollider(pos.x, pos.y, 28, 38);

  createDebugBoxCollider(reward.father, Tyra::MODE_STRETCH);
  rewardExist = true;
}

void eraseRewardLevel1() {
  deletePosArray(reward.father);
  unsigned int animSize = m_animID[AnimIndex::SunFlower].size();
  for (unsigned int i = 0; i < animSize; i++) {
    deletePosArray(reward.id[i]);
    deleteFinalPosArray(reward.id[i]);
    deleteFatherIDChild(&reward.father, &reward.id[i]);

    deleteSprite(reward.id[i]);

    if (animationArray.count(reward.id[i]) == 1) {
      deleteAnimation(reward.id[i]);
    }
    deleteTexPosArray(reward.id[i]);
    Entities::deleteID(reward.id[i]);
  }
  deleteSprite(reward.father);
  deleteFatherID(&reward.father);
  Entities::deleteID(reward.father);
  boxColliderArray.erase(reward.father);
  deleteDebugBoxCollider(reward.father);
  rewardExist = false;
}

void eraseReward() { eraseRewardLevel1(); }

void createReward(Tyra::Vec2 pos) {
  if (maxZombies == zombiesDefeated) {
    printf("crear premio\n");
    rewardLevel1(pos);
  }
}