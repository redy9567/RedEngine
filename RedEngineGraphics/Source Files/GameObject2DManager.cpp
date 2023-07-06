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
	for (vector<GameObject2D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		delete *it;
	}
	mGameObjects.clear();
}

GameObject2D* GameObject2DManager::createAndAddGameObject2D(Sprite* sprite, Vector2D loc)
{
	GameObject2D* obj = new GameObject2D(sprite, loc);

	mGameObjects.push_back(obj);

	return obj;
}

GameObject2D* GameObject2DManager::createAndAddGameObject2D(Animation* anim, Vector2D loc)
{
	GameObject2D* obj = new GameObject2D(anim, loc);

	mGameObjects.push_back(obj);

	return obj;
}

void GameObject2DManager::removeAndDeleteGameObject2D(GameObject2D* obj)
{
	for (vector<GameObject2D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		delete *it;
		mGameObjects.erase(it);
	}
}

void GameObject2DManager::removeAndDeleteGameObject2D(int id)
{
	int i = 0;
	for (vector<GameObject2D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		if (i == id)
		{
			delete *it;
			mGameObjects.erase(it);
			break;
		}
	}
}

GameObject2D* GameObject2DManager::getGameObject2D(int id)
{
	return mGameObjects.at(id);
}