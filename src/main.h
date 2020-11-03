#ifndef MAIN_H
#define MAIN_H

#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"

// Struct definitions
// --------------------------------------------------------------------------------------

typedef struct Sprite Sprite;
typedef struct Entity Entity;

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
    float angle;
    int permanent;  // bool to indicate if sprite should be permanent or disappear after anim cycle
    char type;      // char type to indicate which type of Entity it is, and especially which type of ball
    Entity *satellite;
} Entity;


// Planet Functions
// --------------------------------------------------------------------------------------
Entity CreatePlanet(Vector2 position, Texture2D texture);
void UpdatePlanet(Entity *planet, Vector2 orbitalCenter, float delta);
Vector2 GetOrbitDirection(Vector2 position, Vector2 orbitalCenter);



#endif
