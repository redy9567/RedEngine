#include "Texture2D.h"
#include "stb\stb_image.h"
#include <assert.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(string filepath)
{
	mData = stbi_load(filepath.c_str(), &mWidth, &mHeight, &mNRChannels, 0);

	if (!mData)
	{
		std::cout << "Failed to load texture at filepath: " << filepath << std::endl;
	}

	mTOI = -1; //Not yet registered in OpenGL. GraphicsSystem will handle these

	mReferences = 0;
}

Texture2D::~Texture2D()
{
	assert(!mReferences); //Ensure that no object still expects to use this Texture
	if (mData)
		freeRawData();
}

void Texture2D::freeRawData()
{
	stbi_image_free(mData);
	mData = nullptr;
}