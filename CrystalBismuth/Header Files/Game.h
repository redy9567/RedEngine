#pragma once
#include "Trackable.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;

class Game : public Trackable
{

public:
	static Game* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();
	void play();

private:
	Game();
	~Game();

	bool gameLoop();

	void input();
	void update();
	bool render();

	void initShaderObjects();
	void initShaderPrograms();

	static Game* mspInstance;
	GraphicsSystem* mpGraphicsSystem;

	bool mInputLastF1State;
	bool mInputLastF2State;
	bool mInputLastF4State;

	Texture2D* mpWallTexture;
	Texture2D* mpFaceTexture;
	Texture2D** mpTextureCollection;
	Sprite* mpTestSprite;

};
