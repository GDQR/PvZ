#include "PVZ.hpp"
#include "particles.hpp"
#include "manager.hpp"
#include "imageFiles.hpp"

std::vector<ParticleComponent> particleArray;

void ParticleManager::update(){
    std::vector<int> deleteParticle;
    for(size_t i=0; i< particleArray.size();i++){
        if(particleArray[i].update() == true){
            deleteParticle.push_back(i);
        }
    }

    int particleIndex;
    int size = deleteParticle.size();
    while(size>0){
        particleIndex = deleteParticle[size-1];
        deleteSprite(particleArray[particleIndex].id);
        particleArray.erase(particleArray.begin() + particleIndex);
        size--;
    }
}

bool ParticleComponent::update(){
    if(time == duration){
        printf("borrar projec\n");
        return true;
    }
    time++;
    return false;
}

void ParticleComponent::erase(){
    
}

void CreateParticle(Tyra::Vec2 pos, enumPARTICLETYPE type){
    ParticleComponent particle;
    particle.id = Entities::newID();
    switch (type){
        case PEASPLAT:
        
	// <ParticleDuration>20</ParticleDuration> creo que son en segundos. 20 = 2 segundos
	// <SystemDuration>20</SystemDuration>
        particle.duration = 20;
        createSprite(particle.id,Tyra::SpriteMode::MODE_REPEAT,pos,Vec2(24,24),enumSpriteLayer::sun_layer);
        createTexture(particle.id, IMG_Pea_splats);
        break;
    
    default:
        break;
    }

    particleArray.push_back(particle);
}