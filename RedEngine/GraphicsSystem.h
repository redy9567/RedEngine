#pragma once

#include <raylib-cpp.hpp>

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
	void drawText(std::string text, int x, int y, RColor col, int fontSize = 12);

	void debugDraw(); //TO BE REMOVED

	void flip();

	bool isRunning();

private:
	raylib::Window* mWindow;
	int mWidth, mHeight;


};
