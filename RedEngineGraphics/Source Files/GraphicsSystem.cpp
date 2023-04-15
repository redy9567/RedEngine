//stb_image setup
#define STB_IMAGE_IMPLEMENTATION
#include "stb\stb_image.h"

#include "GraphicsSystem.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include "Mesh2D.h"
#include "Texture2D.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "Font.h"
#include "FontManager.h"
#include "DebugHUD.h"
#include "SpriteManager.h"
#include "GameObject2DManager.h"
#include "GameObject2D.h"
#include "AnimationData.h"
#include "Texture2DManager.h"

using namespace std;

GraphicsSystem* GraphicsSystem::mspInstance = nullptr;

GraphicsSystem* GraphicsSystem::getInstance()
{
	if (!mspInstance)
		mspInstance = new GraphicsSystem();

	return mspInstance;
}

void GraphicsSystem::cleanupInstance()
{
	if (mspInstance)
	{
		if (mspInstance->mInit)
			mspInstance->cleanup();

		delete mspInstance;
		mspInstance = nullptr;
	}
		
}

GraphicsSystem::GraphicsSystem()
{
	mInit = false;
	mDebugMode = false;
	mWindow = nullptr;
	mDrawMode = DrawMode::Fill;
	mpShaderManager = nullptr;
	mpAnimationManager = nullptr;
	mpSpriteManager = nullptr;
	mpDebugHUD = nullptr;
	mpFontManager = nullptr;
	mpGameObjectManager = nullptr;
	mpTexture2DManager = nullptr;
	mDisplayHeight = 0;
	mDisplayWidth = 0;
}

GraphicsSystem::~GraphicsSystem()
{
	if (mInit)
		cleanup();
}

bool GraphicsSystem::init(int displayWidth, int displayHeight)
{
	mDisplayHeight = displayHeight;
	mDisplayWidth = displayHeight;

	//Initialize OpenGL, and set our context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create Window, and verify
	mWindow = glfwCreateWindow(displayWidth, displayHeight, "LearnOpenGL", NULL, NULL);
	if (!mWindow)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(mWindow);

	mWindowResolution = Vector2D(displayWidth, displayHeight);

	//Load glad, and verify
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return false;
	}

	//Tell OpenGL our rendering frame/viewport
	glViewport(0, 0, displayWidth, displayHeight);

	//Determine default background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Set our callback function for resizing the window
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mpShaderManager = ShaderManager::getInstance();
	mpShaderManager->init();

	mpTexture2DManager = Texture2DManager::getInstance();
	mpTexture2DManager->init();

	mpSpriteManager = SpriteManager::getInstance();
	mpSpriteManager->init();

	mpAnimationManager = AnimationManager::getInstance();
	mpAnimationManager->init();

	mpFontManager = FontManager::getInstance();
	mpFontManager->init();

	mpGameObjectManager = GameObject2DManager::getInstance();
	mpGameObjectManager->init();

	mpDebugHUD = DebugHUD::getInstance();
	mpDebugHUD->addDebugValue("Current Shader Program: ", &GraphicsSystem::getCurrentShaderProgram);

	cout << "Well here we are!" << endl;

	mCurrentShaderProgram = "";

	mInit = true;
	return true;
}

void GraphicsSystem::cleanup()
{
	mpGameObjectManager->cleanup();
	GameObject2DManager::cleanupInstance();

	mpShaderManager->cleanup();
	ShaderManager::cleanupInstance();

	mpAnimationManager->cleanup();
	AnimationManager::cleanupInstance();

	mpSpriteManager->cleanup();
	SpriteManager::cleanupInstance();

	mpTexture2DManager->cleanup();
	Texture2DManager::cleanupInstance();

	mpFontManager->cleanup();
	FontManager::cleanupInstance();

	DebugHUD::cleanupInstnace();

	glfwTerminate();
	mInit = false;
}

bool GraphicsSystem::render()
{
	if(mDebugMode)
		drawDebugInfo();

	if (glfwWindowShouldClose(mWindow))
		return false;

	glfwSwapBuffers(mWindow);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

void GraphicsSystem::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsSystem::draw(Mesh2D& mesh)
{
	assert(mCurrentShaderProgram != "");
	setActiveShaderProgram(mCurrentShaderProgram);

	if (mesh.mVBO == -1)
	{
		initMesh2D(&mesh);

		bindMesh2D(&mesh);

		
		for (int i = 0; i < mesh.mTextureDataCount; i++)
		{
			if (mesh.mTextureData[i]->mTOI == -1)
				initTexture2D(mesh.mTextureData[i]);
			bindTexture2D(mesh.mTextureData[i], i);
		}


		//Packing and linking only need to occur on mesh init, as the data is stored in the VAO
		packGPUData(mesh);

		//Copy draw order data into bound buffer (EBO)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.mDrawCount, mesh.mDrawOrder, GL_STATIC_DRAW);

		linkGPUData(mesh);
		
	}
	else
	{
		for (int i = 0; i < mesh.mTextureDataCount; i++)
		{
			bindTexture2D(mesh.mTextureData[i], i);
		}

		bindMesh2D(&mesh);
	}

	glDrawElements(GL_TRIANGLES, mesh.mDrawCount, GL_UNSIGNED_INT, 0);
}

void GraphicsSystem::draw(Sprite& sprite, Vector2D location)
{
	setActiveShaderProgram(mCurrentShaderProgram);

	if (sprite.mpMesh->mVBO == -1)
	{
		initMesh2D(sprite.mpMesh);

		bindMesh2D(sprite.mpMesh);


		for (int i = 0; i < sprite.mpMesh->mTextureDataCount; i++)
		{
			if (sprite.mpMesh->mTextureData[i]->mTOI == -1)
				initTexture2D(sprite.mpMesh->mTextureData[i]);
			bindTexture2D(sprite.mpMesh->mTextureData[i], i);
		}


		//Packing and linking only need to occur on mesh init, as the data is stored in the VAO
		packGPUData(*sprite.mpMesh, sprite.mSize);

		//Copy draw order data into bound buffer (EBO)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * sprite.mpMesh->mDrawCount, sprite.mpMesh->mDrawOrder, GL_STATIC_DRAW);

		linkGPUData(*sprite.mpMesh);

	}
	else
	{
		for (int i = 0; i < sprite.mpMesh->mTextureDataCount; i++)
		{
			bindTexture2D(sprite.mpMesh->mTextureData[i], i);
		}

		bindMesh2D(sprite.mpMesh);
	}

	setMat3Uniform("Textured", "uModelMat", sprite, location); //These game objects shouldn't need these uModelMats sent here. Need some gs funciton to be called by game.
	setMat3Uniform("Green", "uModelMat", sprite, location);

	setActiveShaderProgram(mCurrentShaderProgram);

	glDrawElements(GL_TRIANGLES, sprite.mpMesh->mDrawCount, GL_UNSIGNED_INT, 0);
}

void GraphicsSystem::draw(string animationKey, Vector2D location)
{
	Animation* anim = mpAnimationManager->getAnimation(animationKey);

	Sprite* currentSprite = anim->getCurrentSprite();
	if (currentSprite == nullptr)
		return;

	draw(*currentSprite, location);
}

void GraphicsSystem::draw(Animation& animation, Vector2D location)
{
	Sprite* currentSprite = animation.getCurrentSprite();
	if (currentSprite == nullptr)
		return;

	draw(*currentSprite, location);
}

void GraphicsSystem::draw(GameObject2D* obj)
{
	switch (obj->mDrawingMode)
	{
	case GameObject2D::SpriteMode:
		draw(*obj->mImage.s, obj->mLoc);
		break;
	case GameObject2D::AnimationMode:
		draw(*obj->mImage.a, obj->mLoc);
		break;
	}
}

void GraphicsSystem::draw(std::string gameObjectKey)
{
	GameObject2D* obj = mpGameObjectManager->getGameObject2D(gameObjectKey);

	draw(obj);
}

void GraphicsSystem::draw(string text, string fontKey, string shaderProgram, Vector2D loc, Vector3D color, float scale)
{
	//No need to set active shader program, as setting a uniform sets the shader program as active
	setVec3Uniform(shaderProgram, "textColor", color);

	Font* font = mpFontManager->getFont(fontKey);

	//Init
	if (font->mCharacters.empty())
	{
		initFont(font);
	}

	if (mpFontManager->mVBO == -1)
	{
		glGenVertexArrays(1, &mpFontManager->mVAO);
		glGenBuffers(1, &mpFontManager->mVBO);
		glBindVertexArray(mpFontManager->mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mpFontManager->mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	}
	//Bind
	else
	{
		glBindVertexArray(mpFontManager->mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mpFontManager->mVBO);
	}

	//Pack Data & Draw

	for (string::const_iterator c = text.begin(); c != text.end(); c++)
	{
		Font::Character ch = font->mCharacters.at(*c);

		float x = loc.getX() + ch.bearing.getX() * scale;
		float y = loc.getY() - (ch.size.getY() - ch.bearing.getY()) * scale;

		float w = ch.size.getX() * scale;
		float h = ch.size.getY() * scale;

		float verticies[6][4] = { //Should this be changed? I think the x, y position might be flipped from game on y.
			{x,		y + h,	0.0f, 0.0f },
			{x,		y,		0.0f, 1.0f },
			{x + w,	y,		1.0f, 1.0f },

			{x,		y + h,	0.0f, 0.0f },
			{x + w,	y,		1.0f, 1.0f },
			{x + w, y + h,	1.0f, 0.0f }
		};

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticies), verticies);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		loc.setX(loc.getX() + (ch.advance >> 6) * scale);
	}

	setActiveShaderProgram(mCurrentShaderProgram);
}

void GraphicsSystem::drawDebugInfo()
{
	mpDebugHUD->draw();
}

ShaderObjectIndex GraphicsSystem::sdCreateShader(SHADER_TYPE type)
{
	switch (type)
	{
	case VERTEX_SHADER:
		return glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT_SHADER:
		return glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	return -1;
}

bool GraphicsSystem::sdCompileShader(ShaderObjectIndex soi, string code)
{
	const char* charCode = code.c_str();
	//Attach the Vertex Shader Code and Compile
	glShaderSource(soi, 1, &charCode, NULL);
	glCompileShader(soi);

	int success;
	glGetShaderiv(soi, GL_COMPILE_STATUS, &success);

	return success;
}

string GraphicsSystem::sdCollectDebugInfo(ShaderObjectIndex soi)
{
	char infoLog[512];

	glGetShaderInfoLog(soi, 512, NULL, infoLog);

	return infoLog;
}

ShaderProgramIndex GraphicsSystem::spCreateShaderProgram()
{
	return glCreateProgram();
}

void GraphicsSystem::spAttachShaderToProgram(ShaderProgramIndex spi, ShaderObjectIndex soi)
{
	glAttachShader(spi, soi);
}

bool GraphicsSystem::spLinkProgram(ShaderProgramIndex spi)
{
	glLinkProgram(spi);

	int success;
	glGetProgramiv(spi, GL_LINK_STATUS, &success);

	return success;
}

string GraphicsSystem::spCollectDebugInfo(ShaderProgramIndex spi)
{
	char infoLog[512];

	glGetProgramInfoLog(spi, 512, NULL, infoLog);

	return infoLog;
}

void GraphicsSystem::sdDeleteShader(ShaderObjectIndex shader)
{
	glDeleteShader(shader);
}

void GraphicsSystem::spActivateFloatAttribute(int index, int dimensions)
{
	glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
}

void GraphicsSystem::setActiveShaderProgram(string program)
{
	ShaderProgram* sp = ShaderManager::getInstance()->getShaderProgram(program);

	glUseProgram(sp->mSPI);

	mCurrentShaderProgram = program;
}

void GraphicsSystem::setDrawMode(DrawMode mode)
{
	switch (mode)
	{
	case DrawMode::Fill:
		mDrawMode = DrawMode::Fill;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case DrawMode::Wireframe:
		mDrawMode = DrawMode::Wireframe;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
}

void GraphicsSystem::setFloatUniform(string program, string uniformName, float value)
{
	ShaderProgram* sp = ShaderManager::getInstance()->getShaderProgram(program);

	int uniformLocation = glGetUniformLocation(sp->mSPI, uniformName.c_str());

	if (uniformLocation == -1)
		return;

	glUseProgram(sp->mSPI);
	glUniform1f(uniformLocation, value);
}

void GraphicsSystem::setIntegerUniform(string program, string uniformName, int value)
{
	ShaderProgram* sp = ShaderManager::getInstance()->getShaderProgram(program);

	int uniformLocation = glGetUniformLocation(sp->mSPI, uniformName.c_str());

	if (uniformLocation == -1)
		return;

	glUseProgram(sp->mSPI);
	glUniform1i(uniformLocation, value);
}

void GraphicsSystem::setVec2Uniform(std::string program, std::string uniformName, Vector2D value)
{
	ShaderProgram* sp = ShaderManager::getInstance()->getShaderProgram(program);

	int uniformLocation = glGetUniformLocation(sp->mSPI, uniformName.c_str());

	if (uniformLocation == -1)
		return;

	glUseProgram(sp->mSPI);
	glUniform2f(uniformLocation, value.getX(), value.getY());
}

void GraphicsSystem::setVec3Uniform(std::string program, std::string uniformName, Vector3D value)
{
	ShaderProgram* sp = ShaderManager::getInstance()->getShaderProgram(program);

	int uniformLocation = glGetUniformLocation(sp->mSPI, uniformName.c_str());

	if (uniformLocation == -1)
		return;

	glUseProgram(sp->mSPI);
	glUniform3f(uniformLocation, value.getX(), value.getY(), value.getZ());
}

void GraphicsSystem::setMat3Uniform(std::string program, std::string uniformName, Sprite& sprite, Vector2D location)
{
	ShaderProgram* sp = ShaderManager::getInstance()->getShaderProgram(program);

	int uniformLocation = glGetUniformLocation(sp->mSPI, uniformName.c_str());

	if (uniformLocation == -1)
		return;

	glUseProgram(sp->mSPI);
	float mat[] = {
		sprite.mScale.getX(), 0.0f, location.getX(),
		0.0f, sprite.mScale.getY(), location.getY(),
		0.0f, 0.0f, 1.0f
	};
	glUniformMatrix3fv(uniformLocation, 1, false, mat);
}

float GraphicsSystem::getTime()
{
	return glfwGetTime();
}

void GraphicsSystem::initTexture2D(Texture2D* texture)
{
	glGenTextures(1, &texture->mTOI);
	glBindTexture(GL_TEXTURE_2D, texture->mTOI);

	if(texture->mHasAlpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->mWidth, texture->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->mData);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->mWidth, texture->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->mData);

	glGenerateMipmap(GL_TEXTURE_2D);

	texture->freeRawData();
}

void GraphicsSystem::initMesh2D(Mesh2D* mesh)
{
	//Setup Vertex Buffer Object (VBO)
	glGenBuffers(1, &mesh->mVBO);

	//Setup Vertex Array Object (VAO)
	glGenVertexArrays(1, &mesh->mVAO);
	
	//Setup Element Buffer Object
	glGenBuffers(1, &mesh->mEBO);
}

void GraphicsSystem::initFont(Font* font)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 32; c <= 126; c++)
	{
		if (FT_Load_Char(font->mFontFace, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph: " << c << std::endl;
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			font->mFontFace->glyph->bitmap.width,
			font->mFontFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			font->mFontFace->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Font::Character character
		{
			texture,
			Vector2D(font->mFontFace->glyph->bitmap.width, font->mFontFace->glyph->bitmap.rows),
			Vector2D(font->mFontFace->glyph->bitmap_left, font->mFontFace->glyph->bitmap_top),
			font->mFontFace->glyph->advance.x
		};

		font->mCharacters.emplace(c, character);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	FT_Done_Face(font->mFontFace);
}

void GraphicsSystem::bindMesh2D(Mesh2D* mesh)
{
	//Bind VAO to OpenGL
	glBindVertexArray(mesh->mVAO);

	//Bind VBO to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, mesh->mVBO);

	//Bind EBO to VAO (Don't unbind EBO before VAO [VAO remembers all])
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mEBO);
}

void GraphicsSystem::bindTexture2D(Texture2D* texture, unsigned int textureLocation)
{
	glActiveTexture(GL_TEXTURE0 + textureLocation);
	glBindTexture(GL_TEXTURE_2D, texture->mTOI);
}

void GraphicsSystem::packGPUData(Mesh2D& mesh, Vector2D scale)
{
	unsigned int valuesPerVertex = (mesh.mHasColorData) ? 6 : 3;
	valuesPerVertex += (mesh.mTextureDataCount) ? 2 : 0;
	unsigned int numOfFloats = valuesPerVertex * (double)mesh.mVertexCount;

	float* verticies = new float[numOfFloats];

	float largerSide = scale.getX() > scale.getY() ? scale.getX() : scale.getY();

	for (int i = 0; i < mesh.mVertexCount; i++)
	{
		verticies[i * valuesPerVertex] = mesh.getVertexAt(i).getX() * largerSide;
		verticies[i * valuesPerVertex + 1] = mesh.getVertexAt(i).getY() * largerSide;
		verticies[i * valuesPerVertex + 2] = 1.0f; //2D Objects are drawn at Z = 1

		if (mesh.mHasColorData)
		{
			verticies[i * valuesPerVertex + 3] = mesh.mColorData[i].getX();
			verticies[i * valuesPerVertex + 4] = mesh.mColorData[i].getY();
			verticies[i * valuesPerVertex + 5] = mesh.mColorData[i].getZ();

			if (mesh.mTextureDataCount)
			{
				verticies[i * valuesPerVertex + 6] = mesh.mTextureCoords[i].getX();
				verticies[i * valuesPerVertex + 7] = mesh.mTextureCoords[i].getY();
			}
		}
	}

	//Copy data into bound buffer (VBO)
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfFloats, verticies, GL_STATIC_DRAW);

	delete[] verticies;
	verticies = nullptr;
}

void GraphicsSystem::linkGPUData(Mesh2D& mesh)
{
	//Linking Vertex Attributes
	if (mesh.mTextureDataCount)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	else if (mesh.mHasColorData)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	else
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
}

bool GraphicsSystem::createAndAddShader(string key, SHADER_TYPE type, string filename)
{
	return mpShaderManager->createAndAddShader(key, type, filename);
}

void GraphicsSystem::removeShader(string key)
{
	mpShaderManager->removeShader(key);
}

bool GraphicsSystem::reloadShader(string key)
{
	return mpShaderManager->reloadShader(key);
}

void GraphicsSystem::createAndAddShaderProgram(string key)
{
	mpShaderManager->createAndAddShaderProgram(key);
}

bool GraphicsSystem::createAndAddShaderProgram(string key, string vertexShader, string fragmentShader)
{
	return mpShaderManager->createAndAddShaderProgram(key, vertexShader, fragmentShader);
}

void GraphicsSystem::removeShaderProgram(string key)
{
	mpShaderManager->removeShaderProgram(key);
}

bool GraphicsSystem::attachShaderToProgram(string programKey, string shaderKey)
{
	return mpShaderManager->attachShaderToProgram(programKey, shaderKey);
}

void GraphicsSystem::activateFloatAttributeOnProgram(string key, int index, int dimensions)
{
	mpShaderManager->activateFloatAttributeOnProgram(key, index, dimensions);
}

bool GraphicsSystem::linkShaderProgram(string key)
{
	return mpShaderManager->linkShaderProgram(key);
}

AnimationData* GraphicsSystem::createAndAddAnimationData(string key, Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale)
{
	return mpAnimationManager->createAndAddAnimationData(key, texture, numHorizontal, numVertical, scale);
}

void GraphicsSystem::removeAnimationData(string key)
{
	mpAnimationManager->removeAnimationData(key);
}

Animation* GraphicsSystem::createAndAddAnimation(string key, string animationDataKey, int mFPS, bool isLooping)
{
	return mpAnimationManager->createAndAddAnimation(key, animationDataKey, mFPS, isLooping);
}

void GraphicsSystem::removeAnimation(string key)
{
	mpAnimationManager->removeAnimation(key);
}

Animation* GraphicsSystem::getAnimation(string key)
{
	return mpAnimationManager->getAnimation(key);
}

void GraphicsSystem::update(float deltaTime)
{
	
}

bool GraphicsSystem::_imGetKey(unsigned int keyCode, GraphicsSystemIMKey key)
{
	return glfwGetKey(mWindow, keyCode);
}

bool GraphicsSystem::_imGetMouseButton(unsigned int mouseCode, GraphicsSystemIMKey key)
{
	return glfwGetMouseButton(mWindow, mouseCode) == GLFW_PRESS;
}

Vector2D GraphicsSystem::_imGetMousePosition(GraphicsSystemIMKey key)
{
	double x, y;
	glfwGetCursorPos(mWindow, &x, &y);
	return Vector2D(x, mWindowResolution.getY() - y);
}

void GraphicsSystem::createAndAddFont(string key, string filepath, int pointSize)
{
	mpFontManager->createAndAddFont(key, filepath, pointSize);
}

void GraphicsSystem::removeAndDeleteFont(string key)
{
	mpFontManager->removeAndDeleteFont(key);
}

Texture2D* GraphicsSystem::createAndAddTexture2D(std::string key, std::string filepath, bool hasAlpha)
{
	return mpTexture2DManager->createAndAddTexture2D(key, filepath, hasAlpha);
}

void GraphicsSystem::removeAndDeleteTexture2D(std::string key)
{
	mpTexture2DManager->removeAndDeleteTexture2D(key);
}

void GraphicsSystem::addToDebugHUD(std::string text) 
{
	mpDebugHUD->addDebugValue(text); 
}

void GraphicsSystem::addPersistantToDebugHUD(std::string text)
{
	mpDebugHUD->addPersistantDebugValue(text);
}

Sprite* GraphicsSystem::createAndAddSprite(string key, Texture2D** texture, Vector2D textureStartLoc, Vector2D size, Vector2D scale)
{
	return mpSpriteManager->createAndAddSprite(key, texture, textureStartLoc, size, scale);
}

void GraphicsSystem::removeAndDeleteSprite(string key)
{
	mpSpriteManager->removeAndDeleteSprite(key);
}

Sprite* GraphicsSystem::getSprite(string key)
{
	return mpSpriteManager->getSprite(key);
}

GameObject2D* GraphicsSystem::createAndAddGameObject2D(string key, Sprite* sprite, Vector2D loc)
{
	return mpGameObjectManager->createAndAddGameObject2D(key, sprite, loc);
}

GameObject2D* GraphicsSystem::createAndAddGameObject2D(string key, Animation* anim, Vector2D loc)
{
	return mpGameObjectManager->createAndAddGameObject2D(key, anim, loc);
}

void GraphicsSystem::removeAndDeleteGameObject2D(string key)
{
	mpGameObjectManager->removeAndDeleteGameObject2D(key);
}