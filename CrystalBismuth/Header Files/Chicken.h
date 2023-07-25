#pragma once
#include "Trackable.h"
#include <string>
#include "GameObject2D.h"
#include "Filepaths.h"
#include "Vector3D.h"

class Sprite;
class Texture2D;
class AnimationData;



const float STARTING_MOVEMENT_TIMER = 3.0f;

const float MAXIMUM_MOVE_TIMER = 3.0f;
const float MINIMUM_MOVE_TIMER = 1.0f;
//const float DEBUG_MOVE_TIMER = 1.0f;

const float MOVEMENT_SPEED = 0.01f;

const float MAXIMUM_MOVE_DISTANCE = 1.0f;
const float MINIMUM_MOVE_DISTANCE = 0.25f;

const float BREEDING_COOLDOWN = 60.0f;
const float EGG_LAYING_TIMER = 10.0f;
const float MOVE_RANGE = MAXIMUM_MOVE_TIMER - MINIMUM_MOVE_TIMER;

const std::string CKN_EGG_KEY = "Egg";
const std::string CKN_HATCHING_KEY = "Hatching";
const std::string CKN_GROWING_KEY = "Growing";
const std::string CKN_CHICK_KEY = "Chick";
const std::string CKN_CHICKEN_KEY = "Chicken";
const std::string CKN_CHICK_WALKING_KEY = "ChickWalking";
const std::string CKN_CHICKEN_WALKING_KEY = "ChickenWalking";
const std::string CKN_CHICKEN_DEATH_KEY = "ChickenDeath";
const std::string CKN_CHICKEN_BLACKHOLE_DEATH_KEY = "BlackHoleDeath";
const std::string CKN_MORPHING_KEY = "Morphing";
const std::string CKN_CHICK_CHAO_GROW_KEY = "ChickChao";
const std::string CKN_CHICK_FF7_HATCH_KEY = "ChickFF7Hatch";
const std::string CKN_FALL_INTO_CIRCLE_KEY = "ChickenDeathCircle";

const int INFERTILE_EGG_SELL_AMOUNT = 10;
const int FERTILE_EGG_SELL_AMOUNT = 20;

enum class ChickenColor
{
	WHITE,
	BLACK,
	BLUE,
	LIGHT_BLUE,
	GREEN,
	YELLOW,
	RED,
	PURPLE
};

struct ChickenProperties
{
	float hatchModifier;
	float breedingModifier;
	float eggLayingModifier;
	float growTimerModifier;

	Vector3D chickenColor;

	short int hatchGeneStrength;
	short int breedingGeneStrength;
	short int eggLayingGeneStrength;
	short int growTimerGeneStrength;

	short int colorGeneStrength;
};

class Chicken : public GameObject2D
{
public:
	friend class ChickenManager;

	void update(float deltaTime);

	void onMouseClick();

	void moveToLocation(Vector2D location);
	void setDebugMode(bool isDebugMode) { mDebugMode = isDebugMode; }

	bool isEgg() { return mState == ChickenState::EGG || mState == ChickenState::INFERTILE_EGG; }

	void paintEgg(ChickenColor color) { if (mState == ChickenState::EGG) updateProperties(color); }

	const static int GetSellAmount(Chicken* ckn) { if (ckn->isEgg()) return ckn->mState == ChickenState::EGG ? FERTILE_EGG_SELL_AMOUNT : INFERTILE_EGG_SELL_AMOUNT; else return 0; }

private:
	enum class ChickenState
	{
		EGG,
		EGG_HATCHING,
		CHICK,
		CHICK_WALKING,
		CHICK_GROWING,
		CHICKEN,
		CHICKEN_WALKING,
		INFERTILE_EGG,
		DEAD
	};

	Chicken(float timeToHatch, float timeToMaturity, float timeToDeath, ChickenColor color, Vector2D location = Vector2D::Zero());
	Chicken(float timeToHatch, float timeToMaturity, float timeToDeath, ChickenProperties properties, Vector2D location = Vector2D::Zero());

	Chicken(ChickenProperties properties, Vector2D location = Vector2D::Zero()); //Infertile Egg
	~Chicken();
	Chicken() = delete;

	void updateAnimation(float deltaTime);
	void updateChickenState();
	void updateImage();
	void move();
	void updatePosition();
	void layEgg();
	void fertilize(ChickenProperties babyProperties, float fertilizeTimer);

	bool isFertilized() { return mIsFertile || mFertileTimer > 0.0f; }
	bool canBreed() { return mBreedingTimer <= 0.0f; }

	void changeState(ChickenState state); 

	void updateProperties(ChickenColor color);

	void loadData();

	static float GetHatchModifier(ChickenColor color);
	static float GetBreedingModifier(ChickenColor color);
	static float GetEggLayingModifier(ChickenColor color);
	static float GetGrowTimerModifier(ChickenColor color);
	static Vector3D GetChickenColor(ChickenColor color);

	ChickenState mState;
	bool mStateChanged;
	bool mDebugMode;
	
	float mTimeToHatch = 0.0f;
	float mTimeToMaturity = 0.0f;
	float mTimeToDeath = 0.0f;
	float mLifeTime = 0.0f;

	float mMoveUpdateTimer = 0.0f;

	float mEggLayingTimer = 0.0f;
	bool mIsFertile = false;
	float mFertileTimer = 0.0f;
	ChickenProperties mFertileProperties;
	float mBreedingTimer = 0.0f;

	bool mIsMoving;
	Vector2D mMoveStart;
	Vector2D mMoveEnd;

	ChickenProperties mProperties;
};