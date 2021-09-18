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
		newObj.vel.x = GetRandomValue(-10, 10);
		newObj.vel.y = GetRandomValue(-10, 10);

		int shapeChoose = GetRandomValue(1, 2);
		if (shapeChoose == 1) {
			newObj.collider.type = shapeType::CIRCLE;
		}
		else newObj.collider.type = shapeType::AABB;
		int width = GetRandomValue(10, 25);
		int heigth = GetRandomValue(10, 25);
		newObj.collider.rectData.extents = glm::vec2(width, heigth);

		objs.push_back(newObj);
	}
}