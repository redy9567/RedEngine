#include "Building.h"
#include "GameEvents.h"
#include "EventSystem.h"

Building::Building(Sprite* sprite, BuildingType type, Vector2D loc, GameObject2D* parent)
	: GameObject2D(sprite, loc, parent)
{
	mType = type;
	mTimer = 0.0f;
}

Building::~Building()
{

}

void Building::update(float deltaTime)
{
	mTimer += deltaTime;

	switch (mType)
	{
	case BuildingType::Research:
		if (mTimer >= RESEARCH_BUILDING_RESEARCH_TIME)
		{
			mTimer -= RESEARCH_BUILDING_RESEARCH_TIME;

			ResearchAddEvent event(RESEARCH_BUILDING_SCIENCE_GAIN);
			EventSystem::getInstance()->fireEvent(event);
		}
		break;
	}
}