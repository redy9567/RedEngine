#pragma once

#include "Trackable.h"

const int MAX_COLOR_VALUE = 255;

class Color : public Trackable
{

public:
	friend class GraphicsSystem;

	Color();
	~Color();
	Color(int, int, int, int);
	Color(float, float, float, float);

private:
	int mR, mG, mB, mA;

};
