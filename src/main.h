#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"

// Struct definitions
// --------------------------------------------------------------------------------------
typedef struct Sprite {
    Texture2D texture;
    Rectangle frameRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
} Sprite;

typedef struct Entity {
    Vector2 position;
    Sprite sprite;
    float speed;
    int permanent;  // bool to indicate if sprite should be permanent or disappear after anim cycle
    char type;      // char type to indicate which type of Entity it is, and especially which type of ball
} Entity;


// Planet Functions
// --------------------------------------------------------------------------------------
Entity CreatePlanet(Vector2 position, Texture2D texture);
void UpdatePlanet(Entity *planet, float delta);



#endif
