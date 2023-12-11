#include "debug.hpp"

unsigned int debugOption = 0;
bool debugMode = false;
bool debugAnimation = false;
bool stopAnimation = false;

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