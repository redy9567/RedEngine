#include "SyringeButton.h"
#include "Game.h"

using namespace std;

SyringeButton::SyringeButton(ChickenColor color, string spriteTextureFilepath, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
: UIElement(spriteTextureFilepath, objectKey, location, scale, parent)
{
	mSyringeColor = color;
}

SyringeButton::~SyringeButton()
{

}

void SyringeButton::onClick(Vector2D mousePos)
{
	Game::getInstance()->setMouseToSyringe(mSyringeColor, mousePos);
}