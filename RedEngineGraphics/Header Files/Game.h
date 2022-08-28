#pragma once
#include "Trackable.h"

class GraphicsSystem;
class Shader;
class ShaderProgram;
class Mesh2D;

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

	Shader* mpBasicVertexShader;
	Shader* mpBasicFragmentShader;
	Shader* mpTestFragmentShader;
	Shader* mpTestVertexShader;

	ShaderProgram* mpBasicShaderProgram;
	ShaderProgram* mpTestShaderProgram;

	ShaderProgram* mpCurrentShaderProgram;

	bool mInputLastF1State;
	bool mInputLastF2State;
	bool mInputLastF4State;

	Mesh2D* mpTriangle;

};
