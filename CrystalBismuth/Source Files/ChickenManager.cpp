#include "ChickenManager.h"
#include "Chicken.h"
#include "GraphicsSystem.h"

using namespace std;

ChickenManager* ChickenManager::mspInstance = nullptr;

ChickenManager* ChickenManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new ChickenManager();

	return mspInstance;
}

void ChickenManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

ChickenManager::ChickenManager()
{

}

ChickenManager::~ChickenManager()
{

}

void ChickenManager::init()
{

}

void ChickenManager::cleanup()
{
	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		delete *it;
	}
	mChickens.clear();
}

Chicken* ChickenManager::createAndAddChicken(Vector2D location)
{
	Chicken* obj = new Chicken(DEFAULT_TIME_TO_HATCH, DEFAULT_TIME_TO_MATURITY, DEFAULT_TIME_TO_DEATH, location);

	mChickens.push_back(obj);

	return obj;
}

void ChickenManager::removeAndDeleteChicken(int chickenID)
{
	int i = 0;
	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++, i++)
	{
		if (i == chickenID)
		{
			mChickens.erase(it);
			return;
		}
	}
}

void ChickenManager::removeAndDeleteChicken(Chicken* chicken)
{
	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		if (*it == chicken)
		{
			mChickens.erase(it);
			return;
		}
	}
}

Chicken* ChickenManager::getChicken(int chickenID)
{
	return mChickens.at(chickenID);
}

void ChickenManager::update(float deltaTime)
{
	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		(*it)->update(deltaTime);
	}
}

void ChickenManager::drawAllChickens()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		gs->draw(*it);
	}
}

Chicken* ChickenManager::checkChickenClicked(Vector2D mousePos)
{
	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		Vector2D chickenLoc = (*it)->getLoc();
		Vector2D chickenUpperBound = chickenLoc + (*it)->getSize();

		if (Vector2D::IsPointWithinBounds(mousePos, chickenLoc, chickenUpperBound))
		{
			return (*it);
		}
	}

	return nullptr;
}