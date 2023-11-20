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

Chicken* ChickenManager::createAndAddChicken(ChickenColor color, Vector2D location)
{
	Chicken* obj = new Chicken(DEFAULT_TIME_TO_HATCH, DEFAULT_TIME_TO_MATURITY, DEFAULT_TIME_TO_DEATH, color, location);

	mChickens.push_back(obj);

	return obj;
}

Chicken* ChickenManager::createAndAddChicken(ChickenProperties properties, Vector2D location)
{
	Chicken* obj = new Chicken(DEFAULT_TIME_TO_HATCH, DEFAULT_TIME_TO_MATURITY, DEFAULT_TIME_TO_DEATH, properties, location);

	mChickens.push_back(obj);

	return obj;
}

Chicken* ChickenManager::createUnfertileEgg(ChickenProperties properties, Vector2D location)
{
	Chicken* obj = new Chicken(properties, location);

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
	vector<Chicken*> mChickensSnapshot = mChickens;
	
	for (vector<Chicken*>::iterator it = mChickensSnapshot.begin(); it != mChickensSnapshot.end(); it++)
	{
		(*it)->update(deltaTime);
		
		for (vector<Chicken*>::iterator it2 = mChickensSnapshot.end()-1; it2 != it; it2--)
		{
			Vector2D chicken1HalfSize = GraphicsSystem::getInstance()->convertToGridCoordinates((*it)->getSize() / 2.0f);
			Vector2D chicken1Center = (*it)->getLoc() + chicken1HalfSize;

			if (abs((*it)->getLoc().length() - (*it2)->getLoc().length()) < CHICKEN_BREED_RADIUS
				&& checkBreeding(*it, *it2))
			{
				
				breed((*it), (*it2));
				
			}
		}
			
	}
}

void ChickenManager::drawAllChickens()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		Vector3D color = (*it)->mProperties.chickenColor;

		gs->setVec4Uniform("ChickenColor", "uColor", Vector4D(color.getX(), color.getY(), color.getZ(), 1.0f));
		gs->draw(*it);
	}
}

Chicken* ChickenManager::checkChickenHovered(Vector2D mousePos)
{
	for (vector<Chicken*>::iterator it = mChickens.begin(); it != mChickens.end(); it++)
	{
		Vector2D halfSize = GraphicsSystem::getInstance()->convertToGridCoordinates((*it)->getSize()) / 2.0f;
		Vector2D chickenLowerBound = (*it)->getLoc() - halfSize;
		Vector2D chickenUpperBound = (*it)->getLoc() + halfSize;

		if (Vector2D::IsPointWithinBounds(mousePos, chickenLowerBound, chickenUpperBound))
		{
			return (*it);
		}
	}

	return nullptr;
}

bool ChickenManager::checkBreeding(Chicken* chicken1, Chicken* chicken2)
{
	return (chicken1->mState == Chicken::ChickenState::CHICKEN || chicken1->mState == Chicken::ChickenState::CHICKEN_WALKING) &&
		(chicken2->mState == Chicken::ChickenState::CHICKEN || chicken2->mState == Chicken::ChickenState::CHICKEN_WALKING) &&
		chicken1->mBreedingTimer <= 0.0f && chicken2->mBreedingTimer <= 0.0f;
}

void ChickenManager::breed(Chicken* chicken1, Chicken* chicken2)
{
	ChickenProperties ckn1Prop = chicken1->mProperties,
		ckn2Prop = chicken2->mProperties,
		newCknProp;

	float newValue;
	if (abs(ckn1Prop.breedingGeneStrength - ckn2Prop.breedingGeneStrength) <= 3)
	{
		newValue = (ckn1Prop.breedingModifier + ckn2Prop.breedingModifier) / 2.0f;
		newValue = (newValue < 0) ? -round(abs(newValue)) : round(newValue);
	}
	else
		newValue = ckn1Prop.breedingGeneStrength > ckn2Prop.breedingGeneStrength ? ckn1Prop.breedingModifier : ckn2Prop.breedingModifier;

	newCknProp.breedingModifier = newValue;
	newCknProp.breedingGeneStrength = rand() % 10 + 1;

	if (abs(ckn1Prop.eggLayingGeneStrength - ckn2Prop.eggLayingGeneStrength) <= 3)
	{
		newValue = (ckn1Prop.eggLayingModifier + ckn2Prop.eggLayingModifier) / 2.0f;
		newValue = (newValue < 0) ? -round(abs(newValue)) : round(newValue);
	}
	else
		newValue = ckn1Prop.eggLayingGeneStrength > ckn2Prop.eggLayingGeneStrength ? ckn1Prop.eggLayingModifier : ckn2Prop.eggLayingModifier;

	newCknProp.eggLayingModifier = newValue;
	newCknProp.eggLayingGeneStrength = rand() % 10 + 1;

	if (abs(ckn1Prop.hatchGeneStrength - ckn2Prop.hatchGeneStrength) <= 3)
	{
		newValue = (ckn1Prop.hatchModifier + ckn2Prop.hatchModifier) / 2.0f;
		newValue = (newValue < 0) ? -round(abs(newValue)) : round(newValue);
	}
	else
		newValue = ckn1Prop.hatchGeneStrength > ckn2Prop.hatchGeneStrength ? ckn1Prop.hatchModifier : ckn2Prop.hatchModifier;

	newCknProp.hatchModifier = newValue;
	newCknProp.hatchGeneStrength = rand() % 10 + 1;

	if (abs(ckn1Prop.growTimerGeneStrength - ckn2Prop.growTimerGeneStrength) <= 3)
	{
		newValue = (ckn1Prop.growTimerModifier + ckn2Prop.growTimerModifier) / 2.0f;
		newValue = (newValue < 0) ? -round(abs(newValue)) : round(newValue);
	}
	else
		newValue = ckn1Prop.growTimerGeneStrength > ckn2Prop.growTimerGeneStrength ? ckn1Prop.growTimerModifier : ckn2Prop.growTimerModifier;

	newCknProp.growTimerModifier = newValue;
	newCknProp.growTimerGeneStrength = rand() % 10 + 1;

	Vector3D newColor;
	if (abs(ckn1Prop.colorGeneStrength - ckn2Prop.colorGeneStrength) <= 3)
	{
		newColor = (ckn1Prop.chickenColor + ckn2Prop.chickenColor) / 2.0f;
	}
	else
		newColor = ckn1Prop.colorGeneStrength > ckn2Prop.colorGeneStrength ? ckn1Prop.chickenColor : ckn2Prop.chickenColor;

	newCknProp.chickenColor = newColor;
	newCknProp.colorGeneStrength = rand() % 10 + 1;

	Vector2D midpoint = Vector2D::Midpoint(chicken1->getLoc(), chicken2->getLoc());
	chicken1->moveToLocation(midpoint);
	chicken2->moveToLocation(midpoint);

	chicken1->fertilize(newCknProp, 2.0f);
	if (rand() % 10 == 0) //double breeding
	{
		
		chicken2->fertilize(newCknProp, 2.0f);
	}
}