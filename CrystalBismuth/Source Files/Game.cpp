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
	mpWallTexture = nullptr;
	mpFaceTexture = nullptr;
	mpTestSprite = nullptr;

	mInputLastF1State = false;
	mInputLastF2State = false;
	mInputLastF4State = false;

	mpTextureCollection = nullptr;

	mpChickWalking = nullptr;
	mpChickWalkingData = nullptr;
	mpChickWalkingTexture = nullptr;
}

Game::~Game()
{

}

void Game::init(int mFPS)
{
	//Texture for objects
	mpWallTexture = new Texture2D("Resource Files/wall.jpg");
	mpFaceTexture = new Texture2D("Resource Files/awesomeface.png", true);
	mpChickWalkingTexture = new Texture2D("Resource Files/Chick Walking.png", true);

	mpTextureCollection = new Texture2D * [2];
	mpTextureCollection[0] = mpWallTexture;
	mpTextureCollection[1] = mpFaceTexture;

	//Verticies for our triangles
	Vector2D verticies[] = {
		Vector2D(-0.5f, -0.5f),
		Vector2D(0.5f, -0.5f),
		Vector2D(0.5f, 0.5f),
		Vector2D(-0.5f, 0.5f)
	};

	//Colors for our verticies
	Vector3D vertexColors[] = {
		Vector3D(1.0f, 0.0f, 0.0f),
		Vector3D(0.0f, 1.0f, 0.0f),
		Vector3D(0.0f, 0.0f, 1.0f),
		Vector3D(1.0f, 1.0f, 1.0f)
	};

	Vector2D textureCoords[]
	{
		Vector2D(0.0f, 0.0f),
		Vector2D(1.0f, 0.0f),
		Vector2D(1.0f, 1.0f),
		Vector2D(0.0f, 1.0f),
	};

	//Vertex draw order
	unsigned int drawOrder[] = {
		0, 1, 2,
		2, 0, 3
	};

	// = new Mesh2D(verticies, 4, drawOrder, 6, vertexColors, mpTextureCollection, 2, textureCoords);
	mpTestSprite = new Sprite(&mpFaceTexture, Vector2D(0.0f, 100.0f), Vector2D(0.0f, 500.0f), Vector2D(mpFaceTexture->getWidth(), mpFaceTexture->getHeight() / 2));

	mpGraphicsSystem = GraphicsSystem::getInstance();

	assert(mpGraphicsSystem->init(600, 600));

	initShaderObjects();

	initShaderPrograms();

	mpChickWalkingData = new AnimationData(&mpChickWalkingTexture, 4, 1, Vector2D(8, 8));
	mpChickWalking = new Animation(mpChickWalkingData, 8);

	mTimePerFrame = 1.0f / mFPS;
	mDeltaTime = 0.0f;
	mpTimer = new Timer();
}

void Game::initShaderObjects()
{
	mpGraphicsSystem->createAndAddShader("Textured Vert", VERTEX_SHADER, "textured.vert");
	mpGraphicsSystem->createAndAddShader("Textured Frag", FRAGMENT_SHADER, "textured.frag");
	mpGraphicsSystem->createAndAddShader("Basic Vert", VERTEX_SHADER, "basic.vert");
	mpGraphicsSystem->createAndAddShader("Yellow Frag", FRAGMENT_SHADER, "yellow.frag");
}

void Game::initShaderPrograms()
{
	mpGraphicsSystem->createAndAddShaderProgram("Textured", "Textured Vert", "Textured Frag");
	mpGraphicsSystem->linkShaderProgram("Textured");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Textured", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Yellow", "Basic Vert", "Yellow Frag");
	mpGraphicsSystem->linkShaderProgram("Yellow");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Yellow", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	//Delete Mesh2D objects
	delete mpTestSprite;
	mpTestSprite = nullptr;

	delete mpTextureCollection;
	mpTextureCollection = nullptr;

	delete mpWallTexture;
	mpWallTexture = nullptr;

	delete mpFaceTexture;
	mpFaceTexture = nullptr;

	delete mpChickWalking;
	mpChickWalking = nullptr;

	delete mpChickWalkingData;
	mpChickWalkingData = nullptr;

	delete mpChickWalkingTexture;
	mpChickWalkingTexture = nullptr;

	delete mpTimer;
	mpTimer = nullptr;

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
	bool keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F1);
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

	keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F2);
	if (keyState && !mInputLastF2State)
	{
		if (mpGraphicsSystem->getCurrentShaderProgram() == "Textured")
			mpGraphicsSystem->setActiveShaderProgram("Yellow");
		else
			mpGraphicsSystem->setActiveShaderProgram("Textured");
	}
	mInputLastF2State = keyState;
	
	keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F4);
	if (keyState && !mInputLastF4State)
	{
		mpGraphicsSystem->reloadShader("Textured Vert");
		mpGraphicsSystem->reloadShader("Textured Frag");
		mpGraphicsSystem->reloadShader("Basic Vert");
		mpGraphicsSystem->reloadShader("Yellow Frag");

		mpGraphicsSystem->linkShaderProgram("Textured");
		mpGraphicsSystem->linkShaderProgram("Yellow");
	}
	mInputLastF4State = keyState;
}

void Game::update()
{
	mpChickWalking->update(mDeltaTime);

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", Vector2D(600.0f, 600.0f));
	mpGraphicsSystem->setVec2Uniform("Yellow", "uResolution", Vector2D(600.0f, 600.0f));
}

bool Game::render()
{
	//mpGraphicsSystem->draw(*mpTestSprite);
	mpGraphicsSystem->draw(*mpChickWalking);

	return mpGraphicsSystem->render();
}