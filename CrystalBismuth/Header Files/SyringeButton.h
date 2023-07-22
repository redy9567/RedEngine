#pragma once
#include "UIElement.h"
#include "Chicken.h"

class SyringeButton : public UIElement
{

public:
	SyringeButton(ChickenColor color, std::string spriteTextureFilepath, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	~SyringeButton();

	void onClick(Vector2D mousePos) override;
	
private:
	SyringeButton() = delete;

	ChickenColor mSyringeColor;
	int mCost;

};