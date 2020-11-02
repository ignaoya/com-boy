#include "main.h"

int main(void)
{
	// Initialization
	// -------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Com-Boy");

	// Main Loop
	// -------------------------------------------------------------------------------------
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(LIGHTGRAY);
			DrawText("Computer Boy", 100, 200, 80, BLACK);
		EndDrawing();
	}

	// De-Initialization
	// -------------------------------------------------------------------------------------
	CloseWindow();

	return 0;
}
