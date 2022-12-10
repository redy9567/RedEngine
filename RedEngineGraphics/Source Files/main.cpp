#include <iostream>
#include "GraphicsSystem.h"
#include "Mesh2D.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Game.h"
#include "MemoryTracker.h"

using namespace std;

int main()
{

	Game* game = Game::getInstance();

	game->init();

	game->play();

	game->cleanup();

	Game::cleanupInstance();

	MemoryTracker::cleanupInstance();
	

	return 0;
}