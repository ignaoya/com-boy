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
			
			// Drawing
			// -------------------------------------------------------------------------------------
			BeginDrawing();
				ClearBackground(LIGHTGRAY);
				DrawText("Press ESCAPE to Crash", 150, 100, 40, BLACK);

				DrawTextureRec(earth.sprite.texture, earth.sprite.frameRec, earth.position, WHITE);
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
    planet.permanent = 1;
    planet.type = 'p';

    return planet;
}
