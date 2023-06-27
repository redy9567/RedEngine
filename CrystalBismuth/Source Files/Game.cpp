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
#include "UIManager.h"
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

	mpUIManager = UIManager::getInstance();

	Vector2D shopButtonUILoc = Vector2D(SHOP_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D firstWindowUILoc = Vector2D(FIRST_WINDOW_UI_X, FIRST_WINDOW_UI_Y);
	Vector2D secondWindowUILoc = Vector2D(SECOND_WINDOW_UI_X, SECOND_WINDOW_UI_Y);

	Vector2D coopButtonUILoc = Vector2D(COOP_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D penButtonUILoc = Vector2D(PEN_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D hatcheryButtonUILoc = Vector2D(HATCHERY_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D scienceButtonUILoc = Vector2D(SCIENCE_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D settingsButtonUILoc = Vector2D(SETTINGS_BUTTON_UI_X, BASE_BUTTON_UI_Y);

	Vector2D reserachTreeUIOffset = Vector2D(RESEARCH_TREE_OFFSET_X, RESEARCH_TREE_OFFSET_Y);
	Vector2D scienceTreeUIOffset = Vector2D(SCIENCE_TREE_OFFSET_X, SCIENCE_TREE_OFFSET_Y);
	Vector2D treeUIButtonOffset1 = Vector2D(TREE_UI_BUTTON_OFFSET_1_X, TREE_UI_BUTTON_OFFSET_1_Y);
	Vector2D treeUIButtonOffset2 = Vector2D(TREE_UI_BUTTON_OFFSET_2_X, TREE_UI_BUTTON_OFFSET_2_Y);
	Vector2D treeUIButtonOffset3 = Vector2D(TREE_UI_BUTTON_OFFSET_3_X, TREE_UI_BUTTON_OFFSET_3_Y);
	Vector2D treeUIButtonOffset4 = Vector2D(TREE_UI_BUTTON_OFFSET_4_X, TREE_UI_BUTTON_OFFSET_4_Y);
	Vector2D treeUIButtonOffset5 = Vector2D(TREE_UI_BUTTON_OFFSET_5_X, TREE_UI_BUTTON_OFFSET_5_Y);
	Vector2D treeUIButtonOffset6 = Vector2D(TREE_UI_BUTTON_OFFSET_6_X, TREE_UI_BUTTON_OFFSET_6_Y);
	Vector2D treeUIButtonOffset7 = Vector2D(TREE_UI_BUTTON_OFFSET_7_X, TREE_UI_BUTTON_OFFSET_7_Y);
	Vector2D treeUIButtonOffset8 = Vector2D(TREE_UI_BUTTON_OFFSET_8_X, TREE_UI_BUTTON_OFFSET_8_Y);
	Vector2D treeUIButtonOffset9 = Vector2D(TREE_UI_BUTTON_OFFSET_9_X, TREE_UI_BUTTON_OFFSET_9_Y);
	Vector2D scienceUIButtonOffset1 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_1_X, SCIENCE_UI_BUTTON_OFFSET_1_Y);
	Vector2D scienceUIButtonOffset2 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_2_X, SCIENCE_UI_BUTTON_OFFSET_2_Y);
	Vector2D scienceUIButtonOffset3 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_3_X, SCIENCE_UI_BUTTON_OFFSET_3_Y);
	Vector2D scienceUIButtonOffset4 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_4_X, SCIENCE_UI_BUTTON_OFFSET_4_Y);
	Vector2D scienceUIButtonOffset5 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_5_X, SCIENCE_UI_BUTTON_OFFSET_5_Y);
	Vector2D scienceUIButtonOffset6 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_6_X, SCIENCE_UI_BUTTON_OFFSET_6_Y);
	Vector2D scienceUIButtonOffset7 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_7_X, SCIENCE_UI_BUTTON_OFFSET_7_Y);

	Vector2D currencyUILoc = Vector2D(GAME_DISPLAY_WIDTH + CURRENCY_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - CURRENCY_UI_VERTICAL_OFFSET);
	Vector2D scienceUILoc = Vector2D(GAME_DISPLAY_WIDTH + SCIENCE_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - SCIENCE_UI_VERTICAL_OFFSET);

	Vector2D windowScale = Vector2D(WINDOW_SCALE);
	Vector2D buttonScale = Vector2D(BUTTON_SCALE);
	Vector2D treeButtonScale = Vector2D(TREE_BUTTON_SCALE);
	Vector2D subTreeButtonScale = Vector2D(SUB_TREE_BUTTON_SCALE);
	Vector2D baseTreeScale = Vector2D(BASE_TREE_SCALE);
	Vector2D scienceTreeScale = Vector2D(SCIENCE_TREE_SCALE);
	Vector2D scienceButtonScale = Vector2D(SCIENCE_BUTTON_SCALE);

	UIElement* shopUI = mpUIManager->createAndAddUIElement(SHOP_UI_FILEPATH, "shopUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(SHOP_UI_BUTTON_FILEPATH, "shopButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, shopButtonUILoc, buttonScale, shopUI, true);

	UIElement* coopUI = mpUIManager->createAndAddUIElement(COOP_UI_FILEPATH, "coopUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(COOP_UI_BUTTON_FILEPATH, "coopButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, coopButtonUILoc, buttonScale, coopUI, true);
	mpUIManager->createAndAddUIElement(BASE_RESEARCH_TREE_FILEPATH, "baseResearchTreeUI", firstWindowUILoc + reserachTreeUIOffset, baseTreeScale, coopUI);
	mpUIManager->createAndAddUIElement(COOP_TREE_BUTTON_FILEPATH, "coopTreeButtonUI1", firstWindowUILoc + treeUIButtonOffset1, treeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "coopTreeButtonUI2", firstWindowUILoc + treeUIButtonOffset2, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "coopTreeButtonUI3", firstWindowUILoc + treeUIButtonOffset3, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI4", firstWindowUILoc + treeUIButtonOffset4, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "coopTreeButtonUI5", firstWindowUILoc + treeUIButtonOffset5, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI6", firstWindowUILoc + treeUIButtonOffset6, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI7", firstWindowUILoc + treeUIButtonOffset7, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI8", firstWindowUILoc + treeUIButtonOffset8, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI9", firstWindowUILoc + treeUIButtonOffset9, subTreeButtonScale, coopUI);

	UIElement* penUI = mpUIManager->createAndAddUIElement(PEN_UI_FILEPATH, "penUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(PEN_UI_BUTTON_FILEPATH, "penButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, penButtonUILoc, buttonScale, penUI, true);
	mpUIManager->createAndAddUIElement(BASE_RESEARCH_TREE_FILEPATH, "baseResearchTreeUI", firstWindowUILoc + reserachTreeUIOffset, baseTreeScale, penUI);
	mpUIManager->createAndAddUIElement(PEN_TREE_BUTTON_FILEPATH, "penTreeButtonUI1", firstWindowUILoc + treeUIButtonOffset1, treeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "penTreeButtonUI2", firstWindowUILoc + treeUIButtonOffset2, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "penTreeButtonUI3", firstWindowUILoc + treeUIButtonOffset3, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI4", firstWindowUILoc + treeUIButtonOffset4, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "penTreeButtonUI5", firstWindowUILoc + treeUIButtonOffset5, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI6", firstWindowUILoc + treeUIButtonOffset6, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI7", firstWindowUILoc + treeUIButtonOffset7, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI8", firstWindowUILoc + treeUIButtonOffset8, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI9", firstWindowUILoc + treeUIButtonOffset9, subTreeButtonScale, penUI);

	UIElement* hatcheryUI = mpUIManager->createAndAddUIElement(HATCHERY_UI_FILEPATH, "hatcheryUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(HATCHERY_UI_BUTTON_FILEPATH, "hatcheryButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, hatcheryButtonUILoc, buttonScale, hatcheryUI, true);
	mpUIManager->createAndAddUIElement(BASE_RESEARCH_TREE_FILEPATH, "baseResearchTreeUI", firstWindowUILoc + reserachTreeUIOffset, baseTreeScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(HATCHERY_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI1", firstWindowUILoc + treeUIButtonOffset1, treeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI2", firstWindowUILoc + treeUIButtonOffset2, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI3", firstWindowUILoc + treeUIButtonOffset3, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI4", firstWindowUILoc + treeUIButtonOffset4, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI5", firstWindowUILoc + treeUIButtonOffset5, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI6", firstWindowUILoc + treeUIButtonOffset6, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI7", firstWindowUILoc + treeUIButtonOffset7, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI8", firstWindowUILoc + treeUIButtonOffset8, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI9", firstWindowUILoc + treeUIButtonOffset9, subTreeButtonScale, hatcheryUI);

	UIElement* scienceWindowUI = mpUIManager->createAndAddUIElement(SCIENCE_UI_FILEPATH, "scienceWindowUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(SCIENCE_UI_BUTTON_FILEPATH, "scienceButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, scienceButtonUILoc, buttonScale, scienceWindowUI, true);
	mpUIManager->createAndAddUIElement(SCIENCE_RESEARCH_TREE_FILEPATH, "scienceResearchTreeUI", firstWindowUILoc + scienceTreeUIOffset, scienceTreeScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(RED_SYRINGE_TREE_BUTTON_FILEPATH, "redSyringeButtonUI", firstWindowUILoc + scienceUIButtonOffset1, subTreeButtonScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI2", firstWindowUILoc + scienceUIButtonOffset2, subTreeButtonScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI3", firstWindowUILoc + scienceUIButtonOffset3, subTreeButtonScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI4", firstWindowUILoc + scienceUIButtonOffset4, subTreeButtonScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI5", firstWindowUILoc + scienceUIButtonOffset5, subTreeButtonScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI6", firstWindowUILoc + scienceUIButtonOffset6, subTreeButtonScale, scienceWindowUI);
	mpUIManager->createAndAddUIElement(SCIENCE_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI7", firstWindowUILoc + scienceUIButtonOffset7, scienceButtonScale, scienceWindowUI);

	UIElement* settingsUI = mpUIManager->createAndAddUIElement(SETTINGS_UI_FILEPATH, "settingsUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(SETTINGS_UI_BUTTON_FILEPATH, "settingsButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, settingsButtonUILoc, buttonScale, settingsUI, true);

	mpUIManager->createAndAddUIElement(MONEY_UI_FILEPATH, "currencyUI", Direction::Left, CURRENCY_UI_MOVE_DISTANCE, CURRENCY_UI_ANIMATION_SPEED, currencyUILoc, Vector2D::One(), nullptr, true);
	mpUIManager->createAndAddUIElement(SCIENCE_COUNT_UI_FILEPATH, "scienceUI", Direction::Left, SCIENCE_UI_MOVE_DISTANCE, SCIENCE_UI_ANIMATION_SPEED, scienceUILoc, Vector2D::One(), nullptr, true);

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
	mpUIManager->cleanup();
	UIManager::cleanupInstance();
	mpUIManager = nullptr;

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

	mpUIManager->update(mDeltaTime);

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

	mpUIManager->draw();

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
	mpUIManager->onMouseHover(mousePos);

	mpGraphicsSystem->getCamera()->update(mousePos);
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
		mpUIManager->onClick(event.getMousePosition());
	}
}