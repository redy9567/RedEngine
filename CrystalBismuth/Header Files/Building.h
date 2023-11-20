#pragma once
#include "GameObject2D.h"

const float RESEARCH_BUILDING_RESEARCH_TIME = 5.0f;
const int RESEARCH_BUILDING_SCIENCE_GAIN = 10;

class Building : public GameObject2D
{
public:
	enum class BuildingType
	{
		Research
	};

	Building(Sprite* sprite, BuildingType type, Vector2D loc = Vector2D::Zero(), GameObject2D* parent = nullptr);
	~Building();

	void update(float deltaTime) override;

private:
	Building() = delete;

	BuildingType mType;
	float mTimer;
};