#pragma once
#include "Trackable.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;
class AnimationData;
class Animation;
class Timer;
class InputSystem;

class Game : public Trackable
{

public:
	static Game* getInstance();
	static void cleanupInstance();

	void init(int mFPS);
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
	InputSystem* mpInputSystem;

	float mTimePerFrame;
	Timer* mpTimer;
	float mDeltaTime;

	bool mInputLastF1State;
	bool mInputLastF2State;
	bool mInputLastF4State;

	Texture2D* mpWallTexture;
	Texture2D* mpFaceTexture;
	Texture2D* mpChickWalkingTexture;
	Texture2D** mpTextureCollection;
	Sprite* mpTestSprite;

};
