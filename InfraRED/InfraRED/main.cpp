#include "GraphicsSystem.h"

using namespace std;


int main()
{

	int screenWidth = 800;
	int screenHeight = 450;

	GraphicsSystem* graphicsSystem = new GraphicsSystem();
	graphicsSystem->init(screenWidth, screenHeight);
	
	while (!graphicsSystem->shouldExit())
	{

		graphicsSystem->clearBackground();

		graphicsSystem->drawText("It works! Congrats!", 190, 200);

		graphicsSystem->flipGraphicsBuffer();

	}

	return 0;
}