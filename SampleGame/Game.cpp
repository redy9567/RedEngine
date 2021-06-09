#include "Game.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include "Sprite.h"
#include "Unit.h"

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
	mpInputSystem = nullptr;
	mpSmurfBuffer = nullptr;
	mpSmurfSprite = nullptr;
	mpSmurfUnit = nullptr;
}

Game::~Game()
{
	
}

void Game::init(int screenWidth, int screenHeight)
{
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();

	mpGraphicsSystem->init(screenWidth, screenHeight);

	mpSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	mpSmurfSprite = new Sprite(mpSmurfBuffer, Vector2D::Zero(), Vector2D(60, 60));
	mpSmurfUnit = new Unit(mpSmurfSprite, Vector2D(300, 300));
}

void Game::cleanup()
{
	delete mpSmurfUnit;
	mpSmurfUnit = nullptr;

	delete mpSmurfSprite;
	mpSmurfSprite = nullptr;

	delete mpSmurfBuffer;
	mpSmurfBuffer = nullptr;

	delete mpInputSystem;
	mpInputSystem = nullptr;

	mpGraphicsSystem->cleanup();

	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;
}

void Game::getInput()
{
	if (mpInputSystem->getMouseButtonDown(0))
	{
		mpSmurfUnit->setLocation(mpInputSystem->getMousePosition());
	}
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

	mpSmurfUnit->draw(mpGraphicsSystem);

	mpGraphicsSystem->flip();
}