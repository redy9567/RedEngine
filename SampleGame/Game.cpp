#include "Game.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include "Animation.h"
#include "Player.h"
#include "Timer.h"
#include "UnitManager.h"

#include <iostream>

using namespace std;

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
	mIsPlaying = true;
	mpGameTimer->start();
	while (mIsPlaying)    // Detect window close button or ESC key
	{
		deltaTime = mpGameTimer->getElapsedTime();
		mpGameTimer->start();

		getInput();
		update();
		render();

		debug();

		while(mpGameTimer->getElapsedTime() < mTimePerFrame)
			mpGameTimer->sleepUntilElapsed(mTimePerFrame);
			
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
	mpUnitManager = nullptr;
	mpProjAnimation = nullptr;
	mpProjBuffer = nullptr;

	mDebugMode = false;
	mIsPlaying = false;
	mTimePerFrame = 0.0f;
}

Game::~Game()
{
	
}

void Game::init(int screenWidth, int screenHeight, int fps, bool debugMode)
{
	SetExitKey(-1);
	SetTargetFPS(999);

	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();

	mpGraphicsSystem->init(screenWidth, screenHeight);

	mpUnitManager = new UnitManager();

	mpSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	mpProjBuffer = new GraphicsBuffer(ASSET_PATH + PROJECTILE_FILENAME);
	mpSmurfAnimation = new Animation(mpSmurfBuffer, 4, 4, 16);
	mpProjAnimation = new Animation(mpProjBuffer, 1, 13, 13, 0.25f);
	mpPlayerUnit = new Player(mpSmurfAnimation, 200.0f, Vector2D(300, 300));

	mpGameTimer = new Timer();

	mTimePerFrame = 1.0f / fps;
	mDebugMode = debugMode;

	srand(time(NULL));
}

void Game::cleanup()
{

	delete mpPlayerUnit;
	mpPlayerUnit = nullptr;

	delete mpUnitManager;
	mpUnitManager = nullptr;

	delete mpSmurfAnimation;
	mpSmurfAnimation = nullptr;

	delete mpProjAnimation;
	mpProjAnimation = nullptr;

	delete mpSmurfBuffer;
	mpSmurfBuffer = nullptr;

	delete mpProjBuffer;
	mpProjBuffer = nullptr;

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

	if(mpInputSystem->getMouseButtonDown(0))
	{
		Vector2D dir = Vector2D(mpInputSystem->getMousePosition().getX() - mpPlayerUnit->getLocation().getX(), mpInputSystem->getMousePosition().getY() - mpPlayerUnit->getLocation().getY());
		dir.normalize();
		mpUnitManager->createAndManageUnit(mpProjAnimation, mpPlayerUnit->getLocation(), dir, PROJECTILE_SPEED);
	}

	if(mpInputSystem->getKeyDown(Key_Escape))
	{
		mIsPlaying = false;
		cout << "QUIT" << endl;
	}
}

void Game::update()
{
	mpUnitManager->update(deltaTime);

	mpSmurfAnimation->update(deltaTime);
	mpProjAnimation->update(deltaTime);
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

	mpUnitManager->draw(mpGraphicsSystem);

	mpGraphicsSystem->flip();
}

void Game::debug()
{
	if(mDebugMode)
	{
		cout << "Frame Length: " << deltaTime << ", which is equal to " << 1 / deltaTime << " FPS." << endl;
	}
}