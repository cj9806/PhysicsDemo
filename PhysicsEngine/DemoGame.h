#pragma once
#include "baseGame.h"
#include "RayLib/raylib.h"
using std::vector;
class DemoGame : public baseGame {
	vector<PhysObject> objs;
	void onInit() override;
	void onDraw() const override;
	void onTickFixed() override;
};