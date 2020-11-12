#include "main.h"

int main(void)
{
	// Initialization
	// -------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "MoonShot");

	Texture2D earthTexture = LoadTexture("resources/art/earth-small.png");
	Texture2D sunTexture = LoadTexture("resources/art/big-sun-temp.png");
	Texture2D moonTexture = LoadTexture("resources/art/moon-temp.png");
	Texture2D shipTexture = LoadTexture("resources/art/ship-temp.png");

	Entity sun = CreatePlanet((Vector2){ 400.0f, -500.0f }, sunTexture);
	sun.speed = 20.0f;
	Entity earth = CreatePlanet((Vector2){ 400.0f, 300.0f }, earthTexture);
	Entity moon = CreatePlanet((Vector2){ 400.0f, 400.0f }, moonTexture);
	Entity ships[10] = { 0 };
	int shipsNum = 0;

	bool intro = true;
	SetTargetFPS(60);
	int shipTimer = 0;
	double startTime = 0;
	// Main Loop
	// -------------------------------------------------------------------------------------
	while (!WindowShouldClose())
	{

		if (intro)
		{
			// Update
			// -------------------------------------------------------------------------------------
			if (IsKeyPressed(KEY_SPACE))
			{
				intro = false;
				startTime = GetTime();
			}
			// Drawing
			// -------------------------------------------------------------------------------------
			BeginDrawing();
				ClearBackground(BLACK);
				DrawText("MoonShot", 200, 200, 80, LIGHTGRAY);
				DrawText("a game by", 330, 290, 20, LIGHTGRAY);
				DrawText("Ignacio Oyarzabal", 300, 310, 20, LIGHTGRAY);
				DrawText("Matias Oyarzabal", 300, 330, 20, LIGHTGRAY);
				DrawText("Press SPACE to Launch", 150, 500, 40, LIGHTGRAY);
			EndDrawing();
		}
		else
		{
			// Update
			// -------------------------------------------------------------------------------------
			float deltaTime = GetFrameTime();
			UpdatePlanet(&sun, (Vector2){ screenWidth/2, screenHeight/2 }, deltaTime);
			UpdatePlayer(&moon, earth.position, deltaTime);
			shipTimer = (int)(GetTime() - startTime) % 10;
			if (shipTimer == 3)
				CreateShip(ships, &shipsNum, &earth, shipTexture);
			if (shipsNum != 0)
				UpdateShip(&(ships[0]), &earth, &moon, deltaTime);
			
			// Drawing
			// -------------------------------------------------------------------------------------
			BeginDrawing();

			ClearBackground(BLACK);

			Vector2 earthPos = (Vector2){ earth.position.x - (earth.sprite.frameRec.width/2), earth.position.y - (earth.sprite.frameRec.height/2) };
			Vector2 sunPos = (Vector2){ sun.position.x - (sun.sprite.frameRec.width/2), sun.position.y - (sun.sprite.frameRec.height/2) };
			DrawTextureRec(earth.sprite.texture, earth.sprite.frameRec, earthPos, WHITE);
			DrawTextureRec(moon.sprite.texture, moon.sprite.frameRec, moon.position, WHITE);
			DrawTextureRec(sun.sprite.texture, sun.sprite.frameRec, sunPos, WHITE);
			for (int i = 0; i < shipsNum; i++)
				DrawTextureRec(ships[i].sprite.texture, ships[i].sprite.frameRec, ships[i].position, WHITE);
			DrawFPS(700, 50);

			EndDrawing();
		}
	}

	// De-Initialization
	// -------------------------------------------------------------------------------------
	UnloadTexture(earthTexture);
	UnloadTexture(sunTexture);
	UnloadTexture(shipTexture);
	CloseWindow();

	return 0;
}

Entity CreatePlanet(Vector2 position, Texture2D texture)
{
	Entity planet = { 0 };
	planet.position = position;
    planet.sprite.texture = texture;  // Texture Loading
    planet.sprite.frameRec = (Rectangle){ 0.0f, 0.0f, (float)planet.sprite.texture.width, (float)planet.sprite.texture.height };
    planet.sprite.currentFrame = 0;
    planet.sprite.framesCounter = 0;
    planet.sprite.framesSpeed = 8;
    planet.speed = 200.0f;
	planet.direction = (Vector2){ 0.0f, 0.0f };
    planet.permanent = 1;
    planet.type = 'p';
	planet.satellite = NULL;

    return planet;
}

void UpdatePlanet(Entity *planet, Vector2 orbitalCenter, float delta)
{
	Vector2 direction = GetOrbitDirection(planet->position, orbitalCenter);
	planet->position.x -= direction.x * planet->speed * delta;
	planet->position.y -= direction.y * planet->speed * delta;

	/* THIS IS A FUNCTION THAT MOVES A SATELLITE AT THE SAME TIME AS ITS PARENT PLANET
	if (planet->satellite != NULL)
	{
		planet->satellite->position.x -= direction.x * planet->speed * delta;
		planet->satellite->position.y -= direction.y * planet->speed * delta;
		UpdatePlanet(planet->satellite, planet->position, delta);
	}
	*/
}

void UpdatePlayer(Entity *planet, Vector2 orbitalCenter, float delta)
{
	if(IsKeyDown(KEY_LEFT))
	{
		Vector2 direction = GetOrbitDirection(planet->position, orbitalCenter);
		planet->position.x -= direction.x * planet->speed * delta;
		planet->position.y -= direction.y * planet->speed * delta;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		Vector2 direction = GetOrbitDirection(planet->position, orbitalCenter);
		planet->position.x += direction.x * planet->speed * delta;
		planet->position.y += direction.y * planet->speed * delta;
	}
}

void UpdateShip(Entity *ship, Entity *earth, Entity *moon, float delta)
{
	if (ship->countdown < 0.1f)
	{
		Vector2 direction = { 0.0, 0.0 };
		if (ship->speed < 100)
			ship->speed++;
		if (Vector2Distance(ship->position, moon->position) < 20)
		{
			direction = GetOrbitDirection(ship->position, moon->position);
		}
		else
		{
			direction = GetShipDirection(ship->position, earth->position);
		}
		ship->position.x -= direction.x * ship->speed * delta;
		ship->position.y -= direction.y * ship->speed * delta;
	}
	else
	{
		ship->countdown -= 1.0 * delta;
	}
}

Vector2 GetShipDirection(Vector2 position, Vector2 origin)
{
	float distance = Vector2Distance(position, origin);
	Vector2 direction = (Vector2){ origin.x - position.x, origin.y - position.y };
	Vector2 nDirection = (Vector2){ direction.x / distance, direction.y / distance };

	return nDirection;
}




// NEW FUNCTION TODO
// Make a function that takes a previousVelocityVector and modifies that with the force of gravity towards the planet
// so that each time the previousVelocityVector gets updated and makes it turn downwards organically.

Vector2 GetGravityVector(Vector2 position, Vector2 oldDirection, Vector2 orbitalCenter)
{
	float distance = Vector2Distance(orbitalCenter, (Vector2){ position.x + oldDirection.x, position.y + oldDirection.y });
	Vector2 direction = (Vector2){ position.x + oldDirection.x - orbitalCenter.x, position.y + oldDirection.y - orbitalCenter.y };
	Vector2 nDirection = (Vector2){ direction.x / distance, direction.y / distance };
	float intensity = distance / 3.0f;
	Vector2 gravity = (Vector2){ nDirection.x / intensity, nDirection.y / intensity };

	return gravity;
}


Vector2 GetOrbitDirection(Vector2 position, Vector2 orbitalCenter)
{
	float distance = Vector2Distance(position, orbitalCenter);
	Vector2 direction = (Vector2){ orbitalCenter.x - position.x, orbitalCenter.y - position.y };
	Vector2 nDirection = (Vector2){ direction.x / distance, direction.y / distance };
	Vector2 orbitDirection = Vector2Rotate(nDirection, 95.0f);

	return orbitDirection;
}

void CreateShip(Entity ships[], int *num, Entity * earth, Texture2D texture)
{
	if (*num < 1)
	{
		Entity ship = { 0 };
		Vector2 posModifier = (Vector2){ earth->position.x - (earth->position.x - (earth->sprite.texture.width/2)),
										 earth->position.y - (earth->position.y) };
		//posModifier = (Vector2){ posModifier.x / (earth->sprite.texture.width/2), posModifier.y / (earth->sprite.texture.width/2) };
		posModifier = Vector2Rotate(posModifier, 20.0f * (*num));
		ship.position = (Vector2){ earth->position.x + posModifier.x, earth->position.y + posModifier.y };
		ship.sprite.texture = texture;  // Texture Loading
		ship.sprite.frameRec = (Rectangle){ 0.0f, 0.0f, (float)ship.sprite.texture.width, (float)ship.sprite.texture.height };
		ship.sprite.currentFrame = 0;
		ship.sprite.framesCounter = 0;
		ship.sprite.framesSpeed = 8;
		ship.speed = 200.0f;
		ship.direction = (Vector2){ 0.0f, 0.0f };
		ship.permanent = 1;
		ship.type = 'p';
		ship.satellite = NULL;
		ship.countdown = 2.0f;

		ships[*num] = ship;
		(*num)++;
	}
}


//OLD UPDATE PLAYER FUNCTION USING GRAVITY FUNCITON (WORKS TERRIBLY)
/*
void UpdatePlayer(Entity *planet, Vector2 orbitalCenter, float delta)
{
	if(IsKeyDown(KEY_LEFT))
	{
		Vector2 gravity = GetGravityVector(planet->position, planet->direction, orbitalCenter);
		Vector2 newDirection = (Vector2){ planet->direction.x + gravity.x, planet->direction.y + gravity.y };
		planet->position.x -= newDirection.x * planet->speed * delta; 
		planet->position.y -= newDirection.y * planet->speed * delta;
		planet->direction = newDirection;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		if (planet->playerMove == 'l')
		{
			Vector2 temp = Vector2Rotate(planet->direction, 180.0f);
			planet->direction = temp;
			planet->playerMove = 'r';
		}
		Vector2 gravity = GetGravityVector(planet->position, planet->direction, orbitalCenter);
		Vector2 newDirection = (Vector2){ planet->direction.x + gravity.x, planet->direction.y + gravity.y };
		planet->position.x += newDirection.x * planet->speed * delta;
		planet->position.y += newDirection.y * planet->speed * delta;
		planet->direction = newDirection;
	}
}
*/
