#include "GraphicsSystem.h"
#include "Color.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"

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

void GraphicsSystem::draw(GraphicsBuffer* gb, Vector2D loc, float scale)
{
	gb->mTexture->Draw(convertVector(loc), 0.0f, scale);
}

void GraphicsSystem::draw(Sprite* sprite, Vector2D loc)
{
	sprite->mpGraphicsBuffer->mTexture->Draw(
		raylib::Rectangle(sprite->mLoc.getX(), sprite->mLoc.getY(), sprite->mSize.getX(), sprite->mSize.getY()), //Dimentions of the sprite on the Texture
		raylib::Rectangle(loc.getX(), loc.getY(), sprite->mSize.getX() * sprite->mScale, sprite->mSize.getY() * sprite->mScale)); //convertVector(loc)); //Location to draw on screen
}

raylib::Vector2 GraphicsSystem::convertVector(Vector2D vec)
{
	return raylib::Vector2(vec.getX(), vec.getY());
}