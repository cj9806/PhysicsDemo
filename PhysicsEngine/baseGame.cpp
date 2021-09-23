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
	colMap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = checkCircleCircle;
	colMap[static_cast<collisionPair>(shapeType::AABB   | shapeType::AABB  )] = checkAABBAABB;
	colMap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::AABB  )] = checkCircAABB;

	depMap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = depenetrateCircleCircle;
	depMap[static_cast<collisionPair>(shapeType::AABB   | shapeType::AABB  )] = depenetrateAABBAABB;
	depMap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::AABB  )] = depenetrateCircAABB;
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
			bool collision = colMap[pair](objs[lhs].pos, objs[lhs].collider,
				objs[rhs].pos, objs[rhs].collider);
			if (collision) {
				//do thing
				float pen = 0.0f;
				vec2 normal = depMap[pair](objs[lhs].pos, objs[lhs].collider,
					objs[rhs].pos, objs[rhs].collider,
					pen);

				resolvePhysBodies(objs[lhs], objs[rhs], 1.0f, normal, pen);

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

