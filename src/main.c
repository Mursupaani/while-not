#include "../include/while-not.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

game_t	game;

void	initialize_game()
{
	Image	background = LoadImage("Assets/Background/mountains.jpg");
	ImageResize(&background, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.background = LoadTextureFromImage(background);
}

int	main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "while(not) presents");
	SetTargetFPS(60);
	// 1. Texture loader?
	// 2. Initialize game?
	initialize_game();
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(game.background, 0, 0, WHITE);
		EndDrawing();
	}
	return (0);
}
