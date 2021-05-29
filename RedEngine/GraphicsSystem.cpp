#include "GraphicsSystem.h"
#include "Color.h"

using namespace raylib;
using namespace std;

GraphicsSystem::GraphicsSystem()
{
	mWidth = 0;
	mHeight = 0;
	mWindow = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{
	delete mWindow;
	mWindow = nullptr;
}

bool GraphicsSystem::isRunning()
{
	return !mWindow->ShouldClose();
}

void GraphicsSystem::init(int width, int height, std::string title)
{
	mWidth = width;
	mHeight = height;
	mWindow = new Window(width, height, title);

	SetTargetFPS(60);

	BeginDrawing();
}

void GraphicsSystem::init()
{
	mWidth = 800;
	mHeight = 450;
	mWindow = new Window();

	SetTargetFPS(60);

	BeginDrawing();
}

void GraphicsSystem::cleanup()
{
	EndDrawing();
}

void GraphicsSystem::debugDraw()
{
	raylib::Color textColor = raylib::LIGHTGRAY;

	

	mWindow->ClearBackground(raylib::RAYWHITE);

	textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);

	flip();
}

void GraphicsSystem::flip()
{
	EndDrawing();
	BeginDrawing();
}

void GraphicsSystem::clearScreenToColor(RColor col)
{
	mWindow->ClearBackground(col.getRayColor());
}

void GraphicsSystem::drawText(string text, Vector2D loc, RColor col, int fontSize)
{
	col.getRayColor().DrawText(text, loc.getX(), loc.getY(), fontSize);
}
