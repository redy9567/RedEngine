#pragma once
#include "Trackable.h"
#include <string>
#include "GameObject2D.h"

class Sprite;
class Texture2D;
class AnimationData;

const std::string RESOURCES_DIRECTORY = "Resource Files/";
const std::string ANIMATIONS_DIRECTORY = "Animations/";
const std::string EGG_DIRECTORY = "Eggs/";
const std::string CHICKS_DIRECTORY = "Chicks/";
const std::string CHICKENS_DIRECTORY = "Chickens/";

const std::string CHICK_FILENAME = "Chick.png";
const std::string CHICKEN_FILENAME = "Chicken.png";
const std::string EGG_FILENAME = "Chicken Egg.png";
const std::string EGG_HATCHING_FILENAME = "Egg Hatching.png";
const std::string CHICK_GROWING_FILENAME = "Chick Growing.png";

class Chicken : public GameObject2D
{
public:
	enum class ChickenState
	{
			EGG,
			CHICK,
			CHICKEN
	};

	Chicken(float timeToHatch, float timeToMaturity, Vector2D location = Vector2D::Zero());
	~Chicken();

	void update(float deltaTime);

	void onMouseClick();

private:
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