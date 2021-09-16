#include "DemoGame.h"
#include "RayLib/raylib.h"

void DemoGame::onDraw() const{
	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}