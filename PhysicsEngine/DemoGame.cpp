#include "DemoGame.h"
#include "RayLib/raylib.h"
void DemoGame::onInit(){
	objs = vector<PhysObject>();
	objs.push_back(PhysObject(1.0f,glm::vec2(0,-1)));
}
void DemoGame::onDraw() const{
	ClearBackground(RAYWHITE);
	
	DrawCircle(objs[1].pos.x, objs[1].pos.y, .5, RED);
}
void DemoGame::onTickFixed() {
	objs[1].tickPhys(accumulatedFixedTime);
}