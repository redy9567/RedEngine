#include "Game.h"

Game::Game()
{
	mpGraphicsSystem = nullptr;
}

Game::~Game()
{
	if (mpGraphicsSystem)
		cleanup();
}

void Game::init()
{
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->init(800, 450);
}

void Game::cleanup()
{
	mpGraphicsSystem->cleanup();
}

void Game::doLoop()
{

	while (!mpGraphicsSystem->shouldExit())
	{

		mpGraphicsSystem->clearBackground();

		mpGraphicsSystem->drawText("Everything is abstracted!!", 190, 200);

		mpGraphicsSystem->flipGraphicsBuffer();

	}

}