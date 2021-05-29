#pragma once

#include "raylib-cpp.hpp"

const int MAX_COLOR_VALUE = 255;

class RColor
{

public:
	friend class GraphicsSystem;

	RColor();
	~RColor();
	RColor(int, int, int, int);
	RColor(float, float, float, float);

private:
	int mR, mG, mB, mA;

	raylib::Color getRayColor();

};
