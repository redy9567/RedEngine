#pragma once
#include <string>
#include "Trackable.h"

struct GLFWwindow;

class Mesh2D;

enum SHADER_TYPE;

typedef unsigned int ShaderObjectIndex;
typedef unsigned int ShaderProgramIndex;

class ShaderProgram;

class GraphicsSystem : public Trackable
{

public:
	enum class Key
	{
		F1,
		F2,
		F4
	};

	enum class DrawMode
	{
		Fill,
		Wireframe
	};

	friend class Shader;
	friend class ShaderProgram;

	static GraphicsSystem* getInstance();
	static void cleanupInstance();

	bool init(int displayWidth, int displayHeight);
	void cleanup();

	void setActiveShaderProgram(ShaderProgram program);
	void draw(Mesh2D& mesh);
	void setDrawMode(DrawMode);

	void setFloatUniform(ShaderProgram program, std::string uniformName, float value);

	DrawMode getDrawMode() { return mDrawMode; }

	bool getKey(Key);

	bool render();

	float getTime();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
	GraphicsSystem();
	~GraphicsSystem();

	//SD functions intented for Shader Class use
	ShaderObjectIndex sdCreateShader(SHADER_TYPE type);
	bool sdCompileShader(ShaderObjectIndex soi, std::string code);
	std::string sdCollectDebugInfo(ShaderObjectIndex soi);
	void sdDeleteShader(ShaderObjectIndex soi);

	//SP functions intended for Shader Program Class use
	ShaderProgramIndex spCreateShaderProgram();
	void spAttachShaderToProgram(ShaderProgramIndex spi, ShaderObjectIndex soi);
	bool spLinkProgram(ShaderProgramIndex spi);
	std::string spCollectDebugInfo(ShaderProgramIndex spi);
	void spSetFloatAttribute(int index, int dimensions);


	GLFWwindow* mWindow;

	static GraphicsSystem* mspInstance;

	DrawMode mDrawMode;

	bool mInit;

};