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
#include "UIElement.h"
#include "Camera2D.h"
#include "Vector4D.h"
#include "EventSystem.h"
#include "GameEvents.h"
#include "GridSystem.h"
#include "UIManager.h"
#include "Filepaths.h"
#include "Vector2D.h"
#include <fstream>
#include "Physics.h"

#include <assert.h>
#include <iostream>

using namespace std;

Game* Game::mspInstance = nullptr;

const Vector2D circleStartLoc = Vector2D(21.5f, 11.0f);
const Vector2D rodStartLoc = Vector2D(21.5f, 22.0f);

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

	mpBuildingHighlight = nullptr;
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

	loadData();

	mpGraphicsSystem->setBackgroundColor(Vector3D(0.7f, 0.7f, 0.7f));

	Texture2D* circleTexture = mpGraphicsSystem->createAndAddTexture2D("circle", RESOURCES_DIRECTORY + "circle.png", true);
	Texture2D* squareTexture = mpGraphicsSystem->createAndAddTexture2D("square", RESOURCES_DIRECTORY + "square.png", false);

	Vector2D circleScale = Vector2D(0.05f, 0.05f);
	Vector2D rodScale = Vector2D(0.01f, 0.85f);

	Sprite* squareSprite = mpGraphicsSystem->createAndAddSprite("square", &squareTexture, Vector2D::Zero(), squareTexture->getSize(), rodScale);
	mRodObj = mpGraphicsSystem->createAndAddGameObject2D(squareSprite, rodStartLoc);

	Sprite* circleSprite = mpGraphicsSystem->createAndAddSprite("circle", &circleTexture, Vector2D::Zero(), circleTexture->getSize(), circleScale);
	mCircleObj = mpGraphicsSystem->createAndAddGameObject2D(circleSprite, circleStartLoc);

	mRodObj->setRotation(mRunningTime);

	//Texture2D* bgTexture = mpGraphicsSystem->createAndAddTexture2D("Background", RESOURCES_DIRECTORY + BACKGROUNDS_DIRECTORY + BACKGROUND_FILENAME, true);
	//Vector2D bgScale = Vector2D(2, 2);
	//Sprite* bgSprite = mpGraphicsSystem->createAndAddSprite("Background", &bgTexture, Vector2D::Zero(), bgTexture->getSize(), bgScale);
	//mpBackground = mpGraphicsSystem->createAndAddGameObject2D(bgSprite, Vector2D(21.5f, 19.5f));
	//mpGraphicsSystem->setBackground(mpBackground);

	mpUIManager = UIManager::getInstance();
	mpUIManager->init();

	
	mpGraphicsSystem->createAndAddFont("arial", "Resource Files/Fonts/arial.ttf", 20);

	mTimePerFrame = 1.0f / mFPS;
	mDeltaTime = 0.0f;
	mRunningTime = 0.0f;
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

	srand(time(NULL));
}

void Game::loadData()
{
	//Texture2D* tex = mpGraphicsSystem->createAndAddTexture2D("ScienceBuilding", SCIENCE_BUILDING_FILEPATH, true);
	//mpGraphicsSystem->createAndAddSprite("ScienceBuilding", &tex, Vector2D::Zero(), tex->getSize());
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

	mpGraphicsSystem->createAndAddShader("Textured Bounded Vert", VERTEX_SHADER, "texturedBounded.vert");
	mpGraphicsSystem->createAndAddShader("Textured Bounded Frag", FRAGMENT_SHADER, "texturedBounded.frag");
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

	mpGraphicsSystem->createAndAddShaderProgram("Textured Bounded", "Textured Bounded Vert", "Textured Bounded Frag");
	mpGraphicsSystem->linkShaderProgram("Textured Bounded");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Textured Bounded", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	mpUIManager->cleanup();
	UIManager::cleanupInstance();
	mpUIManager = nullptr;

	delete mpTimer;
	mpTimer = nullptr;

	InputSystem::cleanupInstance();
	
	EventSystem::cleanupInstance();

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
	mRunningTime += mDeltaTime;
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
	mCircleObj->setLoc(circleStartLoc + Vector2D(smallAnglePendulumFunction(mRunningTime), 0.0f));
	mRodObj->setRotation(smallAnglePendulumAngle(mRunningTime));
	
	mpGraphicsSystem->update(mDeltaTime);

	mpUIManager->update(mDeltaTime);

	int fps = debugGetFPS();
	if(fps != -1)
		mpGraphicsSystem->addToDebugHUD("FPS: " + to_string(debugGetFPS()));

	//Vector2D mousePos = mpInputSystem->getMousePosition();
	//mpGraphicsSystem->addToDebugHUD("Mouse Position: " + mousePos.toString());
	mpGraphicsSystem->addToDebugHUD("Camera Position: " + mpGraphicsSystem->getCamera()->getLoc().toString());

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("Textured Bounded", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("Color", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("Text", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("ColorTextured", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
}

bool Game::render()
{

	mpGraphicsSystem->setActiveShaderProgram("ColorTextured");
	mpGraphicsSystem->setVec4Uniform("ColorTextured", "uColor", Vector4D(1.0f, 0.0f, 0.0f, 1.0f));
	
	mpGraphicsSystem->drawInternalObjects();

	mpGraphicsSystem->setActiveShaderProgram("Textured");



	string previousShader = mpGraphicsSystem->getCurrentShaderProgram();
	mpGraphicsSystem->setActiveShaderProgram("Textured Bounded");
	mpUIManager->draw();
	mpGraphicsSystem->setActiveShaderProgram(previousShader);

	mpGraphicsSystem->drawUI("Hello World!", "arial", "Text", Vector2D(50, 50));

	return mpGraphicsSystem->render();
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

	mpGraphicsSystem->setDebugMode(mDebugMode);
}