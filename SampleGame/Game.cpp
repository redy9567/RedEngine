#include "Game.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include "Animation.h"
#include "Player.h"
#include "Timer.h"

#include <iostream>

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
	mpGameTimer->start();
	while (mpGraphicsSystem->isRunning())    // Detect window close button or ESC key
	{
		deltaTime = mpGameTimer->getElapsedTime();
		mpGameTimer->start();

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
	mpSmurfAnimation = nullptr;
	mpPlayerUnit = nullptr;
	mpGameTimer = nullptr;
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
	mpSmurfAnimation = new Animation(mpSmurfBuffer, 4, 4, 16);
	mpPlayerUnit = new Player(mpSmurfAnimation, 200.0f, Vector2D(300, 300));

	mpGameTimer = new Timer();
}

void Game::cleanup()
{

	delete mpPlayerUnit;
	mpPlayerUnit = nullptr;

	delete mpSmurfAnimation;
	mpSmurfAnimation = nullptr;

	delete mpSmurfBuffer;
	mpSmurfBuffer = nullptr;

	delete mpInputSystem;
	mpInputSystem = nullptr;

	mpGraphicsSystem->cleanup();

	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

	delete mpGameTimer;
	mpGameTimer = nullptr;
}

void Game::getInput()
{

	Vector2D dir = Vector2D::Zero();

	if(mpInputSystem->getKey(Key_A))
	{
		dir += Vector2D::Left();
	}
	if(mpInputSystem->getKey(Key_S))
	{
		dir += Vector2D::Down();
	}
	if(mpInputSystem->getKey(Key_D))
	{
		dir += Vector2D::Right();
	}
	if(mpInputSystem->getKey(Key_W))
	{
		dir += Vector2D::Up();
	}

	dir.normalize();
	
	mpPlayerUnit->setMoveDirection(dir);
}

void Game::update()
{
	mpSmurfAnimation->update(deltaTime);
	mpPlayerUnit->update(deltaTime);
}

void Game::render()
{
	RColor lightGrey = RColor(150, 150, 150, 255);
	RColor white = RColor(255, 255, 255, 255);

	mpGraphicsSystem->clearScreenToColor(white);

	Vector2D loc(190, 200);

	mpGraphicsSystem->drawText("Guess what, BOYS", loc, lightGrey, 20);

	mpPlayerUnit->draw(mpGraphicsSystem);

	mpGraphicsSystem->flip();
}