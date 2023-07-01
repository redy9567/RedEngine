#include "SpriteManager.h"
#include "Sprite.h"
#include "GraphicsSystem.h"

using namespace std;

SpriteManager* SpriteManager::mspInstance = nullptr;

SpriteManager* SpriteManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new SpriteManager();

	return mspInstance;
}

void SpriteManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

SpriteManager::SpriteManager()
{

}

SpriteManager::~SpriteManager()
{

}

void SpriteManager::init()
{

}

void SpriteManager::cleanup()
{
	for (unordered_map<string, Sprite*>::iterator it = mSprites.begin(); it != mSprites.end(); it++)
	{
		delete it->second;
	}
	mSprites.clear();
}

Sprite* SpriteManager::createAndAddSprite(string key, Texture2D** texture, Vector2D textureStartLoc, Vector2D size, Vector2D scale)
{
	Sprite* sprite = getSprite(key);
		
	if (!sprite)
	{
		sprite = new Sprite(texture, textureStartLoc, size, scale);

		mSprites.emplace(key, sprite);
	}

	return sprite;
}

void SpriteManager::removeAndDeleteSprite(string key)
{
	Sprite* sprite = mSprites.at(key);

	if (sprite)
	{
		delete sprite;
		mSprites.erase(key);
	}
}