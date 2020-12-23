#include "GraphicsSystem.h"
#include "raylib-cpp.hpp"

using namespace raylib;
using namespace std;

GraphicsSystem::GraphicsSystem()
{
	mScreenWidth = 0;
	mScreenHeight = 0;
	mpWindow = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{

	if (mpWindow)
		cleanup();

}

void GraphicsSystem::init()
{
	if (mpWindow)
		cleanup();

	mpWindow = new raylib::Window();

	BeginDrawing();
	SetTargetFPS(60);
}

void GraphicsSystem::init(int screenWidth, int screenHeight)
{
	if (mpWindow)
		cleanup();

	mpWindow = new Window(screenWidth, screenHeight);
}

void GraphicsSystem::init(int screenWidth, int screenHeight, string windowName)
{
	if (mpWindow)
		cleanup();

	mpWindow = new Window(screenWidth, screenHeight, windowName);
}

void GraphicsSystem::cleanup()
{
	if (mpWindow)
	{
		delete mpWindow;
	}
}

bool GraphicsSystem::shouldExit()
{
	return mpWindow->ShouldClose();
}

void GraphicsSystem::flipGraphicsBuffer()
{
	EndDrawing();
	BeginDrawing();
}

void GraphicsSystem::clearBackground()
{
	raylib::Color::RayWhite.ClearBackground();
}

void GraphicsSystem::drawText(string text, int xLoc, int yLoc)
{
	DrawText(text.c_str(), xLoc, yLoc, 24, ::LIGHTGRAY);
}