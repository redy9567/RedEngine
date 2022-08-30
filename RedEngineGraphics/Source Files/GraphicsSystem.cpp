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

	cout << "Well here we are!" << endl;

	mInit = true;
	return true;
}

void GraphicsSystem::cleanup()
{
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
	if (mesh.mVBO == -1)
	{
		//Setup Vertex Buffer Object (VBO)
		glGenBuffers(1, &mesh.mVBO);

		//Setup Vertex Array Object (VAO)
		glGenVertexArrays(1, &mesh.mVAO);

		//Bind VAO to OpenGL
		glBindVertexArray(mesh.mVAO);

		//Bind VBO to OpenGL
		glBindBuffer(GL_ARRAY_BUFFER, mesh.mVBO);

		if (mesh.mHasTextureData && mesh.mTextureData->mTOI == -1)
		{
			glGenTextures(1, &mesh.mTextureData->mTOI);
			glBindTexture(GL_TEXTURE_2D, mesh.mTextureData->mTOI);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mesh.mTextureData->mWidth, mesh.mTextureData->mHeight, 0, GL_RGB,
				GL_UNSIGNED_BYTE, mesh.mTextureData->mData);
			glGenerateMipmap(GL_TEXTURE_2D);

			mesh.mTextureData->freeRawData();
		}

		unsigned int valuesPerVertex = (mesh.mHasColorData) ? 6 : 3;
		valuesPerVertex += (mesh.mHasTextureData) ? 2 : 0;
		unsigned int numOfFloats = valuesPerVertex * (double)mesh.mVertexCount;

		float* verticies = new float[numOfFloats];

		for (int i = 0; i < mesh.mVertexCount; i++)
		{
			verticies[i * valuesPerVertex] = mesh.getVertexAt(i).getX();
			verticies[i * valuesPerVertex + 1] = mesh.getVertexAt(i).getY();
			verticies[i * valuesPerVertex + 2] = 0.0f;

			if (mesh.mHasColorData)
			{
				verticies[i * valuesPerVertex + 3] = mesh.mColorData[i].getX();
				verticies[i * valuesPerVertex + 4] = mesh.mColorData[i].getY();
				verticies[i * valuesPerVertex + 5] = mesh.mColorData[i].getZ();

				if (mesh.mHasTextureData)
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

		//Setup Element Buffer Object
		glGenBuffers(1, &mesh.mEBO);

		//Bind EBO to VAO (Don't unbind EBO before VAO [VAO remembers all])
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.mEBO);

		//Copy draw order data into bound buffer (EBO)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.mDrawCount, mesh.mDrawOrder, GL_STATIC_DRAW);

		//Linking Vertex Attributes
		if (mesh.mHasTextureData)
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
	else
	{
		if (mesh.mHasTextureData)
			glBindTexture(GL_TEXTURE_2D, mesh.mTextureData->mTOI);

		glBindVertexArray(mesh.mVAO);
	}

	glDrawElements(GL_TRIANGLES, mesh.mDrawCount, GL_UNSIGNED_INT, 0);
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

void GraphicsSystem::spSetFloatAttribute(int index, int dimensions)
{
	glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
}

void GraphicsSystem::setActiveShaderProgram(ShaderProgram& program)
{
	glUseProgram(program.mSPI);
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

void GraphicsSystem::setFloatUniform(ShaderProgram& program, string uniformName, float value)
{
	int uniformLocation = glGetUniformLocation(program.mSPI, uniformName.c_str());

	if (uniformLocation == -1)
		return;

	glUseProgram(program.mSPI);
	glUniform1f(uniformLocation, value);
}

float GraphicsSystem::getTime()
{
	return glfwGetTime();
}