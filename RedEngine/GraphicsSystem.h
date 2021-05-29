#pragma once

#include <raylib-cpp.hpp>
#include "Vector2D.h"

class RColor;

class GraphicsSystem
{

public:
	GraphicsSystem();
	~GraphicsSystem();

	void init();
	void init(int width, int height, std::string title = "InfraRED");

	void cleanup();

	void clearScreenToColor(RColor);
	void drawText(std::string text, Vector2D loc, RColor col, int fontSize = 12);

	void debugDraw(); //TO BE REMOVED

	void flip();

	bool isRunning();

private:
	raylib::Window* mWindow;
	int mWidth, mHeight;


};
