#include "Game.h"
#include "GraphicsSystem.h"
#include "Color.h"

Game* Game::mspInstance = nullptr;

Game* Game::getInstance()
{
	if (!mspInstance)
		mspInstance = new Game();

	return mspInstance;
}

void Game::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

void Game::startGame()
{
	while (mpGraphicsSystem->isRunning())    // Detect window close button or ESC key
	{
		getInput();
		update();
		render();
	}
}

Game::Game()
{
	mpGraphicsSystem = nullptr;
}

Game::~Game()
{
	
}

void Game::init(int screenWidth, int screenHeight)
{
	mpGraphicsSystem = new GraphicsSystem();

	mpGraphicsSystem->init(screenWidth, screenHeight);
}

void Game::cleanup()
{
	mpGraphicsSystem->cleanup();

	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;
}

void Game::getInput()
{

}

void Game::update()
{

}

void Game::render()
{
	RColor lightGrey = RColor(150, 150, 150, 255);
	RColor white = RColor(255, 255, 255, 255);

	mpGraphicsSystem->clearScreenToColor(white);

	Vector2D loc(190, 200);

	mpGraphicsSystem->drawText("Guess what, BOYS", loc, lightGrey, 20);

	mpGraphicsSystem->flip();
}