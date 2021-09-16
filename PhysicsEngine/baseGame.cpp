#include "baseGame.h"
#include "RayLib/raylib.h"
baseGame::baseGame() {

}
float accumulatedFixedTime = 0;
float targetFixedStep = 1 / 30;
float maxFixedStep = targetFixedStep * 3;

void baseGame::init(){
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	SetTargetFPS(60);

	onInit();
}
void baseGame::tick() {
	onTick();

	while (accumulatedFixedTime >= targetFixedStep) {
		onTickFixed();
		if (accumulatedFixedTime > maxFixedStep) 
			accumulatedFixedTime = maxFixedStep;
		accumulatedFixedTime -= targetFixedStep;
	}
	accumulatedFixedTime += GetFrameTime();
}
void baseGame::draw()const {
	BeginDrawing();

	onDraw();

	EndDrawing();
}
void baseGame::exit() {
	onExit();
	CloseWindow();
}
bool baseGame::shouldClose() const {
	return WindowShouldClose();
}

