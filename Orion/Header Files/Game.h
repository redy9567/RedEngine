#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "MouseEvent.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;
class AnimationData;
class Animation;
class Timer;
class InputSystem;
class UIManager;
class Mesh2D;
class GameObject2D;
class UIElement;

const int GAME_DISPLAY_WIDTH = 1536;
const int GAME_DISPLAY_HEIGHT = 864;

class Game : public Trackable
{

public:
	friend class GameListener;

	static Game* getInstance();
	static void cleanupInstance();

	void init(int mFPS);
	void cleanup();
	void play();

	int debugGetFPS() { return mDebugMode ? 1 / mDeltaTime : -1; }

private:
	Game();
	~Game();

	void loadData();

	bool gameLoop();

	void input();
	void update();
	bool render();

	void initShaderObjects();
	void initShaderPrograms();

	void onToggleDrawMode();
	void onToggleShaders();
	void onShaderHotReload();
	void onToggleDebugMode();

	static Game* mspInstance;

	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;
	UIManager* mpUIManager;

	Mesh2D* mpChickenSelectionMesh;

	GameObject2D* mpBackground;

	UIElement* mpBuildingHighlight;

	//Timing Stuff
	float mTimePerFrame;
	Timer* mpTimer;
	float mDeltaTime;

	//Are we in Debug Mode?
	bool mDebugMode;

	//Keyboard stuff
	bool mInputLastF1State;
	bool mInputLastF2State;
	bool mInputLastF4State;
	bool mInputLastF5State;

};
