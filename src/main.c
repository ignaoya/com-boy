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
			DrawText("A game by Ignacio Oyarzabal", 280, 290, 20, BLACK);
		EndDrawing();
	}

	// De-Initialization
	// -------------------------------------------------------------------------------------
	CloseWindow();

	return 0;
}
