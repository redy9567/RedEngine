#include "Texture2D.h"
#include "stb\stb_image.h"
#include <assert.h>
#include <iostream>
#include "GraphicsSystem.h"

using namespace std;

Texture2D::Texture2D(string filepath, bool hasAlpha)
{
	stbi_set_flip_vertically_on_load(true);
	mData.push_back(stbi_load(filepath.c_str(), &mWidth, &mHeight, &mNRChannels, 0));

	if (!mData[0])
	{
		std::cout << "Failed to load texture at filepath: " << filepath << std::endl;
	}

	mTOI = -1; //Not yet registered in OpenGL. GraphicsSystem will handle these

	mReferences = 0;

	mHasAlpha = hasAlpha;
}

Texture2D::Texture2D(vector<string> filepaths, bool hasAlpha)
{
	stbi_set_flip_vertically_on_load(false);

	for (int i = 0; i < filepaths.size(); ++i)
	{
		mData.push_back(stbi_load(filepaths[i].c_str(), &mWidth, &mHeight, &mNRChannels, 0));

		if (!mData[i])
		{
			std::cout << "Failed to load texture at filepath: " << filepaths[i] << std::endl;
		}
	}
	

	mTOI = -1; //Not yet registered in OpenGL. GraphicsSystem will handle these

	mReferences = 0;

	mHasAlpha = hasAlpha;
}

Texture2D::~Texture2D()
{
	assert(!mReferences); //Ensure that no object still expects to use this Texture
	if (!mData.empty())
		freeRawData();

	GraphicsSystem::getInstance()->cleanupTexture2D(this);
}

void Texture2D::freeRawData()
{
	for(int i = 0; i < mData.size(); ++i)
		stbi_image_free(mData[i]);

	mData.clear();
}