#include "ShopButton.h"
#include "Game.h"

using namespace std;

ShopButton::ShopButton(ChickenColor color, string spriteTextureFilepath, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
: UIElement(spriteTextureFilepath, objectKey, location, scale, parent)
{
	mType = ShopButtonType::Syringe;

	mData.c = color;
	mCost = SYRINGE_COST;
}

ShopButton::ShopButton(Building::BuildingType buildingType, string spriteTextureFilepath, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
	: UIElement(spriteTextureFilepath, objectKey, location, scale, parent)
{
	mType = ShopButtonType::Building;

	mData.b = buildingType;
	mCost = BUILDING_COST;
}

ShopButton::ShopButton(string spriteTextureFilepath, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
	: UIElement(spriteTextureFilepath, objectKey, location, scale, parent)
{
	mType = ShopButtonType::Evolution;

	mCost = EVOLUTION_COST;
}

ShopButton::~ShopButton()
{

}

void ShopButton::onClick(Vector2D mousePos)
{
	if(mType == ShopButtonType::Syringe)
		if (Game::getInstance()->buySyringe(mData.c, mousePos, mCost))
			mCost *= 2;

	if (mType == ShopButtonType::Building)
		Game::getInstance()->buyBuilding(mData.b, mousePos, mCost);
	
	if (mType == ShopButtonType::Evolution)
		Game::getInstance()->buyEvolution(mousePos, mCost);
}