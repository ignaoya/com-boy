#include "main.h"

int main(void)
{
	// Initialization
	// -------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "MoonShot");

	Texture2D earthTexture = LoadTexture("resources/art/earth-temp.png");
	Texture2D sunTexture = LoadTexture("resources/art/sun-temp.png");

	Entity sun = CreatePlanet((Vector2){ 400.0f, 300.0f }, sunTexture);
	Entity earth = CreatePlanet((Vector2){ 400.0f, 500.0f }, earthTexture);
	Entity moon = CreatePlanet((Vector2){ 400.0f, 450.0f }, earthTexture);
	earth.satellite = &moon;

	bool intro = true;
	SetTargetFPS(60);
	// Main Loop
	// -------------------------------------------------------------------------------------
	while (!WindowShouldClose())
	{

		if (intro)
		{
			// Update
			// -------------------------------------------------------------------------------------
			if (IsKeyPressed(KEY_SPACE))
				intro = false;
			// Drawing
			// -------------------------------------------------------------------------------------
			BeginDrawing();
				ClearBackground(LIGHTGRAY);
				DrawText("MoonShot", 200, 200, 80, BLACK);
				DrawText("a game by", 330, 290, 20, BLACK);
				DrawText("Ignacio Oyarzabal", 300, 310, 20, BLACK);
				DrawText("Matias Oyarzabal", 300, 330, 20, BLACK);
				DrawText("Press SPACE to Launch", 150, 500, 40, BLACK);
			EndDrawing();
		}
		else
		{
			// Update
			// -------------------------------------------------------------------------------------
			float deltaTime = GetFrameTime();
			UpdatePlanet(&earth, sun.position, deltaTime);
			UpdatePlanet(&moon, earth.position, deltaTime);
			
			// Drawing
			// -------------------------------------------------------------------------------------
			BeginDrawing();
				ClearBackground(LIGHTGRAY);
				DrawText("Press ESCAPE to Crash", 150, 100, 40, BLACK);

				DrawTextureRec(earth.sprite.texture, earth.sprite.frameRec, earth.position, WHITE);
				DrawTextureRec(moon.sprite.texture, moon.sprite.frameRec, moon.position, GRAY);
				DrawTextureRec(sun.sprite.texture, sun.sprite.frameRec, sun.position, WHITE);

			EndDrawing();
		}
	}

	// De-Initialization
	// -------------------------------------------------------------------------------------
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
    planet.speed = 250.0f;
	planet.angle = 0.0f;
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

	if (planet->satellite != NULL)
	{
		planet->satellite->position.x -= direction.x * planet->speed * delta;
		planet->satellite->position.y -= direction.y * planet->speed * delta;
	}
}

Vector2 GetOrbitDirection(Vector2 position, Vector2 orbitalCenter)
{
	float distance = Vector2Distance(position, orbitalCenter);
	Vector2 direction = (Vector2){ orbitalCenter.x - position.x, orbitalCenter.y - position.y };
	Vector2 nDirection = (Vector2){ direction.x / distance, direction.y / distance };
	Vector2 orbitDirection = Vector2Rotate(nDirection, 90.2f);

	return orbitDirection;
}


