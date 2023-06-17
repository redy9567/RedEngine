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

	mpShopButtonUI = nullptr;
	mpShopUI = nullptr;

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
	mpChickenManager->createAndAddChicken(ChickenColor::WHITE, Vector2D(9, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::BLACK, Vector2D(10, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::BLUE, Vector2D(11, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::LIGHT_BLUE, Vector2D(12, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::GREEN, Vector2D(13, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::YELLOW, Vector2D(14, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::RED, Vector2D(15, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::PURPLE, Vector2D(16, 5));

	Vector2D shopButtonUILoc = Vector2D(SHOP_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D firstWindowUILoc = Vector2D(FIRST_WINDOW_UI_X, FIRST_WINDOW_UI_Y);
	Vector2D secondWindowUILoc = Vector2D(SECOND_WINDOW_UI_X, SECOND_WINDOW_UI_Y);

	Vector2D coopButtonUILoc = Vector2D(COOP_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D penButtonUILoc = Vector2D(PEN_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D hatcheryButtonUILoc = Vector2D(HATCHERY_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D scienceButtonUILoc = Vector2D(SCIENCE_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D settingsButtonUILoc = Vector2D(SETTINGS_BUTTON_UI_X, BASE_BUTTON_UI_Y);

	Vector2D currencyUILoc = Vector2D(GAME_DISPLAY_WIDTH + CURRENCY_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - CURRENCY_UI_VERTICAL_OFFSET);
	Vector2D scienceUILoc = Vector2D(GAME_DISPLAY_WIDTH + SCIENCE_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - SCIENCE_UI_VERTICAL_OFFSET);

	Vector2D windowScale = Vector2D(WINDOW_SCALE);
	Vector2D buttonScale = Vector2D(BUTTON_SCALE);

	mpShopUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + WINDOWS_DIRECTORY + BASE_WINDOW_FILENAME, "shopUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpShopButtonUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + SHOP_BUTTON_FILENAME, "shopButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, shopButtonUILoc, buttonScale, mpShopUI);

	mpCoopUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + WINDOWS_DIRECTORY + BUTTON_WINDOWS_DIRECTORY + COOP_WINDOW_FILENAME, "coopUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpCoopButtonUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + COOP_BUTTON_FILENAME, "coopButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, coopButtonUILoc, buttonScale, mpCoopUI);

	mpPenUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + WINDOWS_DIRECTORY + BUTTON_WINDOWS_DIRECTORY + PEN_WINDOW_FILENAME, "penUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpPenButtonUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + PEN_BUTTON_FILENAME, "penButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, penButtonUILoc, buttonScale, mpPenUI);

	mpHatcheryUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + WINDOWS_DIRECTORY + BUTTON_WINDOWS_DIRECTORY + HATCHERY_WINDOW_FILENAME, "hatcheryUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpHatcheryButtonUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + HATCHERY_BUTTON_FILENAME, "hatcheryButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, hatcheryButtonUILoc, buttonScale, mpHatcheryUI);

	mpScienceWindowUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + WINDOWS_DIRECTORY + BUTTON_WINDOWS_DIRECTORY + SCIENCE_WINDOW_FILENAME, "scienceWindowUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpScienceButtonUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + SCIENCE_BUTTON_FILENAME, "scienceButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, scienceButtonUILoc, buttonScale, mpScienceWindowUI);

	mpSettingsUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + WINDOWS_DIRECTORY + BASE_WINDOW_FILENAME, "settingsUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpSettingsButtonUI = new UIElement(RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + MAIN_BUTTONS_DIRECTORY + SETTINGS_BUTTON_FILENAME, "settingsButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, settingsButtonUILoc, buttonScale, mpSettingsUI);

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

	mpGraphicsSystem->createAndAddShader("Chicken Color", FRAGMENT_SHADER, "chickenColor.frag");
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

	mpGraphicsSystem->createAndAddShaderProgram("ChickenColor", "Textured Vert", "Chicken Color");
	mpGraphicsSystem->linkShaderProgram("ChickenColor");
	mpGraphicsSystem->activateFloatAttributeOnProgram("ChickenColor", 0, 3); //Sets Attribute 0 to a 3 dimentional float value
	mpGraphicsSystem->activateFloatAttributeOnProgram("ChickenColor", 1, 3); //Sets Attribute 1 to a 3 dimentional float value
	mpGraphicsSystem->activateFloatAttributeOnProgram("ChickenColor", 2, 2); //Sets Attribute 2 to a 2 dimentional float value

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	delete mpShopButtonUI;
	delete mpShopUI;

	delete mpCoopButtonUI;
	delete mpCoopUI;

	delete mpPenButtonUI;
	delete mpPenUI;

	delete mpHatcheryButtonUI;
	delete mpHatcheryUI;

	delete mpScienceButtonUI;
	delete mpScienceWindowUI;

	delete mpSettingsButtonUI;
	delete mpSettingsUI;

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

	mpShopUI->update(mDeltaTime);

	if(!mpShopUI->getIsAnimating())
		mpShopButtonUI->update(mDeltaTime);

	mpCoopUI->update(mDeltaTime);

	if (!mpCoopUI->getIsAnimating())
		mpCoopButtonUI->update(mDeltaTime);

	mpPenUI->update(mDeltaTime);

	if (!mpPenUI->getIsAnimating())
		mpPenButtonUI->update(mDeltaTime);

	mpHatcheryUI->update(mDeltaTime);

	if (!mpHatcheryUI->getIsAnimating())
		mpHatcheryButtonUI->update(mDeltaTime);

	mpScienceWindowUI->update(mDeltaTime);

	if (!mpScienceWindowUI->getIsAnimating())
		mpScienceButtonUI->update(mDeltaTime);

	mpSettingsUI->update(mDeltaTime);

	if (!mpSettingsUI->getIsAnimating())
		mpSettingsButtonUI->update(mDeltaTime);

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
	mpGraphicsSystem->setIntegerUniform("ChickenColor", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("ChickenColor", "uResolution", mpGraphicsSystem->getDisplayResolution());
}

bool Game::render()
{
	mpGraphicsSystem->setActiveShaderProgram("ChickenColor");

	mpChickenManager->drawAllChickens();

	mpGraphicsSystem->setActiveShaderProgram("Textured");

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

	mpGraphicsSystem->drawUI(mpShopUI);
	mpGraphicsSystem->drawUI(mpShopButtonUI);

	mpGraphicsSystem->drawUI(mpCoopUI);
	mpGraphicsSystem->drawUI(mpCoopButtonUI);

	mpGraphicsSystem->drawUI(mpPenUI);
	mpGraphicsSystem->drawUI(mpPenButtonUI);

	mpGraphicsSystem->drawUI(mpHatcheryUI);
	mpGraphicsSystem->drawUI(mpHatcheryButtonUI);

	mpGraphicsSystem->drawUI(mpScienceWindowUI);
	mpGraphicsSystem->drawUI(mpScienceButtonUI);

	mpGraphicsSystem->drawUI(mpSettingsUI);
	mpGraphicsSystem->drawUI(mpSettingsButtonUI);

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
	Vector2D buttonHalfSize = mpShopButtonUI->getSize() / 2.0f;

	Vector2D buttonLowerBound = mpShopButtonUI->getLoc() - buttonHalfSize;
	Vector2D buttonUpperBound = mpShopButtonUI->getLoc() + buttonHalfSize;

	Vector2D currencyHalfSize = mpCurrencyUI->getSize() / 2.0f;

	Vector2D currencyLowerBound = mpCurrencyUI->getLoc() - currencyHalfSize;
	Vector2D currencyUpperBound = mpCurrencyUI->getLoc() + currencyHalfSize;

	Vector2D scienceHalfSize = mpScienceUI->getSize() / 2.0f;

	Vector2D scienceLowerBound = mpScienceUI->getLoc() - scienceHalfSize;
	Vector2D scienceUpperBound = mpScienceUI->getLoc() + scienceHalfSize;

	mpGraphicsSystem->getCamera()->update(mousePos);

	mpShopButtonUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));


	buttonHalfSize = mpCoopButtonUI->getSize() / 2.0f;

	buttonLowerBound = mpCoopButtonUI->getLoc() - buttonHalfSize;
	buttonUpperBound = mpCoopButtonUI->getLoc() + buttonHalfSize;

	mpCoopButtonUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));


	buttonHalfSize = mpPenButtonUI->getSize() / 2.0f;

	buttonLowerBound = mpPenButtonUI->getLoc() - buttonHalfSize;
	buttonUpperBound = mpPenButtonUI->getLoc() + buttonHalfSize;

	mpPenButtonUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));


	buttonHalfSize = mpHatcheryButtonUI->getSize() / 2.0f;

	buttonLowerBound = mpHatcheryButtonUI->getLoc() - buttonHalfSize;
	buttonUpperBound = mpHatcheryButtonUI->getLoc() + buttonHalfSize;

	mpHatcheryButtonUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));


	buttonHalfSize = mpScienceButtonUI->getSize() / 2.0f;

	buttonLowerBound = mpScienceButtonUI->getLoc() - buttonHalfSize;
	buttonUpperBound = mpScienceButtonUI->getLoc() + buttonHalfSize;

	mpScienceButtonUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));


	buttonHalfSize = mpSettingsButtonUI->getSize() / 2.0f;

	buttonLowerBound = mpSettingsButtonUI->getLoc() - buttonHalfSize;
	buttonUpperBound = mpSettingsButtonUI->getLoc() + buttonHalfSize;

	mpSettingsButtonUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, buttonLowerBound, buttonUpperBound));


	mpCurrencyUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, currencyLowerBound, currencyUpperBound));
	mpScienceUI->setAnimating(Vector2D::IsPointWithinBounds(mousePos, scienceLowerBound, scienceUpperBound));
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

void Game::checkUIClicked(const MouseEvent event)
{
	if (event.getButtonState() == ButtonState::Down)
	{
		Vector2D buttonHalfSize = mpShopButtonUI->getSize() / 2.0f;

		Vector2D buttonLowerBound = mpShopButtonUI->getLoc() - buttonHalfSize;
		Vector2D buttonUpperBound = mpShopButtonUI->getLoc() + buttonHalfSize;

		if (Vector2D::IsPointWithinBounds(event.getMousePosition(), buttonLowerBound, buttonUpperBound))
		{
			mpShopUI->setAnimating(!mpShopUI->getIsAnimating());
		}


		buttonHalfSize = mpCoopButtonUI->getSize() / 2.0f;

		buttonLowerBound = mpCoopButtonUI->getLoc() - buttonHalfSize;
		buttonUpperBound = mpCoopButtonUI->getLoc() + buttonHalfSize;

		if (Vector2D::IsPointWithinBounds(event.getMousePosition(), buttonLowerBound, buttonUpperBound))
		{
			mpCoopUI->setAnimating(!mpCoopUI->getIsAnimating());
		}


		buttonHalfSize = mpPenButtonUI->getSize() / 2.0f;

		buttonLowerBound = mpPenButtonUI->getLoc() - buttonHalfSize;
		buttonUpperBound = mpPenButtonUI->getLoc() + buttonHalfSize;

		if (Vector2D::IsPointWithinBounds(event.getMousePosition(), buttonLowerBound, buttonUpperBound))
		{
			mpPenUI->setAnimating(!mpPenUI->getIsAnimating());
		}

		buttonHalfSize = mpHatcheryButtonUI->getSize() / 2.0f;

		buttonLowerBound = mpHatcheryButtonUI->getLoc() - buttonHalfSize;
		buttonUpperBound = mpHatcheryButtonUI->getLoc() + buttonHalfSize;

		if (Vector2D::IsPointWithinBounds(event.getMousePosition(), buttonLowerBound, buttonUpperBound))
		{
			mpHatcheryUI->setAnimating(!mpHatcheryUI->getIsAnimating());
		}


		buttonHalfSize = mpScienceButtonUI->getSize() / 2.0f;

		buttonLowerBound = mpScienceButtonUI->getLoc() - buttonHalfSize;
		buttonUpperBound = mpScienceButtonUI->getLoc() + buttonHalfSize;

		if (Vector2D::IsPointWithinBounds(event.getMousePosition(), buttonLowerBound, buttonUpperBound))
		{
			mpScienceWindowUI->setAnimating(!mpScienceWindowUI->getIsAnimating());
		}


		buttonHalfSize = mpSettingsButtonUI->getSize() / 2.0f;

		buttonLowerBound = mpSettingsButtonUI->getLoc() - buttonHalfSize;
		buttonUpperBound = mpSettingsButtonUI->getLoc() + buttonHalfSize;

		if (Vector2D::IsPointWithinBounds(event.getMousePosition(), buttonLowerBound, buttonUpperBound))
		{
			mpSettingsUI->setAnimating(!mpSettingsUI->getIsAnimating());
		}
	}
}