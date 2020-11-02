#include "main.h"

int main(void)
{
	// Initialization
	// -------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "MoonShot");

	bool gameOver = false;
	bool intro = true;
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
			if (IsKeyPressed(KEY_SPACE))
				gameOver = true;
			// Drawing
			// -------------------------------------------------------------------------------------
			BeginDrawing();
				ClearBackground(LIGHTGRAY);
				DrawText("Press ESCAPE to Crash", 150, 500, 40, BLACK);
			EndDrawing();
		}
	}

	// De-Initialization
	// -------------------------------------------------------------------------------------
	CloseWindow();

	return 0;
}
