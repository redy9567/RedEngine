#include "GridSystem.h"
#include <assert.h>

using namespace std;

GridSystem* GridSystem::mspInstance = nullptr;

GridSystem* GridSystem::getInstance()
{
	if (!mspInstance)
		mspInstance = new GridSystem();

	return mspInstance;
}

void GridSystem::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

GridSystem::GridSystem()
{
	mInit = false;
	mGridBoxWidth = 0.0f;
	mGridBoxHeight = 0.0f;
}

GridSystem::~GridSystem()
{

}

void GridSystem::init(int displayWidth, int displayHeight)
{
	updateResolution(displayWidth, displayHeight);
	mInit = true;
}

void GridSystem::updateResolution(int displayWidth, int displayHeight)
{
	mGridBoxWidth = displayWidth / STARTING_GRID_COUNT_X;
	mGridBoxHeight = displayHeight / STARTING_GRID_COUNT_Y;
}

void GridSystem::cleanup()
{
	mInit = false;
}

Vector2D GridSystem::convertPixelsToGrid(Vector2D pxLoc)
{
	assert(mInit);
	
	return Vector2D(
		(pxLoc.getX() / mGridBoxWidth),
		(pxLoc.getY() / mGridBoxHeight)
			);
}

Vector2D GridSystem::convertGridToPixels(Vector2D gridLoc)
{
	assert(mInit);

	return Vector2D(
		(int)(gridLoc.getX() * mGridBoxWidth),
		(int)(gridLoc.getY() * mGridBoxHeight)
			);
}

Vector2D GridSystem::convertScreenToGrid(Vector2D screenLoc)
{
	return Vector2D(
		screenLoc.getX() * STARTING_GRID_COUNT_X,
		screenLoc.getY() * STARTING_GRID_COUNT_Y
	);
}