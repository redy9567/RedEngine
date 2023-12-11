#include "Texture2DManager.h"
#include "Texture2D.h"
#include "GraphicsSystem.h"

using namespace std;

Texture2DManager* Texture2DManager::mspInstance = nullptr;

Texture2DManager* Texture2DManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new Texture2DManager();

	return mspInstance;
}

void Texture2DManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

Texture2DManager::Texture2DManager()
{

}

Texture2DManager::~Texture2DManager()
{

}

void Texture2DManager::init()
{

}

void Texture2DManager::cleanup()
{
	for (unordered_map<string, Texture2D*>::iterator it = mTextures.begin(); it != mTextures.end(); it++)
	{
		delete it->second;
	}
	mTextures.clear();
}

Texture2D* Texture2DManager::createAndAddTexture2D(string key, string filepath, bool hasAlpha)
{
	Texture2D* texture = getTexture2D(key);

	if (!texture)
	{
		texture = new Texture2D(filepath, hasAlpha);

		mTextures.emplace(key, texture);
	}

	return texture;
}

void Texture2DManager::removeAndDeleteTexture2D(string key)
{
	Texture2D* texture = mTextures.at(key);

	if (texture)
	{
		delete texture;
		mTextures.erase(key);
	}
}