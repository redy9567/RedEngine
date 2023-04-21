#include "Game.h"
#include "Mesh2D.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture2D.h"
#include "ShaderManager.h"
#include "Animation.h"
#include "AnimationData.h"
#include "Timer.h"
#include "InputSystem.h"
#include "DebugHUD.h"
#include "Chicken.h";
#include "UIButton.h"
#include "ChickenManager.h"
#include <fstream>

#include <assert.h>
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

Game::Game()
{
	mpGraphicsSystem = nullptr;

	mInputLastF1State = false;
	mInputLastF2State = false;
	mInputLastF4State = false;
	mInputLastF5State = false;

	mDebugMode = false;

	mpButton = nullptr;
	mpButton2 = nullptr;
}

Game::~Game()
{

}

void Game::init(int mFPS)
{

	mpGraphicsSystem = GraphicsSystem::getInstance();
	mpInputSystem = InputSystem::getInstance();

	assert(mpGraphicsSystem->init(GAME_DISPLAY_WIDTH, GAME_DISPLAY_HEIGHT));

	initShaderObjects();

	initShaderPrograms();

	mpChickenManager = ChickenManager::getInstance();
	mpChickenManager->createAndAddChicken(Vector2D(9, 5));

	mpButton = new UIButton(Vector2D(300.0f, 0.0f));
	mpButton2 = new UIButton(Vector2D(400.0f, -20.0f), true);

	mpGraphicsSystem->createAndAddFont("arial", "Resource Files/Fonts/arial.ttf", 20);

	mTimePerFrame = 1.0f / mFPS;
	mDeltaTime = 0.0f;
	mpTimer = new Timer();

	ifstream versionFile = ifstream("buildInfo.dat");
	if (!versionFile.is_open())
	{
		mpGraphicsSystem->addPersistantToDebugHUD("Version: Debug");
	}
	else
	{
		string version;
		versionFile >> version;
		mpGraphicsSystem->addPersistantToDebugHUD("Version: " + version);
	}

	mCurrentMoney = 0;

	srand(time(NULL));
}

void Game::initShaderObjects()
{
	mpGraphicsSystem->createAndAddShader("Textured Vert", VERTEX_SHADER, "textured.vert");
	mpGraphicsSystem->createAndAddShader("Textured Frag", FRAGMENT_SHADER, "textured.frag");
	mpGraphicsSystem->createAndAddShader("Basic Vert", VERTEX_SHADER, "basic.vert");
	mpGraphicsSystem->createAndAddShader("Green Frag", FRAGMENT_SHADER, "green.frag");
	mpGraphicsSystem->createAndAddShader("Text Vert", VERTEX_SHADER, "text.vert");
	mpGraphicsSystem->createAndAddShader("Text Frag", FRAGMENT_SHADER, "text.frag");
}

void Game::initShaderPrograms()
{
	mpGraphicsSystem->createAndAddShaderProgram("Textured", "Textured Vert", "Textured Frag");
	mpGraphicsSystem->linkShaderProgram("Textured");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Textured", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Green", "Basic Vert", "Green Frag");
	mpGraphicsSystem->linkShaderProgram("Green");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Green", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Text", "Text Vert", "Text Frag");
	mpGraphicsSystem->linkShaderProgram("Text");

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	mpChickenManager->cleanup();
	ChickenManager::cleanupInstance();
	mpChickenManager = nullptr;

	delete mpTimer;
	mpTimer = nullptr;

	InputSystem::cleanupInstance();

	mpGraphicsSystem->cleanup();
	GraphicsSystem::cleanupInstance();
	mpGraphicsSystem = nullptr;
}

void Game::play()
{
	bool shouldContinue;

	do
	{
		shouldContinue = gameLoop();
	} while (shouldContinue);
}

bool Game::gameLoop()
{

	input();
	update();
	bool result = render();

	mpTimer->sleepUntilElapsed(mTimePerFrame * 1000);
	mDeltaTime = mpTimer->getElapsedTime();
	cout << "Delta Time: " << mDeltaTime << endl;
	mpTimer->start();

	return result;
}

void Game::input()
{
	
	Vector2D mousePos = mpInputSystem->getMousePosition();

	Vector2D buttonLoc = mpButton->getLoc();
	Vector2D buttonUpperBound = buttonLoc + mpButton->getSize();

	Vector2D button2Loc = mpButton2->getLoc();
	Vector2D button2UpperBound = button2Loc + mpButton2->getSize();

	Chicken* clickedChicken = mpChickenManager->checkChickenClicked(mousePos);

	if (clickedChicken)
	{
		if (mpInputSystem->getMouseButtonDown(InputSystem::MouseButton::Left))
		{
			clickedChicken->onMouseClick();
		}
		else if (mpInputSystem->getMouseButtonDown(InputSystem::MouseButton::Right) && clickedChicken->isEgg())
		{
			mpChickenManager->removeAndDeleteChicken(clickedChicken);

			mCurrentMoney += EGG_SELL_AMOUNT;
		}

	}

	mpButton->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, buttonLoc, buttonUpperBound));
	mpButton2->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, button2Loc, button2UpperBound));
	

	bool keyState = mpInputSystem->getKey(InputSystem::KeyCode::F1); //Fill vs. Wireframe
	if (keyState && !mInputLastF1State)
	{
		switch (mpGraphicsSystem->getDrawMode())
		{
		case GraphicsSystem::DrawMode::Fill:
			mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Wireframe);
			break;

		case GraphicsSystem::DrawMode::Wireframe:
			mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Fill);
			break;
		}
	}
	mInputLastF1State = keyState;

	keyState = mpInputSystem->getKey(InputSystem::KeyCode::F2); //Shader Switch
	if (keyState && !mInputLastF2State)
	{
		if (mpGraphicsSystem->getCurrentShaderProgram() == "Textured")
			mpGraphicsSystem->setActiveShaderProgram("Green");
		else
			mpGraphicsSystem->setActiveShaderProgram("Textured");
	}
	mInputLastF2State = keyState;
	
	keyState = mpInputSystem->getKey(InputSystem::KeyCode::F4); //Hot Reload Shaders... Should probably do this through the managers (to not add a line for every new shader)
	if (keyState && !mInputLastF4State)
	{
		mpGraphicsSystem->reloadShader("Textured Vert");
		mpGraphicsSystem->reloadShader("Textured Frag");
		mpGraphicsSystem->reloadShader("Basic Vert");
		mpGraphicsSystem->reloadShader("Green Frag");

		mpGraphicsSystem->linkShaderProgram("Textured");
		mpGraphicsSystem->linkShaderProgram("Green");
	}
	mInputLastF4State = keyState;

	keyState = mpInputSystem->getKey(InputSystem::KeyCode::F5); //Debug Mode
	if (keyState && !mInputLastF5State)
	{
		mDebugMode = !mDebugMode;
		mpGraphicsSystem->setDebugMode(mDebugMode);
	}
	mInputLastF5State = keyState;
}

void Game::update()
{
	mpGraphicsSystem->update(mDeltaTime);

	mpInputSystem->update();

	mpChickenManager->update(mDeltaTime);

	mpButton->update(mDeltaTime);
	mpButton2->update(mDeltaTime);

	Vector2D moneyTextOffset = Vector2D(MONEY_TEXT_HORIZONTAL_OFFSET, MONEY_TEXT_VERTICAL_OFFSET);
	mpGraphicsSystem->draw("$: " + to_string(mCurrentMoney), "arial", "Text", mpGraphicsSystem->getDisplayResolution() - moneyTextOffset,
		Vector3D::Up());

	int fps = debugGetFPS();
	if(fps != -1)
		mpGraphicsSystem->addToDebugHUD("FPS: " + to_string(debugGetFPS()));

	Vector2D mousePos = mpInputSystem->getMousePosition();
	mpGraphicsSystem->addToDebugHUD("Mouse Position: " + mousePos.toString());

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setVec2Uniform("Green", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setVec2Uniform("Text", "uResolution", mpGraphicsSystem->getDisplayResolution());
}

bool Game::render()
{
	mpChickenManager->drawAllChickens();

	mpGraphicsSystem->draw(mpButton);
	mpGraphicsSystem->draw(mpButton2);

	mpGraphicsSystem->draw("Hello World!", "arial", "Text", Vector2D(50, 50));

	return mpGraphicsSystem->render();
}