#include "GameObject2DManager.h"
#include "GameObject2D.h"

using namespace std;

GameObject2DManager* GameObject2DManager::mspInstance = nullptr;

GameObject2DManager* GameObject2DManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new GameObject2DManager();

	return mspInstance;
}

void GameObject2DManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

GameObject2DManager::GameObject2DManager()
{

}

GameObject2DManager::~GameObject2DManager()
{

}

void GameObject2DManager::init()
{

}

void GameObject2DManager::cleanup()
{
	for (unordered_map<string, GameObject2D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		delete it->second;
	}
	mGameObjects.clear();
}

GameObject2D* GameObject2DManager::createAndAddGameObject2D(std::string key, Sprite* sprite, Vector2D loc)
{
	GameObject2D* obj = new GameObject2D(sprite, loc);

	mGameObjects.emplace(key, obj);

	return obj;
}

GameObject2D* GameObject2DManager::createAndAddGameObject2D(std::string key, Animation* anim, Vector2D loc)
{
	GameObject2D* obj = new GameObject2D(anim, loc);

	mGameObjects.emplace(key, obj);

	return obj;
}

void GameObject2DManager::removeAndDeleteGameObject2D(string key)
{
	GameObject2D* obj = mGameObjects.at(key);

	if (obj)
	{
		delete obj;
		mGameObjects.erase(key);
	}
}

GameObject2D* GameObject2DManager::getGameObject2D(string key)
{
	return mGameObjects.at(key);
}