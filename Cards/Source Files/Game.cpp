#include "Game.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Animation.h"
#include "AnimationData.h"
#include "Timer.h"
#include "UnitManager.h"
#include "AnimationManager.h"
#include "GraphicsBufferManager.h"
#include "EventSystem.h"
#include "GameListener.h"

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
	mpPlayerUnit = nullptr;
	mpGameTimer = nullptr;

	mpUnitManager = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpAnimationManager = nullptr;

	mpGameListener = nullptr;

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

	mpGraphicsSystem->init(screenWidth, screenHeight);

	mpUnitManager = new UnitManager();

	initGraphicsBuffers();

	mpAnimationManager = new AnimationManager();

	//AnimationData* playerAnimData = mpAnimationManager->createAndManageAnimationData("smurf", smurfBuffer, 4, 4);
	//mpAnimationManager->createAndManageAnimationData("proj", projBuffer, 1, 13, 0.25f);

	mpGameListener = new GameListener();
	EventSystem::getInstance()->addListener(KEYBOARD_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener(MOUSE_EVENT, mpGameListener);

	mpGameTimer = new Timer();

	mTimePerFrame = 1.0f / fps;
	mDebugMode = debugMode;

	srand(time(NULL));
}

void Game::initGraphicsBuffers()
{
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CA", ASSET_PATH + CLUBS_ACE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C2", ASSET_PATH + CLUBS_TWO_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C3", ASSET_PATH + CLUBS_THREE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C4", ASSET_PATH + CLUBS_FOUR_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C5", ASSET_PATH + CLUBS_FIVE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C6", ASSET_PATH + CLUBS_SIX_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C7", ASSET_PATH + CLUBS_SEVEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C8", ASSET_PATH + CLUBS_EIGHT_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C9", ASSET_PATH + CLUBS_NINE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("C10", ASSET_PATH + CLUBS_TEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CJ", ASSET_PATH + CLUBS_JACK_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CQ", ASSET_PATH + CLUBS_QUEEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CK", ASSET_PATH + CLUBS_KING_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("DA", ASSET_PATH + DIAMONDS_ACE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D2", ASSET_PATH + DIAMONDS_TWO_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D3", ASSET_PATH + DIAMONDS_THREE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D4", ASSET_PATH + DIAMONDS_FOUR_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D5", ASSET_PATH + DIAMONDS_FIVE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D6", ASSET_PATH + DIAMONDS_SIX_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D7", ASSET_PATH + DIAMONDS_SEVEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D8", ASSET_PATH + DIAMONDS_EIGHT_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D9", ASSET_PATH + DIAMONDS_NINE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("D10", ASSET_PATH + DIAMONDS_TEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("DJ", ASSET_PATH + DIAMONDS_JACK_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("DQ", ASSET_PATH + DIAMONDS_QUEEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("DK", ASSET_PATH + DIAMONDS_KING_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("HA", ASSET_PATH + HEARTS_ACE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H2", ASSET_PATH + HEARTS_TWO_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H3", ASSET_PATH + HEARTS_THREE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H4", ASSET_PATH + HEARTS_FOUR_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H5", ASSET_PATH + HEARTS_FIVE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H6", ASSET_PATH + HEARTS_SIX_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H7", ASSET_PATH + HEARTS_SEVEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H8", ASSET_PATH + HEARTS_EIGHT_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H9", ASSET_PATH + HEARTS_NINE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("H10", ASSET_PATH + HEARTS_TEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("HJ", ASSET_PATH + HEARTS_JACK_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("HQ", ASSET_PATH + HEARTS_QUEEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("HK", ASSET_PATH + HEARTS_KING_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("SA", ASSET_PATH + SPADES_ACE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S2", ASSET_PATH + SPADES_TWO_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S3", ASSET_PATH + SPADES_THREE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S4", ASSET_PATH + SPADES_FOUR_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S5", ASSET_PATH + SPADES_FIVE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S6", ASSET_PATH + SPADES_SIX_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S7", ASSET_PATH + SPADES_SEVEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S8", ASSET_PATH + SPADES_EIGHT_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S9", ASSET_PATH + SPADES_NINE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("S10", ASSET_PATH + SPADES_TEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("SJ", ASSET_PATH + SPADES_JACK_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("SQ", ASSET_PATH + SPADES_QUEEN_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("SK", ASSET_PATH + SPADES_KING_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("JB", ASSET_PATH + BLACK_JOKER_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("JR", ASSET_PATH + RED_JOKER_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CB1", ASSET_PATH + BACK_ONE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CB2", ASSET_PATH + BACK_TWO_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CB3", ASSET_PATH + BACK_THREE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CB4", ASSET_PATH + BACK_FOUR_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CB5", ASSET_PATH + BACK_FIVE_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("CB6", ASSET_PATH + BACK_SIX_FILEPATH);
	mpGraphicsBufferManager->createAndManageGraphicsBuffer("background", ASSET_PATH + BACKGROUND_FILEPATH);
}

void Game::cleanup()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(mpGameListener);
	delete mpGameListener;
	mpGameListener = nullptr;

	delete mpUnitManager;
	mpUnitManager = nullptr;

	delete mpAnimationManager;
	mpAnimationManager = nullptr;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;

	EventSystem::cleanupInstance();

	InputSystem::cleanupInstance();

	mpGraphicsSystem->cleanup();

	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

	delete mpGameTimer;
	mpGameTimer = nullptr;
}

void Game::getInput()
{
	InputSystem::getInstance()->inputUpdate();
}

void Game::update()
{
	mpUnitManager->update(deltaTime);

	mpAnimationManager->update(deltaTime);
}

void Game::render()
{
	RColor lightGrey = RColor(150, 150, 150, 255);
	RColor white = RColor(255, 255, 255, 255);

	mpGraphicsSystem->clearScreenToColor(white);

	mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("background"), Vector2D::Zero());

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

void Game::DPlayerMove(Vector2D loc)
{
	cout << "Player move to: " << loc << endl;
}

void Game::DKeyPress(KeyCode key)
{
	cout << "Key pressed with ID: " << key << endl;
}

void Game::DMousePress(int button)
{
	cout << "Mouse Button pressed with ID: " << button << endl;
}

void Game::DKeyRelease(KeyCode key)
{
	cout << "Key released with ID: " << key << endl;
}

void Game::DMouseRelease(int button)
{
	cout << "Mouse Button released with ID: " << button << endl;
}

void Game::quitGame()
{
	mIsPlaying = false;
	cout << "QUIT" << endl;
}