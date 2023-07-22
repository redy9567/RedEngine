#include "SyringeButton.h"
#include "Game.h"

using namespace std;

SyringeButton::SyringeButton(ChickenColor color, string spriteTextureFilepath, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
: UIElement(spriteTextureFilepath, objectKey, location, scale, parent)
{
	mSyringeColor = color;
	mCost = 100;
}

SyringeButton::~SyringeButton()
{

}

void SyringeButton::onClick(Vector2D mousePos)
{
	if (Game::getInstance()->buySyringe(mSyringeColor, mousePos, mCost))
		mCost *= 2;
	
}