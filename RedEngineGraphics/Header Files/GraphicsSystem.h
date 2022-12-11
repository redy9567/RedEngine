#pragma once
#include <string>
#include "Trackable.h"

struct GLFWwindow;

class Mesh2D;
class Sprite;

enum SHADER_TYPE;

typedef unsigned int ShaderObjectIndex;
typedef unsigned int ShaderProgramIndex;

class ShaderProgram;
class Texture2D;
class ShaderManager;

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
	void draw(Sprite& sprite);
	void setDrawMode(DrawMode);

	void setFloatUniform(std::string program, std::string uniformName, float value);
	void setIntegerUniform(std::string program, std::string uniformName, int value);

	//Shaders
	bool createAndAddShader(std::string key, SHADER_TYPE type, std::string filename);
	void removeShader(std::string key);
	bool reloadShader(std::string key);

	//ShaderPrograms
	void createAndAddShaderProgram(std::string key);
	bool createAndAddShaderProgram(std::string key, std::string vertexShader, std::string fragmentShader);
	void removeShaderProgram(std::string key);
	bool attachShaderToProgram(std::string programKey, std::string shaderKey);
	void activateFloatAttributeOnProgram(std::string key, int index, int dimensions);
	bool linkShaderProgram(std::string key);

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

	ShaderManager* mpShaderManager;

	DrawMode mDrawMode;

	std::string mCurrentShaderProgram;

	bool mInit;

};