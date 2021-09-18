#pragma once
#include "baseGame.h"
#include "RayLib/raylib.h"
using std::vector;
class DemoGame : public baseGame {	
	void onDraw() const override;
	void onTickFixed() override;
	void onTick() override;
};