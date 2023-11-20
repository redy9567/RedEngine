#pragma once
#include "UIElement.h"
#include "Chicken.h"
#include "Building.h"

const int SYRINGE_COST = 100;
const int BUILDING_COST = 100;
const int EVOLUTION_COST = 100;

class ShopButton : public UIElement
{

public:
	enum class ShopButtonType
	{
		Syringe,
		Building,
		Evolution
	};

	union ShopButtonData
	{
		ChickenColor c;
		Building::BuildingType b;
	};

	ShopButton(ChickenColor color, std::string spriteTextureFilepath, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	ShopButton(Building::BuildingType buildingType, std::string spriteTextureFilepath, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	ShopButton(std::string spriteTextureFilepath, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr); //Temp Evolution
	~ShopButton();

	void onClick(Vector2D mousePos) override;
	
private:
	ShopButton() = delete;

	ShopButtonType mType;

	ShopButtonData mData;
	int mCost;

};