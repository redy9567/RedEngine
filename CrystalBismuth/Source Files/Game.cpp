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
#include "UIElement.h"
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

	mpSelectedChicken = nullptr;

	mpButton = nullptr;
	mpButton2 = nullptr;

	mpCurrencyUI = nullptr;
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
	mpChickenManager->createAndAddChicken(Vector2D(12, 5));

	Vector2D button1Loc = mpGraphicsSystem->convertToGridCoordinates(Vector2D(300.0f, 0.0f)) + Vector2D(0.0f, -0.1f);
	Vector2D button2Loc = mpGraphicsSystem->convertToGridCoordinates(Vector2D(400.0f, -20.0f));
	Vector2D currencyUILoc = mpGraphicsSystem->convertToGridCoordinates(Vector2D(GAME_DISPLAY_WIDTH - CURRENCY_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - CURRENCY_UI_VERTICAL_OFFSET));

	mpButton = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + SETTINGS_BUTTON_FILENAME, "codeAnimationSettingsButton", Direction::Up, 0.1f, button1Loc);
	mpButton2 = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + ANIMATIONS_DIRECTORY + BUTTONS_DIRECTORY + SETTINGS_BUTTON_ANIMATION_FILENAME, 
		"animationAnimationSettingsButton", 9, 1, button2Loc);

	mpCurrencyUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + CURRENCY_DIRECTORY + MONEY_UI_FILENAME, "currencyUI", Direction::Left, 20.0f, currencyUILoc);

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
	
	//Honestly all these calculations should be inherent in the UIElement class
	Vector2D buttonHalfSize = mpGraphicsSystem->convertToGridCoordinates(mpButton->getSize()) / 2.0f;

	Vector2D buttonLowerBound = mpButton->getLoc() - buttonHalfSize;
	Vector2D buttonUpperBound = mpButton->getLoc() + buttonHalfSize;

	Vector2D button2LowerBound = mpButton2->getLoc() - buttonHalfSize;
	Vector2D button2UpperBound = mpButton2->getLoc() + buttonHalfSize;

	Vector2D currencyHalfSize = mpGraphicsSystem->convertToGridCoordinates(mpCurrencyUI->getSize()) / 2.0f;

	Vector2D currencyLowerBound = mpCurrencyUI->getLoc() - currencyHalfSize;
	Vector2D currencyUpperBound = mpCurrencyUI->getLoc() + currencyHalfSize;


	if (mpInputSystem->getMouseButtonDown(InputSystem::MouseButton::Left))
	{
		Chicken* clickedChicken = mpChickenManager->checkChickenClicked(mousePos);

		if (clickedChicken)
		{
			if (mDebugMode)
			{

				if (mpSelectedChicken)
				{
					mpSelectedChicken->setDebugMode(false);
				}

				mpSelectedChicken = clickedChicken;
				mpSelectedChicken->setDebugMode(true);
			}
			else
				clickedChicken->onMouseClick();
		}
		
	}
	else if (mpInputSystem->getMouseButtonDown(InputSystem::MouseButton::Right))
	{
		Chicken* clickedChicken = mpChickenManager->checkChickenClicked(mousePos);

		if (mpSelectedChicken && mDebugMode && mpInputSystem->getMouseButtonDown(InputSystem::MouseButton::Right))
		{
			mpSelectedChicken->moveToLocation(mousePos);
		}
		else if (clickedChicken) 
		{
			if (!mDebugMode)
			{
				if (clickedChicken->isEgg())
				{
					mpChickenManager->removeAndDeleteChicken(clickedChicken);

					mCurrentMoney += EGG_SELL_AMOUNT;
				}
			}
		}
	}

	

	mpButton->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));
	mpButton2->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, buttonUpperBound, button2UpperBound));

	mpCurrencyUI->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, currencyLowerBound, currencyUpperBound));


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

		if (mpSelectedChicken && !mDebugMode)
		{
			mpSelectedChicken->setDebugMode(false);
			mpSelectedChicken = nullptr;
		}

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

	mpCurrencyUI->update(mDeltaTime);

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

	if (mpSelectedChicken)
	{
		if (mpChickenSelectionMesh && mpChickenSelectionMesh->getVertexAt(3).getX() != mpSelectedChicken->getSize().getX())
		{
			delete mpChickenSelectionMesh;
			mpChickenSelectionMesh = nullptr;
		}

		if (!mpChickenSelectionMesh)
		{
			int pixelWidth = mpSelectedChicken->getSize().getX();

			Vector2D verticies[4] = {Vector2D(0,0), Vector2D(0,pixelWidth), Vector2D(pixelWidth,0), Vector2D(pixelWidth,pixelWidth)};
			unsigned int drawOrder[6] = {0, 1, 2, 1, 2, 3};
			mpChickenSelectionMesh = new Mesh2D(verticies, 4, drawOrder, 6);
		}

		string previousShader = mpGraphicsSystem->getCurrentShaderProgram();
		GraphicsSystem::DrawMode previousDrawMode = mpGraphicsSystem->getDrawMode();

		mpGraphicsSystem->setActiveShaderProgram("Green");
		mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Wireframe);
		mpGraphicsSystem->draw(*mpChickenSelectionMesh);
		mpGraphicsSystem->setActiveShaderProgram(previousShader);
		mpGraphicsSystem->setDrawMode(previousDrawMode);
	}

	mpGraphicsSystem->draw(mpButton);
	mpGraphicsSystem->draw(mpButton2);

	mpGraphicsSystem->draw(mpCurrencyUI);

	mpGraphicsSystem->draw("Hello World!", "arial", "Text", Vector2D(50, 50));

	return mpGraphicsSystem->render();
}