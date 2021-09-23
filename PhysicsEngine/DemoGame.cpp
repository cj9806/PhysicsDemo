#include "DemoGame.h"
#include "RayLib/raylib.h"

void DemoGame::onDraw() const{
	ClearBackground(RAYWHITE);
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i].draw();
	}
	
}
void DemoGame::onTickFixed() {
	/*for (int i=0; i < objs.size();i++)
	{
	
	}*/
	
}
void DemoGame::onTick() {
	if (IsMouseButtonPressed(0)) {
		PhysObject newObj;
		glm::vec2 mosPos = glm::vec2(GetMouseX(), GetMouseY());
		newObj.pos = mosPos;
		newObj.vel.x = GetRandomValue(-20, 20);
		newObj.vel.y = GetRandomValue(-20, 20);
		newObj.collider.type = shapeType::CIRCLE;
		newObj.collider.circleData.radius = GetRandomValue(5, 12.5);
		int shapeChoose = GetRandomValue(1, 2);
		
		

		objs.push_back(newObj);
	}
	else if(IsMouseButtonPressed(1)) {
		PhysObject newObj;
		newObj.collider.type = shapeType::AABB;
		glm::vec2 mosPos = glm::vec2(GetMouseX(), GetMouseY());
		newObj.pos = mosPos;
		newObj.vel.x = GetRandomValue(-20, 20);
		newObj.vel.y = GetRandomValue(-20, 20);
		int width = GetRandomValue(10, 25);
		int heigth = GetRandomValue(10, 25);
		newObj.collider.rectData.extents = glm::vec2(width, heigth);
		objs.push_back(newObj);
	}
	else if (IsMouseButtonPressed(2)) {
		PhysObject newObj;
		newObj.collider.type = shapeType::AABB;
		glm::vec2 mosPos = glm::vec2(GetMouseX(), GetMouseY());
		newObj.pos = mosPos;
		newObj.collider.rectData.extents = glm::vec2(50, 50);
		newObj.isStatic = true;
		objs.push_back(newObj);
	}
}