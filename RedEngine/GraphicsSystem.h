#pragma once

#include <raylib-cpp.hpp>

class GraphicsSystem
{

public:
	GraphicsSystem();
	~GraphicsSystem();

	void init();
	void init(int width, int height, std::string title = "InfraRED");

	void cleanup();

	void debugDraw(); //TO BE REMOVED

	void flip();

	bool isRunning();

private:
	raylib::Window* mWindow;
	int mWidth, mHeight;


};
