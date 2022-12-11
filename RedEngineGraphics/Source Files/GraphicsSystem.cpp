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
	}
		
}

GraphicsSystem::GraphicsSystem()
{
	mInit = false;
	mWindow = nullptr;
	mDrawMode = DrawMode::Fill;
	mpShaderManager = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{
	if (mInit)
		cleanup();
}

bool GraphicsSystem::init(int displayWidth, int displayHeight)
{
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

	mpShaderManager = ShaderManager::getInstance();
	mpShaderManager->init();

	cout << "Well here we are!" << endl;

	mCurrentShaderProgram = "";

	mInit = true;
	return true;
}

void GraphicsSystem::cleanup()
{
	mpShaderManager->cleanup();
	ShaderManager::cleanupInstance();

	glfwTerminate();
	mInit = false;
}

bool GraphicsSystem::render()
{
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

void GraphicsSystem::draw(Sprite& sprite)
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
		packGPUData(*sprite.mpMesh);

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

	glDrawElements(GL_TRIANGLES, sprite.mpMesh->mDrawCount, GL_UNSIGNED_INT, 0);
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

bool GraphicsSystem::getKey(Key key)
{
	unsigned int glfwKey = 0;

	switch (key)
	{
	case Key::F1:
		glfwKey = GLFW_KEY_F1;
		break;

	case Key::F2:
		glfwKey = GLFW_KEY_F2;
		break;

	case Key::F4:
		glfwKey = GLFW_KEY_F4;
		break;

	default:
		return false;
	}

	return glfwGetKey(mWindow, glfwKey);
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

float GraphicsSystem::getTime()
{
	return glfwGetTime();
}

void GraphicsSystem::initTexture2D(Texture2D* texture)
{
	glGenTextures(1, &texture->mTOI);
	glBindTexture(GL_TEXTURE_2D, texture->mTOI);

	if(texture->mHasAlpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->mWidth, texture->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->mData);
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

void GraphicsSystem::packGPUData(Mesh2D& mesh)
{
	unsigned int valuesPerVertex = (mesh.mHasColorData) ? 6 : 3;
	valuesPerVertex += (mesh.mTextureDataCount) ? 2 : 0;
	unsigned int numOfFloats = valuesPerVertex * (double)mesh.mVertexCount;

	float* verticies = new float[numOfFloats];

	for (int i = 0; i < mesh.mVertexCount; i++)
	{
		verticies[i * valuesPerVertex] = mesh.getVertexAt(i).getX();
		verticies[i * valuesPerVertex + 1] = mesh.getVertexAt(i).getY();
		verticies[i * valuesPerVertex + 2] = 0.0f; //2D Objects are drawn at Z = 0

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
