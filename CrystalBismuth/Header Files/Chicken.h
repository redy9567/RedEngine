#pragma once
#include "Trackable.h"
#include <string>
#include "GameObject2D.h"
#include "Filepaths.h"

class Sprite;
class Texture2D;
class AnimationData;



class Chicken : public GameObject2D
{
public:
	Chicken(float timeToHatch, float timeToMaturity, Vector2D location = Vector2D::Zero());
	~Chicken();

	void update(float deltaTime);

	void onMouseClick();

	bool isEgg() { return mState == ChickenState::EGG; }

private:
	enum class ChickenState
	{
		EGG,
		CHICK,
		CHICKEN
	};

	ChickenState mState;

	Texture2D* mpEggTexture;
	Sprite* mpEggSprite;

	Texture2D* mpEggHatchingTexture;
	AnimationData* mpEggHatchingAnimationData;
	Animation* mpEggHatchingAnimation;

	Texture2D* mpChickGrowingTexture;
	AnimationData* mpChickGrowingAnimationData;
	Animation* mpChickGrowingAnimation;

	Texture2D* mpChickTexture;
	Sprite* mpChickSprite;

	Texture2D* mpChickenTexture;
	Sprite* mpChickenSprite;
	
	float mTimeToHatch = 0.0f;
	float mTimeToMaturity = 0.0f;
	float mLifeTime = 0.0f;
};