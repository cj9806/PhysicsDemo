#include "baseGame.h"
#include "RayLib/raylib.h"
#include"EnumUtils.h"
#include <vector>
#include <iostream>
baseGame::baseGame() {
	objs = vector<PhysObject>();
	accumulatedFixedTime = 0;
	targetFixedStep = 1.0f / 30.0f;
	//maxFixedStep = targetFixedStep * 3.0f;
	colmap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = checkCircleCircle;
	colmap[static_cast<collisionPair>(shapeType::AABB   | shapeType::AABB  )] = checkAABBAABB;
	colmap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::AABB  )] = checkCircAABB;
}


void baseGame::init(){
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	SetTargetFPS(60);

	onInit();
}
void baseGame::tick() {
	onTick();

	accumulatedFixedTime += GetFrameTime();
}
void baseGame::tickFixed() {
	accumulatedFixedTime -= targetFixedStep;
	for (size_t i = 0; i < objs.size(); i++) {
		objs[i].tickPhys(targetFixedStep);
	}
	for (size_t i = 0; i < objs.size(); i++) {
		for (size_t j = 0; j < objs.size(); j++) {
			//skip self collision
			if (i == j) continue;
			//skip things that have no collider
			if (objs[i].collider.type == shapeType::NONE ||
				objs[j].collider.type == shapeType::NONE)
			    continue;

			int lhs = i;
			int rhs = j;

			//keep lesser oriented collider first
			if ((uint8_t)objs[i].collider.type > (uint8_t)objs[j].collider.type) {
				lhs = j;
				rhs = i;
			}

			collisionPair pair = (collisionPair)(objs[lhs].collider.type | objs[rhs].collider.type);
			bool collision = colmap[pair](objs[lhs].pos, objs[lhs].collider,
				objs[rhs].pos, objs[rhs].collider);
			if (collision) {
				std::cout << "collision at" << accumulatedFixedTime<<std::endl;
			}
		}
	}
	onTickFixed();
	//if (accumulatedFixedTime > maxFixedStep)
	//	accumulatedFixedTime = maxFixedStep;
	
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
bool baseGame::shouldTickFixed() const {
	return accumulatedFixedTime > targetFixedStep;
}

