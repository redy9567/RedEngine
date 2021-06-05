#pragma once

#include <raylib-cpp.hpp>
#include "Vector2D.h"
#include "Trackable.h"
#include "GraphicsBuffer.h"

class RColor;

class GraphicsSystem : public Trackable
{

public:
	GraphicsSystem();
	~GraphicsSystem();

	void init();
	void init(int width, int height, std::string title = "InfraRED");

	void cleanup();

	void clearScreenToColor(RColor);
	void drawText(std::string text, Vector2D loc, RColor col, int fontSize = 12);
	void draw(GraphicsBuffer* gb);
	void draw(GraphicsBuffer* gb, Vector2D loc);

	void flip();

	bool isRunning();

private:
	raylib::Window* mWindow;
	int mWidth, mHeight;

	raylib::Vector2 convertVector(Vector2D vec);

};
