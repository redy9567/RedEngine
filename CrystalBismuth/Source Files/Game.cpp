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

	mpTextureCollection = nullptr;

	mpChickWalkingTexture = nullptr;
}

Game::~Game()
{

}

void Game::init(int mFPS)
{
	

	mpTextureCollection = new Texture2D * [2];
	//mpTextureCollection[0] = mpWallTexture;
	//mpTextureCollection[1] = mpFaceTexture;


	mpGraphicsSystem = GraphicsSystem::getInstance();
	mpInputSystem = InputSystem::getInstance();

	assert(mpGraphicsSystem->init(600, 600));

	initShaderObjects();

	initShaderPrograms();

	//Texture for objects
	mpChickWalkingTexture = mpGraphicsSystem->createAndAddTexture2D("chickWalking", "Resource Files/Chicks/Animations/Chick Walking.png", true);

	mpChicken = new Chicken(5.0f, 5.0f);

	mpGraphicsSystem->createAndAddAnimationData("ChickenAnimData", &mpChickWalkingTexture, 4, 1, Vector2D(8, 8));
	mpGraphicsSystem->createAndAddAnimation("Chicken1", "ChickenAnimData", 8);

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
	//Delete Mesh2D objects
	delete mpTextureCollection;
	mpTextureCollection = nullptr;

	delete mpChicken;
	mpChicken = nullptr;

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

	mpChicken->update(mDeltaTime);

	int fps = debugGetFPS();
	if(fps != -1)
		mpGraphicsSystem->addToDebugHUD("FPS: " + to_string(debugGetFPS()));

	mpGraphicsSystem->addToDebugHUD("Mouse Position: " + mpInputSystem->getMousePosition().toString());

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", Vector2D(600.0f, 600.0f));
	mpGraphicsSystem->setVec2Uniform("Green", "uResolution", Vector2D(600.0f, 600.0f));
	mpGraphicsSystem->setVec2Uniform("Text", "uResolution", Vector2D(600.0f, 600.0f));
}

bool Game::render()
{
	mpGraphicsSystem->draw("Chicken1", Vector2D::One());

	mpGraphicsSystem->draw(mpChicken);

	mpGraphicsSystem->draw("Hello World!", "arial", "Text", Vector2D(50, 50));

	return mpGraphicsSystem->render();
}