#include "renderSprite/textures.hpp"
#include "renderSprite/animations.hpp"
#include "states.hpp"
#include "scenes.hpp"
#include "scenes/level-1.hpp"
#include "entities.hpp"
#include "components.hpp"
#include "plants.hpp"
#include "debug.hpp"
#include "main.hpp"
using namespace Tyra;

Sprite background;
Sprite Cursor;
Sprite map[5][9];

bool plantCreatedInMap[5][9];
BoxCollider mapCollider[5][9];

int plantsCreated = 0;
const int maxPlants = 5*9;
Plant plant[maxPlants];

int xMap = 9;
int yMap = 5;

AnimationManager animManager;
int cursor;
Vec2 cursorTile;


bool collision(BoxCollider* col1, BoxCollider* col2){
    if(col1->x + col1->width >= col2->x &&
        col2->x + col2->width >= col1->x &&
       col1->y + col1->height >= col2->y &&
        col2->y + col2->height >= col1->y){
            return true;
    }
    return false;
}

void newCursor(){
    cursor = Entities::newID();
    createSprite(cursor,MODE_STRETCH,Vec2(map[0][0].position.x,map[0][0].position.y),Vec2(56,48));
    createTexture(cursor,"cursor6.png");
    // textureArray[cursor] = loadTexture("cursor6.png");
    // textureArray[cursor]->addLink(spriteArray[cursor]->id);
    // vec2Array[cursor] = new Vec2(0,0);
    vec2Array[cursor] = Vec2(0,0);
    boxColliderArray[cursor] = BoxCollider(map[0][0].position.x,map[0][0].position.y,24,24,28/2,24/2);
    createDebugBoxCollider(cursor, MODE_STRETCH);
    copyTexture(&map[0][0],&debugBoxColliderArray[cursor]);
}

void newPeashotter(int pos, int row, int column){
    plant[pos].newPlant(PeaShotter);

    plant[pos].id[0] = Entities::newID();
    plant[pos].id[1] = Entities::newID();
    plant[pos].id[2] = Entities::newID();

    // printf("plant[%d].id[0]: %d\n",pos,plant[pos].id[0]);
    // printf("plant[%d].id[1]: %d\n",pos,plant[pos].id[1]);
    // printf("plant[%d].id[2]: %d\n",pos,plant[pos].id[2]);

    vec2Array[*plant[pos].father] = Vec2(row,column);
    spriteArray[*plant[pos].body[0]] = Sprite();

    loadSprite(&spriteArray[*plant[pos].body[0]],Tyra::MODE_REPEAT,Vec2(mapCollider[row][column].x,mapCollider[row][column].y),Vec2(128,128));

    animationArray[*plant[pos].body[0]] = Animation();
    animationArray[*plant[pos].body[0]].animID = peaShooterHead;

    animationDataArray[peaShooterHead].keys[0]->addLink(spriteArray[*plant[pos].body[0]].id);

    spriteArray[*plant[pos].body[1]] = Sprite();
    loadSprite(&spriteArray[*plant[pos].body[1]],Tyra::MODE_STRETCH,Vec2(mapCollider[row][column].x,mapCollider[row][column].y),Vec2(128,128));
    animationDataArray[peaShooterBody].keys[0]->addLink(spriteArray[*plant[pos].body[1]].id);
}

void createPlant(const int row, const int column){
    if(plantCreatedInMap[row][column] == false){
        plantCreatedInMap[row][column] = true;
        newPeashotter(plantsCreated,cursorTile.x,cursorTile.y);
        plantsCreated++;
        // printf("estoy en tile %f,%f\n",cursorTile.x,cursorTile.y);
        // printf("plantas creadas: %d\n",plantsCreated);
    }else{
        printf("no se puede crear aqui, ya existe una planta\n");
    }
}

void plantMovement(){
    float x = 0.0F;
    float y = 0.0F;

    if(leftJoy->h <= 100){
        x = -1;
    }else if(leftJoy->h >= 200){
        x = 1;
    }

    if(leftJoy->v <= 100){
        y = -1; 
    }else if(leftJoy->v >= 200){
        y = 1;
    }

    if(x != 0 || y != 0){
        printf("me movi\n");
    }
    // *vec2Array[plant.father] = Vec2(x,y);
    // spriteArray[plant.body[0]]->position += *vec2Array[plant.father];
    // spriteArray[plant.body[1]]->position += *vec2Array[plant.father];

    // *vec2Array[plant.father] = Vec2(0,1);
}

void cursorMovement(){
    float x = 0.0F;
    float y = 0.0F;

    if(leftJoy->h <= 100){
        x = -1;
    }else if(leftJoy->h >= 200){
        x = 1;
    }

    if(leftJoy->v <= 100){
        y = -1; 
    }else if(leftJoy->v >= 200){
        y = 1;
    }

    vec2Array[cursor] = Vec2(x,y); 
    spriteArray[cursor].position += vec2Array[cursor];
    vec2Array[cursor] = Vec2(0,1);
}

void updateBoxCollider(){
    boxColliderArray[cursor].x = boxColliderArray[cursor].offsetX + spriteArray[cursor].position.x;
    boxColliderArray[cursor].y = boxColliderArray[cursor].offsetY + spriteArray[cursor].position.y;
    debugBoxColliderArray[cursor].position = Vec2(boxColliderArray[cursor].x,boxColliderArray[cursor].y);
}

void Level1::init(){
    animManager.texRepo = &engine->renderer.getTextureRepository();
    
    // load background
    loadSprite(&background,Vec2(780,524));
    loadTexture(&background,"Backgrounds/DAY.png");
    background.position = Vec2(-56,-1);
    
    loadTexture(&map[0][0],"asset_box.png"); // debug map

    for(int i=0; i < 5;i++){
        for(int j=0; j < 9;j++){
            plantCreatedInMap[i][j] = false;
            map[i][j].mode = SpriteMode::MODE_STRETCH;
            map[i][j].position= Vec2(85 + (45*j), 58 + (72*i));
            map[i][j].size= Vec2(45,72);
            mapCollider[i][j].x = 85 + (45*j);
            mapCollider[i][j].y = 58 + (72*i);
            mapCollider[i][j].width = 45;
            mapCollider[i][j].height = 72;
            // mapX++;
            // printf("%d,%d\n",j,i);
            copyTexture(&map[0][0],&map[i][j]);
        }
    }
    map[0][1].color = Color(0,255,0,128);
    printf("pase una vez 1\n");
    // newPeashotter();
    newCursor();
    loadPeaShooterAnimation();
    //renderer->core.setFrameLimit(false);
}



void Level1::update(){

    if(engine->pad.getClicked().R1){
        debugMode = !debugMode;
        if(debugMode == true){
            printf("\nDEBUG MODE ACTIVE\n");
            debugMenu();
        }else{
            printf("\nDEBUG MODE DEACTIVE\n");
        }
    }

    if(debugMode == true){
        if(engine->pad.getPressed().DpadUp){
            if(debugOption == 0){ debugOption = debugModesSize-1; }
            else{
                debugOption--;
            }
            debugMenu();
        }else if(engine->pad.getPressed().DpadDown){

            if(debugOption == debugModesSize-1){ debugOption = 0; }
            else{
                debugOption++;
            }
            debugMenu();
        }

        if(engine->pad.getPressed().Cross){
            activeDebugMode();
        }else if(engine->pad.getPressed().Circle){
            deactiveDebugMode();
        }
    }
    

    // plantMovement();
    cursorMovement();
    updateBoxCollider();

    for(int i=0; i < 5; i++){
        for(int j=0; j < 9; j++){
            if(collision(&boxColliderArray[cursor],&mapCollider[i][j]) == true/*collision(spriteArray[cursor],&map[i][j]) == true*/){
             cursorTile = Vec2(i,j);
            //  printf("estoy en tile %d,%d\n",j,i);
             i=5;
             j=9;
            }
        }
    }

    if(engine->pad.getClicked().Cross && debugMode == false){
        if(plantsCreated < maxPlants){
            createPlant(cursorTile.x,cursorTile.y);
        }else{
            printf("max plants created\n");
        }
    }

    if(stopAnimation==false){
        animManager.update();
    }
    
    // printf("animarray size: %d\n",animationArray.size());

    renderer->beginFrame();
    renderer->renderer2D.render(&background);
    
    // printf("cursor sprite id: %d\n",spriteArray[cursor].id);
    renderer->renderer2D.render(spriteArray[cursor]);
    renderer->renderer2D.render(debugBoxColliderArray[cursor]);

    for(int i=0; i < plantsCreated; i++){
        if(plant[i].type != None){
            renderer->renderer2D.render(spriteArray[*plant[i].body[0]]);
            renderer->renderer2D.render(spriteArray[*plant[i].body[1]]);
        }
    }
    
    for(int i=0;i<5;i++){
        for(int j=0;j<9;j++){
            renderer->renderer2D.render(&map[i][j]);
        }
    }
    
    renderer->endFrame();

}

void Level1::destroy(){

}
