#include "main.hpp"
#include "components.hpp"
#include <iostream>
// sparse array
std::map <int,Animation> animationArray;
std::map <int,Time> animationTime;
std::unordered_map <int,AnimationData> animationDataArray;
std::vector <MultipleID*> componentMultipleID(100,nullptr);
std::map<int,Tyra::Vec2> vec2Array;
std::map <int,Tyra::Sprite> spriteArray; 
std::vector <Tyra::Texture*> textureArray(100,nullptr);
std::map <int,BoxCollider> boxColliderArray;
std::map <int,Tyra::Sprite> debugBoxColliderArray;

BoxCollider::BoxCollider(){}
BoxCollider::BoxCollider(float x, float y, float width, float height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
BoxCollider::BoxCollider(float x, float y, float width, float height, float offsetX, float offsetY){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

MultipleID::MultipleID(const int fatherID){
    id.push_back(fatherID);
}


void AnimationManager::update(){
    // printf("entro\n");
    std::map<int, Animation>::iterator it;
    auto& textureRepository = renderer->getTextureRepository();

    for (it = animationArray.begin(); it != animationArray.end(); it++)
    {
        // std::cout << it->first    // string (key)
        //         //   << ':'
        //         //   << it   // string's value 
        //           << std::endl;

        if(animationArray[it->first].time < animationTime[animationArray[it->first].animID].seconds[animationArray[it->first].key]){
            animationArray[it->first].time++;
            continue;
        }
        
        textureRepository.getBySpriteId(spriteArray[it->first].id)->removeLinkById(spriteArray[it->first].id);

        animationArray[it->first].key++; 
        animationArray[it->first].time = 0;

        if(animationArray[it->first].key >= animationDataArray[animationArray[it->first].animID].keys.size()){
            animationArray[it->first].key = 0;
        }

        // textureArray[it->first] = animationDataArray[animationArray[it->first].animID].keys[animationArray[it->first].key];

        // textureArray[it->first]->addLink(spriteArray[it->first].id);
        animationDataArray[animationArray[it->first].animID].keys[animationArray[it->first].key]->addLink(spriteArray[it->first].id);
    }
    
}

void AnimationManager::debug(){
    
}

void createSprite(int id, Tyra::SpriteMode mode, Tyra::Vec2 position, Tyra::Vec2 size){
    spriteArray[id] = Sprite();
    loadSprite(&spriteArray[id],mode,position,size);
}

void createTexture(int id, std::string fileImage){
    textureArray[id] = loadTexture(fileImage);
    TYRA_ASSERT(!(spriteArray.find(id) == spriteArray.end()),"Entitie id: ",id,"Is NULL, use <<CreateSprite>> function");
    textureArray[id]->addLink(spriteArray[id].id);
}

void createDebugBoxCollider(int id, Tyra::SpriteMode mode){
    printf("id debug box: %d\n", id);
    debugBoxColliderArray[id] = Sprite();
    loadSprite(&debugBoxColliderArray[id],mode,Vec2(boxColliderArray[id].x,boxColliderArray[id].y),Vec2(boxColliderArray[id].width,boxColliderArray[id].height));
}
