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
#include "Camera2D.h"
#include "Vector4D.h"
#include "EventSystem.h"
#include "GameEvents.h"
#include "GameListener.h"
#include "GridSystem.h"
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
	mpScienceUI = nullptr;

	mpGameListener = nullptr;
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

	Texture2D* bgTexture = mpGraphicsSystem->createAndAddTexture2D("Background", RESOURCES_DIRECTORY + BACKGROUNDS_DIRECTORY + BACKGROUND_FILENAME, true);
	Vector2D bgScale = Vector2D(2, 2);
	Sprite* bgSprite = mpGraphicsSystem->createAndAddSprite("Background", &bgTexture, Vector2D::Zero(), bgTexture->getSize(), bgScale);
	mpBackground = mpGraphicsSystem->createAndAddGameObject2D("Background", bgSprite, Vector2D(21.5f, 19.5f));
	mpGraphicsSystem->setBackground(mpBackground);

	mpChickenManager = ChickenManager::getInstance();
	mpChickenManager->createAndAddChicken(Vector2D(9, 5));
	mpChickenManager->createAndAddChicken(Vector2D(12, 5));

	Vector2D button1Loc = Vector2D(500.0f, 100.0f);
	Vector2D button2Loc = Vector2D(700.0f, 100.0f);
	Vector2D currencyUILoc = Vector2D(GAME_DISPLAY_WIDTH + CURRENCY_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - CURRENCY_UI_VERTICAL_OFFSET);
	Vector2D scienceUILoc = Vector2D(GAME_DISPLAY_WIDTH + SCIENCE_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - SCIENCE_UI_VERTICAL_OFFSET);

	mpButton = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + SETTINGS_BUTTON_FILENAME, "codeAnimationSettingsButton", Direction::Up, 0.1f, 5.0f, button1Loc);
	mpButton2 = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + ANIMATIONS_DIRECTORY + BUTTONS_DIRECTORY + SETTINGS_BUTTON_ANIMATION_FILENAME, 
		"animationAnimationSettingsButton", 9, 1, button2Loc);

	mpCurrencyUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + CURRENCY_DIRECTORY + MONEY_UI_FILENAME, "currencyUI", Direction::Left, CURRENCY_UI_MOVE_DISTANCE, CURRENCY_UI_ANIMATION_SPEED, currencyUILoc);
	mpScienceUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + CURRENCY_DIRECTORY + SCIENCE_UI_FILENAME, "scienceUI", Direction::Left, SCIENCE_UI_MOVE_DISTANCE, SCIENCE_UI_ANIMATION_SPEED, scienceUILoc);

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

	mpGameListener = new GameListener();

	EventSystem::getInstance()->addListener(Event::MOUSE_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener(Event::KEYBOARD_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener((Event::EventType)GameEvent::CHICKEN_CLICK_EVENT, mpGameListener);

	srand(time(NULL));
}

void Game::initShaderObjects()
{
	mpGraphicsSystem->createAndAddShader("Textured Vert", VERTEX_SHADER, "textured.vert");
	mpGraphicsSystem->createAndAddShader("Textured Frag", FRAGMENT_SHADER, "textured.frag");
	mpGraphicsSystem->createAndAddShader("Basic Vert", VERTEX_SHADER, "basic.vert");
	mpGraphicsSystem->createAndAddShader("Basic UI Vert", VERTEX_SHADER, "basicUI.vert");
	mpGraphicsSystem->createAndAddShader("Color Frag", FRAGMENT_SHADER, "color.frag");
	mpGraphicsSystem->createAndAddShader("Text Vert", VERTEX_SHADER, "text.vert");
	mpGraphicsSystem->createAndAddShader("Text Frag", FRAGMENT_SHADER, "text.frag");
}

void Game::initShaderPrograms()
{
	mpGraphicsSystem->createAndAddShaderProgram("Textured", "Textured Vert", "Textured Frag");
	mpGraphicsSystem->linkShaderProgram("Textured");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Textured", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Color", "Basic Vert", "Color Frag");
	mpGraphicsSystem->linkShaderProgram("Color");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Color", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("ColorUI", "Basic UI Vert", "Color Frag");
	mpGraphicsSystem->linkShaderProgram("ColorUI");
	mpGraphicsSystem->activateFloatAttributeOnProgram("ColorUI", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Text", "Text Vert", "Text Frag");
	mpGraphicsSystem->linkShaderProgram("Text");

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	delete mpButton;
	delete mpButton2;
	delete mpCurrencyUI;
	delete mpScienceUI;

	mpChickenManager->cleanup();
	ChickenManager::cleanupInstance();
	mpChickenManager = nullptr;

	delete mpTimer;
	mpTimer = nullptr;

	InputSystem::cleanupInstance();
	
	delete mpGameListener;

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
	//cout << "Delta Time: " << mDeltaTime << endl;
	mpTimer->start();

	return result;
}

void Game::input()
{
	mpInputSystem->update();
}

void Game::update()
{
	mpGraphicsSystem->update(mDeltaTime);

	mpChickenManager->update(mDeltaTime);

	mpButton->update(mDeltaTime);
	mpButton2->update(mDeltaTime);

	mpCurrencyUI->update(mDeltaTime);
	mpScienceUI->update(mDeltaTime);

	Vector2D moneyTextOffset = Vector2D(MONEY_TEXT_HORIZONTAL_OFFSET, MONEY_TEXT_VERTICAL_OFFSET);
	mpGraphicsSystem->draw("$: " + to_string(mCurrentMoney), "arial", "Text", mpGraphicsSystem->getDisplayResolution() - moneyTextOffset,
		Vector3D::Up());

	int fps = debugGetFPS();
	if(fps != -1)
		mpGraphicsSystem->addToDebugHUD("FPS: " + to_string(debugGetFPS()));

	//Vector2D mousePos = mpInputSystem->getMousePosition();
	//mpGraphicsSystem->addToDebugHUD("Mouse Position: " + mousePos.toString());
	mpGraphicsSystem->addToDebugHUD("Camera Position: " + mpGraphicsSystem->getCamera()->getLoc().toString());

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setVec2Uniform("Color", "uResolution", mpGraphicsSystem->getDisplayResolution());
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

		mpGraphicsSystem->setActiveShaderProgram("Color");

		Vector4D green = Vector4D(0.0f, 1.0f, 0.0f, 1.0f);
		mpGraphicsSystem->setVec4Uniform("Color", "uColor", green);

		mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Wireframe);
		mpGraphicsSystem->draw(*mpChickenSelectionMesh);
		mpGraphicsSystem->setActiveShaderProgram(previousShader);
		mpGraphicsSystem->setDrawMode(previousDrawMode);
	}

	mpGraphicsSystem->drawUI(mpButton);
	mpGraphicsSystem->drawUI(mpButton2);

	mpGraphicsSystem->drawUI(mpCurrencyUI);
	mpGraphicsSystem->drawUI(mpScienceUI);

	mpGraphicsSystem->draw("Hello World!", "arial", "Text", Vector2D(50, 50));

	return mpGraphicsSystem->render();
}

void Game::checkChickenClicked(Vector2D mousePos, MouseAction mouseButton)
{
	GridSystem* grs = GridSystem::getInstance();
	Chicken* clickedChicken = mpChickenManager->checkChickenHovered(grs->convertPixelsToGrid(mousePos));
	EventSystem* es = EventSystem::getInstance();

	if (clickedChicken)
	{
		
		ChickenClickEvent cknEvent(clickedChicken, mouseButton);
		es->fireEvent(cknEvent);
	}
}

void Game::onChickenLeftClick(Chicken* ckn)
{
	if (mDebugMode)
	{

		if (mpSelectedChicken)
		{
			mpSelectedChicken->setDebugMode(false);
		}

		mpSelectedChicken = ckn;
		mpSelectedChicken->setDebugMode(true);
	}
	else
		ckn->onMouseClick();
}

void Game::onChickenRightClick(Chicken* ckn)
{
	if (!mDebugMode)
	{
		if (ckn->isEgg())
		{
			mpChickenManager->removeAndDeleteChicken(ckn);

			mCurrentMoney += EGG_SELL_AMOUNT;
		}
	}
}

void Game::moveDebugChicken(Vector2D mousePos)
{
	if (mpSelectedChicken && mDebugMode)
	{
		mpSelectedChicken->moveToLocation(mousePos);
	}
}

void Game::startMouseDrag(Vector2D mousePos)
{
	mpGraphicsSystem->getCamera()->startMouseDrag(mousePos);
}

void Game::stopMouseDrag()
{
	mpGraphicsSystem->getCamera()->stopMouseDrag();
}

void Game::onMouseMove(Vector2D mousePos)
{
	//Honestly all these calculations should be inherent in the UIElement class
	Vector2D buttonHalfSize = mpButton->getSize() / 2.0f;

	Vector2D buttonLowerBound = mpButton->getLoc() - buttonHalfSize;
	Vector2D buttonUpperBound = mpButton->getLoc() + buttonHalfSize;

	Vector2D button2LowerBound = mpButton2->getLoc() - buttonHalfSize;
	Vector2D button2UpperBound = mpButton2->getLoc() + buttonHalfSize;

	Vector2D currencyHalfSize = mpCurrencyUI->getSize() / 2.0f;

	Vector2D currencyLowerBound = mpCurrencyUI->getLoc() - currencyHalfSize;
	Vector2D currencyUpperBound = mpCurrencyUI->getLoc() + currencyHalfSize;

	Vector2D scienceHalfSize = mpScienceUI->getSize() / 2.0f;

	Vector2D scienceLowerBound = mpScienceUI->getLoc() - scienceHalfSize;
	Vector2D scienceUpperBound = mpScienceUI->getLoc() + scienceHalfSize;

	mpGraphicsSystem->getCamera()->update(mousePos);

	mpButton->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));
	mpButton2->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, buttonUpperBound, button2UpperBound));

	mpCurrencyUI->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, currencyLowerBound, currencyUpperBound));
	mpScienceUI->setIsHovered(Vector2D::IsPointWithinBounds(mousePos, scienceLowerBound, scienceUpperBound));
}

void Game::onToggleDrawMode()
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

void Game::onToggleShaders()
{
	if (mpGraphicsSystem->getCurrentShaderProgram() == "Textured")
	{
		mpGraphicsSystem->setActiveShaderProgram("Color");
		Vector4D green = Vector4D(0.0f, 1.0f, 0.0f, 1.0f);
		mpGraphicsSystem->setVec4Uniform("Color", "uColor", green);
	}
	else
		mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::onShaderHotReload()
{
	//Hot Reload Shaders... Should probably do this through the managers (to not add a line for every new shader)
	mpGraphicsSystem->reloadShader("Textured Vert");
	mpGraphicsSystem->reloadShader("Textured Frag");
	mpGraphicsSystem->reloadShader("Basic Vert");
	mpGraphicsSystem->reloadShader("Color Frag");

	mpGraphicsSystem->linkShaderProgram("Textured");
	mpGraphicsSystem->linkShaderProgram("Color");
}

void Game::onToggleDebugMode()
{
	mDebugMode = !mDebugMode;

	if (mpSelectedChicken && !mDebugMode)
	{
		mpSelectedChicken->setDebugMode(false);
		mpSelectedChicken = nullptr;
	}

	mpGraphicsSystem->setDebugMode(mDebugMode);
}