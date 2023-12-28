#include "debug.hpp"
#include "components.hpp"

unsigned int debugOption = 0;
bool debugMode = false;
bool debugAnimation = false;
bool stopAnimation = false;

Tyra::Texture* debugBoxTexture;
Tyra::Texture* debugPointTexture;

void debugMenu(){
    printf("PRESS X FOR ACTIVE\n");
    printf("PRESS O FOR DESACTIVE\n");
    for(unsigned int i=0; i<debugModesSize; i++){
        switch (i)
        {
        case AnimationDebug:
            printf("Animation Debug");
            break;
        case testDebug:
            printf("test Debug");
            break;
        default:
            break;
        }

        if(debugOption != i){
            printf("\n");
        }else{
            printf(" <---\n");
        }
    }
   
}

void activeDebugMode(){
    switch (debugOption)
    {
    case AnimationDebug:
        debugAnimation = true;
        break;
    case testDebug:
        break;
    default:
        break;
    }
}

void deactiveDebugMode(){
    switch (debugOption)
    {
    case AnimationDebug:
        debugAnimation = false;
        break;
    case testDebug:
        break;
    default:
        break;
    }
}

void loadDebugTextures(){
    debugBoxTexture = loadTexture("asset_box.png");
    debugPointTexture = loadTexture("debugPoint.png");
}

void createDebugBoxCollider(const int id, Tyra::SpriteMode mode){
    // printf("id debug box: %d\n", id);
    debugSpriteBoxCollider[id] = Sprite();
    loadSprite(&debugSpriteBoxCollider[id],mode,Vec2(boxColliderArray[id].x,boxColliderArray[id].y),Vec2(boxColliderArray[id].width,boxColliderArray[id].height));
    debugBoxTexture->addLink(debugSpriteBoxCollider[id].id);
}

void deleteDebugBoxCollider(const int id){
    debugBoxTexture->removeLinkById(debugSpriteBoxCollider[id].id);
    debugSpriteBoxCollider.erase(id);
}

void createDebugPoint(const int id, Tyra::SpriteMode mode){
    // printf("id point box: %d\n", id);
    debugSpritePointCollider[id] = Sprite();
    loadSprite(&debugSpritePointCollider[id],mode,Vec2(pointColliderArray[id].x-1,pointColliderArray[id].y-1),Vec2(31,31));
    debugPointTexture->addLink(debugSpritePointCollider[id].id);
    debugSpritePointCollider[id].color = Tyra::Color(255.0f,0.0f,0.0f);
}

void deleteDebugPoint(const int id){
    debugPointTexture->removeLinkById(debugSpritePointCollider[id].id);
    debugSpritePointCollider.erase(id);
}