#include "Game.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include "Animation.h"
#include "AnimationData.h"
#include "Player.h"
#include "Timer.h"
#include "UnitManager.h"
#include "AnimationManager.h"

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
	mpPlayerUnit = nullptr;
	mpGameTimer = nullptr;
	mpUnitManager = nullptr;
	mpProjBuffer = nullptr;
	mpSmurfAnimationData = nullptr;
	mpProjAnimationData = nullptr;

	mpAnimationManager = nullptr;

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

	mpSmurfAnimationData = new AnimationData(mpSmurfBuffer, 4, 4);
	mpProjAnimationData = new AnimationData(mpProjBuffer, 1, 13, 0.25f);
	mpAnimationManager = new AnimationManager();

	Animation* playerAnim = mpAnimationManager->createAndManageAnimation(mpSmurfAnimationData, 16);
	mpPlayerUnit = new Player(playerAnim, 200.0f, Vector2D(300, 300));

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

	delete mpSmurfAnimationData;
	mpSmurfAnimationData = nullptr;

	delete mpProjAnimationData;
	mpProjAnimationData = nullptr;

	delete mpAnimationManager;
	mpAnimationManager = nullptr;

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

		Animation* projAnim = mpAnimationManager->createAndManageAnimation(mpProjAnimationData, 13);

		mpUnitManager->createAndManageUnit(projAnim, mpPlayerUnit->getLocation(), dir, PROJECTILE_SPEED);
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

	mpAnimationManager->update(deltaTime);
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