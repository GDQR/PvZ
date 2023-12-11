#include "renderSprite/animations.hpp"
#include "renderSprite/textures.hpp"
// Animations animations;

void loadPeaShooterAnimation(){
    animationDataArray[peaShooterHead] = AnimationData();
    animationTime[peaShooterHead] = Time();
    animationDataArray[peaShooterBody] = AnimationData();
    animationTime[peaShooterBody] = Time();
    // animationDataArray[0]->keys.push_back(new Tyra::Sprite());
    
    printf("cargando PeaShooter animation\n");
    std::string filepath;
    // Tyra::Texture* texture = loadTexture("Animations/PeaShooterSingle/PeaShooterSingle0030.png");
    Tyra::Texture* texture;
    for(int i=30; i<=54; i++){
        filepath = "Animations/PeaShooterSingle/PeaShooterSingle00";
        filepath += std::to_string(i);
        filepath += ".png";
        texture = loadTexture(filepath);
        animationDataArray[peaShooterHead].keys.push_back(texture);
        animationTime[peaShooterHead].seconds.push_back(2);
        // printf("pase\n");
    }
    // animationDataArray[peaShooterHead]->keys.push_back(texture);
    // animationTime.push_back(20);
    // texture = loadTexture("Animations/PeaShooterSingle/PeaShooterSingle0031.png");
    // animationDataArray[peaShooterHead]->keys.push_back(texture);
    // animationTime.push_back(20);
    texture = loadTexture("Animations/PeaShooterSingle/PeaShooterSingle0005.png");
    animationDataArray[peaShooterBody].keys.push_back(texture);
    animationTime[peaShooterBody].seconds.push_back(20);

    // loadSprite(animationDataArray[0]->keys[0]);
    // loadTexture(animationDataArray[0]->keys[0],"Animations/PeaShooterSingle/PeaShooterSingle0030.png");
    // animationDataArray[0]->keys.push_back(new Tyra::Sprite());
    // animationDataArray[0]->keys.push_back(new Tyra::Sprite());
    // loadSprite(animationDataArray[0]->keys[1]);
    // loadTexture(animationDataArray[0]->keys[1],"Animations/PeaShooterSingle/PeaShooterSingle0031.png");
}
