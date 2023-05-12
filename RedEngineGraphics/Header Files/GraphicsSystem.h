#pragma once
#include <string>
#include "Trackable.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

struct GLFWwindow;

class Mesh2D;
class Sprite;
class Animation;
class AnimationData;
class Font;

enum SHADER_TYPE;
enum MeshType;

typedef unsigned int ShaderObjectIndex;
typedef unsigned int ShaderProgramIndex;

class ShaderProgram;
class Texture2D;
class ShaderManager;
class AnimationManager;
class FontManager;
class SpriteManager;
class GameObject2DManager;
class GameObject2D;
class Texture2DManager;
class Camera2D;


class DebugHUD;
class GridSystem;

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

	friend class DebugHUD; //So that the HUD can access private getter functions

	static GraphicsSystem* getInstance();
	static void cleanupInstance();

	bool init(int displayWidth, int displayHeight);
	void cleanup();

	void update(float deltaTime);

	void setActiveShaderProgram(std::string program);
	void draw(Mesh2D& mesh);
	void draw(Sprite& sprite, Vector2D location);
	void draw(std::string animationKey, Vector2D location);
	void draw(Animation& animation, Vector2D location);
	void draw(GameObject2D* gameObject);
	void draw(std::string gameObjctKey);
	void draw(std::string text, std::string fontKey, std::string shaderProgram, Vector2D loc, Vector3D color = Vector3D::One(), float scale = 1.0f);
	void drawUI(Sprite& sprite, Vector2D location);
	void drawUI(GameObject2D* gameObject);
	void drawUI(Animation& animation, Vector2D location);
	void setDrawMode(DrawMode);

	void setFloatUniform(std::string program, std::string uniformName, float value);
	void setIntegerUniform(std::string program, std::string uniformName, int value);
	void setVec2Uniform(std::string program, std::string uniformName, Vector2D value);
	void setVec3Uniform(std::string program, std::string uniformName, Vector3D value);
	void setVec4Uniform(std::string program, std::string uniformName, Vector4D value);
	void setMat3Uniform(std::string program, std::string uniformName, Sprite& sprite, Vector2D location); //This needs to be Deprecated
	void setMat3Uniform(std::string program, std::string uniformName, Matrix3D matrix);

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
	AnimationData* createAndAddAnimationData(std::string key, Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale = Vector2D::One());
	void removeAnimationData(std::string key);

	//Animation
	Animation* createAndAddAnimation(std::string key, std::string animationDataKey, int mFPS, bool isLooping = false);
	void removeAnimation(std::string key);
	Animation* getAnimation(std::string key);

	//Font
	void createAndAddFont(std::string key, std::string filepath, int pointSize = 12);
	void removeAndDeleteFont(std::string key);

	//Texture2Ds
	Texture2D* createAndAddTexture2D(std::string key, std::string filepath, bool hasAlpha = false);
	void removeAndDeleteTexture2D(std::string key);

	//Sprites
	Sprite* createAndAddSprite(std::string key, Texture2D** texture, Vector2D textureStartLoc, Vector2D size, Vector2D scale = Vector2D::One());
	void removeAndDeleteSprite(std::string key);
	Sprite* getSprite(std::string key);

	//GameObject2D
	GameObject2D* createAndAddGameObject2D(std::string key, Sprite*, Vector2D loc = Vector2D::Zero());
	GameObject2D* createAndAddGameObject2D(std::string key, Animation*, Vector2D loc = Vector2D::Zero());
	void removeAndDeleteGameObject2D(std::string key);

	Vector2D convertToGridCoordinates(Vector2D pixelCoordinates);

	Camera2D* getCamera() { return mpCamera; }

	//DebugHUD
	void addToDebugHUD(std::string text);
	void addPersistantToDebugHUD(std::string text);

	//IM functions intended for Input Manager Class use
	bool _imGetKey(unsigned int keyCode, GraphicsSystemIMKey key);
	bool _imGetMouseButton(unsigned int mouseCode, GraphicsSystemIMKey key);
	Vector2D _imGetMousePosition(GraphicsSystemIMKey key);

	DrawMode getDrawMode() { return mDrawMode; }

	int getDisplayWidth() { return mWindowResolution.getX(); }
	int getDisplayHeight() { return mWindowResolution.getY(); }
	Vector2D getDisplayResolution() { return mWindowResolution; }

	void setBackground(GameObject2D* bg) { mpBackground = bg; }

	bool render();

	void setDebugMode(bool val) { mDebugMode = val; }

	float getTime();
	std::string getCurrentShaderProgram() { return mCurrentShaderProgram; }

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//GLCleanupFunctions
	void cleanupMesh2D(Mesh2D*);
	void cleanupTexture2D(Texture2D*);

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
	void packGPUData(Mesh2D&, Vector2D size = Vector2D::One());
	void linkGPUData(Mesh2D&);
	void internalDrawSprite(Sprite& sprite);

	void drawDebugInfo();

	void drawGrid();

	unsigned int convertMeshType(MeshType meshType);

	GLFWwindow* mWindow;
	Vector2D mWindowResolution;

	static GraphicsSystem* mspInstance;

	ShaderManager* mpShaderManager;
	AnimationManager* mpAnimationManager;
	FontManager* mpFontManager;
	SpriteManager* mpSpriteManager;
	GameObject2DManager* mpGameObjectManager;
	Texture2DManager* mpTexture2DManager;

	GameObject2D* mpBackground;

	Camera2D* mpCamera;

	DebugHUD* mpDebugHUD;
	GridSystem* mpGridSystem;

	DrawMode mDrawMode;

	std::string mCurrentShaderProgram;

	bool mInit;
	bool mDebugMode;

};