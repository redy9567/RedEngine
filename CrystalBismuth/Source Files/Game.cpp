#include "Game.h"
#include "Mesh2D.h"
#include "GraphicsSystem.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture2D.h"
#include "ShaderManager.h"

#include <assert.h>

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
	mpTriangles = nullptr;

	mInputLastF1State = false;
	mInputLastF2State = false;
	mInputLastF4State = false;

	mpTextureCollection = nullptr;
}

Game::~Game()
{

}

void Game::init()
{
	//Texture for objects
	mpWallTexture = new Texture2D("Resource Files/wall.jpg");
	mpFaceTexture = new Texture2D("Resource Files/awesomeface.png", true);

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

	mpTriangles = new Mesh2D(verticies, 4, drawOrder, 6, vertexColors, mpTextureCollection, 2, textureCoords);

	mpGraphicsSystem = GraphicsSystem::getInstance();

	assert(mpGraphicsSystem->init(800, 600));

	initShaderObjects();

	initShaderPrograms();
}

void Game::initShaderObjects()
{
	mpGraphicsSystem->createAndAddShader("Basic Vert", VERTEX_SHADER, "basic.vert");
	mpGraphicsSystem->createAndAddShader("Basic Frag", FRAGMENT_SHADER, "basic.frag");
	mpGraphicsSystem->createAndAddShader("Test Vert", VERTEX_SHADER, "test.vert");
	mpGraphicsSystem->createAndAddShader("Test Frag", FRAGMENT_SHADER, "test.frag");
}

void Game::initShaderPrograms()
{
	mpGraphicsSystem->createAndAddShaderProgram("Basic", "Basic Vert", "Basic Frag");
	mpGraphicsSystem->linkShaderProgram("Basic");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Basic", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Test", "Test Vert", "Test Frag");
	mpGraphicsSystem->linkShaderProgram("Test");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Test", 0, 3); //Sets Attribute 0 to a 3 dimentional float value
}

void Game::cleanup()
{
	//Delete Mesh2D objects
	delete mpTriangles;
	mpTriangles = nullptr;

	delete mpTextureCollection;
	mpTextureCollection = nullptr;

	delete mpWallTexture;
	mpWallTexture = nullptr;

	delete mpFaceTexture;
	mpFaceTexture = nullptr;

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
	return render();
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
		if (mpGraphicsSystem->getCurrentShaderProgram() == "Basic")
			mpGraphicsSystem->setActiveShaderProgram("Test");
		else
			mpGraphicsSystem->setActiveShaderProgram("Basic");
	}
	mInputLastF2State = keyState;
	
	keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F4);
	if (keyState && !mInputLastF4State)
	{
		mpGraphicsSystem->reloadShader("Basic Vert");
		mpGraphicsSystem->reloadShader("Basic Frag");
		mpGraphicsSystem->reloadShader("Test Vert");
		mpGraphicsSystem->reloadShader("Test Frag");

		mpGraphicsSystem->linkShaderProgram("Basic");
		mpGraphicsSystem->linkShaderProgram("Test");
	}
	mInputLastF4State = keyState;
}

void Game::update()
{
	mpGraphicsSystem->setFloatUniform("Test", "uTime", mpGraphicsSystem->getTime());
	mpGraphicsSystem->setIntegerUniform("Test", "uTexture0", 0);
	mpGraphicsSystem->setIntegerUniform("Test", "uTexture1", 1);
}

bool Game::render()
{
	mpGraphicsSystem->draw(*mpTriangles);

	return mpGraphicsSystem->render();
}