/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib/raylib.h"
#include "baseGame.h"
#include "DemoGame.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	DemoGame* game = new DemoGame();
	game->init();
	//--------------------------------------------------------------------------------------
	while (!game->shouldClose()) {
		game->tick();
		while (game->shouldTickFixed()) {
			game->tickFixed();
		}
		game->draw();
	}
	// Main game loop
	
	return 0;
}