#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "MouseEvent.h"
#include "GameListener.h"

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

	void startScene1();
	void startScene2();
	void startScene3();

private:
	Game();
	~Game();

	void loadData();

	bool gameLoop();

	void input();
	void update();
	bool render();

	void cleanupCurrentScene();

	void initScene1();
	void updateScene1();
	void cleanupScene1();

	void initScene2();
	void updateScene2();
	void cleanupScene2();

	void initScene3();
	void updateScene3();
	void cleanupScene3();

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
	float mRunningTime;

	//Are we in Debug Mode?
	bool mDebugMode;

	//Keyboard stuff
	bool mInputLastF1State;
	bool mInputLastF2State;
	bool mInputLastF4State;
	bool mInputLastF5State;

	GameObject2D* mCircleObj;
	GameObject2D* mRodObj;

	GameObject2D* mCircle2Obj;
	GameObject2D* mRod2Obj;

	GameObject2D* mOriginObj;

	int mCurrentScene;

	float mPendulumAngle;
	float mPendulumAngleVelocity;

	float mPendulumAngleAcceleration;
	float mPendulum2Angle;
	float mPendulum2AngleVelocity;
	float mPendulum2AngleAcceleration;

	GameListener mListener;

};
