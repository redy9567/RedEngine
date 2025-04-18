#include "GameObject3DManager.h"
#include "GameObject3D.h"
#include "GraphicsSystem.h"

using namespace std;

GameObject3DManager* GameObject3DManager::mspInstance = nullptr;

GameObject3DManager* GameObject3DManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new GameObject3DManager();

	return mspInstance;
}

void GameObject3DManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

GameObject3DManager::GameObject3DManager()
{

}

GameObject3DManager::~GameObject3DManager()
{

}

void GameObject3DManager::init()
{

}

void GameObject3DManager::cleanup()
{
	for (vector<GameObject3D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		delete* it;
	}
	mGameObjects.clear();
}

GameObject3D* GameObject3DManager::createGameObject3D(Mesh3D* mesh, Vector3D loc, Vector3D color, Vector3D scale, Vector3D rot)
{
	return new GameObject3D(mesh, loc, color, scale, rot);
}

GameObject3D* GameObject3DManager::createAndAddGameObject3D(Mesh3D* mesh, Vector3D loc, Vector3D color, Vector3D scale, Vector3D rot)
{
	GameObject3D* obj = new GameObject3D(mesh, loc, color, scale, rot);

	mGameObjects.push_back(obj);

	return obj;
}

void GameObject3DManager::addGameObject3D(GameObject3D* obj)
{
	mGameObjects.push_back(obj);
}

void GameObject3DManager::removeAndDeleteGameObject3D(GameObject3D* obj)
{
	for (vector<GameObject3D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		if (*it == obj)
		{
			delete* it;
			mGameObjects.erase(it);
			break;
		}
	}
}

void GameObject3DManager::removeAndDeleteGameObject3D(int id)
{
	int i = 0;
	for (vector<GameObject3D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		if (i == id)
		{
			delete* it;
			mGameObjects.erase(it);
			break;
		}
	}
}

GameObject3D* GameObject3DManager::getGameObject3D(int id)
{
	return mGameObjects.at(id);
}

void GameObject3DManager::updateAll(float deltaTime)
{
	for (vector<GameObject3D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		(*it)->update(deltaTime);
	}
}

void GameObject3DManager::drawAll()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (vector<GameObject3D*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		gs->draw(*it);
	}
}