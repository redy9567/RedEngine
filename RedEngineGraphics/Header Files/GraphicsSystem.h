#pragma once
#include <string>
#include "Trackable.h"
#include "Vector2D.h"
#include "Vector3D.h"

struct GLFWwindow;

class Mesh2D;
class Sprite;
class Animation;
class Font;

enum SHADER_TYPE;

typedef unsigned int ShaderObjectIndex;
typedef unsigned int ShaderProgramIndex;

class ShaderProgram;
class Texture2D;
class ShaderManager;
class AnimationManager;
class FontManager;

class GraphicsSystem : public Trackable
{

public:
	class GraphicsSystemIMKey
	{
	public:
		friend class InputSystem;

	private:
		GraphicsSystemIMKey() {};
	};

	enum class DrawMode
	{
		Fill,
		Wireframe
	};

	friend class Shader; // Change to the Graphics Key System
	friend class ShaderProgram;

	static GraphicsSystem* getInstance();
	static void cleanupInstance();

	bool init(int displayWidth, int displayHeight);
	void cleanup();

	void update(float deltaTime);

	void setActiveShaderProgram(std::string program);
	void draw(Mesh2D& mesh);
	void draw(Sprite& sprite);
	void draw(std::string animationKey);
	void draw(std::string text, std::string fontKey, std::string shaderProgram, Vector2D loc, Vector3D color = Vector3D::One(), float scale = 1.0f);
	void setDrawMode(DrawMode);

	void setFloatUniform(std::string program, std::string uniformName, float value);
	void setIntegerUniform(std::string program, std::string uniformName, int value);
	void setVec2Uniform(std::string program, std::string uniformName, Vector2D value);
	void setVec3Uniform(std::string program, std::string uniformName, Vector3D value);
	void setMat3Uniform(std::string program, std::string uniformName, Sprite& sprite); //Make this not use sprite in the future? Need Mat implementations

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

	//AnimationData
	void createAndAddAnimationData(std::string key, Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale = Vector2D::One());
	void removeAnimationData(std::string key);

	//Animation
	bool createAndAddAnimation(std::string key, std::string animationDataKey, int mFPS);
	void removeAnimation(std::string key);

	//Font
	void createAndAddFont(std::string key, std::string filepath, int pointSize = 12);
	void removeAndDeleteFont(std::string key);

	//IM functions intended for Input Manager Class use
	bool _imGetKey(unsigned int keyCode, GraphicsSystemIMKey key);

	DrawMode getDrawMode() { return mDrawMode; }

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
	void initFont(Font*);

	//Helper Draw Functions
	void bindMesh2D(Mesh2D*);
	void bindTexture2D(Texture2D*, unsigned int textureLocation);
	void packGPUData(Mesh2D&, Vector2D scale = Vector2D::One());
	void linkGPUData(Mesh2D&);

	int getDisplayWidth() { return mDisplayWidth; }
	int getDisplayHeight() { return mDisplayHeight; }


	GLFWwindow* mWindow;

	static GraphicsSystem* mspInstance;

	ShaderManager* mpShaderManager;
	AnimationManager* mpAnimationManager;
	FontManager* mpFontManager;

	DrawMode mDrawMode;

	std::string mCurrentShaderProgram;

	bool mInit;

	int mDisplayWidth;
	int mDisplayHeight;

};