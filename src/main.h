#ifndef MAIN_H
#define MAIN_H

#include "stdlib.h"
#include "time.h"
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
    Vector2 direction;
    char playerMove;
    int permanent;  // bool to indicate if sprite should be permanent or disappear after anim cycle
    char type;      // char type to indicate which type of Entity it is, and especially which type of ball
    bool leftEarth; //bool to indicate if a ship has left earth's orbit
    float countdown; // Counter for ships to liftoff
    bool exploded; //bool to indicate if a ship has exploded
} Entity;


// Planet Functions
// --------------------------------------------------------------------------------------
Entity CreatePlanet(Vector2 position, Texture2D texture);
void CreateShip(Entity ships[], int *num, Entity *earth, Texture2D texture);
void UpdateShip(Entity *ship, Entity *earth, Entity *moon, float delta, Texture2D explosion);
void UpdatePlanet(Entity *planet, Vector2 orbitalCenter, float delta);
void UpdatePlayer(Entity *planet, Vector2 orbitalCenter, float delta);
Vector2 GetOrbitDirection(Vector2 position, Vector2 orbitalCenter, bool isPlanet);
Vector2 GetShipDirection(Vector2 position, Vector2 origin);
Vector2 GetGravityVector(Vector2 position, Vector2 oldDirection, Vector2 orbitalCenter);
bool CheckCollisions(Entity *ship, Vector2 earthPos);
void UpdateSpriteFrame(Sprite *sprite);



#endif
