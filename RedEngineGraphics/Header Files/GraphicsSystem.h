#pragma once
#include <string>
#include "Trackable.h"

struct GLFWwindow;

class Mesh2D;

enum SHADER_TYPE;

typedef unsigned int ShaderObjectIndex;
typedef unsigned int ShaderProgramIndex;

class ShaderProgram;
class Texture2D;

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

	void setActiveShaderProgram(std::string program);
	void draw(Mesh2D& mesh);
	void setDrawMode(DrawMode);

	void setFloatUniform(std::string program, std::string uniformName, float value);
	void setIntegerUniform(std::string program, std::string uniformName, int value);

	DrawMode getDrawMode() { return mDrawMode; }

	bool getKey(Key);

	bool render();

	float getTime();
	std::string getCurrentShaderProgram() { return mCurrentShaderProgram; }

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
	void spActivateFloatAttribute(int index, int dimensions);

	//GLInitFunctions
	void initMesh2D(Mesh2D*);
	void initTexture2D(Texture2D*);

	//Helper Draw Functions
	void bindMesh2D(Mesh2D*);
	void bindTexture2D(Texture2D*, unsigned int textureLocation);
	void packGPUData(Mesh2D&);
	void linkGPUData(Mesh2D&);


	GLFWwindow* mWindow;

	static GraphicsSystem* mspInstance;

	DrawMode mDrawMode;

	std::string mCurrentShaderProgram;

	bool mInit;

};