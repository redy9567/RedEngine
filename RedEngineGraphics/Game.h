#pragma once

class GraphicsSystem;
class Shader;
class ShaderProgram;
class Mesh2D;

class Game
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
	void render();

	static Game* mspInstance;
	GraphicsSystem* mpGraphicsSystem;

	Shader* mpVertexShader;
	Shader* mpFragmentShader;

	ShaderProgram* mpShaderProgram;

	Mesh2D* mpTriangle;

};
